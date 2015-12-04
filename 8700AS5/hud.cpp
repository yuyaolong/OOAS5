#include "hud.h"

Hud& Hud::getInstance()
{
    static Hud instance("hud");
    return instance;
}

Hud::Hud(const std::string & name) :
  io(IOManager::getInstance()),
  clock( Clock::getInstance() ),
  screen(io.getScreen()),
  position(Vector2f(_gd.getXmlInt(name+"/x"),
  		_gd.getXmlInt(name+"/y"))), 
  length(_gd.getXmlInt(name+"/length")), 
  width(_gd.getXmlInt(name+"/width")), 
  thick(_gd.getXmlFloat(name+"/thick")),
  deltaTime(0),
  color(SDL_MapRGB(screen->format, 0x00, 0xff, 0x00)),
  bShow(true),
  showTime(_gd.getXmlInt(name+"/showtime")),
  bulletPool(BulletPool::getInstance("Bullet"))
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
    io.printMessageAt("r - restart game", 10, 180);
    io.printMessageAt("SPACE - throw bullet", 10, 200);
    io.printMessageAt("z - laser(need points)", 10, 220);
    io.printMessageAt("G - god mode", 10, 240);
    io.printMessageAt("Goal is fight for highest score", 10, 260);
    //std::cout<<&bulletpool<<"\n";
    io.printMessageValueAt("Bullets: ", bulletPool.bulletCount(), 140, 20);
    io.printMessageValueAt("FreeList: ", bulletPool.freeCount(), 140, 40);
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
