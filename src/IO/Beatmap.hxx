#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <map>

using namespace std;

//ummmm class that parses beatmaps

//fuck ppy, fuck osu file format v14

namespace IO {
    struct TimingPoint {
        int time;
        double beatLength;
        int meter, sampleSet, sampleIndex, volume;
        bool uninherited;
        int effects;
    };

    enum class HitObjectType : int {
        HitCircle = 1 << 0,
        Slider = 1 << 1,
        Spinner = 1 << 3,
    };

    struct HitObject {
        int x, y;
        int time;
        HitObjectType type;
    };

    class Beatmap {
    public:
        explicit Beatmap(string path);

        struct {
            string AudioFilename;
            int AudioLeadIn = 0;
        } General;
        struct {
            string Title;
        } Metadata;
        struct {
            double HPDrainRate;
            double CircleSize;
            double OverallDifficulty;
            double ApproachRate;
            double SliderMultiplier;
            double SliderTickRate;
        } Difficulty;

        vector<TimingPoint> TimingPoints;
        vector<HitObject> HitObjects;

        const string &getAudioPath() const;

    protected:
        string audiopath;

        void parseGeneral(fstream &file);

        void parseMetadata(fstream &file);

        void parseDifficulty(fstream &file);

        void parseEvents(fstream &file);

        void parseTimingPoints(fstream &file);

        void parseColours(fstream &file);

        void parseHitObjects(fstream &file);
    };
}


