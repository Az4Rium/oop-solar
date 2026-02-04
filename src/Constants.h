#include <cmath>
#include <cstdint>
#include <sys/types.h>

// Constants

constexpr double Delta = 11.0 * M_PI / 180.0;
constexpr int Max = 8;

constexpr uint16_t cmNothing = 0;
constexpr uint16_t cmMouse = 1;
constexpr uint16_t cmKeyboard = 2;
constexpr uint16_t cmBroadcast = 3;
constexpr uint16_t cmPressPoint = 100;
constexpr uint16_t cmPressCircle = 101;
constexpr uint16_t cmPressRect = 102;
constexpr uint16_t cmRed = 103;
constexpr uint16_t cmGreen = 104;
constexpr uint16_t cmCollision = 105;
