#include "SolarBody.h"
#include "Group.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>

void SolarBody::update(float dt) {
  angle += orbitSpeed * dt;

  if (owner) {
    pos.x = owner->pos.x + orbitRadius * std::cos(angle);
    pos.y = owner->pos.y + orbitRadius * std::sin(angle);
  }

  shape.setPosition(pos);
  Group::update(dt);
}

void SolarBody::draw(sf::RenderWindow &w) {
  if (owner && orbitRadius > 0) {
    sf::CircleShape orbit(orbitRadius);
    orbit.setOrigin({orbitRadius, orbitRadius});
    orbit.setPosition(owner->pos);
    orbit.setFillColor(sf::Color::Transparent);
    orbit.setOutlineThickness(1);
    orbit.setOutlineColor(sf::Color(80, 80, 80));
    w.draw(orbit);
  }
}
