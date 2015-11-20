#include "twowaysprite.h"
#include "gamedata.h"
#include "frameFactory.h"

TwoWaySprite::TwoWaySprite( const std::string& name) :
Drawable(name,
         Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                  Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
         Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                  Gamedata::getInstance().getXmlInt(name+"/speedY"))
         ),
explosion(NULL),
frames( FrameFactory::getInstance().getFrames(name) ),
worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

currentFrame(0),
numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
timeSinceLastFrame( 0 ),
frameWidth(frames[0]->getWidth()),
frameHeight(frames[0]->getHeight()),
flipX(1),
flipY(1)
{
}


TwoWaySprite::TwoWaySprite( const std::string& name, int Px, int Py, int Vx, int Vy, double scale) :
    Drawable(name, Vector2f(Px, Py), Vector2f(Vx, Vy),scale),
  explosion(NULL),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
flipX(1),
flipY(1)
{ }

void TwoWaySprite::draw() const {
    
    if (explosion) {
        explosion->draw();
        return;
    }
    
    Uint32 x = static_cast<Uint32>(X());
    Uint32 y = static_cast<Uint32>(Y());
    frames[currentFrame]->draw(x, y, 0, flipX, flipY);
}

void TwoWaySprite::update(Uint32 ticks) {
    if (explosion) {
        explosion->update(ticks);
        if ( explosion->chunkCount() == 0 ) {
            delete explosion;
            explosion = NULL;
        }
        return;
    }
    
    advanceFrame(ticks);
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);

    if ( Y() < 0) {
        velocityY( abs( velocityY() ) );
      
    }
    if ( Y() > worldHeight-frameHeight) {
        velocityY( -abs( velocityY() ) );
     
    }

    if ( X() < 0) {
        velocityX( abs( velocityX() ) );
        flipX = 1;
    }
  
    if ( X() > worldWidth-frameWidth) {
        velocityX( -abs( velocityX() ) );
        flipX = -1;
    }

}

void TwoWaySprite::explode()
{
    if (explosion) {
        std::cout<<"in have\n";
        return;
    }
    else
    {
        std::cout<<"in null\n";
        Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
        explosion = new ExplodingSprite(sprite);
    }
}

void TwoWaySprite::advanceFrame(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame+1) % numberOfFrames;
        timeSinceLastFrame = 0;
    }
}



