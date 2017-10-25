#include "editormenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace sf;
using namespace std;

editormenu::editormenu()
{

	if (!retro.loadFromFile("resources\\font.ttf"))
		std::cout << "error loading font on options";

	editortext.setFont(retro);
	editortext.setFillColor(Color::White);

	newtext.setFont(retro);
	newtext.setFillColor(Color::White);

	opentext.setFont(retro);
	opentext.setFillColor(Color::White);

	back.setFont(retro);
	back.setFillColor(Color::White);
}

bool editormenu::mouseontext(RenderWindow &window, Text &text)
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

string editormenu::language()
{
	string text;
	int longest;
	ifstream lang;
	lang.open("settings\\language.dat");
	if (lang.is_open() == 1)
	{
		getline(lang, text);
		lang.close();
		return text;
	}
	else
		cout << "Error opening settings\n";

}

void editormenu::load(string language)
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
		for (i = 1; i <= 3; i++)
			getline(lang, text);
		back.setString(text);
		for (i = 1; i <= 14; i++)
			getline(lang, text);
		editortext.setString(text);
		for (i = 1; i <= 3; i++)
			getline(lang, text);
		newtext.setString(text);
		getline(lang, text);
		opentext.setString(text);
	}
	else
		std::cout << "Language file not found";

}

void editormenu::positioning(RenderWindow &window)
{
	editortext.setCharacterSize(textsize((10 * window.getSize().y) / 100));
	editortext.setPosition(Vector2f(window.getSize().x/2 - editortext.getGlobalBounds().width / 2, (25 * window.getSize().y)/100-editortext.getGlobalBounds().height/2));
	newtext.setCharacterSize(textsize((10 * window.getSize().y) / 100));
	newtext.setPosition(Vector2f((window.getSize().x / 2)/2 - newtext.getGlobalBounds().width / 2, window.getSize().y/2-newtext.getGlobalBounds().height/2));
	opentext.setCharacterSize(textsize((10 * window.getSize().y) / 100));
	opentext.setPosition(Vector2f( (window.getSize().x / 2)+ (window.getSize().x / 2) / 2 - opentext.getGlobalBounds().width / 2, window.getSize().y / 2 - newtext.getGlobalBounds().height / 2));
	back.setCharacterSize(textsize((10 * window.getSize().y) / 100));
	back.setPosition(Vector2f(window.getSize().x / 2 - back.getGlobalBounds().width / 2, (75 * window.getSize().y) / 100 - back.getGlobalBounds().height));
}

int editormenu::textsize(int height)
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

int editormenu::display(RenderWindow &window)
{
	load(language());
	positioning(window);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed && mouseontext(window, newtext))
		{
			back.setFillColor(Color(80, 0, 0));
			window.draw(newtext);
			window.display();
			while (Mouse::isButtonPressed(Mouse::Left));
			if (mouseontext(window, newtext))
				return 1;
		}
		if (event.type == sf::Event::MouseButtonPressed && mouseontext(window, opentext))
		{
			back.setFillColor(Color(80, 0, 0));
			window.draw(opentext);
			window.display();
			while (Mouse::isButtonPressed(Mouse::Left));
			if (mouseontext(window, opentext))
				return 2;
		}
		if (event.type == sf::Event::MouseButtonPressed && mouseontext(window, back))
		{
			back.setFillColor(Color(80, 0, 0));
			window.draw(back);
			window.display();
			while (Mouse::isButtonPressed(Mouse::Left));
			if (mouseontext(window, back))
				return 3;
		}
		window.clear(Color::Black);
		mouseontext(window, newtext);
		mouseontext(window, opentext);
		mouseontext(window, back);
		window.draw(editortext);
		window.draw(newtext);
		window.draw(opentext);
		window.draw(back);
		window.display();
	}
}