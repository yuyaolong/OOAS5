//
//  player.cpp
//  8700AS4
//
//  Created by yuyaolong on 15/11/5.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#include "player.h"


Player::Player(const std::string& name):
        TwoWaySprite(name),
        state(MOVELEFT),
        gameOver(false),
        bulletPool(BulletPool::getInstance("Bullet"))
{
    velocity[0] =abs(Gamedata::getInstance().getXmlInt(name+"/speedX"));
    velocity[1] =abs(Gamedata::getInstance().getXmlInt(name+"/speedY"));
}





void Player::draw() const
{
    if (!gameOver) {
         TwoWaySprite::draw();
         bulletPool.draw();
    }
}

void Player::setStatus(PlayerStatus s)
{
    state = s;
    switch (state) {
        case STAND:
            velocityX(0);
            velocityY(0);
            break;
        case MOVERIGHT:
            velocityX(velocity[0]);
            velocityY(0);
            //flipX = 1;
            break;
        case MOVELEFT:
            velocityX(-1*velocity[0]);
            velocityY(0);
            //flipX = -1;
            break;
        case MOVEUP:
            velocityX(0);
            velocityY(-1*velocity[1]);
            break;
        case MOVEDOWN:
            velocityX(0);
            velocityY(velocity[1]);
            break;
        case UPRIGHT:
            velocityX(velocity[0]);
            velocityY(-1*velocity[1]);
            break;
        case UPLEFT:
            velocityX(-velocity[0]);
            velocityY(-1*velocity[1]);
            break;
        case DOWNRIGHT:
            velocityX(velocity[0]);
            velocityY(1*velocity[1]);
            break;
        case DOWNLEFT:
            velocityX(-velocity[0]);
            velocityY(1*velocity[1]);
            break;
        default:
            break;
    }
}


void Player:: update(unsigned int ticks)
{
    if (!gameOver) {
 
        advanceFrame(ticks);
        
        Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
        setPosition(getPosition() + incr);
        
        if ( Y() < 0) {
            velocityY(0);
            Y(0);
            
        }
        if ( Y() > worldHeight-frameHeight) {
            velocityY(0);
            Y(worldHeight-frameHeight);
        }
        
        if ( X() < 0) {
            velocityX(0);
            X(0);
        }
        
        if ( X() > worldWidth-frameWidth) {
            velocityX(0);
            X(worldWidth-frameWidth);
        }
        bulletPool.update(ticks);
    }
}


void Player::advanceFrame(Uint32 ticks)
{
    unsigned int min = 0;
    unsigned int max = 0;
    
    switch (state) {
        case STAND:
            min = Gamedata::getInstance().getXmlInt(getName()+"/STAND/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/STAND/max");
            break;
        case MOVEUP:
            min = Gamedata::getInstance().getXmlInt(getName()+"/UP/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/UP/max");
            break;
        case MOVERIGHT:
            min = Gamedata::getInstance().getXmlInt(getName()+"/RIGHT/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/RIGHT/max");
            break;
        case MOVEDOWN:
            min = Gamedata::getInstance().getXmlInt(getName()+"/DOWN/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/DOWN/max");
            break;
        case MOVELEFT:
            min = Gamedata::getInstance().getXmlInt(getName()+"/LEFT/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/LEFT/max");
            break;
        
        case DOWNLEFT:
            min = Gamedata::getInstance().getXmlInt(getName()+"/LEFTDU/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/LEFTDU/max");
            break;
        case UPLEFT:
            min = Gamedata::getInstance().getXmlInt(getName()+"/LEFTDU/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/LEFTDU/max");
            break;
        case SHOOT:
            min = Gamedata::getInstance().getXmlInt(getName()+"/SHOOT/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/SHOOT/max");
            break;
        case FIRE:
            min = Gamedata::getInstance().getXmlInt(getName()+"/FIRE/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/FIRE/max");
            break;
        
        default:
            min = Gamedata::getInstance().getXmlInt(getName()+"/STAND/min");
            max = Gamedata::getInstance().getXmlInt(getName()+"/STAND/max");
            break;
    }
    
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
        currentFrame++;
        if (currentFrame > max || currentFrame < min) {
            currentFrame = min;
        }
        timeSinceLastFrame = 0;
    }
}

void Player::shoot()
{
    float x = X() + frameWidth;
    float y = Y() + frameHeight/8;
    bulletPool.shoot(Vector2f(x,y), getVelocity());
}


bool Player::hit(const Drawable *obj)
{
    return bulletPool.colliedWith(obj);
}


