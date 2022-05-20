#include "BeatmapCollection.hxx"

using namespace std;
namespace fs = std::filesystem;

void IO::BeatmapCollection::scan() {
    if (beatmaps == nullptr)
        beatmaps = new vector<string>();
    else beatmaps->clear();

    for (const auto & entry : fs::directory_iterator(BEATMAP_PATH))
    {
        if (fs::is_directory(entry)) continue;
        string path = entry.path();
        if (!path.ends_with(OSU_EXTENSION)) continue;

        beatmaps->push_back(path);
        logher(INFO,"BeatmapCollection") << "Found beatmap: " << path << endlog;
    }

}

vector<string> *IO::BeatmapCollection::getBeatmaps() {
    return nullptr;
}
