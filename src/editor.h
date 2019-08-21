#pragma once
#include "oxygine-framework.h"
#include "Scene.h"
#include "modify_data.cpp"
#include "button.cpp"
#include "menu.h"
#include <vector>

using namespace oxygine;

DECLARE_SMART(Editor, spEditor);

class Editor : public Scene
{
public:
	static spEditor instance;
	int h = 5, w = 5;

	Editor(int size_pict_w, int size_pict_h);

	friend class Modify_data;
	void save(Event * ev);
	void get_id(Event * ev);
	void change_color(Event * ev);
	void touch(Event * ev);
private:
	std::vector<ColorRectSprite*> variants;
	spActor _stage;
	Modify_data * _data;
	int _cur_id = 0;
};