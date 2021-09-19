#pragma once
#include <SFML/Graphics.hpp>
#include "Line.h"
#include <iostream>
using namespace std;
using namespace sf;
class Side
{
public:
	bool visible;
	ConvexShape shape;
	Side() {
		visible = false;
		shape.setPointCount(4);

	}
	void update(vector<Line>& cube, int* info) {
		shape.setPoint(0, cube.at(info[0]).lines[info[1]].position);
		shape.setPoint(1, cube.at(info[2]).lines[info[3]].position);
		shape.setPoint(2, cube.at(info[4]).lines[info[5]].position);
		shape.setPoint(3, cube.at(info[6]).lines[info[7]].position);
	}
	

};

