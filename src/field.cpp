#pragma once
#include "field.h"

spField Field::instance;

Field::Field(int size_pict_w, int size_pict_h)
{
	_stage = new Actor;
	_stage->attachTo(_view);
	int size_w = getStage()->getWidth();
	int size_h = getStage()->getHeight();
	_data = new Modify_data;
	_data->read();
	for (int i = 0; i < _data->samples.size(); ++i)
	{
		ColorRectSprite * spr = new ColorRectSprite;
		spr->setSize((size_w / w) * 5, (size_h / h) * 5 - 1);
		spr->setPosition(size_w - size_w / w * 5, (size_h / h) * 5 * i);
		spr->setColor(Color::Yellow);
		spr->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &Field::get_id));
		spr->setName(to_string(i) + " ");
		spr->attachTo(_stage);
		//cout << size_w << " " << size_h << endl;
	}
	double scale = (double)(size_w - w * (size_w / w - 1)) / size_pict_w;
	cout << size_w - size_pict_w * scale << "   " <<  size_h - size_pict_h * scale << endl;
	spButtton but = new Buttton(size_w - size_pict_w * scale, size_h - size_pict_h * scale, "exit");
	but->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Field::exit));
	but->setScale(scale);
	but->attachTo(_stage);
	vector <pair <int, int>> pairs = {{24, 0}, {22, 1}, {24, 1}, {12, 2}, {13, 2}, {20, 2}, {21, 2}, {34, 2}, {35, 2}, {11, 3}, {15, 3}, {20, 3}, {21, 3}, {34, 3}, {35, 3}, {0, 4}, {1, 4}, {10, 4}, {16, 4}, {20, 4}, {21, 4}, {0, 5}, {1, 5}, {10, 5}, {14, 5}, {16, 5}, {17, 5}, {22, 5}, {24, 5}, {10, 6}, {16, 6}, {24, 6}, {11, 7}, {15, 7}, {12, 8}, {13, 8}};
	for (int i = 0; i < pairs.size(); ++i)
	{
		squaress[pairs[i].second][pairs[i].first] = 1;
		squaress[h - pairs[i].second - 1][w - pairs[i].first - 1] = 1;
	}
	/*for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			squaress[i][j] = 1;
		}
	}*/
	int a = size_w / w * 5;
	size_w -= a;
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            ColorRectSprite * spr = new ColorRectSprite;
            spr->setSize(size_w / w - 1, size_h / h - 1);
            spr->setColor(Color::Black);
            spr->setPosition(size_w / w * j, size_h / h * i);
            spr->setName(to_string(j) + " " + to_string(i) + " ");
            spr->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &Field::add_figure));
            if (squaress[i][j])
            {
                spr->setColor(Color(0, 255, 0, 255));
            }
            _stage->addChild(spr);
            situation_on_field[i * w + j] = spr;
        }
    }
}
void Field::exit(Event *)
{
	changeScene(prev_scene);
}
void Field::update()
{
	if (flag)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(25));
		update_actor();
		next_generation();
	}
}
void Field::count_live_squares()
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
            live_squares[i][j] = 0;
			for (int x = -1; x <= 1; ++x)
			{
				for (int y = -1; y <= 1; ++y)
				{
                    if (x == 0 and y == 0);
					else if ((-1 < i + x && i + x < h) && (-1 < j + y && j + y < w))
					{
						live_squares[i][j] += squaress[i + x][j + y];
					}
				}
			}
		}
	}
}
void Field::next_generation()
{
	count_live_squares();
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (live_squares[i][j] < 2 || live_squares[i][j] > 3)
			{
				squaress[i][j] = 0;
			}
			if (live_squares[i][j] == 3)
			{
				squaress[i][j] = 1;
			}
		}
	}
}
void Field::update_actor()
{
	for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            situation_on_field[i * w + j]->setColor(Color::Black);
            if (squaress[i][j])
            {
                situation_on_field[i * w + j]->setColor(Color(0, 255, 0, 255));
            }
        }
    }
}
void Field::get_id(Event * ev)
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
}
void Field::add_figure(Event * ev)
{
	if (_cur_id == -1)
		return;
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
	x -= 2; //centering point
	y -= 2; //because 5 / 2 = 2
	//cout << x + 2 << " " << y + 2 << endl;
	vector <int> help = _data->samples[_cur_id];
	for (int i = 0; i < int(sqrt(help.size())); ++i)
	{
		for (int j = 0; j < int(sqrt(help.size())); ++j)
		{
			if (i + x >= 0 && j + y >= 0 && j + x < w && i + y < h)
			{
				squaress[i + y][j + x] = help[i * int(sqrt(help.size())) + j];
			}
		}
	}
	_cur_id = -1;
}