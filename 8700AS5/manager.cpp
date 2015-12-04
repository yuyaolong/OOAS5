#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "gamedata.h"
#include "manager.h"
#include "twowaysprite.h"
#include "randomSprite.h"
#include "smartsprite.h"

Manager::~Manager() { 
  std::vector<Drawable*>::const_iterator ptr = sprites.begin();
    std::vector<World*>::const_iterator wPtr = worlds.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
    while (wPtr != worlds.end() ) {
        delete (*wPtr);
        ++wPtr;
    }

}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  viewport( Viewport::getInstance() ),
    worlds(),
  sprites(),
  currentSprite(),
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  eachSpritsNumbe(),
  viewWidth(_gd.getXmlInt("view/width")/2),
  gundam(),
  hud(Hud::getInstance()),
  health("health"),
  playerCollsionInterTime(0),
  godMode(false)
{
     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
         throw string("Unable to initialize SDL: ");
     }
    SDL_WM_SetCaption(title.c_str(), NULL);
    atexit(SDL_Quit);

    
    worlds.push_back(new World("back1"));
    worlds.push_back(new World("back2"));
    worlds.push_back(new World("back3"));
    worlds.push_back(new World("back4"));
    std::sort(worlds.begin(), worlds.end(), FactorCompare());
    
    eachSpritsNumbe.push_back(Gamedata::getInstance().getXmlInt("Enemy/number"));
    eachSpritsNumbe.push_back(Gamedata::getInstance().getXmlInt("Vessel1/number"));
    eachSpritsNumbe.push_back(Gamedata::getInstance().getXmlInt("Explotion/number"));
        eachSpritsNumbe.push_back(1);
    
    gundam = new Player("Gundam");
    gundam -> setStatus(STAND);
    
    
    for (int i = 0; i< eachSpritsNumbe[0]; i++) {
        sprites.push_back( new Smartsprite("Enemy"));
    }
  
    for (int i=0; i< eachSpritsNumbe[1]; i++) {
        sprites.push_back( new RandomSprite("Vessel1") );
    }
    

    for (int i=0; i< eachSpritsNumbe[2]; i++) {
        sprites.push_back( new Scaledsprite("Explotion") );
    }
    
    std::sort(sprites.begin(), sprites.begin()+eachSpritsNumbe[0],SpriteCompareLess());
//    
//    for (int i=0; i<20; i++) {
//        std::cout<<sprites[i]->getScale()<<"\n";
//    }
    sprites.push_back(gundam);
    currentSprite = sprites.begin();
    viewport.setObjectToTrack(*(sprites.end()-1));
}



void Manager::collisionDetec(Uint32 ticks)
{
    playerCollsionInterTime += ticks;
    for (int i=0; i<eachSpritsNumbe[0]; i++) {
        if (sprites[i]->X()<(gundam->X() + viewWidth*2)  && sprites[i]->X()>gundam->X() ) {
            Smartsprite* tmp = dynamic_cast<Smartsprite*>(sprites[i]);
            if (tmp->getReDisplay() && gundam->hit(tmp)) {
                tmp->setReDisplay(false);
                tmp->explode(6);
                //std::cout<<"collision: "<<i<<"\n";
                gundam->addScore();
            }
            
            if (playerCollsionInterTime > 1000) {
                if (tmp->getReDisplay() && tmp->collidedWith(gundam)) {
                    if (!godMode) {
                        health.getHurt();
                        playerCollsionInterTime = 0;
                        if (health.getCurrentLength() == 0) {
                            gundam->explode(0);
                            tmp->setReDisplay(true);
                            health.reset();
                        }
                    }
                }
            }
        }

    }
}


void Manager::cleanHitedSprite()
{
    std::vector<Drawable*>::iterator ptr = sprites.begin();
    for (int i=0; i<eachSpritsNumbe[0]; i++) {
        if ((dynamic_cast<Smartsprite*>(*ptr))->canDelete) {
            //std::cout<<"delete sprite\n";
            delete (*ptr);
            ptr = sprites.erase(ptr);
            eachSpritsNumbe[0] = eachSpritsNumbe[0]-1;
        }
        else
            ptr++;
    }
}



void Manager::showAginHitedSprite()
{
    for (int i =0; i<eachSpritsNumbe[0]; i++) {
        Scaledsprite* tmp = dynamic_cast<Scaledsprite*>(sprites[i]);
        if (tmp->canDelete) {
            tmp->resetVP();
            tmp->canDelete = false;
            tmp->setReDisplay(true);
        }
    }
}



