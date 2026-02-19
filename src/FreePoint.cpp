#include "FreePoint.h"
#include "Event.h"

void FreePoint::update(float angle) {
  if (pos.x + velocity.x > windowWidth /*- radius*/ || pos.x + velocity.x < 0)
    velocity.x *= -1;
  else
    pos.x += velocity.x;
  if (pos.y + velocity.y > windowHeight /*- radius*/ || pos.y + velocity.y < 0)
    velocity.y *= -1;
  else
    pos.y += velocity.y;

  shape.setPosition(pos);
  message(nullptr, cmCollision, this);
};

void FreePoint::handleEvent(Event &e) {
  std::visit(Overloaded{[&](BroadcastEvent &b) {
                          if (b.code == cmRed) {
                            if (b.addr == this) {
                              velocity.x *= -1;
                              velocity.y *= -1;
                              // pos.x += 5*velocity.x;
                              // pos.y += 5*velocity.y;
                            }
                          }
                        },
                        [&](auto &) {}},
             e);
};
