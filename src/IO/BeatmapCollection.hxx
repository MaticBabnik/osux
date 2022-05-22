#pragma once
#include "../include.hxx"


namespace IO {

    class BeatmapCollection {
    protected:
        static constexpr auto OSU_EXTENSION = ".osu";
        static constexpr auto BEATMAP_PATH = "beatmaps/";
        static inline std::vector<std::string> *beatmaps = nullptr;
    public:
        static void scan();
        static std::vector<std::string> *getBeatmaps();
    };

}
