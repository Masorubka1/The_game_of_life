#pragma once
#include "editor.h"

using namespace oxygine;

spEditor Editor::instance;

Editor::Editor(int size_pict_w, int size_pict_h)
{
	_stage = new Actor;
	_stage->attachTo(_view);
	int size_w = getStage()->getWidth();
	int size_h = getStage()->getHeight();

	_data = new Modify_data;
	_data->read();
	size_h -= size_pict_h;
	for (int i = 0; i < _data->samples.size(); ++i)
	{
		ColorRectSprite * spr = new ColorRectSprite;
		spr->setSize(size_w / w - 1, size_h / h - 1);
		spr->setPosition(size_w - size_w / (w), (size_h / (h)) * i);
		spr->setColor(Color::Yellow);
		spr->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &Editor::get_id));
		spr->setName(to_string(i) + " ");
		spr->attachTo(_stage);
		cout << size_w << " " << size_h << endl;
	}
	size_h += size_pict_h;
	//int scale = size_pict_w / ((size_w / w) * 5);
	spButtton but = new Buttton(size_w - size_pict_w, size_h - size_pict_h, "save&exit");
	but->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Editor::save));
	but->attachTo(_stage);
	for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            ColorRectSprite * spr = new ColorRectSprite;
            spr->setSize((size_w - size_w / (w)) / (w), size_h / (h));
            spr->setColor(Color::Black);
            spr->setPosition((size_w - size_w / (w) - w + 1) / (w) * j, (size_h - h + 1) / (h) * i);
            spr->setName(to_string(j) + " " + to_string(i) + " ");
            spr->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &Editor::change_color));
            if (_data->samples[_cur_id][j + i * w])
            {
                spr->setColor(Color(0, 255, 0, 255));
            }
            _stage->addChild(spr);
            variants.push_back(spr);
        }
    }
}
void Editor::get_id(Event * ev)
{
	string s = ev->target->getName();
	_cur_id = 0;
	int i = 0;
	while (s[i] != ' ')
	{
		_cur_id *= 10;
		_cur_id += s[i] - '0';
		i++;
	}
	for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (_data->samples[_cur_id][j + i * w])
				variants[j + i * w]->setColor(Color(0, 255, 0, 255));
			else
				variants[j + i * w]->setColor(Color::Black);
        }
    }
}
void Editor::change_color(Event * ev)
{
	string s = ev->target->getName();
	int i = 0;
	int x = 0;
	while (s[i] != ' ')
	{
		x *= 10;
		x += s[i] - '0';
		i++;
	}
	i++;
	int y = 0;
	while (s[i] != ' ')
	{
		y *= 10;
		y += s[i] - '0';
		i++;
	}
	Color cl = variants[x + y * w]->getColor();
	if (cl == Color::Black)
		variants[x + y * w]->setColor(Color(0, 255, 0, 255));
	else
		variants[x + y * w]->setColor(Color::Black);
	_data->samples[_cur_id][x + y * w] = 1 - _data->samples[x][y];
}
void Editor::save(Event * ev)
{
	_data->write();
	changeScene(prev_scene);
}