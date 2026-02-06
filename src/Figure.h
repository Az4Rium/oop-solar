#include "Constants.h"
#include <queue>
#include <variant>

class Figure;

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

class Group : Figure {
public:
  Figure *elem;
  Group(int xn, int yn, int radn);
  ~Group();
  void Insert(Figure *p);
};

class Rect : Group {
  int SizeX;
  int RedGreenState;
  Rect(int xn, int yn, int radn, int SizeX, double Angle);
};

class Circle : Group {
public:
  int rad;
  int redGreenState;
  Circle(int xn, int yn, int radn, double ang);
};

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

class Desktop : Group {
public:
  bool Quit = 0;
  double Speed;
  std::queue<evnt> q;
  Desktop(int xn, int yn, int radn, int coln);
  virtual ~Desktop();
  void getEvent(evnt &e);
  virtual void PutEvent(evnt &e);
  virtual void HandleEvnt(evnt &e);
};

class FreePoint : Point {
public:
  int dx, dy;
  FreePoint(int ax, int ay);
  virtual ~FreePoint();
};
