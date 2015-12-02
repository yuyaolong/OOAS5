//
//  smartsprite.cpp
//  8700AS5
//
//  Created by yuyaolong on 15/12/1.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#include <cmath>
#include "smartsprite.h"

float Smartsprite::safeDistance = 200;


int Smartsprite::getDistance(float &x1, float &y1, float &x2, float &y2) const
{
    return hypot(x1-x2, y1-y2);
}

Smartsprite::Smartsprite(const std::string& name):Scaledsprite(name),
    avoidFlag(false),
    currentMode(NORMAL),
    ex(0),
    ey(0)

{
    
}

void Smartsprite::draw() const
{
    Scaledsprite::draw();
}

void Smartsprite::update(Uint32 ticks)
{
    Scaledsprite::update(ticks);
    if (avoidFlag) {
        float x=X();
        float y=Y();
        float distanceToEnemy = getDistance(x, y, ex, ey);
        
        if  ( currentMode == NORMAL ) {
            if(distanceToEnemy < safeDistance)
            {   currentMode = EVADE;
            }
        }
        else if  ( currentMode == EVADE ) {
            if(distanceToEnemy > safeDistance) currentMode=NORMAL;
            else {
                if ( x < ex ) goLeft();
                if ( x > ex ) goRight();
                if ( y < ey ) goUp();
                if ( y > ey ) goDown();
            }
        }
    }
}


void Smartsprite::goLeft()  {
    if (X() > 0) velocityX( -abs(velocityX()) );
}
void Smartsprite::goRight() { velocityX( fabs(velocityX()) ); }
void Smartsprite::goUp()    { velocityY( -fabs(velocityY()) ); }
void Smartsprite::goDown()  { velocityY( fabs(velocityY()) ); }


