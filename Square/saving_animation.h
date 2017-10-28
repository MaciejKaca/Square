#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;
class saving_animation
{
public:
	void start();
	void setPosition(Vector2f(position));
private:
	RectangleShape column;
};