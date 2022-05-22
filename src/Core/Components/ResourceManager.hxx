#pragma once

#include "../../include.hxx"

using namespace std;

namespace Core {
    template<typename T>
    class ResourceContainer {
    protected:
        map<string, T *> *resources;
    public:
        ResourceContainer();

        virtual T *get(const string &name);

        virtual T *load(const string &name, const string &path);

        virtual bool has(const string &name);

        virtual ~ResourceContainer();
    };


    struct Texture {
        SDL_Texture *texture;
        SDL_Surface *surface;
        int width, height;
    };

    class FontManager : public ResourceContainer<TTF_Font> {
    public:
        using ResourceContainer<TTF_Font>::ResourceContainer;

        TTF_Font *load(const string &name, const string &path, int size = 11);
    };

    class TextureManager : public ResourceContainer<Texture> {
    public:
        using ResourceContainer<Texture>::ResourceContainer;

        Texture *load(const string &name, const string &path) override;

        SDL_Texture *getRawTexture(const string &name);
    };

    class ResourceManager {
    public:
        ResourceManager();

        FontManager *fonts;
        ResourceContainer<Mix_Music> *music;
        ResourceContainer<Mix_Chunk> *chunks;
        TextureManager *textures;

        ~ResourceManager();

    };
}