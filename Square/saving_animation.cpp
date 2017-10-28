#include "saving_animation.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;

saving_animation::saving_animation()
{
	column.setFillColor(Color(80, 80, 80));
}

void saving_animation::setSize(int size)
{
	column.setSize(Vector2f(size, size));
}

void saving_animation::setPosition(Vector2f(position))
{
	column.setPosition(position);
}

void saving_animation::animation()
{
	for (int i = 0; i <= column.getSize().x; i++)
	{
		column.setPosition(Vector2f(column.getPosition().x, column.getPosition().y+1));
		column.setSize(Vector2f(column.getSize().x, column.getSize().y+1));
	}
	for (int i = 0; i <= column.getSize().x; i++)
	{
		column.setPosition(Vector2f(column.getPosition().x, column.getPosition().y - 1));
		column.setSize(Vector2f(column.getSize().x, column.getSize().y - 1));
	}
}