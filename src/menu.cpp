#pragma once
#include "menu.h"
#include "button.cpp"

using namespace oxygine;

spMenu Menu::instance;

Menu::Menu(int Size_pict_w, int Size_pict_h)
{
    _stage = new Actor;
    _stage->attachTo(_view);

    int h = getStage()->getHeight();
    int w = getStage()->getWidth();
    int h_position = h / (2 * Size_pict_h);
    //Centering button
    //possible to use chekList() + iter, but i`m lazy)
    n1 = new Buttton((w - Size_pict_w) / 2, (h_position - 1) * Size_pict_h, "Multiplayer");
    n2 = new Buttton((w - Size_pict_w) / 2, h_position * Size_pict_h, "Editor");
    n3 = new Buttton((w - Size_pict_w) / 2, (h_position + 1) * Size_pict_h, "Settings");
    _stage->addChild(n1);
    _stage->addChild(n2);
    _stage->addChild(n3);
    n1->setName("mult");
    n2->setName("edit");
    n3->setName("sett");
    n1->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Menu::onEvent));
    n2->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Menu::onEvent));
    /*addChild(new Buttton((w - size_pict_w) / 2, (h_position - 1) * size_pict_h, "Multiplayer"));
    addChild(new Buttton((w - size_pict_w) / 2, h_position * size_pict_h, "Editor"));
    addChild(new Buttton((w - size_pict_w) / 2, (h_position + 1) * size_pict_h, "Settings"));*/
}

void Menu::onEvent(Event * ev)
{
    string id = ev->currentTarget->getName();
    if (id == "mult")
    {
        changeScene(Field::instance);
        Field::instance->flag = 1;
        Field::instance->update_actor();
    }
    else if (id == "edit")
    {
        changeScene(Editor::instance);
    }
}