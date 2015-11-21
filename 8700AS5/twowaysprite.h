#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "explodingSprite.h"
class TwoWaySprite : public Drawable {
public:

  TwoWaySprite(const std::string&);
  TwoWaySprite(const std::string&, int Px, int Py, int Vx, int Vy, double scale=1);
  
    
  virtual ~TwoWaySprite();

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  void explode();
    virtual bool collidedWith(const Drawable*) const;
    bool canDelete;
protected:
  ExplodingSprite* explosion;
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  int flipX;
  int flipY;
  
    
  virtual void advanceFrame(Uint32 ticks);
  TwoWaySprite(const TwoWaySprite&);
  TwoWaySprite& operator=(const TwoWaySprite&);
};
#endif
