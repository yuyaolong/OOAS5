//
//  bulletPool.cpp
//  8700AS5
//
//  Created by yuyaolong on 15/11/15.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#include "bulletPool.h"
#include "collisionStrategy.h"
#include "gamedata.h"
#include "ioManager.h"
#include "smartsprite.h"


BulletPool& BulletPool::getInstance(const std::string& n)
{
    static BulletPool bulletpool(n);
    return bulletpool;
}


BulletPool::BulletPool(const std::string& n):
                        name(n),
                        frameInterval(_gd.getXmlInt(name+"/frameInterval")),
                        timeSinceLastFrame(0),
                        bulletList(),
                        freeList()

{
    
    
}





bool BulletPool::collidedWith(Drawable *obj) const
{
    static PerPixelCollisionStrategy pcs;
    std::list<Bullet>::iterator ptr = bulletList.begin();
    Smartsprite* tmp = dynamic_cast<Smartsprite*>(obj);
    while (ptr != bulletList.end()) {
        if (tmp) {
            tmp->setAvoid(tmp->X(), (*ptr).Y());
            tmp->avoidFlag = true;
        }
        if (pcs.execute(*ptr, *obj)) {
            freeList.push_back(*ptr);
            ptr = bulletList.erase(ptr);
            tmp->avoidFlag = false;
            return true;
        }
        else
        {
            ptr++;
        }
    }
    
    
    return false;
}


void BulletPool::shoot(const Vector2f& pos, const Vector2f& vel)
{
    if (timeSinceLastFrame > frameInterval) {
        if (freeList.empty()) {
            Bullet b(name,pos[0], pos[1], vel[0]);
            bulletList.push_back(b);
        }
        else
        {
//            Bullet b = freeList.front();
//            freeList.pop_front();
//            b.reset(pos, vel);
//            bulletList.push_back(b);
            freeList.begin()->reset(pos, vel);
            bulletList.push_back(*(freeList.begin()));
            freeList.erase(freeList.begin());
            
        }
        timeSinceLastFrame=0;
    }
}

void BulletPool::draw() const {
    //IOManager::getInstance().printMessageValueAt("Bullets: ", bulletCount(), 700, 20);
    //IOManager::getInstance().printMessageValueAt("FreeList: ", freeCount(), 700, 40);
    std::list<Bullet>::const_iterator ptr = bulletList.begin();
    while(ptr != bulletList.end()) {
        ptr->draw();
        ++ptr;
    }
}

void BulletPool::update(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    std::list<Bullet>::iterator ptr = bulletList.begin();
    while(ptr != bulletList.end()) {
        ptr->update(ticks);
        if(ptr->outViewPort()) {
            freeList.push_back(*ptr);
            ptr = bulletList.erase(ptr);
        }
        else ++ptr;
    }
}






