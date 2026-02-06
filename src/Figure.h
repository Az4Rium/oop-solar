#include "Constants.h"
#include "evnt.h"

class Group;
class Figure {
public:
  int x, y;
  double angle, orbitRadius;
  int Color;
  Figure *Next;
  Group *Owner;

  Figure();
  ~Figure();
  void Draw();
  virtual void Hide();
  virtual void HandleEvent(evnt ev);
  virtual void PutEvent(evnt ev);
  virtual void ClearEvent(evnt ev);
  virtual void SetMyColor(int color);
  virtual void Move();
  virtual void SetAngle(double ang);
  virtual void Message(Figure *addr, int command, int code, Figure *infoptr);
};
