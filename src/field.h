#pragma once
#include "oxygine-framework.h"
#include "Scene.cpp"
#include "modify_data.cpp"
#include "button.cpp"
#include <chrono>
#include <thread>
#include <random>
#include <vector>

using namespace oxygine;

DECLARE_SMART(Field, spField);

class Field : public Scene
{
public:
	static spField instance;
	const int w = 90, h = 60;
	int flag = 0;
	
	Field(int size_pict_w, int size_pict_h);

	friend class Modify_data;
	void count_live_squares();
	void next_generation();
	void update();
	void exit(Event *);
	void update_actor();
	void get_id(Event * ev);
	void add_figure(Event * ev);	
protected:
	std::vector<ColorRectSprite*> situation_on_field = std::vector<ColorRectSprite*> (w * h);
	std::vector<std::vector<int>> squaress = std::vector<std::vector<int>> (h, std::vector<int> (w, 0));
	std::vector<std::vector<int>> live_squares = std::vector<std::vector<int>> (h, std::vector<int> (w, 0));
	spActor _stage;
	Modify_data * _data;
	int _cur_id = -1;
};