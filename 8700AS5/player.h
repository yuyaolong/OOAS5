//
//  player.hpp
//  8700AS4
//
//  Created by yuyaolong on 15/11/5.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "gamedata.h"
#include "twowaysprite.h"
#include "bulletPool.h"
#include "ioManager.h"


class Player: public TwoWaySprite{
public:
    Player(const std::string&);
    virtual ~Player(){};
    
    virtual void draw() const;
    virtual void update(unsigned int ticks);
    
    void setStatus(PlayerStatus s);
    void shoot();
    bool hit(const Drawable* obj);
    void laserFire();
    
private:
    PlayerStatus state;
    bool gameOver;
    float velocity[2];
    BulletPool& bulletPool;
    MultiSprite* laser;
    bool laserFired;
    int laserTime;
    int delatTime;
    
    Player(const Player&);
    Player& operator=(const Player&);
    virtual void advanceFrame(Uint32 ticks);
    
    
};




#endif /* player_hpp */
