#include <variant>

// forward declaration
class Figure;

// Event declaration
struct MouseEvent {
  int mx;
  int my;
  int mask;
};

struct KeyboardEvent {
  char key;
  char scan;
};

struct BroadcastEvent {
  Figure *addr;
  Figure *infoPtr;
  int code;
};

using evnt =
    std::variant<std::monostate, MouseEvent, KeyboardEvent, BroadcastEvent>;

struct tEvent {
  int what;
  evnt ev;
};
