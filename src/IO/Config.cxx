#include "Config.hxx"

using namespace std;

bool IO::Config::load() {
    ifstream f;
    f.open("config.sux", ios::binary);

    if (!f.good()) {
        logher(ERROR, "Config") << "Could not read config" << endlog;
        f.close();
        return false;
    }

    { //check file
        char buf[sizeof(CONFIG_HEADER)];
        f.read(buf, sizeof(CONFIG_HEADER));

        if (strcmp(buf, CONFIG_HEADER) != 0) {
            logher(ERROR, "Config") << "Invalid Header" << endlog;
            f.close();
            return false;
        }
    }

    { //try loading the config
        OsuxConfig buf;
        f.read((char*)&buf,sizeof(buf));

        char last;
        f.read(&last,1);

        if (last != CONFIG_LASTBYTE) {
            logher(ERROR, "Config") << "Last byte was not 0" << endlog;
            f.close();
            return false;
        }

        memcpy(&this->cfg,&buf,sizeof(buf));
        f.close();

        if (!f.eof()) {
            logher(WARN, "Config") << "Did not reach EOF. Is file OK?" << endlog;
        }

        return true;

    }
}

IO::OsuxConfig *IO::Config::getConfig() {
    return &this->cfg;
}

bool IO::Config::save() {
    ofstream f;
    f.open("config.sux",ios::binary | ios::trunc);

    f.write(CONFIG_HEADER,CONFIG_HEADER_SIZE);
    f.write((char*)&this->cfg,sizeof(OsuxConfig));
    f<<'\0';
    auto r = f.good();
    f.close();
    return r;
}
