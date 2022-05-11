//
// Created by babnik on 2/17/22.
//

#include "Beatmap.hxx"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <chrono>

#include "Logger.hxx"
#include "../Util/StringSplit.hxx"

using namespace std::chrono;
using namespace std;

namespace IO {

    Beatmap::Beatmap(string path) {
        std::fstream fs;
        fs.open(path, std::fstream::in);
        string currentLine;
        auto st = high_resolution_clock::now();
        while (getline(fs, currentLine)) {
            if (!currentLine.starts_with("[")) continue;
            auto end = currentLine.find(']');
            if (end == string::npos) continue;
            string categoryName = currentLine.substr(1, end - 1);

            if (categoryName == "General") // I wish there was a better way
                parseGeneral(fs);
            else if (categoryName == "Metadata")
                parseMetadata(fs);
            else if (categoryName == "Difficulty")
                parseDifficulty(fs);
            else if (categoryName == "Events")
                parseEvents(fs);
            else if (categoryName == "TimingPoints")
                parseTimingPoints(fs);
            else if (categoryName == "Colours")
                parseColours(fs);
            else if (categoryName == "HitObjects")
                parseHitObjects(fs);
        }

        std::filesystem::path p(path);
        this->audiopath = (p.parent_path() / this->General.AudioFilename).string();

        auto time = duration_cast<microseconds>(high_resolution_clock::now() - st);
        logher(INFO, "Beatmap") << "Parsing done in " << time.count() << " us ... FUCK YOU PPY" <<endlog;
    }

    void Beatmap::parseGeneral(fstream &file) {
        string currentLine;
        while (getline(file, currentLine)) {
            if (currentLine.empty() || currentLine.length() < 2 /* idk */) return;

            string key, value;
            key = currentLine.substr(0, currentLine.find(':'));
            auto start = currentLine.find(':') + 2;
            value = currentLine.substr(start, currentLine.length() - start - 1);

            if (key == "AudioFilename") this->General.AudioFilename = value;
            else if (key == "AudioLeadIn") this->General.AudioLeadIn = stoi(value);
        }
    }

    void Beatmap::parseMetadata(fstream &file) {
        string currentLine;
        while (getline(file, currentLine)) {
            if (currentLine.empty() || currentLine.length() < 2 /* idk */) return;

            string key, value;
            key = currentLine.substr(0, currentLine.find(':'));
            value = currentLine.substr(currentLine.find(':') + 1, currentLine.length() - 1);

            if (key == "Title") this->Metadata.Title = value;
        }
    }

    void Beatmap::parseDifficulty(fstream &file) {
        string currentLine;
        while (getline(file, currentLine)) {
            if (currentLine.empty() || currentLine.length() < 2 /* idk */) return;

            string key, value;
            key = currentLine.substr(0, currentLine.find(':'));
            value = currentLine.substr(currentLine.find(':') + 1, currentLine.length() - 1);

            if (key == "HPDrainRate") this->Difficulty.HPDrainRate = stod(value);
            else if (key == "CircleSize") this->Difficulty.CircleSize = stod(value);
            else if (key == "OverallDifficulty") this->Difficulty.OverallDifficulty = stod(value);
            else if (key == "ApproachRate") this->Difficulty.ApproachRate = stod(value);
            else if (key == "SliderMultiplier") this->Difficulty.SliderMultiplier = stod(value);
            else if (key == "SliderTickRate") this->Difficulty.SliderTickRate = stod(value);
        }
    }

    void Beatmap::parseTimingPoints(fstream &file) {
        this->TimingPoints = vector<TimingPoint>();

        string currentLine;
        while (getline(file, currentLine)) {
            if (currentLine.empty() || currentLine.length() < 2 /* idk */) break;

            TimingPoint tp;

            auto commas = std::count(currentLine.begin(), currentLine.end(), ',');

            if (commas != 7) continue;

            for (int i = 0, j = 0, jn = currentLine.find(','); i < 8; i++) {
                switch (i) {
                    case 0:
                        tp.time = stoi(currentLine.substr(j, jn - j));
                        break;
                    case 1:
                        tp.beatLength = stod(currentLine.substr(j, jn - j));
                        break;
                    case 2:
                        tp.meter = stoi(currentLine.substr(j, jn - j));
                        break;
                    case 3:
                        tp.sampleSet = stoi(currentLine.substr(j, jn - j));
                        break;
                    case 4:
                        tp.sampleIndex = stoi(currentLine.substr(j, jn - j));
                        break;
                    case 5:
                        tp.volume = stoi(currentLine.substr(j, jn - j));
                        break;
                    case 6:
                        tp.uninherited = stoi(currentLine.substr(j, jn - j)) != 0;
                        break;
                    case 7:
                        tp.effects = stoi(currentLine.substr(j, jn - j));
                        break;
                }

                j = jn + 1;
                jn = currentLine.find(',', jn + 1);
                if (jn == string::npos) jn = currentLine.length();
            }
            this->TimingPoints.push_back(tp);
        }
        logher(INFO, "Beatmap") << "Parsed " << this->TimingPoints.size() << " timing points" << endlog;
    }


    void Beatmap::parseHitObjects(fstream &file) {
        string currentLine;
        while (getline(file, currentLine)) {
            if (currentLine.empty() || currentLine.length() < 2 /* idk */) return;

            //split string on commas
            auto split = StringSplit(currentLine, ",");
            HitObject ho{};
            ho.dummy_args = nullptr;
            ho.x = stoi(split[0]);
            ho.y = stoi(split[1]);
            ho.time = stoi(split[2]) + this->General.AudioLeadIn;

            int type = stoi(split[3]);

            if (type & (int) HitObjectType::HitCircle) {
                ho.type = HitObjectType::HitCircle;
                // we don't care about the rest of the data
            } else if (type & (int) HitObjectType::Slider) {
                ho.type = HitObjectType::Slider;
                //parseSliderArgs
                // x,y,time,type,hitSound,curveType|curvePoints,slides,length,edgeSounds,edgeSets,hitSample
                ho.slider_args = new SliderArgs();
                ho.slider_args->type = (SliderType) split[5][0];
                ho.slider_args->repeat = stoi(split[6]);
                ho.slider_args->length = (int)stod(split[7]);

                logher(DEBUG,"Beatmap")<<split[5]<<endlog;
                //parse curve points
                auto curvePoints = StringSplit(split[5], "|");
                ho.slider_args->points = vector<SDL_Point>();

                for (int i = 1; i < curvePoints.size(); i++) {
                    auto curvePointSplit = StringSplit(curvePoints[i], ":");
                    auto op = SDL_Point{stoi(curvePointSplit[0]), stoi(curvePointSplit[1])};
                    ho.slider_args->points.push_back(op);
                }

            } else if (type & (int) HitObjectType::Spinner) {
                ho.type = HitObjectType::Spinner;
                // we don't care about the rest of the data
            }

            this->HitObjects.push_back(ho);
        }
        logher(INFO, "Beatmap") << "Parsed " << this->HitObjects.size() << " hit objects" << endlog;
    }

    void Beatmap::parseColours(fstream &file) {
        asm("nop");
    }

    void Beatmap::parseEvents(fstream &file) {
        asm("nop");
    }

    const string &Beatmap::getAudioPath() const {
        return this->audiopath;
    }
}
