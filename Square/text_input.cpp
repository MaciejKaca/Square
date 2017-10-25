#include "Text_input.h"
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
text_input::text_input()
{
	retro.loadFromFile("resources\\font.ttf");
	name.setFont(retro);
	name.setFillColor(Color::Black);
	frame.setFillColor(Color::White);
}

void text_input::setString(string text)
{
	name.setString(text);
}

void text_input::add(char text)
{
	if (lenght() > string(name.getString()).size())
	{
		string add;
		add = name.getString() + text;
		name.setString(add);
	}
}

int text_input::lenght()
{
	Text test;
	test.setFont(retro);
	test.setCharacterSize(textsize(frame.getSize().y));
	test.setString("W");
	return frame.getSize().x / test.getGlobalBounds().width;
}

Vector2f text_input::getPosition()
{
	return frame.getPosition();
}
 

void text_input::remove()
{
	if (name.getGlobalBounds().width > 0)
	{
		string remove;
		remove = name.getString();
		remove.erase(remove.begin() + remove.size() - 1);
		name.setString(remove);
	}
}

void text_input::setPosition(Vector2f position) 
{
	test.setFont(retro);
	test.setString("jIi");
	test.setCharacterSize(name.getCharacterSize());
	float y = position.y+((frame.getGlobalBounds().height/2)-(test.getGlobalBounds().height/2));
	frame.setPosition(position);
	test.setPosition(Vector2f(position.x,y));
	while(test.getGlobalBounds().top>y)
		test.setPosition(Vector2f(position.x, --position.y));
	name.setPosition(Vector2f(position.x+(position.x - test.getGlobalBounds().left), position.y));
}

FloatRect text_input::getGlobalBounds()
{
	return frame.getGlobalBounds();
}

Color text_input::getColor()
{
	return frame.getFillColor();
}

void text_input::setColor(Color color)
{
	frame.setFillColor(color);
}

int text_input::textsize(int height)
{
	int charsize = 0;
	Text texter;
	texter.setFont(retro);
	texter.setString("Iji");
	texter.setCharacterSize(charsize);
	while (texter.getGlobalBounds().height <= (80*height)/100)
	{
		texter.setCharacterSize(charsize++);
	}
	return charsize;
}

string text_input::getString()
{
	return name.getString();
}

void text_input::setSize(Vector2f size)
{
	frame.setSize(size);
	name.setCharacterSize(textsize(size.y));
}

void text_input::draw(RenderWindow &window)
{
	name.setPosition(Vector2f(frame.getPosition().x+(frame.getGlobalBounds().width-name.getGlobalBounds().width)/2 + (getPosition().x - test.getGlobalBounds().left), name.getPosition().y));
	window.draw(frame);
	window.draw(name);
}