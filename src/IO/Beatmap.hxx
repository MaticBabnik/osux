#pragma once

#include <fstream>
#include "../include.hxx"
#include "../Core/Math2D.hxx"

using namespace std;

//ummmm class that parses beatmaps
//fuck ppy, fuck osu file format v14
#define OSU_WIDTH (16 * 32)
#define OSU_HEIGHT (12 * 32)

namespace IO {
    struct TimingPoint {
        int time;
        double beatLength;
        int meter, sampleSet, sampleIndex, volume;
        bool uninherited; //why????
        int effects;
    };

    enum class HitObjectType : int {
        HitCircle = 1 << 0,
        Slider = 1 << 1,
        Spinner = 1 << 3,
    };

    enum class SliderType : char {
        Linear = 'L',
        Catmull = 'C',
        Bezier = 'B',
        Circle = 'P',
    };

    struct SliderArgs {
        int repeat;
        vector<SDL_Point> points;
    };

    struct HitObject {
        int x, y;
        int time;
        union {
            SliderArgs *slider_args;
            void *dummy_args;
        };
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

        void resolveSlider(HitObject &ho,vector<SDL_Point> &points , SliderType type, double length);
    };
}


