#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "help.h"
using namespace sf;
using namespace std;

help::help()
{
	retro.loadFromFile("resources\\font.ttf");
	quote.setFont(retro);
	quote.setFillColor(Color::Black);
	quote.setString("?");
	frame.setFillColor(Color::White);
	background.setFillColor(Color(64,64,64));
	mouse_L.loadFromFile("resources\\lpm.png");
	lpm.setTexture(mouse_L);
	mouse_P.loadFromFile("resources\\ppm.png");
	ppm.setTexture(mouse_P);
	or[0].setFont(retro);
	or[0].setFillColor(Color::Black);
	or [1].setFont(retro);
	or [1].setFillColor(Color::Black);
	move.setFont(retro);
	move.setFillColor(Color::Black);
	resize.setFont(retro);
	resize.setFillColor(Color::Black);
	create.setFont(retro);
	create.setFillColor(Color::Black);
	remove.setFont(retro);
	remove.setFillColor(Color::Black);
	coursor.loadFromFile("resources\\mouse.png");
	mouse_sprite.setTexture(coursor);
	modificator.setFillColor(Color(104, 0, 205));
	background.setOutlineColor(Color::Black);
}

void help::background_size(Vector2f size)
{
	background.setSize(size);
	lpm.setScale(float(float((10 * size.x) / 100)/mouse_L.getSize().x), float(float((20 * size.y) / 100) / mouse_L.getSize().y));
	ppm.setScale(lpm.getScale());
	or[0].setCharacterSize(textsize((3 * size.x) / 100));
	or [1].setCharacterSize(textsize((3 * size.x) / 100));
	move.setCharacterSize(or[0].getCharacterSize());
	resize.setCharacterSize(or [0].getCharacterSize());
	create.setCharacterSize(or [0].getCharacterSize());
	remove.setCharacterSize(or [0].getCharacterSize());
	obstacle.setSize(Vector2f((15 * size.y) / 100, (15 * size.y) / 100));
	mouse_sprite.setScale(float(((3 * size.x) / 100)/2 / coursor.getSize().x), float(((7 * size.y) / 100) / 2 / coursor.getSize().y));
	modificator.setSize(Vector2f((15*obstacle.getGlobalBounds().width)/100, obstacle.getGlobalBounds().height));
}

FloatRect help::background_bounds()
{
	return background.getGlobalBounds();
}

void help::load()
{
	string text;
	ifstream lang;
	lang.open("settings\\language.dat");
	if (lang.is_open() == 1)
	{
		getline(lang, text);
		lang.close();
	}
	int i;
	string source;
	source = "lang\\";
	source += text;
	source += ".dat";
	lang.open(source.c_str());
	if (lang.is_open() == 1)
	{
		for (i = 1; i <= 22; i++)
			getline(lang, text);
		or[0].setString(text);
		or [1].setString(text);
		getline(lang, text);
		move.setString(text);
		getline(lang, text);
		resize.setString(text);
		getline(lang, text);
		create.setString(text);
		getline(lang, text);
		remove.setString(text);
	}

}

void help::background_position(Vector2f position)
{
	int padding = (5 * background.getGlobalBounds().width) / 100;
	background.setPosition(position);
	lpm.setPosition(Vector2f(position.x+((background.getGlobalBounds().width/2) - (lpm.getGlobalBounds().width+padding+move.getGlobalBounds().width+padding+or[0].getGlobalBounds().width+padding+resize.getGlobalBounds().width)/2),position.y+(background.getSize().y/2)/2-lpm.getGlobalBounds().height/2));
	text_position(Vector2f(lpm.getPosition().x+lpm.getGlobalBounds().width+padding,lpm.getPosition().y+(lpm.getGlobalBounds().height/2)-(move.getGlobalBounds().height/2)), move);
	or [0].setPosition(Vector2f(move.getPosition().x+move.getGlobalBounds().width+padding,move.getPosition().y));
	resize.setPosition(Vector2f(or[0].getPosition().x+or[0].getGlobalBounds().width+padding,move.getPosition().y));
	ppm.setPosition(Vector2f(position.x + ((background.getGlobalBounds().width / 2) - (ppm.getGlobalBounds().width + padding + create.getGlobalBounds().width + padding + or[1] .getGlobalBounds().width + padding + remove.getGlobalBounds().width) / 2), position.y+background.getSize().y/4+ background.getSize().y/2-ppm.getGlobalBounds().height/2));
	text_position(Vector2f(ppm.getPosition().x + ppm.getGlobalBounds().width + padding, ppm.getPosition().y + (ppm.getGlobalBounds().height / 2) - (create.getGlobalBounds().height / 2)), create);
	or [1].setPosition(Vector2f(create.getPosition().x+create.getGlobalBounds().width+padding, create.getPosition().y));
	remove.setPosition(Vector2f(or[1].getPosition().x+or[1].getGlobalBounds().width+padding, create.getPosition().y));
	//	or .setPosition(Vector2f( position.x + ( background.getGlobalBounds().width/2 ) - (or.getGlobalBounds().width/2), position.y));
	//move.setPosition(Vector2f(or.getPosition().x-move.getGlobalBounds().width-(5*background.getGlobalBounds().width)/100, or.getPosition().y));
	//resize.setPosition(Vector2f(or.getPosition().x+or.getGlobalBounds().width+ (5 * background.getGlobalBounds().width) / 100, or .getPosition().y));
	//lpm.setPosition(Vector2f( background.getPosition().x + (background.getGlobalBounds().width/2) - (lpm.getGlobalBounds().width+ (5 * background.getSize().x) / 100 + LPM_text.getGlobalBounds().width)/2 , position.y+10));
	//text_position(Vector2f(lpm.getPosition().x + lpm.getGlobalBounds().width + (5*background.getSize().x)/100, lpm.getGlobalBounds().top+(lpm.getGlobalBounds().height/2)-(LPM_text.getGlobalBounds().height/2)), LPM_text);
}

