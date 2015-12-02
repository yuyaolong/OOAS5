//
//  enemy.cpp
//  OOAS3
//
//  Created by yuyaolong on 15/10/18.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#include "scaledsprite.h"
#include "gamedata.h"

Scaledsprite::Scaledsprite(const std::string& name): TwoWaySprite(name,
                                                   Gamedata::getInstance().getXmlInt("world/width")*(rand()*1.0/RAND_MAX),
                                                   Gamedata::getInstance().getXmlInt("world/height")*(rand()*1.0/RAND_MAX),
                                                                  Gamedata::getInstance().getXmlInt(name+"/speedX")*(rand()%2?-1:+1),
                                                   Gamedata::getInstance().getXmlInt(name+"/speedY")*(rand()%2?-1:+1),
                                                                  Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlFloat(name+"/scale/min"),
                                                                                                             Gamedata::getInstance().getXmlFloat(name+"/scale/max"))
                                                   ),
reDisplay(true)
{
    velocityX(velocityX()*getScale());
    velocityY(velocityY()*getScale());
}


void Scaledsprite::draw() const {
    if (explosion) {
        explosion->draw();
        return;
    }
    if (reDisplay) {
        Uint32 x = static_cast<Uint32>(X());
        Uint32 y = static_cast<Uint32>(Y());
        getFrame()->draw(x, y, 0, flipX, flipY, getScale());
    }
}

void Scaledsprite::update(Uint32 ticks) {
    if (explosion) {
        explosion->update(ticks);
        if ( explosion->chunkCount() == 0 ) {
            canDelete = true;
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

void Scaledsprite::setReDisplay(bool reds)
{
    reDisplay = reds;
}

bool Scaledsprite::getReDisplay()const
{
    return reDisplay;
}

void Scaledsprite::resetVP()
{
    this->setPosition(Vector2f( _gd.getXmlInt("world/width")*(rand()*1.0/RAND_MAX),
                               _gd.getXmlInt("world/height")*(rand()*1.0/RAND_MAX))
                      );
    
    this->setVelocity(Vector2f(
                      _gd.getXmlInt(getName()+"/speedX")*(rand()%2?-1:+1),
                      _gd.getXmlInt(getName()+"/speedY")*(rand()%2?-1:+1))
                               );
}


