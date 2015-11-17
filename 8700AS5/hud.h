#ifndef HUD__H
#define HUD__H

#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"
#include "clock.h"
#include "health.h"

class Hud {
public:
  Hud(const std::string & name);
  void draw() const;
  void update(Uint32);
  void toggle();
private:
  const IOManager & io;
  Clock& clock;
  SDL_Surface* screen;
  Vector2f position;
  int length;
  int width;
  float thick;
  int deltaTime;
  const Uint32 color;
  bool bShow;
  int showTime;

  void drawBox() const;
  Hud(const Hud&);
  Hud& operator=(const Hud&);
};

#endif
