#include "Circle.h"
#include "Comet.h"
#include "Desktop.h"
#include "Event.h"
#include "FreePoint.h"
#include "Group.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include <cstdlib>
#include <queue>
#include <vector>

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
    : Group(pos, orbitRadius) {}

int main() {
  srand(time(nullptr));
  sf::RenderWindow window(sf::VideoMode({1000, 800}), "Solar System",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);

  sf::Clock clock;

  SolarBody *sun = new SolarBody({500, 400}, 0, 40, 0, sf::Color::Yellow);
  SolarBody *mercury =
      new SolarBody({0, 0}, 100, 8, 0.7f, sf::Color(171, 80, 63));
  SolarBody *venus =
      new SolarBody({0, 0}, 130, 10, 0.5f, sf::Color(171, 124, 63));
  SolarBody *earth =
      new SolarBody({0, 0}, 150, 12, 0.4f, sf::Color(63, 171, 110));
  SolarBody *moon =
      new SolarBody({0, 0}, 20, 4, 1.5f, sf::Color(158, 158, 158));
  earth->insert(moon);
  SolarBody *mars = new SolarBody({0, 0}, 190, 10, 0.3f, sf::Color::Red);
  SolarBody *jupter =
      new SolarBody({0, 0}, 320, 25, 0.2f, sf::Color(200, 150, 100));
  for (int i = 0; i < 4; i++) {
    SolarBody *m = new SolarBody({0, 0}, 40 + i * 10, 3, 1.5f - i * 0.3f,
                                 sf::Color::White);
    jupter->insert(m);
  }
  sun->insert(mercury);
  // sun->insert(venus);
  sun->insert(earth);
  sun->insert(mars);
  sun->insert(jupter);

  std::vector<Comet> comets;
  for (int i = 0; i < rand() % 10; i++)
    comets.emplace_back(1000, 800);

  std::vector<sf::CircleShape> stars;
  for (int i = 0; i < std::round(1000 * 800 * 0.005); i++) {
    sf::CircleShape s(0.5f);
    s.setPosition({float(rand() % 1000), float(rand() % 800)});
    s.setFillColor({uint8_t(rand() % 256), uint8_t(rand() % 200),
                    uint8_t(rand() % 256), uint8_t(rand() % 256)});
    stars.push_back(s);
  }
  while (window.isOpen()) {
    while (std::optional<sf::Event> e = window.pollEvent()) {
      if (e->is<sf::Event::Closed>()) {
        window.close();
      }
      //    pushSFMLEvent(*e);
    }

    float dt = clock.restart().asSeconds();

    sun->update(dt);
    for (auto &c : comets)
      c.update(dt, 1000, 800);

    window.clear(sf::Color::Black);
    for (auto &s : stars) {
      window.draw(s);
    }

    sun->draw(window);
    for (auto &c : comets)
      c.draw(window);

    window.display();
  }

  return 0;
}
