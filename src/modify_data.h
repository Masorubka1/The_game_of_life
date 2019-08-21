#pragma once 
#include "oxygine-framework.h"
#include <fstream>

using namespace oxygine;
using namespace std;

class Modify_data
{
public:
	vector<vector<int>> samples;
	Modify_data();
	void read();
	void write();
};