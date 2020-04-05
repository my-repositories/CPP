#include <iostream>
#include <optional>

typedef bool lua_State;

lua_State* lua_state = new lua_State;

bool lua_isinteger(lua_State* state, int idx) { return true; }
int lua_tointeger(lua_State* state, int idx) { return 42; }

bool lua_isstring(lua_State* state, int idx) { return true; }
char* lua_tostring(lua_State* state, int idx) { return (char*)"asd"; }

// стало:
template<typename T>
struct type_name
{
    static auto get_value()
    {
        throw "Invalid type for struct 'type_name'";
    }
};

#define GENERATE_TYPENAME(type, predicate, getter) \
template<>                                         \
struct type_name<type>                             \
{                                                  \
    static auto get_value()                        \
    {                                              \
        std::optional<type> value;                 \
                                                   \
        if (predicate(lua_state, -1))              \
        {                                          \
            value = (type)getter(lua_state, -1);   \
        }                                          \
                                                   \
        return value;                              \
    }                                              \
};                                                 \

GENERATE_TYPENAME(int, lua_isinteger, lua_tointeger);
GENERATE_TYPENAME(char*, lua_isstring, lua_tostring);

template<typename T>
std::optional<T> readValue()
{
    return type_name<T>::get_value();
}

int main()
{
    std::cout << *readValue<int>() << std::endl;

    std::cout << *readValue<char*>() << std::endl;

    std::cout << std::endl;

    delete lua_state;

    return 0;
}
