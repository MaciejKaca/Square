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
	floppy.setScale(float(float(size)/float(floppy_tex.getSize().x))*0.8, float(float(size) / float(floppy_tex.getSize().y))*0.8);
}

void save_frame::setPosition(Vector2f position)
{
	frame.setPosition(position);
	floppy.setPosition(Vector2f(position.x+(frame.getSize().x-floppy.getGlobalBounds().width)/2, 
	position.y + (frame.getSize().y - floppy.getGlobalBounds().height) / 2));
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
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			frame.setFillColor(Color(80, 0, 0));
			window.draw(frame);
			window.draw(floppy);
			window.display();
			while (Mouse::isButtonPressed(Mouse::Left));
		}
	}
	else
	{
		frame.setFillColor(Color::White);
	}
}

void save_frame::setFillColor(Color color)
{
	frame.setFillColor(color);
}

void save_frame::display(RenderWindow& window)
{
	window.draw(frame);
	window.draw(floppy);
}