#pragma once
#include "modify_data.h"
#include <iostream>

using namespace oxygine;

Modify_data::Modify_data()
{
	
}
void Modify_data::read()
{
	for (int i = 0; i < 5; ++i)
	{
		ifstream fin(to_string(i) + ".txt");
		if(fin.good())
		{
			string s;
			getline(fin, s);
			vector <int> help;
			for (int j = 0; j < s.size(); ++j)
			{
				help.push_back(s[j] - '0');
			}
			samples.push_back(help);
		}
		else
		{
			ofstream fout(to_string(i) + ".txt");
			vector <int> help;
			for (int j = 0; j < 25; ++j) //zahardkocheno chislo 5 ^ 2
			{
				help.push_back(0);
				fout << 0;
			}
			samples.push_back(help);
			fout.close();
		}
		fin.close();
	}
}
void Modify_data::write()
{
	for (int i = 0; i < samples.size(); ++i)
	{
		ofstream fout(to_string(i) + ".txt", ofstream::trunc);
		for (int k = 0; k < samples[i].size(); ++k)
		{
				fout << samples[i][k];
		}
		fout.close();
	}
}