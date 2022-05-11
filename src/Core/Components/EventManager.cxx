#include "EventManager.hxx"

Core::EventManager::EventManager() {
    eventHandlers = new map<SDL_EventType, vector<Event> *>();
    //register default quit handler
    this->addEventListener(this,SDL_QUIT,0, [] (SDL_Event *e) {
        exit(0);
        return EventControl::HANDLED;
    });
}

Core::EventManager::~EventManager() {
    for (auto p: *eventHandlers) {
        delete p.second;
    }
    delete eventHandlers;
}

int Core::EventManager::clearAllListeners() {
    int c = 0;

    for (auto p: *eventHandlers) {
        auto events = p.second;
        c += events->size();
        events->clear();
    }

    return c;
}

int Core::EventManager::clearAllListeners(void *holder) {
    int c = 0;

    for (auto p: *eventHandlers) {
        auto events = *p.second;

        for (int i = events.size() - 1; i >= 0; i--) {
            if (events[i].holder == holder) {
                events.erase(events.begin() + i);
                c++;
            }
        }
    }

    return c;
}

bool Core::EventManager::clearEventListener(void *holder, SDL_EventType type) {
    if (!eventHandlers->contains(type)) return false;
    auto eventTypeVec = *(*eventHandlers)[type];

    for (int i = eventTypeVec.size() - 1; i >= 0; i--) {
        if (eventTypeVec[i].holder == holder) {
            eventTypeVec.erase(eventTypeVec.begin() + i);
            return true;
        }
    }
    return false;
}

void Core::EventManager::addEventListener(void *holder, SDL_EventType type, int priority,
                                          function<EventControl(SDL_Event *)> handler) {

    vector<Event> *events;
    if (eventHandlers->contains(type)) {
        events = (*eventHandlers)[type];
    } else {
        auto e = new vector<Event>();
        eventHandlers->emplace(type, e);
        events = e;
    }

    //TODO: consider checking if event already exists?
    Event e = {holder, type, priority, handler};

    auto p = events->begin();
    while (true) {
        if (p == events->end()) {
            events->push_back(e);
            return;
        }

        if (p->priority > priority) {
            events->insert(p, e);
            return;
        }
        p++;
    }

}

int Core::EventManager::dispatchEvent(SDL_Event *e) {
    int c = 0;
    auto type = (SDL_EventType) e->type;

    if (!eventHandlers->contains(type)) return 0;
    auto eventTypeVec = *(*eventHandlers)[type];


    for (const auto &ev: eventTypeVec) {
        try {
            auto r = ev.handler(e);
            if (r & HANDLED) c++;
            if (r & STOP_PROPAGATION) return c;
        } catch (...) {
            logher(ERROR, "Events") << "Exception occured when calling event handler" << endlog;
        }
    }
    return c;
}
