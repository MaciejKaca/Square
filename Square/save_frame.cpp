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
	floppy_tex.loadFromFile("resources\\floppy.png");
	floppy.setTexture(floppy_tex);
}

void save_frame::setSize(int size)
{
	cout << floppy_tex.getSize().x;
	frame.setSize(Vector2f(size, size));
	//floppy.setScale(float(1),float(1));
	floppy.setScale(float(float(size)/float(floppy_tex.getSize().x)), float(float(size) / float(floppy_tex.getSize().y)));
}

void save_frame::setPosition(Vector2f position)
{
	frame.setPosition(position);
	floppy.setPosition(position);
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
	window.draw(floppy);
}


