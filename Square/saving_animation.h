#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <thread>
using namespace sf;
using namespace std;
class saving_animation
{
public:
	saving_animation();
	void animation();
	void setPosition(Vector2f(position));
	void setSize(int size);
	void start();
private:
	RectangleShape column;
};