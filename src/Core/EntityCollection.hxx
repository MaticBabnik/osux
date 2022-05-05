#pragma once

#include "Entity.hxx"
#include "../include.hxx"
#include <vector>
#include <list>

//this is a bad idea

namespace Core {

    class EntityCollection : public Entity {
    protected:
        std::list<Entity *> *entities;
        size_t n_ent;
    public:
        EntityCollection();

        virtual void Render() override;

        virtual void AddEntity(Entity *ent);

        virtual void RemoveEntity(Entity *ent);

        virtual void DestroyEntity(Entity *ent);

        ~EntityCollection() override;
    };
}