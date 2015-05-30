//This class implements an event queue using a simple array

//==============================================================================
//Include guard
#ifndef __EVENTQUEUE_INCLUDED__
#define __EVENTQUEUE_INCLUDED__
//Included dependencies
#include "Event.h"
#include <stddef.h>
#include <vector>
//==============================================================================
class EventQueue
{
    public:
        EventQueue();
        EventQueue(const size_t len);
        void add(const Event e);
        void reg(); //TODO: implement registration function
    protected:

    private:
        size_t _len;
        unsigned long _idx = 0;
        Event *_elist;
};

#endif
