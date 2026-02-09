#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <variant>

struct Figure;

struct MouseEvent {
  int x, y;
};

struct KeyEvent {
  sf::Keyboard::Key key;
};

struct BroadcastEvent {
  Figure *addr;
  Figure *info;
  int code;
};

using Event =
    std::variant<std::monostate, MouseEvent, KeyEvent, BroadcastEvent>;
