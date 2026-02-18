#include "Circle.h"
#include "Desktop.h"
#include "Event.h"
#include "FreePoint.h"
#include "Group.h"
#include "Rectangle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <queue>

std::queue<Event> EventQueue;

const int FIG_MAX = 8;

void pushSFMLEvent(const sf::Event &e) {
  if (e.is<sf::Event::MouseButtonPressed>()) {
    const auto &m = e.getIf<sf::Event::MouseButtonPressed>();
    EventQueue.push(MouseEvent{m->position.x, m->position.y});
  } else if (e.is<sf::Event::KeyPressed>()) {
    const auto &k = e.getIf<sf::Event::KeyPressed>();
    EventQueue.push(KeyEvent{k->code});
  }
}

Desktop::Desktop(sf::Vector2f pos, float orbitRadius, int figmax)
    : Group(pos, orbitRadius) {
  // inset Free points
  for (int i = 0; 3 + rand() % 5; i++) {
    // insert(new FreePoint({10.f + rand() % 800, 10.f + rand() % 600}, 0, 0,
    //                      {5.f + rand() % 40, 5.f + rand() % 40}));
  }
  float angle = 0;
  int rr = 150;
  Group *p;
  for (int i = 0; i < figmax; i++) {
    if (i % 2 != 0) {
      p = new CircleFigure({(pos.x + std::round(rr * std::cos(angle))),
                            pos.y + std::round(rr * std::sin(angle))},
                           rr - 25, 50, angle, sf::Color::Green);
      insert(p);
    } else {
      p = new RectangleFigure({pos.x + std::round(rr * std::cos(angle)),
                               pos.y + std::round(rr * std::round(angle))},
                              rr - 25, 50, angle);
      insert(p);
    }
    angle += 2 * M_PI / figmax;
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Test 2",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);

  Desktop desktop({400, 300}, 300, 8);

  sf::Clock clock;

  while (window.isOpen()) {
    while (std::optional<sf::Event> e = window.pollEvent()) {
      if (e->is<sf::Event::Closed>()) {
        window.close();
      }
      pushSFMLEvent(*e);
    }
    float dt = clock.restart().asSeconds();
    desktop.setAngle(dt * desktop.speed);
    desktop.update(dt);

    while (!EventQueue.empty()) {
      Event e = EventQueue.front();
      EventQueue.pop();
      desktop.handleEvent(e);
    }
    if (desktop.quit)
      window.close();
    window.clear(sf::Color::Black);
    desktop.draw(window);
    window.display();
  }
  return 0;
}
