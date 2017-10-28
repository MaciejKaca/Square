#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;
class saving_animation
{
public:
	saving_animation();
	void animation();
	void setPosition(Vector2f(position));
	void setSize(int size);
private:
	RectangleShape column;};