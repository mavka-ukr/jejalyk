#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#include <string>
#include <cstring>

char *cstr(const std::string &message) {
    char *cstr = new char[message.length() + 1];
    std::strcpy(cstr, message.c_str());
    return cstr;
}

extern "C"
{
EMSCRIPTEN_KEEPALIVE
char *compile(char *code) {
    return code;
}
}