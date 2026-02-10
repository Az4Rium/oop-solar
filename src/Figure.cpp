#include "Figure.h"
#include "Event.h"
#include <queue>

extern std::queue<Event> EventQueue;

void Figure::message(Figure* addr, int code, Figure* info){
  Event e = BroadcastEvent{addr,info,code};
  if(addr) addr->handleEvent(e);
  else EventQueue.push(e);
}
