//
//  player.cpp
//  8700AS4
//
//  Created by yuyaolong on 15/11/5.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#include "player.h"
#include "smartsprite.h"

Player::Player(const std::string& name):
        TwoWaySprite(name),
        state(MOVELEFT),
        gameOver(false),
        bulletPool(BulletPool::getInstance("Bullet")),
        laser(NULL),
        laserFired(false),
        laserTime(_gd.getXmlInt("Laser/showtime")),
        delatTime(0),
        score(0),
        laserCounter(0),
        bonus(_gd.getXmlInt(name+"/bonus")),
        scoreNeed(_gd.getXmlInt(name+"/scoreneed"))

{
    velocity[0] =abs(_gd.getXmlInt(name+"/speedX"));
    velocity[1] =abs(_gd.getXmlInt(name+"/speedY"));
    sound[7];
}



void Player::draw() const
{

    if (!gameOver) {
        
        static unsigned int hisgestScore = 0;
        if (hisgestScore < score) {
            hisgestScore = score;
        }
        
        IOManager::getInstance().printMessageValueAt("Your Score: ", score, 700, 20);
        IOManager::getInstance().printMessageValueAt("Highest Score: ", hisgestScore, 680, 40);
        IOManager::getInstance().printMessageValueAt("Laser counter: ", laserCounter, 680, 60);
        if (explosion) {
            explosion->draw();
            return;
        }
        if (laserFired) {
            laser->draw();
        }
        TwoWaySprite::draw();
         bulletPool.draw();
    }
}



void Player:: update(unsigned int ticks)
{
    if (!gameOver) {
        
        if (explosion) {
            explosion->update(ticks);
            if ( explosion->chunkCount() == 0 ) {
                delete explosion;
                explosion = NULL;
                this->reset();
            }
            return;
        }
 
        if (laserFired) {
            laser->update(ticks);
            delatTime+=ticks;
            state = FIRE;
            if (delatTime > laserTime) {
                laserFired = false;
                delatTime =0;
                delete laser;
                laser = NULL;
            }
        }
        
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


void Player::setStatus(PlayerStatus s)
{
    
    
    state = s;
    if (!laserFired) {
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
            case FIRE:
                velocityX(0);
                velocityY(0);
                break;
            default:
                velocityX(0);
                velocityY(0);
                break;
        }
    }
    else
    {
        velocityX(0);
        velocityY(0);
    }
    
}


void Player::advanceFrame(Uint32 ticks)
{
    unsigned int min = 0;
    unsigned int max = 0;
    
    switch (state) {
        case STAND:
            min = _gd.getXmlInt(getName()+"/STAND/min");
            max = _gd.getXmlInt(getName()+"/STAND/max");
            break;
        case MOVEUP:
            min = _gd.getXmlInt(getName()+"/UP/min");
            max = _gd.getXmlInt(getName()+"/UP/max");
            break;
        case MOVERIGHT:
            min = _gd.getXmlInt(getName()+"/RIGHT/min");
            max = _gd.getXmlInt(getName()+"/RIGHT/max");
            break;
        case MOVEDOWN:
            min = _gd.getXmlInt(getName()+"/DOWN/min");
            max = _gd.getXmlInt(getName()+"/DOWN/max");
            break;
        case MOVELEFT:
            min = _gd.getXmlInt(getName()+"/LEFT/min");
            max = _gd.getXmlInt(getName()+"/LEFT/max");
            break;
        
        case DOWNLEFT:
            min = _gd.getXmlInt(getName()+"/LEFTDU/min");
            max = _gd.getXmlInt(getName()+"/LEFTDU/max");
            break;
        case UPLEFT:
            min = _gd.getXmlInt(getName()+"/LEFTDU/min");
            max = _gd.getXmlInt(getName()+"/LEFTDU/max");
            break;
        case SHOOT:
            min = _gd.getXmlInt(getName()+"/SHOOT/min");
            max = _gd.getXmlInt(getName()+"/SHOOT/max");
            break;
        case FIRE:
            min = _gd.getXmlInt(getName()+"/FIRE/min");
            max = _gd.getXmlInt(getName()+"/FIRE/max");
            break;
        default:
            min = _gd.getXmlInt(getName()+"/STAND/min");
            max = _gd.getXmlInt(getName()+"/STAND/max");
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


bool Player::hit(Drawable *obj)
{
    Smartsprite* tmp = dynamic_cast<Smartsprite*>(obj);
    if (laserFired) {
        bool result = laser->collidedWith(obj);
        if (!result) {
            
            if (tmp) {
                tmp->avoidFlag = true;
                tmp->setAvoid(laser->X(), laser->Y());
            }
        }
        return result;
    }
    else
    {
        tmp->avoidFlag = false;
        
        return bulletPool.collidedWith(obj);
    }
    
    
    
}

bool Player::laserFire()
{
    if ( (!laserFired) && laserCounter>0) {
        laser = new MultiSprite("Laser", X()+frameWidth, Y()+frameHeight*1.0/3, 0, 0);
        laserFired = true;
        laserCounter--;
        
        return true;
        
    }
    return false;

}

void Player::addScore()
{
    score += bonus;
    if (score%scoreNeed == 0) {
        laserCounter++;
        sound[5];
    }
}


void Player::reset()
{
    score = 0;

    
    this->setPosition( Vector2f(_gd.getXmlInt(getName()+"/startLoc/x"),
                                _gd.getXmlInt(getName()+"/startLoc/y"))
                      );
    sound[7];
    
    this->setVelocity(Vector2f(0,0)
                      );
    laserCounter = 0;
    
}



