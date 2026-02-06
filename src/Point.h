#include "Group.h"

class Point : Group {
public:
  double angle;
  virtual void Draw();
  virtual void Hide();
  virtual void Move();
  virtual void HandleEvnt();
  virtual void SetAngle(double du);
  Point(int xn, int xy, int rad, double ang);
};
