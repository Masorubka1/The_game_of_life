#pragma once
#include "oxygine-framework.h"
#include <string>

using namespace oxygine;

Resources gameResources;

DECLARE_SMART(Buttton, spButtton);

class Buttton : public Sprite
{
public:
	spTextField _text;
	std::string _name;

    Buttton(int w, int h, std::string name);
    
    void onEvent(Event* ev);
    void outEvent(Event* ev);
};