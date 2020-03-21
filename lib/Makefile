BUILD_DIR = ./build

DEPS_DIR = ./deps
DEPS_INC_DIR = ${DEPS_DIR}/inc
DEPS_LIB_DIR = ${DEPS_DIR}/lib

APP_NAME = app
APP_BIN_DIR = ./bin
APP_BIN_NAME = executable
APP_BUILD_DIR = ${BUILD_DIR}/${APP_NAME}
APP_DIR = ./${APP_NAME}
APP_INC_DIR = ${APP_DIR}/inc
APP_SRC_DIR = ${APP_DIR}/src

LIB_NAME = lib
LIB_BIN_DIR = ${DEPS_LIB_DIR}
LIB_BIN_NAME = testlib
LIB_BUILD_DIR = ${BUILD_DIR}/${LIB_NAME}
LIB_DIR = ./${LIB_NAME}
LIB_INC_DIR = ${LIB_DIR}/inc
LIB_SRC_DIR = ${LIB_DIR}/src

build_all: lib_build app_build

clean:
	rm -rf ./*.o ${BUILD_DIR}


cmake: clean lib_clean app_clean cmake_compile cmake_link
cmake_compile:
	cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake_link:
	cmake --build build --config Release


lib_build: clean lib_clean lib_compile lib_move_output lib_archive

lib_clean:
	rm -rf ${LIB_BIN_DIR}

lib_compile:
	g++ -c ${LIB_SRC_DIR}/*.cpp -I ${LIB_INC_DIR}

lib_move_output:
	mkdir -p ${LIB_BUILD_DIR} && mv ./*.o ${LIB_BUILD_DIR}/

lib_archive:
	mkdir -p ${LIB_BIN_DIR} && ar rsv ${LIB_BIN_DIR}/${LIB_BIN_NAME}.a ${LIB_BUILD_DIR}/*.o



app_build: clean app_clean app_compile app_move_output app_link

app_clean:
	rm -rf ${APP_BIN_DIR}

app_compile:
	g++ -c ${APP_SRC_DIR}/*.cpp -I ${APP_INC_DIR} -I ${DEPS_INC_DIR}

app_move_output:
	mkdir -p ${APP_BUILD_DIR} && mv ./*.o ${APP_BUILD_DIR}/

app_link:
	mkdir -p ${APP_BIN_DIR} && g++ -o ${APP_BIN_DIR}/${APP_BIN_NAME} ${APP_BUILD_DIR}/*.o ${DEPS_LIB_DIR}/${LIB_BIN_NAME}.a -I ${DEPS_INC_DIR}

run:
	${APP_BIN_DIR}/${APP_BIN_NAME}