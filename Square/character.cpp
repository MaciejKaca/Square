#include <SFML\Graphics.hpp>
#include "weapon.h"
#include "character.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <stdio.h>
using namespace sf;
using namespace std;

character::character()
{
	characterShape.setRadius(15);
	characterShape.setOutlineThickness(2);
	characterShape.setFillColor(Color(0, 255, 0));
	characterShape.setOutlineColor(Color(255, 0, 0));
	characterShape.setPosition(20, 20);
}

int character::stringint(string number)
{
	return atoi(number.c_str());
}

void character::up()
{
	if (position().y > 0)
		characterShape.move(0, -1);
};
void character::down()
{
	if (position().y < 720)
		characterShape.move(0, 1);
};
void character::left()
{
	if (position().x > 0)
		characterShape.move(-1, 0);
};
void character::right()
{
	if (position().x < 1280)
		characterShape.move(1, 0);
};

Keyboard::Key key(int keynumber)
{
	return static_cast<Keyboard::Key>(keynumber);
}

void character::read()
{
	string transform;
	ifstream steering;
	steering.open("settings\\steering.dat");
	if (steering.is_open() == 1)
	{
		getline(steering, transform);
		keyup = key(stringint(transform));
		getline(steering, transform);
		keydown = key(stringint(transform));
		getline(steering, transform);
		keyleft = key(stringint(transform));
		getline(steering, transform);
		keyright = key(stringint(transform));;
		getline(steering, transform);
		keysprint = key(stringint(transform));
		steering.close();
	}
	else
		cout << "Error opening steering\n";
}

void character::steering()
{
	if (sf::Keyboard::isKeyPressed(keyleft))
	{
		if (sf::Keyboard::isKeyPressed(keysprint) == 1)
			left();
		left();
	}
	if (sf::Keyboard::isKeyPressed(keyright))
	{
		if (sf::Keyboard::isKeyPressed(keysprint) == 1)
			right();
		right();
	}
	if (sf::Keyboard::isKeyPressed(keyup))
	{
		if (sf::Keyboard::isKeyPressed(keysprint) == 1)
			up();
		up();
	}
	if (sf::Keyboard::isKeyPressed(keydown))
	{
		if (sf::Keyboard::isKeyPressed(keysprint) == 1)
			down();
		down();
	}
}

void character::display(RenderWindow &window)
{
	steering();
	window.draw(characterShape);
}

Vector2f character::position()
{
	return characterShape.getPosition();
}