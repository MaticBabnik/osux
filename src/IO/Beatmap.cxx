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
        logher(INFO, "Beatmap") << "Parsing done in " << time.count() << " us ... FUCK YOU PPY" << endlog;
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

            if (key == "HPDrainRate") this->Difficulty.HPDrainRate = stod(value); // DRAAAAAAIN GAAAANG
            // A kej poslusas tega bladeeja
            // On je cist jak pa drained
            // nwm kaj to pomen
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
                ho.slider_args->repeat = stoi(split[6]);

                logher(DEBUG, "Beatmap") << split[5] << endlog;

                auto curvePoints = StringSplit(split[5], "|");
                vector<SDL_Point> p;
                p.push_back({ho.x, ho.y});

                for (int i = 1; i < curvePoints.size(); i++) {
                    auto curvePointSplit = StringSplit(curvePoints[i], ":");
                    auto op = SDL_Point{stoi(curvePointSplit[0]), stoi(curvePointSplit[1])};

                    p.push_back(op);
                }

//                for (const SDL_Point& ppp : p ) {
//                    cout << ppp.x << " " << ppp.y << endl;
//                }

                //this->resolveSlider(ho, p, (SliderType) split[5][0], stod(split[7]));

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

    void Beatmap::resolveSlider(HitObject &ho, vector<SDL_Point> &points, SliderType type, double length) {

        switch (type) {
            case SliderType::Linear: {
                double cLen = 0;
                auto last = points[0];
                ho.slider_args->points.push_back(last);

                auto n_points = points.size();
                for (int i = 1; i < n_points - 1; i++) {
                    cLen += Core::distance(last, points[i]);
                    last = points[i];
                    ho.slider_args->points.push_back(last);
                }

                auto last_segment_wanted_length = length - cLen;

                auto fxp = Core::fix_point(last, points.back(), last_segment_wanted_length);

                ho.slider_args->points.push_back(fxp);

                break;
            }

            case SliderType::Bezier: {

                double total_distance = 0;
                auto last_accepted = points[0];
                ho.slider_args->points.push_back(last_accepted);
                for (double t = 0; t < 1.0; t += 0.005) {
                    auto np = Core::Bezier::bezier_point(points, t);
                    double distance1 = Core::distance(last_accepted, np);
                    if (distance1 > 10) {
                        total_distance += distance1;
                        last_accepted = np;
                        ho.slider_args->points.push_back(last_accepted);
                    }
                }
                auto lengthDelta = length - total_distance;

                if (lengthDelta > 3) {
                    //slider is too short
                    auto pop = ho.slider_args->points.back();
                    ho.slider_args->points.pop_back();

                    ho.slider_args->points.push_back(Core::fix_point(ho.slider_args->points.back(), pop, lengthDelta));
                } else if (lengthDelta < 3) {
                    //while slider is too long
                    while (lengthDelta < 0) {
                        // pop off last point
                        auto pop = ho.slider_args->points.back();
                        ho.slider_args->points.pop_back();
                        // calculate new length delta
                        auto newLengthDelta = lengthDelta + Core::distance(pop, ho.slider_args->points.back());
                        // if the new slider is too short
                        if (newLengthDelta > 0) {
                            //repush the shortened point
                            ho.slider_args->points.push_back(
                                    Core::fix_point(ho.slider_args->points.back(), pop, newLengthDelta));
                            break;
                        } else {
                            //change delta; continue
                            lengthDelta = newLengthDelta;
                        }
                    }
                }

                break;
            }

            case SliderType::Circle: {


                SDL_Point p1 = {ho.x, ho.y},
                        p2 = points[1],
                        p3 = points[2];

                auto circle = Core::get_circle(p1, p2, p3);
                auto orientation = Core::get_orientation(p1, p2, p3);

                if (orientation == 0) {
                    logher(FATAL, "Beatmap") << "BAD" << endlog;
                    exit(-1);
                }


                auto start_angle = Core::angle_between_points(circle.center, p1);
                auto end_angle = start_angle + (length / (circle.r)) * orientation;

//                circle.r =100;
                if (orientation > 0) {
                    for (double a = start_angle; a < end_angle; a += (M_PI / 64)) {
                        ho.slider_args->points.push_back({(int) (circle.center.x - cos(a) * circle.r),
                                                          (int) (circle.center.y + sin(a) * circle.r)});
                    }
                } else {
                    for (double a = start_angle; a > end_angle; a -= (M_PI / 64)) {
                        ho.slider_args->points.push_back({(int) (circle.center.x - cos(a) * circle.r),
                                                          (int) (circle.center.y + sin(a) * circle.r)});
                    }
                }

                SDL_Point end_point = {(int) (circle.center.x - cos(end_angle) * circle.r),
                                       (int) (circle.center.y + sin(end_angle) * circle.r)};

                if (Core::distance(ho.slider_args->points.back(), end_point) > 1) {
                    ho.slider_args->points.push_back(end_point);
                }
                break;
            }

            default:
                logher(FATAL, "Beatmap") << "Unsupported Slider Type (Catmull)" << endlog;
        }
    }
}
