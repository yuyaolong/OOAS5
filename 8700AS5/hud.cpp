#include "hud.h"

Hud::Hud(const std::string & name) :
  io(IOManager::getInstance()),
  clock( Clock::getInstance() ),
  screen(io.getScreen()),
  position(Vector2f(Gamedata::getInstance().getXmlInt(name+"/x"), 
  		Gamedata::getInstance().getXmlInt(name+"/y"))), 
  length(Gamedata::getInstance().getXmlInt(name+"/length")), 
  width(Gamedata::getInstance().getXmlInt(name+"/width")), 
  thick(Gamedata::getInstance().getXmlFloat(name+"/thick")),
  deltaTime(0),
  color(SDL_MapRGB(screen->format, 0x00, 0xff, 0x00)),
  bShow(true),
  showTime(Gamedata::getInstance().getXmlInt(name+"/showtime"))
{
}

void Hud::drawBox() const {
  // Two Horizontal lines
  Draw_AALine(screen, position[0], position[1], 
                      position[0]+length, position[1], 
                      thick, color);
  Draw_AALine(screen, position[0], position[1]+width, 
                      position[0]+length, position[1]+width, 
                      thick, color);
  // Two Vertical lines
  Draw_AALine(screen, position[0], position[1], 
                      position[0], position[1]+width, 
                      thick, color);
  Draw_AALine(screen, position[0]+length, position[1], 
                      position[0]+length, position[1]+width, 
                      thick, color);
  // Padding
  Draw_AALine(screen, position[0], position[1]+width/2, 
                      position[0]+length, position[1]+width/2, 
                      width, 0x02, 0x02, 0x02, 0xc8);
}

void Hud::draw() const {
  if(bShow) {
    drawBox();
    io.printMessageValueAt("Seconds: ", Clock::getInstance().getSeconds(), 10, 20);
    io.printMessageValueAt("fps: ", Clock::getInstance().getFps(), 10, 40);
    io.printMessageAt("D - move left", 10, 60);
    io.printMessageAt("A - move right", 10, 80);
    io.printMessageAt("S - move down", 10, 100);
    io.printMessageAt("W - move up", 10, 120);
    io.printMessageAt("l - slow; p - pasue", 10, 140);
    io.printMessageAt("you can press both buttons", 10, 160);
    
    //io.printMessageAt("r - restart game", 10, 140);
    //io.printMessageAt("SPACE - throw acorn", 10, 160);
    io.printMessageAt("Press T to switch sprites", 10, 180);
  } else {
    io.printMessageAt("F1 Help", 10, 20);
  }
}

void Hud::update(Uint32 ticks) {
  deltaTime += ticks;
  if(bShow && deltaTime > showTime) toggle();
}

void Hud::toggle() {
  bShow = !bShow;
  deltaTime = 0;
}
