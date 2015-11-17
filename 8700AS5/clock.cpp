#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  ticks(0),
  totalTicks(0),
  started(false), 
  paused(false), 
  sloMo(false), 

  framesAreCapped(Gamedata::getInstance().getXmlBool("framesAreCapped")), 
  frameCap(Gamedata::getInstance().getXmlInt("frameCap")), 

  sumOfTicks(SDL_GetTicks()),
  pos( Gamedata::getInstance().getXmlInt("clock/locX"),
       Gamedata::getInstance().getXmlInt("clock/locY")),

  seconds(0),
  pauseTicks(0),
  pauseStartTicks(0),
  sumOfPauseTicks(0),
  framCounter(0),
  tickesForFps(0)

  
  {
  start();
}

void Clock::draw() const { 
//  IOManager::getInstance().
//    printMessageValueAt("Seconds: ", getSeconds(), pos[0], pos[1]);
//  IOManager::getInstance().
//    printMessageValueAt("fps: ", getFps(), pos[0], pos[1]+20);
}

void Clock::update() { 
  if (started){
    totalTicks = SDL_GetTicks();
    ticks = totalTicks - sumOfTicks;
    
    if (framesAreCapped)
    {
      double delayTicks = 1000.0/frameCap - ticks;
      delayTicks = delayTicks<0.0 ? 0 : delayTicks;
      SDL_Delay(delayTicks);
      ticks = ticks + delayTicks;
    }
    
    
    sumOfTicks += ticks;

    seconds = (sumOfTicks-sumOfPauseTicks-pauseTicks)/1000;

    if(paused == true)
    {
      pauseTicks = totalTicks - pauseStartTicks;
    }
    else
    {
      pauseTicks = 0;
      framCounter++;
      tickesForFps+=ticks;
    }
    
  }
}



unsigned int Clock::getTicksSinceLastFrame() const {
  if (paused == true)
  {
    return 0;
  }
  else
  {
    if (sloMo == false)
    {
      return ticks;
    }
    else
    {
      return ticks/2;
    }
    
  }
}

void Clock::toggleSloMo() {
  sloMo = ! sloMo;
}

int Clock::getFps() const { 
  static unsigned int lastFramCounter = 0;
  static unsigned int fps = 0;
  static unsigned int lastTickesForFps = 0;

    if (paused) {
        fps = 0;
    }
    else
    {
        if(tickesForFps-lastTickesForFps>200)
        {
            fps = (int)( (framCounter-lastFramCounter) / ( (tickesForFps-lastTickesForFps) *1.0/1000) );
            lastTickesForFps = tickesForFps;
            lastFramCounter = framCounter;
        }
    }

  return fps;
}

void Clock::start() { 
  started = true; 
  paused = false; 
}

void Clock::pause() { 
  paused = true;
  pauseStartTicks = sumOfTicks;
  //std::cout << "pause: Not implemented yet" << std::endl;
}

void Clock::unpause() { 
  paused = false;
  sumOfPauseTicks += pauseTicks;
  //std::cout << "unpause: Not implemented yet" << std::endl;
}

