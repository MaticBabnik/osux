//
// Created by babnik on 2/17/22.
//

#include "Beatmap.hxx"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

#include "Logger.hxx"
#include "../Util/StringSplit.hxx"

using namespace std;

namespace IO {

    Beatmap::Beatmap(string path) {
        std::fstream fs;
        fs.open(path, std::fstream::in);
        string currentLine;
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

            ho.x = stoi(split[0]);
            ho.y = stoi(split[1]);
            ho.time = stoi(split[2]) + this->General.AudioLeadIn;

            int type = stoi(split[3]);

            if (type & (int) HitObjectType::HitCircle)
                ho.type = HitObjectType::HitCircle;
            else if (type & (int) HitObjectType::Slider)
                ho.type = HitObjectType::Slider;
            else if (type & (int) HitObjectType::Spinner)
                ho.type = HitObjectType::Spinner;

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
