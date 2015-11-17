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
                                                                
                                                   )


{
    velocityX(velocityX()*getScale());
    velocityY(velocityY()*getScale());
}


void Scaledsprite::draw() const {
    Uint32 x = static_cast<Uint32>(X());
    Uint32 y = static_cast<Uint32>(Y());
    getFrame()->draw(x, y, 0, flipX, flipY, getScale());
}
      

      
      
