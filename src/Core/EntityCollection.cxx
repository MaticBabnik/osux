#include "EntityCollection.hxx"

namespace Core {
    EntityCollection::EntityCollection() {
        this->entities = new std::list<Entity *>();
        this->n_ent = 0;
    }

    EntityCollection::~EntityCollection() {
        logher(DEBUG,"EntityCollection")<< "Destructor called"<<endlog;
        for (Entity *ent: *this->entities) {
            delete ent;
        }
        delete this->entities;
    }

    void EntityCollection::AddEntity(Entity *ent) {
        this->entities->push_back(ent);
        ent->setParent(this);
        this->n_ent++;
    }


    void EntityCollection::RemoveEntity(Entity *ent) {
        this->entities->erase(
                std::remove(
                        this->entities->begin(),
                        this->entities->end(),
                        ent));

        ent->setParent(nullptr);
        this->n_ent--;

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