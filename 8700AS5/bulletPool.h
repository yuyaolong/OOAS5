//
//  bulletPool.hpp
//  8700AS5
//
//  Created by yuyaolong on 15/11/15.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__

#include <list>
#include "bullet.h"

class BulletPool {
public:
    BulletPool(const std::string &);
    ~BulletPool() {};
    void draw() const;
    void update(Uint32 ticks);
    
    void shoot(const Vector2f& pos, const Vector2f& vel);
    bool colliedWith(const Drawable* obj) const;
    unsigned bulletCount() const { return bulletList.size(); }
    unsigned freeCount() const { return freeList.size(); }
    bool isShooting() const { return bulletList.empty(); }


private:
    std::string name;
    float frameInterval;
    float timeSinceLastFrame;
    mutable std::list<Bullet> bulletList;
    mutable std::list<Bullet> freeList;
    
};



#endif /* bulletPool_hpp */
