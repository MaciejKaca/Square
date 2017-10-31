#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
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