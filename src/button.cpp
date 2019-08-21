#pragma once
#include "button.h"

using namespace oxygine;

Buttton::Buttton(int w, int h, std::string name)
{
   	setPosition(w, h);
    setResAnim(gameResources.getResAnim("button_before"));
    addEventListener(TouchEvent::OVER, CLOSURE(this, &Buttton::onEvent));
    addEventListener(TouchEvent::OUTX, CLOSURE(this, &Buttton::outEvent));
    addEventListener(TouchEvent::CLICK, CLOSURE(this, &Buttton::outEvent));

    spTextField text = new TextField;
    text->setPosition(this->getSize() / 2);
    addChild(text);

    TextStyle style = TextStyle(gameResources.getResFont("main")).withColor(Color(0, 255, 0, 255)).alignMiddle();
    text->setStyle(style);
    text->setText(name);
	_text = text;
	_name = name;
}
void Buttton::onEvent(Event* ev)
{
   	TextStyle style = TextStyle(gameResources.getResFont("main")).withColor(Color::Black).alignMiddle();
   	setResAnim(gameResources.getResAnim("button_after"));
   	_text->setStyle(style);
    _text->setText(_name);
}
void Buttton::outEvent(Event* ev)
{
   	TextStyle style = TextStyle(gameResources.getResFont("main")).withColor(Color::Black).alignMiddle();
   	setResAnim(gameResources.getResAnim("button_before"));
	style = TextStyle(gameResources.getResFont("main")).withColor(Color(0, 255, 0, 255)).alignMiddle();
   	_text->setStyle(style);
    _text->setText(_name);
}