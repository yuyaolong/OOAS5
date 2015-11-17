//
//  vessel.c
//  OOAS3
//
//  Created by yuyaolong on 15/10/19.
//  Copyright © 2015 yuyaolong. All rights reserved.
//

#include "randomSprite.h"
#include "gamedata.h"

RandomSprite:: RandomSprite(const std::string& name):Sprite(name,
                                       
                                       Gamedata::getInstance().getXmlInt("world/width")*(rand()*1.0/RAND_MAX),
                                       Gamedata::getInstance().getXmlInt("world/height")*(rand()*1.0/RAND_MAX),
                                       Gamedata::getInstance().getXmlInt(name+"/speedX")*(rand()*1.0/RAND_MAX+0.3),
                                       Gamedata::getInstance().getXmlInt(name+"/speedY")*(rand()*1.0/RAND_MAX+0.2)
                                       ){}


