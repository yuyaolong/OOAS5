#ifndef _WORLD_H
#define _WORLD_H

#include <string>
#include "ioManager.h"
#include "frame.h"
#include "viewport.h"

class World {
public:
  World(const std::string& name);
  // ~World() { ; } // The frame will be deleted by the FrameFactory
  void update();
  void draw() const;
    int getFactor();
private:
  const IOManager& io;
  Frame* frame;
  int factor;
  unsigned frameWidth;
  unsigned worldWidth;
  float viewX;
  float viewY;
  const Viewport & view;
  World(const World&);
  World& operator=(const World&);
};

class FactorCompare {
public:
    bool operator()(World* lhs, World* rhs ) {
        return lhs->getFactor() > rhs->getFactor();
    }
};


#endif

