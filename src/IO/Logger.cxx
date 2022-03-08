#include "Logger.hxx"

namespace IO {
    void SetupLogging() {
#ifdef _WIN32
        //windows is stupid
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    }
}