#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "help.h"
#include "save_frame.h"
using namespace sf;
using namespace std;

save_frame::save_frame()
{
	frame.setFillColor(Color::White);
}

void save_frame::setSize(int size)
{
	frame.setSize(Vector2f(size, size));
}

void save_frame::setPosition(Vector2f position)
{
	frame.setPosition(position);
}

FloatRect save_frame::getGlobalBounds()
{
	return frame.getGlobalBounds();
}

void save_frame::onShape(RenderWindow& window)
{
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if (frame.getGlobalBounds().contains(mouse))
	{
		frame.setFillColor(Color::Red);
	}
	else
	{
		frame.setFillColor(Color::White);
	}
}

void save_frame::display(RenderWindow& window)
{
	window.draw(frame);
}


