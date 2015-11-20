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
    static BulletPool& getInstance(const std::string& n);
    
    ~BulletPool() {};
    void draw() const;
    void update(Uint32 ticks);
    
    void shoot(const Vector2f& pos, const Vector2f& vel);
    bool colliedWith(const Drawable* obj) const;
    unsigned int bulletCount() const { return bulletList.size(); }
    unsigned int freeCount() const { return freeList.size(); }
    bool isShooting() const { return bulletList.empty(); }


private:
    BulletPool(const std::string& n);
    BulletPool(const BulletPool&);
    BulletPool& operator=(const BulletPool&);
    std::string name;
    float frameInterval;
    float timeSinceLastFrame;
    mutable std::list<Bullet> bulletList;
    mutable std::list<Bullet> freeList;
    
};



#endif /* bulletPool_hpp */
