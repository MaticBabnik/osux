#include "EntityCollection.hxx"

namespace Core {
    EntityCollection::EntityCollection() {
        this->entities = new std::vector<Entity *>();
    }

    EntityCollection::~EntityCollection() {
        for (Entity *ent: *this->entities) {
            delete ent;
        }
        delete this->entities;
    }

    void EntityCollection::AddEntity(Entity *ent) {
        this->entities->push_back(ent);
        ent->setParent(this);
    }


    void EntityCollection::RemoveEntity(Entity *ent) {
        this->entities->erase(
                std::remove(
                        this->entities->begin(),
                        this->entities->end(),
                        ent));

        ent->setParent(nullptr);
    }

    void EntityCollection::DestroyEntity(Entity *ent) {
        this->RemoveEntity(ent);

        delete ent;
    }

    void EntityCollection::Render() {
        for (Entity *ent: *this->entities) {
            ent->Render();
        }
    };
}