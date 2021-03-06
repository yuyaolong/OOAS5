//
//  enemy.h
//  OOAS3
//
//  Created by yuyaolong on 15/10/18.
//  Copyright © 2015 yuyaolong. All rights reserved.
//

#ifndef __SCALEDSPRITE_H__
#define __SCALEDSPRITE_H__

#include "twowaysprite.h"

class Scaledsprite:public TwoWaySprite{
public:
    Scaledsprite(const std::string& name);
    virtual void draw() const;
    virtual void update(Uint32 ticks);
    void setReDisplay(bool reds);
    bool getReDisplay()const;
    
    void resetVP();
    
private:
    bool reDisplay;
};




#endif 