/*
void Manager::switchSprite() {
    static int whichKindSprite = 0;
    whichKindSprite++;
    for (int k=0; k<eachSpritsNumbe[whichKindSprite%(eachSpritsNumbe.size())]; ++k) {
        currentSprite++;
    }
    if ( currentSprite == sprites.end() ) {
        currentSprite = sprites.begin();
    }
    viewport.setObjectToTrack(*currentSprite);
}
*/

void Manager::draw() const {
    
    for (unsigned int i=0; i<worlds.size(); i++) {
            worlds[i]->draw();
        }
    clock.draw();
    std::vector<Drawable*>::const_iterator ptr = sprites.begin();
    while ( ptr != sprites.end() ) {
      (*ptr)->draw();
      ++ptr;
    }
    io.printMessageAt(title, 770, 450);
    if (godMode) {
        io.printMessageAt("God mode on", 200, 40);
    }
    hud.draw();
    health.draw();
    viewport.draw();
    SDL_Flip(screen);
    
}


void Manager::update() {
    showAginHitedSprite();
    clock.update();
    Uint32 ticks = clock.getTicksSinceLastFrame();
    std::vector<Drawable*>::const_iterator ptr = sprites.begin();
    while ( ptr != sprites.end() ) {
        (*ptr)->update(ticks);
        ++ptr;
    }
    if ( makeVideo && frameCount < frameMax ) {
        io.makeFrame(frameCount);
    }
    for (unsigned int i=0; i<worlds.size(); i++) {
        worlds[i]->update();
    }
    hud.update(ticks);
    health.update(ticks);
    viewport.update(); // always update viewport last
    collisionDetec(ticks);
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  clock.start();
  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
        if (event.type ==  SDL_QUIT) { done = true; break; }
       
        if (event.type == SDL_KEYUP) {
            gundam->setStatus(STAND);
        }
        
//        if (event.type == SDL_MOUSEMOTION) {
//            int x_coordinate = 0, y_coordinate=0;
//            SDL_GetMouseState(&x_coordinate, &y_coordinate);
//            std::cout<<x_coordinate<<"   "<<y_coordinate<<"\n";
//        }
        
        if(event.type == SDL_KEYDOWN) {
          
            if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
                done = true;
                break;
            }
//            if ( keystate[SDLK_t] ) {
//                switchSprite();
//            }
            if ( keystate[SDLK_p] ) {
              if ( clock.isPaused() ) clock.unpause();
              else clock.pause();
            }
            if (keystate[SDLK_l]) {
              clock.toggleSloMo();
            }
            if (keystate[SDLK_F4] && !makeVideo) {
              std::cout << "Making video frames" << std::endl;
              makeVideo = true;
            }
              if (keystate[SDLK_F1]) {
                  hud.toggle();
              }
        }
        
        if(keystate[SDLK_a])
        {
            gundam->setStatus(MOVELEFT);
            
        }
        if(keystate[SDLK_d])
        {
            gundam->setStatus(MOVERIGHT);
        }
        if(keystate[SDLK_s])
        {
            gundam->setStatus(MOVEDOWN);
        }
        if(keystate[SDLK_w])
        {
            gundam->setStatus(MOVEUP);
        }
        
        if(keystate[SDLK_SPACE])
        {
            gundam->setStatus(SHOOT);
            gundam->shoot();
            sound[3];
        }
        if(keystate[SDLK_z])
        {
            gundam->setStatus(FIRE);
            if(gundam->laserFire())
            {
                sound[4];
            }
        }
        
        if (keystate[SDLK_r]) {
            resetGame();
        }
        if (keystate[SDLK_g]) {
            godMode = !godMode;
        }
        if (keystate[SDLK_m]) {
            sound.toggleMusic();
        }
        
        if (keystate[SDLK_w] && keystate[SDLK_d]) {
            gundam->setStatus(UPRIGHT);
        }
        if (keystate[SDLK_w] && keystate[SDLK_a]) {
            gundam->setStatus(UPLEFT);
        }
        if (keystate[SDLK_s] && keystate[SDLK_d]) {
            gundam->setStatus(DOWNRIGHT);
        }
        if (keystate[SDLK_s] && keystate[SDLK_a]) {
            gundam->setStatus(DOWNLEFT);
        }
        
        if(keystate[SDLK_a] && keystate[SDLK_d])
        {
            gundam->setStatus(STAND);
        }
        if(keystate[SDLK_w] && keystate[SDLK_s])
        {
            gundam->setStatus(STAND);
        }
    }

    update();
    draw();
    
  }
}

void Manager::resetGame()
{
    std::cout<<"resetGame\n";
    gundam->reset();
    health.reset();

}

