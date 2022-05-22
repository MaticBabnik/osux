#pragma once

#include "../EntityCollection.hxx"
#include "../Components/EventManager.hxx"

namespace Core {
    class Scene : public EntityCollection {
    public:
        EventManager *eventManager;
        Scene();
        virtual void Activate();
        ~Scene() override;
    };
}