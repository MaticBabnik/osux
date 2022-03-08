#include "ResourceManager.hxx"

#include "../Engine.hxx"

namespace Core {
    template<typename T>
    ResourceContainer<T>::ResourceContainer() {
        this->resources = new map<string, T *>;
    }

    template<typename T>
    ResourceContainer<T>::~ResourceContainer() {
        logher(ERROR, "ResourceManager") << "!!! Default destructor for ResourceContainer got called !!!" << endlog;
        for (const auto &p: this->resources) {
            delete p.second;
        }
    }

    template<typename T>
    T *ResourceContainer<T>::get(const string &name) {
        if (resources->find(name) != resources->end())
            return resources->at(name);
        return nullptr;
    }

    template<typename T>
    bool ResourceContainer<T>::has(const string &name) {
        return (resources->find(name) != resources->end());
    }

    template<typename T>
    T *ResourceContainer<T>::load(const string &name, const string &path) {
        throw std::runtime_error("Default ResourceContainer<T>.load called");
    }

    template<>
    Mix_Music *ResourceContainer<Mix_Music>::load(const string &name, const string &path) {
        if (resources->find(name) != resources->end()) {
            return this->resources->at(name);
        }

        auto m = Mix_LoadMUS(path.c_str());
        if (m != nullptr) {
            this->resources->insert(pair(name, m));
        }
        return m;
    }

    template<>
    ResourceContainer<Mix_Music>::~ResourceContainer() {
        for (const auto &p: *this->resources) {
            Mix_FreeMusic(p.second);
        }
        delete this->resources;
    }

    TTF_Font *FontManager::load(const string &name, const string &path, int size) {
        if (resources->find(name) != resources->end()) {
            return this->resources->at(name);
        }

        auto f = TTF_OpenFont(path.c_str(), size);
        if (f != nullptr) {
            this->resources->insert(pair(name, f));
        }
        return f;
    }

    template<>
    ResourceContainer<TTF_Font>::~ResourceContainer() {
        for (const auto &p: *this->resources) {
            TTF_CloseFont(p.second);
        }
        delete this->resources;
    }

    Texture *TextureManager::load(const string &name, const string &path) {
        if (resources->find(name) != resources->end()) {
            return this->resources->at(name);
        }

        auto t = new Texture;

        t->surface = IMG_Load(path.c_str());
        if (t->surface == nullptr) return nullptr;

        t->texture = SDL_CreateTextureFromSurface(Engine::getRenderer(), t->surface);
        if (t->texture == nullptr) {
            SDL_FreeSurface(t->surface);
            return nullptr;
        }

        auto s = SDL_QueryTexture(t->texture, nullptr, nullptr, &t->width, &t->height);
        if (s != 0) {
            SDL_FreeSurface(t->surface);
            SDL_DestroyTexture(t->texture);
            return nullptr;
        }
        this->resources->insert(pair(name, t));
        return t;
    }

    SDL_Texture *TextureManager::getRawTexture(const string &name) {
        return this->get(name)->texture;
    }

    template<>
    ResourceContainer<Texture>::~ResourceContainer() {
        for (const auto &p: *this->resources) {
            SDL_FreeSurface(p.second->surface);
            SDL_DestroyTexture(p.second->texture);
            delete p.second;
        }
        delete this->resources;
    }

    ResourceManager::ResourceManager() {
        this->textures = new TextureManager();
        this->fonts = new FontManager();
        this->music = new ResourceContainer<Mix_Music>();
    }

    ResourceManager::~ResourceManager() {
        delete this->textures;
        delete this->fonts;
        delete this->music;
    }
}