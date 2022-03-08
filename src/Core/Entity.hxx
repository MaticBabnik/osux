#pragma once

namespace Core {

    class Entity {
    protected:
        Entity *parent;
    public:
        virtual void Render() = 0;

        virtual ~Entity() = 0;

        void setParent(Entity *p);
    };

}