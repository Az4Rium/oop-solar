#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <variant>

const int _MAX_POINT_ = 8;



constexpr uint16_t cmNothing = 0;
constexpr uint16_t cmMouse = 1;
constexpr uint16_t cmKeyboard = 2;
constexpr uint16_t cmBroadcast = 3;
constexpr uint16_t cmPressPoint = 100;
constexpr uint16_t cmPressCircle =101;
constexpr uint16_t cmPressRect = 102;
constexpr uint16_t cmRed = 103;
constexpr uint16_t cmGreen = 104;
constexpr uint16_t cmCollision =105;




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

template <class... Ts> struct Overloaded : Ts... {
  using Ts::operator()...;
};

template <class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;
