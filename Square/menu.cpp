#pragma once
#include <SFML\Graphics.hpp>
#include "menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace sf;
using namespace std;

string menu::language()
{
	string text;
	int longest;
	ifstream lang;
	lang.open("settings\\language.dat");
	if (lang.is_open())
	{
		getline(lang, text);
		lang.close();
		return text;
	}
	else
	{
		lang.close();
		ofstream new_lang;
		new_lang.open("settings\\language.dat");
		new_lang << 1 << endl;
		new_lang.close();
		return "1";
	}
}

void menu::load(string language)
{
	string text;
	int longest;
	int i;
	ifstream lang;
	string source;
	source = "lang\\";
	source += language;
	source += ".dat";
	lang.open(source.c_str());
	if (lang.is_open() == 1)
	{
		for(i=1;i<=15;i++)
			getline(lang, text);
		getline(lang, text);
		play.setString(text);
		getline(lang, text);
		editor.setString(text);
		getline(lang, text);
		options.setString(text);
		getline(lang, text);
		exit.setString(text);
	}
	else
		std::cout << "Language file not found";

}

menu::menu()
{
	retro.loadFromFile("resources\\font.ttf");
	
	tittle.setFont(retro);
	tittle.setFillColor(Color::White);
	tittle.setString("Square");

	line.setFillColor(Color::White);
	
	play.setFont(retro);
	play.setFillColor(Color::White);
	
	options.setFont(retro);
	options.setFillColor(Color::White);
	
	autor.setFont(retro);
	autor.setFillColor(Color::White);
	autor.setString("Maciej Kaca (C) 2016");

	exit.setFont(retro);
	exit.setFillColor(Color::White);

	editor.setFont(retro);
	editor.setFillColor(Color::White);

	choiced = false;
}

void menu::positioning(RenderWindow &window)
{
	tittle.setCharacterSize(textsize((15*window.getSize().y)/100));
	tittle.setPosition(Vector2f(window.getSize().x/2 - tittle.getGlobalBounds().width/ 2, 0));
	line.setSize(Vector2f(tittle.getGlobalBounds().width+ tittle.getGlobalBounds().width/2, (1*window.getSize().y)/100));
	line.setPosition(Vector2f(window.getSize().x/2 - line.getGlobalBounds().width / 2, tittle.getGlobalBounds().top+ tittle.getGlobalBounds().height+line.getGlobalBounds().height));
	play.setCharacterSize(textsize((7 * window.getSize().y) / 100));
	play.setPosition(Vector2f(window.getSize().x/2 - play.getGlobalBounds().width / 2, line.getPosition().y));
	editor.setCharacterSize(textsize((7 * window.getSize().y) / 100));
	editor.setPosition(Vector2f(window.getSize().x/2 - editor.getGlobalBounds().width / 2, play.getGlobalBounds().top + play.getGlobalBounds().height + (1.25 * window.getSize().y) / 100));
	options.setCharacterSize(textsize((7 * window.getSize().y) / 100));
	options.setPosition(Vector2f(window.getSize().x/2 - options.getGlobalBounds().width / 2, editor.getGlobalBounds().top + editor.getGlobalBounds().height + (1.25 * window.getSize().y) / 100));
	exit.setCharacterSize(textsize((7 * window.getSize().y) / 100));
	exit.setPosition(Vector2f(window.getSize().x/2 - exit.getGlobalBounds().width / 2, options.getGlobalBounds().top + options.getGlobalBounds().height + (1.25 * window.getSize().y) / 100));
	autor.setCharacterSize(textsize((3 * window.getSize().y) / 100));
	autor.setPosition(Vector2f(window.getSize().x-autor.getGlobalBounds().width, window.getSize().y - autor.getGlobalBounds().height*2));
}

bool menu::mouseontext(RenderWindow &window, Text &text)
{
	FloatRect boundingBox = text.getGlobalBounds();
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if (boundingBox.contains(mouse))
	{
		text.setFillColor(Color::Red);
		return true;
	}
	else
	{
		text.setFillColor(Color::White);
		return false;
	}
}

int menu::textsize(int height)
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

int menu::menudisplay(RenderWindow &window)
{
		load(language());
		positioning(window);
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonPressed && mouseontext(window, play))
				{
					play.setFillColor(Color(80, 0, 0));
					window.draw(play);
					window.display();
					while (Mouse::isButtonPressed(Mouse::Left));
					if (mouseontext(window, play))
					{
						return 1;
					}
				}
				if (event.type == Event::MouseButtonPressed && mouseontext(window, editor))
				{
					editor.setFillColor(Color(80, 0, 0));
					window.draw(editor);
					window.display();
					while (Mouse::isButtonPressed(Mouse::Left));
					if (mouseontext(window, editor))
						return 2;
				}
				if (event.type == Event::MouseButtonPressed && mouseontext(window, options))
				{
					options.setFillColor(Color(80, 0, 0));
					window.draw(options);
					window.display();
					while (Mouse::isButtonPressed(Mouse::Left));
					if (mouseontext(window, options))
					{
						return 3;
					}
				}
				if ((event.type == Event::MouseButtonPressed && mouseontext(window, exit)))
				{
					exit.setFillColor(Color(80, 0, 0));
					window.draw(exit);
					window.display();
					while (Mouse::isButtonPressed(Mouse::Left));
					if (mouseontext(window, exit))
						return 4;
				}
				if (event.type == Event::Closed)
					return 4;
			}
			mouseontext(window, play);
			mouseontext(window, editor);
			mouseontext(window, options);
			mouseontext(window, exit);
			window.clear(Color::Black);
			window.draw(line);
			window.draw(tittle);
			window.draw(play);
			window.draw(editor);
			window.draw(options);
			window.draw(exit);
			window.draw(autor);
			window.display();

		}
	}
