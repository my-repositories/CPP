# download http://gnuwin32.sourceforge.net/downlinks/make.php
# or here: http://gnuwin32.sourceforge.net/packages/make.htm

target = libqa
generator = "Visual Studio 16 2019"
arch = Win32 # Win32 || Win64
configuration = Release
ideName = clion

sourceDir = .
projectDir = .
binDirName = bin
objDirName = build
objDir = ${objDirName}/${ideName}

build: clean compile link

clean:
	rm -rf ${binDirName} ${objDirName} deps/lib/testlib.*

compile:
	cmake -B ${objDir} -S ${sourceDir} -G ${generator} -A ${arch} ${projectDir}

link:
	cmake --build ${objDir} --target ${target} --config ${configuration} -j 8
