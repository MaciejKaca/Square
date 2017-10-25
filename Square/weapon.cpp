#include <SFML\Graphics.hpp>
#include "weapon.h"
#include <math.h>
#include <iostream>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#define PI 3.14159265
using namespace sf;
using namespace std;
weapon::weapon()
{
	weaponShape.setSize(Vector2f(40, 8));
	weaponShape.setFillColor(Color(139, 69, 19));
	weaponBarrel.setSize(Vector2f(20, 4));
	weaponBarrel.setFillColor(Color(139, 69, 19));
	weaponChamber.setSize(Vector2f(3, 5));
	weaponChamber.setFillColor(Color(128, 128, 128));
	weaponChamber.setOrigin(-30 , -(weaponShape.getSize().y));
	FireCountMove = 0;
	FireFinished = true;
	MousePressed = false;
	autofire = false;
	if (!font.loadFromFile("resources\\font.ttf"))
		std::cout << "error loading font on weapon";
	mode.setFont(font);
	mode.setFillColor(sf::Color::Black);
	mode.setPosition(Vector2f(580, 570));
	mode.setCharacterSize(24);
	mode.setString("Mode:");
	type.setFont(font);
	type.setFillColor(sf::Color::Black);
	type.setPosition(Vector2f(660, 570));
	type.setCharacterSize(24);

	shot.loadFromFile("resources\\shot.wav");
	shotsound.setBuffer(shot);
}
void weapon::display(RenderWindow &window, Vector2f user)
{
	weaponShape.rotate(-(weaponShape.getRotation()));
	weaponBarrel.rotate(-(weaponBarrel.getRotation()));
	weaponChamber.rotate(-(weaponChamber.getRotation()));
	if (Mouse::getPosition(window).x > user.x)
	{
		weaponShape.rotate(atan((user.y - Mouse::getPosition(window).y) / (user.x - Mouse::getPosition(window).x)) * 180 / PI);
		weaponBarrel.rotate(atan((user.y - Mouse::getPosition(window).y) / (user.x - Mouse::getPosition(window).x)) * 180 / PI);
		weaponChamber.rotate(atan((user.y - Mouse::getPosition(window).y) / (user.x - Mouse::getPosition(window).x)) * 180 / PI);
	}
	else
	{
		weaponShape.rotate(180 + atan((user.y - Mouse::getPosition(window).y) / (user.x - Mouse::getPosition(window).x)) * 180 / PI);
		weaponBarrel.rotate(180 + atan((user.y - Mouse::getPosition(window).y) / (user.x - Mouse::getPosition(window).x)) * 180 / PI);
		weaponChamber.rotate(180 + atan((user.y - Mouse::getPosition(window).y) / (user.x - Mouse::getPosition(window).x)) * 180 / PI);
	}
	weaponBarrel.setOrigin(-(weaponShape.getSize().x),-(weaponBarrel.getSize().y)/2);
	weaponShape.setPosition(user.x + 15, user.y + 15);
	weaponBarrel.setPosition(user.x + 15, user.y + 15);
	weaponChamber.setPosition(user.x + 15, user.y + 15);
	fireactionmouse();
	if(autofire==1)
		type.setString("Auto");
	else
		type.setString("Semi");
	window.draw(mode);
	window.draw(type);
	window.draw(weaponChamber);
	window.draw(weaponShape);
	window.draw(weaponBarrel);
}

int weapon::stringint(string number)
{
	return atoi(number.c_str());
}

Keyboard::Key keyw(int keynumber)
{
	return static_cast<Keyboard::Key>(keynumber);
}

void weapon::read()
{
	string transform;
	ifstream steering;
	int i;
	steering.open("settings\\steering.dat");
	if (steering.is_open() == 1)
	{
		for(i=1;i<=6;i++)
			getline(steering, transform);
		keyfiremode = keyw(stringint(transform));
		steering.close();
	}
	else
		cout << "Error opening steering\n";
	ifstream volume;
	volume.open("settings\\volume.dat");
	if (volume.is_open() == 1)
	{
		getline(volume, transform);
		shotsound.setVolume(stringint(transform));
		volume.close();
	}
}

void weapon::fireanimation()
{
	if (MousePressed == true)
	{
		if (FireCountMove < 10 && FireFinished != false)
		{
			if (FireCountMove == 0)
				shotsound.play();
			FireCountMove++;
			weaponChamber.setOrigin(-30 + FireCountMove, -(weaponShape.getSize().y));
		}
		else if (FireCountMove > 0)
		{
			FireCountMove--;
			weaponChamber.setOrigin(-30 + FireCountMove, -(weaponShape.getSize().y));
			FireFinished = false;
		}
		else if (autofire == 1)
		{
			FireCountMove = 0;
			FireFinished = true;
			MousePressed = false;
		}
		else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			FireCountMove = 0;
			FireFinished = true;
			MousePressed = false;
		}
	}
}
void weapon::fireactionmouse()
{
	if (!sf::Keyboard::isKeyPressed(keyfiremode))
		firebutton = false;
	if (sf::Keyboard::isKeyPressed(keyfiremode))
	{
		if (firebutton == false)
		{
			if (autofire == true)
				autofire = false;
			else
				autofire = true;
			firebutton = true;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		MousePressed = true;
	fireanimation();
}