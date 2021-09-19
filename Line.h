#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;
class Line
{
public:
	float x0;
	float y0;
	float z0;
	float x1;
	float y1;
	float z1;
	Color color;
	VertexArray lines;
	Line(float x_, float y_, float z_, float x__, float y__, float z__, Color color) {
		this->color = color;
		x0 = x_;
		y0 = y_;
		z0 = z_;
		x1 = x__;
		y1 = y__;
		z1 = z__;
		VertexArray temp(sf::LineStrip, 2);
		lines = temp;
		
		
		lines[0].position = (Vector2f(500 + x0, 500 - y0));
		lines[0].color = color;
		lines[1].position = (Vector2f(500 + x1, 500 - y1));
		lines[1].color = color;
		
	}
	VertexArray getDrawAble();
	
};
