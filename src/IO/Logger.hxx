#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif

#define DEBUG       "\x1B[37mDEBUG ["
#define INFO        "\x1B[96m INFO ["
#define WARN        "\x1B[93m WARN ["
#define ERROR       "\x1B[91mERROR ["
#define FATAL       "\x1B[31mFATAL ["

// log her? i hardly even know her
#define logher(level, unit) std::cout << level << unit << ':' << __FUNCTION__ << "] "
#define endlog "\x1B[0m" << std::endl

namespace IO {
    void SetupLogging();
}