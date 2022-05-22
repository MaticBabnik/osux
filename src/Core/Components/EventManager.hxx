#pragma once

#include "../../include.hxx"
#include <functional>

using namespace std;


namespace Core {
    enum EventControl : short {
        NOT_HANDLED = 0,
        HANDLED = 1,
        STOP_PROPAGATION_BIT = 2,
        CANCEL = 3,
    };

    struct Event {
        void *holder;
        SDL_EventType type;
        int priority;
        function<EventControl(SDL_Event *)> handler;
    };

    class EventManager {
    public:
        int dispatchEvent(SDL_Event *e);

        void
        addEventListener(void *holder, SDL_EventType type, int priority, const function<EventControl(SDL_Event *)> &handler);

        bool clearEventListener(void *holder, SDL_EventType type);

        int clearAllListeners(void *holder);

        int clearAllListeners();

        EventManager();

        ~EventManager();

    protected:
        map<SDL_EventType, vector<Event> *> *eventHandlers;
    };


}