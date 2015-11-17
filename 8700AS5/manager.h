#include <list>
#include <vector>
#include <SDL.h>
#include <algorithm>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "hud.h"
#include "health.h"
#include "scaledsprite.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  //World world;
  Viewport& viewport;

  std::vector<World*> worlds;
  std::vector<Drawable*> sprites;
  std::vector<Drawable*>::iterator currentSprite;

    
  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;
    
  std::vector<int> eachSpritsNumbe;
    
    Player *gundam;
    Hud hud;
    Health health;
    
  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
