#include "Constants.h"
#include "evnt.h"

class Group;
class Figure {
private:
  int x, y;
  double angle, orbitRadius;
  int Color;
  Figure *Next;
  Group *Owner;

public:
  Figure();
  ~Figure();
  void Draw();
};
