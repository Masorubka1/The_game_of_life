#include "oxygine-framework.h"
//include "oxygine-sound.h"
#include <cmath>
#include "menu.cpp"
#include <vector>
#include <iostream>
#include <ctime>

using namespace oxygine;
//it is our resources
//in real project you would have more than one Resources declarations.
//It is important on mobile devices with limited memory and you would load/unload them
//Resources gameResources;

const int size_pict_w = 201;
const int size_pict_h = 59;
int window_w = 0;
int window_h = 0;
int flag = 0;

class Seeder
{
public:
    Seeder()
    {
        srand(time(NULL));
    }
};

Seeder seeder;

void example_preinit() {}
void pause()
{
    flag++;
    //flag += ox::key::wasPressed(SDL_SCANCODE_SPACE);
    flag %= 2;
}

//called from main.cpp

void example_init()
{
    window_w = getStage()->getWidth();
    window_h = getStage()->getHeight();
    //cout << window_w << " " << window_h << endl;
    gameResources.loadXML("res.xml");
    Field::instance = new Field(size_pict_w, size_pict_h);
    Editor::instance = new Editor(size_pict_w, size_pict_h);
    Menu::instance = new Menu(size_pict_w, size_pict_h);
    Menu::instance->show();
    /*SoundSystem::create()->init(16);
    SoundPlayer::initialize();
    splayer.setResources(&resources);
    splayer.setVolume(0.5f);
    splayer.play();*/
}

//called each frame from main.cpp
//void example_update(field &game, std::vector<Sprite> &situation_on_field)
void example_update()
{
    Field::instance->update();
}

//called each frame from main.cpp
void example_destroy()
{
    //free previously loaded resources
    Menu::instance = 0;
    Field::instance = 0;
    Editor::instance = 0;
    gameResources.free();
}