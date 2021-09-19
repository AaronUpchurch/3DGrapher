#include "Line.h"
using namespace std;
using namespace sf;
VertexArray Line::getDrawAble() {
	VertexArray temp(sf::LineStrip, 2);
	lines = temp;
	lines[0].position = Vector2f(500 + x0, 500 - y0);
	lines[1].position = Vector2f(500 + x1, 500 - y1);
	lines[0].color = color;
	lines[1].color = color;
	return lines;
}