int help::textsize(int height)
{
	int charsize = 0;
	Text texter;
	texter.setFont(retro);
	texter.setString("Ip");
	texter.setCharacterSize(charsize);
	while (texter.getGlobalBounds().height <= height)
	{
		texter.setCharacterSize(charsize++);
	}
	return charsize;
}

void help::setSize(int size)
{
	frame.setSize(Vector2f(size,size));
	quote.setCharacterSize(textsize(size));
}

void help::text_position(Vector2f position, Text &text)
{
	float y = position.y;
	text.setPosition(position);
	while (text.getGlobalBounds().top>position.y)
		text.setPosition(Vector2f(position.x, y--));
	text.setPosition(Vector2f(position.x, y));
}

void help::setPosition(Vector2f position)
{
	frame.setPosition(position);
	float y = position.y+((frame.getGlobalBounds().height/2)-(quote.getGlobalBounds().height/2));
	quote.setPosition(position);
	while (quote.getGlobalBounds().top>=y)
		quote.setPosition(Vector2f(position.x, position.y--));
}

FloatRect help::getGlobalBounds()
{
	return frame.getGlobalBounds();
}

void help::setFillColor(Color color)
{
	frame.setFillColor(color);
}

void help::onShape(RenderWindow &window)
{
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if ( frame.getGlobalBounds().contains(mouse))
	{
		frame.setFillColor(Color::Red);
		display(window);
		window.draw(background);
		window.draw(move);
		window.draw(or[0] );
		window.draw(resize);
		window.draw(lpm);
		obstacle.setPosition(Vector2f(move.getPosition().x+(move.getGlobalBounds().width/2)-(obstacle.getGlobalBounds().width/2), move.getGlobalBounds().top+move.getGlobalBounds().height+(5*background.getGlobalBounds().height)/100));
		obstacle.setFillColor(Color(80, 0, 0));
		window.draw(obstacle);
		mouse_sprite.setPosition(Vector2f(obstacle.getPosition().x + obstacle.getGlobalBounds().width / 2, obstacle.getPosition().y + obstacle.getGlobalBounds().height / 2));
		window.draw(mouse_sprite);
		obstacle.setPosition(Vector2f(resize.getPosition().x + (resize.getGlobalBounds().width / 2) - (obstacle.getGlobalBounds().width / 2), resize.getGlobalBounds().top + resize.getGlobalBounds().height+ (5 * background.getGlobalBounds().height) / 100));
		obstacle.setFillColor(Color::Red);
		window.draw(obstacle);
		modificator.setPosition(obstacle.getPosition());
		window.draw(modificator);
		mouse_sprite.setPosition(Vector2f(obstacle.getPosition().x, obstacle.getPosition().y + obstacle.getGlobalBounds().height / 2));
		window.draw(mouse_sprite);
		window.draw(ppm);
		window.draw(create);
		window.draw(or [1]);
		window.draw(remove);
		/*
		obstacle.setPosition(Vector2f(((background.getGlobalBounds().width/2)/2)-(obstacle.getGlobalBounds().width/2) + background.getPosition().x, lpm.getPosition().y+lpm.getGlobalBounds().height));
		mouse_sprite.setPosition(Vector2f(obstacle.getPosition().x+obstacle.getGlobalBounds().width/2, obstacle.getPosition().y + obstacle.getGlobalBounds().height / 2));
		window.draw(mouse_sprite);
		obstacle.setPosition(Vector2f((((background.getGlobalBounds().width / 2) / 2) - (obstacle.getGlobalBounds().width / 2) + ((background.getGlobalBounds().width / 2))) + background.getPosition().x, lpm.getPosition().y + lpm.getGlobalBounds().height));
		obstacle.setFillColor(Color::Red);
		window.draw(obstacle);
		modificator.setPosition(obstacle.getPosition());
		window.draw(modificator);
		mouse_sprite.setPosition(Vector2f(obstacle.getPosition().x, obstacle.getPosition().y + obstacle.getGlobalBounds().height / 2));
		window.draw(mouse_sprite);
		window.draw(ppm);
		*/
		window.display();
		while (frame.getGlobalBounds().contains(mouse))
		{
			mouse = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}
			}
			
		}
	}
	else
	{
		frame.setFillColor(Color::White);
	}
}

Vector2f help::getPosition()
{
	return frame.getPosition();
}

void help::display(RenderWindow &window)
{
	window.draw(frame);
	window.draw(quote);
}