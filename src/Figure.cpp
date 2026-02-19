#include "Figure.h"
#include "Event.h"
#include <SFML/System/Vector2.hpp>
#include <queue>

extern std::queue<Event> EventQueue;

void Figure::message(Figure *addr, int code, Figure *info) {
  Event e = BroadcastEvent{addr, info, code};
  if (addr)
    addr->handleEvent(e);
  else
    EventQueue.push(e);
}

// Figure::Figure(sf::Vector2f pos, float orbitRadius) {
//   this->pos = pos;
//   this->orbitRadius = orbitRadius;
//   angle = 0;
//   owner = nullptr;
// }

// void Figure::setColor(int r, int g, int b) { color = sf::Color(r, g, b); }
