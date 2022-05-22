#pragma once
#include "../include.hxx"
/*
 * Config file layout:
 *
 *  0             7
 *  o s u x _ 0 1 \0
 *  <--------
 *    OsuxConfig
 *      struct
 *         ------->
 * \0 EOF
 *
 */


namespace IO {
    constexpr auto CONFIG_HEADER_SIZE = 8;
    constexpr char CONFIG_LASTBYTE = 0;
    constexpr char CONFIG_HEADER[CONFIG_HEADER_SIZE] = "osux_01";

    struct OsuxConfig {
        int hres = 800;
        int vres = 600;

        bool fullscreen = false;

        SDL_Scancode clickOne = SDL_SCANCODE_Z;
        SDL_Scancode clickTwo = SDL_SCANCODE_X;
    };

    class Config {
    protected:
        OsuxConfig cfg;
    public:
        bool load();
        bool save();
        OsuxConfig *getConfig();
    };

}
