//
//  bullet.hpp
//  8700AS5
//
//  Created by yuyaolong on 15/11/15.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#ifndef __BULLET_H__
#define __BULLET_H__
#include "multisprite.h"

class Bullet: public MultiSprite {
public:
    Bullet(const std::string&, int Px, int Py, int Vx);
    
    void reset(const Vector2f &, const Vector2f &);
    bool outViewPort() const;
    
    virtual void update(Uint32 ticks);
private:
    Vector2f V;
    
};

#endif

