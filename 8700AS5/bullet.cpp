//
//  bullet.cpp
//  8700AS5
//
//  Created by yuyaolong on 15/11/15.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#include "bullet.h"
#include "gamedata.h"
#include "viewport.h"
Bullet::Bullet(const std::string& name, int Px, int Py, int Vx):MultiSprite(name, Px, Py, _gd.getXmlInt(name+"/speedX"), _gd.getXmlInt(name+"/speedY")),
    V(Vector2f(_gd.getXmlInt(name+"/speedX"),_gd.getXmlInt(name+"/speedY")))
{
    if (Vx>0) {
        velocityX(velocityX()+Vx);
    }
    
}




void Bullet::reset(const Vector2f & pos, const Vector2f & vel) {
    
    setPosition(pos);
    Vector2f tmpV(V);
    if (vel[0]> 0) {
        tmpV[0] = tmpV[0] +vel[0];
    }
    setVelocity(V);
}


bool Bullet::outViewPort() const
{
    return X()> (Viewport::getInstance().getPosition())[0]+_gd.getXmlInt("view/width");
}


void Bullet::update(Uint32 ticks)
{
    advanceFrame(ticks);
    
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
    
}

