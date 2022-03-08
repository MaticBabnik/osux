#pragma once

#include "Entity.hxx"
#include "../include.hxx"
#include <vector>

//this is a bad idea

namespace Core {

    class EntityCollection : public Entity {
    protected:
        std::vector<Entity *> *entities;
    public:
        EntityCollection();

        virtual void Render();

        virtual void AddEntity(Entity *ent);

        virtual void RemoveEntity(Entity *ent);

        virtual void DestroyEntity(Entity *ent);

        ~EntityCollection() override;
    };
}