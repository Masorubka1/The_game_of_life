#pragma once
#include "oxygine-framework.h"
#include "button.cpp"
#include "field.cpp"
#include "editor.cpp"

using namespace oxygine;

DECLARE_SMART(Menu, spMenu)

class Menu : public Scene
{
public:
	static spMenu instance;
    //int h, w, h_position, size_pict_h, size_pict_w;

    Menu(int, int);

    void onEvent(Event * ev);
private:
    spButtton n1, n2, n3;
	spActor _stage;
};