#include "../include/EventQueue.h"

EventQueue::EventQueue()
{
    EventQueue(50);
}

EventQueue::EventQueue(const size_t len)
{
    _len = len;
    _elist = new Event[len];
}

//Adds an event to the Queue
void EventQueue::add(const Event e)
{
    _elist[_idx] = e;
    _idx = ((_idx+1)%_len);
}
