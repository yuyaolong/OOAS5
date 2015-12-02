//
//  smartsprite.hpp
//  8700AS5
//
//  Created by yuyaolong on 15/12/1.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#ifndef __SMARTSPRITE_H__
#define __SMARTSPRITE_H__

#include "scaledsprite.h"

enum MODE{
    NORMAL=0,
    EVADE
};

class Smartsprite: public Scaledsprite{
public:
    Smartsprite(const std::string& name);
    virtual void draw() const;
    virtual void update(Uint32 ticks);


    int getDistance(float &x1, float &y1, float &x2, float &y2) const;
    
    void setAvoid(float x1, float y1) {ex = x1; ey = y1; }
    bool avoidFlag;
    
private:

    Smartsprite(const Smartsprite&);
    Smartsprite& operator=(const Smartsprite&);
    static float safeDistance;
    MODE currentMode;
    float ex;
    float ey;
    
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
    

};



#endif /* smartsprite_h */
