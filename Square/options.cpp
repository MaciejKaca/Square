#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "options.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <stdio.h>
#include <math.h>
using namespace std;

int stringint(string number)
{
	return atoi(number.c_str());
}

string intstring(int number)
{
	ostringstream ss;
	ss << number;
	return ss.str();
}

string options::language()
{
	string text;
	int longest;
	ifstream lang;
	lang.open("settings\\language.dat");
	getline(lang, text);
	lang.close();
	return text;
}

void options::load(string language)
{
	string text;
	ifstream lang;
	string source;
	source = "lang\\";
	source += language;
	source += ".dat";
	lang.open(source.c_str());
		getline(lang, text);
		languagetext.setString(text);

		getline(lang, text);
		header.setString(text);

		getline(lang, text);
		back.setString(text);

		getline(lang, text);
		savetext.setString(text);

		getline(lang, text);
		defaulttext.setString(text);

		getline(lang, text);
		moveup.setString(text);

		getline(lang, text);
		movedown.setString(text);

		getline(lang, text);
		moveleft.setString(text);

		getline(lang, text);
		moveright.setString(text);

		getline(lang, text);
		sprint.setString(text);

		getline(lang, text);
		firemode.setString(text);

		getline(lang, text);
		antialiasingtext.setString(text);

		getline(lang, text);
		volumetext.setString(text);

		getline(lang, text);
		duplicate.setString(text);

		getline(lang, text);
		fullscreen.setString(text);

		lang.close();
}

int options::size(RenderWindow &window, int value)
{
	int charsize = 0;
	Text texter;
	texter.setFont(retro);
	texter.setString("Ip");
	texter.setCharacterSize(charsize);
	while (texter.getGlobalBounds().height <= (value*window.getSize().y) / 100)
	{
		texter.setCharacterSize(charsize++);
	}
	return charsize;
}

void options::repetition(RenderWindow &window)
{
	int i;
	int a;
	int y_key[6];
	string keys[6];
	Vector2f pos;
	keys[0] = moveupkey.getString();
	keys[1] = movedownkey.getString();
	keys[2] = moveleftkey.getString();
	keys[3] = moverightkey.getString();
	keys[4] = sprintkey.getString();
	keys[5] = firemodekey.getString();
	y_key[0] = moveupkey.getPosition().y;
	y_key[1] = movedownkey.getPosition().y;
	y_key[2] = moveleftkey.getPosition().y;
	y_key[3] = moverightkey.getPosition().y;
	y_key[4] = sprintkey.getPosition().y;
	y_key[5] = firemodekey.getPosition().y;
	for (a = 0; a <= 6; a++)
	{
		for (i = 0; i <= 6; i++)
		{
			if (keys[a] == keys[i] && i != a)
			{
				caution.setPosition(Vector2f(selection_pos_x-caution.getGlobalBounds().width-selection.getOutlineThickness(), y_key[a]-longestkey.getGlobalBounds().height));
				caution.setFillColor(Color::Red);
				window.draw(caution);
			}
		}
	}
	if (caution.getFillColor() == (Color::Transparent))
		duplicate.setFillColor(Color::Transparent);
	else
		duplicate.setFillColor(Color::Red);
	caution.setFillColor(Color::Transparent);
}

int options::leftlongest()
{
	int longest;
	longest = moveup.getGlobalBounds().width;
	if (longest < movedown.getGlobalBounds().width)
		longest = movedown.getGlobalBounds().width;
	if (longest < moveleft.getGlobalBounds().width)
		longest = moveleft.getGlobalBounds().width;
	if (longest < moveright.getGlobalBounds().width)
		longest = moveright.getGlobalBounds().width;
	if (longest < sprint.getGlobalBounds().width)
		longest = sprint.getGlobalBounds().width;
	if (longest < firemode.getGlobalBounds().width)
		longest = firemode.getGlobalBounds().width;
	return longest;
}

int options::rightlongest()
{
	Text slider;
	int longest;
	slider.setFont(retro);
	slider.setFillColor(Color::White);
	slider.setCharacterSize(30);
	slider.setString("100");
	longest = volumecase.getGlobalBounds().width + 10 + slider.getGlobalBounds().width;
	if (longest < antialiasingtext.getGlobalBounds().width)
		longest = antialiasingtext.getGlobalBounds().width;
	if (longest < volumetext.getGlobalBounds().width)
		longest = volumetext.getGlobalBounds().width;
	return longest;
}

int options::numberoflangauges()
{
	string text;
	int i;
	ifstream lang;
	string source;
	for (i = 1; i <= 24; i++)
	{
		source = "lang\\";
		source += intstring(i);
		source += ".dat";
		lang.open(source.c_str());
		if (lang.is_open() == 1)
		{
			getline(lang, text);
			languageselection[i] = text;
			lang.close();
		}
		else
		{
			return i - 1;
		}
	}
}

int options::longestlanguage()
{
	int i;
	int index=1;
	int longest=languageselection[1].length();
	for (i = 2; i <= numberoflangauges(); i++)
		if (longest < languageselection[i].length())
		{
			longest = languageselection[i].length();
			index = i;

		}
	return index;
}

options::options()
{
	background.White;
	retro.loadFromFile("resources\\font.ttf");
	header.setFont(retro);
	header.setFillColor(Color::White);

	back.setFont(retro);
	back.setFillColor(Color::White);

	savetext.setFont(retro);
	savetext.setFillColor(Color::White);

	defaulttext.setFont(retro);
	defaulttext.setFillColor(Color::White);

	longestkey.setFont(retro);
	longestkey.setString("BIpkSpace");

	longestlang.setFont(retro);
	longestlang.setString(languageselection[longestlanguage()]);
	
	moveup.setFont(retro);
	moveup.setFillColor(Color::White);

	movedown.setFont(retro);
	movedown.setFillColor(Color::White);

	moveleft.setFont(retro);
	moveleft.setFillColor(Color::White);

	moveright.setFont(retro);
	moveright.setFillColor(Color::White);

	sprint.setFont(retro);
	sprint.setFillColor(Color::White);

	firemode.setFont(retro);
	firemode.setFillColor(Color::White);

	languagetext.setFont(retro);
	languagetext.setFillColor(Color::White);

	moveupkey.setFont(retro);
	moveupkey.setFillColor(Color::White);

	movedownkey.setFont(retro);
	movedownkey.setFillColor(Color::White);

	moveleftkey.setFont(retro);
	moveleftkey.setFillColor(Color::White);

	moverightkey.setFont(retro);
	moverightkey.setFillColor(Color::White);

	sprintkey.setFont(retro);
	sprintkey.setFillColor(Color::White);

	firemodekey.setFont(retro);
	firemodekey.setFillColor(Color::White);

	antialiasingtext.setFont(retro);
	antialiasingtext.setFillColor(Color::White);

	duplicate.setFont(retro);
	duplicate.setFillColor(Color::Transparent);

	antialiasingvalue.setFont(retro);
	antialiasingvalue.setFillColor(Color::White);

	volumetext.setFont(retro);
	volumetext.setFillColor(Color::White);

	volumetextvalue.setFont(retro);
	volumetextvalue.setFillColor(Color::White);

	selection.setFillColor(Color::Transparent);

	selected.setFillColor(Color::Transparent);
	selected.setOutlineColor(Color::Transparent);

	change.setFillColor(Color::Transparent);

	changed.setFillColor(Color::Transparent);
	changed.setOutlineColor(Color::Transparent);

	leftlanguage.setPointCount(3);
	leftlanguage.setFillColor(Color::White);

	rightlanguage.setPointCount(3);
	rightlanguage.setFillColor(Color::White);

	antialiasingcase.setOutlineColor(Color::White);
	antialiasingcase.setFillColor(Color::Transparent);

	antialiasingcaselevel.setFillColor(Color::White);

	cleaner.setFillColor(Color::Transparent);

	volumecase.setOutlineColor(Color::White);
	volumecase.setFillColor(Color::Transparent);

	volumecaselevel.setFillColor(Color::White);

	fullscreen_frame.setOutlineColor(Color::White);

	caution.setFont(retro);
	caution.setString("!");

	fullscreen.setFont(retro);
	fullscreen.setFillColor(Color::White);

	shot.loadFromFile("resources\\shot.wav");
	shotsound.setBuffer(shot);
}

void options::clean(RenderWindow &window, Text &text)
{
	cleaner.setSize(Vector2f(text.getGlobalBounds().width+2, text.getGlobalBounds().height+1));
	cleaner.setPosition(Vector2f(text.getPosition().x-2, text.getPosition().y+text.getGlobalBounds().height));
	window.draw(cleaner);
}

void options::positioning(RenderWindow &window)
{
	selection.setOutlineThickness((1.3*window.getSize().y)/100);
	change.setOutlineThickness(selection.getOutlineThickness());
	selected.setOutlineThickness(selection.getOutlineThickness());
	changed.setOutlineThickness(selection.getOutlineThickness());
	header.setCharacterSize(size(window, 7));
	back.setCharacterSize(size(window, 4));
	savetext.setCharacterSize(size(window, 4));
	defaulttext.setCharacterSize(size(window, 4));
	longestlang.setCharacterSize(size(window, 3));
	longestkey.setCharacterSize(size(window, 3));
	moveup.setCharacterSize(size(window, 3));
	movedown.setCharacterSize(size(window, 3));
	moveright.setCharacterSize(size(window, 3));
	moveleft.setCharacterSize(size(window, 3));
	sprint.setCharacterSize(size(window, 3));
	firemode.setCharacterSize(size(window, 3));
	antialiasingtext.setCharacterSize(size(window, 3));
	antialiasingvalue.setCharacterSize(size(window, 3));
	level.setCharacterSize(size(window, 3));
	sprintkey.setCharacterSize(size(window, 3));
	moveupkey.setCharacterSize(size(window, 3));
	movedownkey.setCharacterSize(size(window, 3));
	moveleftkey.setCharacterSize(size(window, 3));
	moverightkey.setCharacterSize(size(window, 3));
	firemodekey.setCharacterSize(size(window, 3));
	duplicate.setCharacterSize(size(window, 3));
	fullscreen.setCharacterSize(size(window, 3));
	volumetext.setCharacterSize(size(window, 3));
	antialiasingcase.setSize(Vector2f((25 * window.getSize().x) / 100, longestkey.getGlobalBounds().height));

	selection_widht = leftlongest() + (2*window.getSize().x)/100 + longestkey.getGlobalBounds().width + (0.39*window.getSize().x)/100 + selection.getOutlineThickness();
	movetext = Vector2f((window.getSize().x/2)-(rightlongest()+selection_widht+ ((1 * window.getSize().x) / 100))/2, (20*window.getSize().y) / 100);
	movetextkey = Vector2f(movetext.x + leftlongest() + (1.17*window.getSize().x) / 100, movetext.y);
	padding = (6.94*window.getSize().y)/100;
	selection_pos_x = movetext.x-(0.39*window.getSize().x)/100;
	change_pos_x = (0.39*window.getSize().x) / 100;
	selection.setSize(Vector2f(selection_widht, longestkey.getGlobalBounds().height+selection.getOutlineThickness()));
	selected.setSize(selection.getSize());
	change.setSize(Vector2f((selection_pos_x+selection_widht)- (movetextkey.x - change_pos_x), longestkey.getGlobalBounds().height + selection.getOutlineThickness()));
	changed.setSize(change.getSize());
	header.setPosition(Vector2f((window.getSize().x / 2) - (header.getGlobalBounds().width / 2), 10));
	moveup.setPosition(movetext);
	movedown.setPosition(Vector2f(movetext.x, movetext.y + padding));
	moveleft.setPosition(Vector2f(movetext.x, movetext.y + 2 * padding));
	moveright.setPosition(Vector2f(movetext.x, movetext.y + 3 * padding));
	sprint.setPosition(Vector2f(movetext.x, movetext.y + 4 * padding));
	volumecase.setSize(antialiasingcase.getSize());
	firemode.setPosition(Vector2f(movetext.x, movetext.y + 5 * padding));
	languagetext.setCharacterSize(size(window, 3));
	languagetext.setPosition(Vector2f((window.getSize().x /2)- languagetext.getGlobalBounds().width/2, movetext.y + 7 * padding));
	leftlanguage.setPosition(Vector2f(((window.getSize().x / 2) - longestlang.getGlobalBounds().width / 2)-leftlanguage.getGlobalBounds().width/2, languagetext.getPosition().y + longestlang.getGlobalBounds().height));
	rightlanguage.setPosition(Vector2f(((window.getSize().x / 2) + longestlang.getGlobalBounds().width / 2) + leftlanguage.getGlobalBounds().width/2, languagetext.getPosition().y + longestlang.getGlobalBounds().height));

	duplicate.setPosition(Vector2f((window.getSize().x / 2) - duplicate.getGlobalBounds().width / 2, movetext.y + 8 * padding));

	back.setPosition(Vector2f(((window.getSize().x / 2 + window.getSize().x / 4) - back.getGlobalBounds().width / 2), movetext.y + 9 * padding));
	savetext.setPosition(Vector2f((window.getSize().x / 2) - savetext.getGlobalBounds().width / 2, movetext.y + 9 * padding));
	defaulttext.setPosition(Vector2f(((window.getSize().x / 4) - defaulttext.getGlobalBounds().width / 2), movetext.y + 9 * padding));

	moveupkey.setPosition(Vector2f(movetextkey));
	movedownkey.setPosition(Vector2f(movetextkey.x, movetext.y + padding));
	moveleftkey.setPosition(Vector2f(movetextkey.x, movetext.y + 2 * padding));
	moverightkey.setPosition(Vector2f(movetextkey.x, movetext.y + 3 * padding));
	sprintkey.setPosition(Vector2f(movetextkey.x, movetext.y + 4 * padding));
	firemodekey.setPosition(Vector2f(movetextkey.x, movetext.y + 5 * padding));

	antialiasingcase.setOutlineThickness((1.3*window.getSize().y) / 100);

	antialiasingtext.setPosition(Vector2f(selection_pos_x+selection.getGlobalBounds().width+ ((1*window.getSize().x) / 100),movetext.y));
	antialiasingcase.setPosition(Vector2f(antialiasingtext.getPosition().x, movetext.y + padding + antialiasingcase.getOutlineThickness()));
	antialiasingcaselevel.setPosition(Vector2f(antialiasingcase.getPosition().x, antialiasingcase.getPosition().y));
	antialiasingvalue.setPosition(Vector2f(antialiasingcase.getPosition().x + antialiasingcase.getGlobalBounds().width + 10, antialiasingcase.getPosition().y- antialiasingcase.getGlobalBounds().height/2));

	volumetext.setPosition(Vector2f(antialiasingtext.getPosition().x, movetext.y+2*padding));
	volumetextvalue.setCharacterSize(size(window, 3));
	volumecase.setOutlineThickness(antialiasingcase.getOutlineThickness());
	volumecase.setPosition(Vector2f(antialiasingtext.getPosition().x, movetext.y + 3 * padding + volumecase.getOutlineThickness()));
	volumecaselevel.setPosition(Vector2f(antialiasingtext.getPosition().x, volumecase.getPosition().y));
	volumetextvalue.setPosition(Vector2f(antialiasingtext.getPosition().x+volumecase.getGlobalBounds().width+10, volumecase.getPosition().y-volumecase.getGlobalBounds().height/2));

	fullscreen.setPosition(Vector2f(antialiasingtext.getPosition().x, movetext.y + 4 * padding));
	fullscreen_frame.setSize(Vector2f(fullscreen.getGlobalBounds().height, fullscreen.getGlobalBounds().height));
	fullscreen_frame.setOutlineThickness((0.41*window.getSize().y)/100);
	fullscreen_frame.setFillColor(Color::Transparent);
	fullscreen_frame.setPosition(Vector2f(fullscreen.getPosition().x + fullscreen.getGlobalBounds().width + (0.69*window.getSize().y) / 100, fullscreen.getGlobalBounds().top));

	caution.setCharacterSize(size(window, 5));

	leftlanguage.setRadius((longestlang.getGlobalBounds().height*sqrt(3)) / 3);
	leftlanguage.setOrigin(Vector2f(leftlanguage.getRadius(), leftlanguage.getRadius()));
	leftlanguage.setRotation(270);

	rightlanguage.setRadius((longestlang.getGlobalBounds().height*sqrt(3)) / 3);
	rightlanguage.setOrigin(Vector2f(leftlanguage.getRadius(), leftlanguage.getRadius()));
	rightlanguage.setRotation(90);
}

bool options::mouseontext(RenderWindow &window, Text &text)
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

bool options::mouseonshapecircle(RenderWindow &window, CircleShape &shape)
{
	FloatRect boundingBox = shape.getGlobalBounds();
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if (boundingBox.contains(mouse))
	{
		shape.setFillColor(Color::Red);
		return true;
	}
	else
	{
		shape.setFillColor(Color::White);
		return false;
	}
}

bool options::mouseonshaperectangle(RenderWindow &window, RectangleShape &shape)
{
	FloatRect boundingBox = shape.getGlobalBounds();
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if (boundingBox.contains(mouse))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void options::save()
{
	ofstream steering;
steering.open("settings\\steering.dat");
steering << keyup << endl;
steering << keydown << endl;
steering << keyleft << endl;
steering << keyright << endl;
steering << keysprint << endl;
steering << keyfiremode << endl;
steering.close();
ofstream graphics;
graphics.open("settings\\graphics.dat");
graphics << stringint(antialiasingvalue.getString()) << endl;
graphics << intstring(fullscreen_state);
graphics.close();
ofstream volume;
volume.open("settings\\volume.dat");
volume << stringint(volumetextvalue.getString()) << endl;
volume.close();
}

void options::draw(RenderWindow &window)
{
	window.draw(selection);
	window.draw(change);
	if (changed.getOutlineColor() != Color::Transparent)
	{
		window.draw(selected);
		window.draw(changed);
	}
	repetition(window);
	window.draw(header);
	window.draw(moveup);
	window.draw(movedown);
	window.draw(moveright);
	window.draw(moveleft);
	window.draw(sprint);
	window.draw(firemode);
	window.draw(moveupkey);
	window.draw(movedownkey);
	window.draw(moveleftkey);
	window.draw(moverightkey);
	window.draw(sprintkey);
	window.draw(firemodekey);
	window.draw(leftlanguage);
	window.draw(languagetext);
	window.draw(rightlanguage);
	window.draw(duplicate);
	window.draw(antialiasingtext);
	window.draw(antialiasingcase);
	window.draw(antialiasingcaselevel);
	window.draw(antialiasingvalue);
	window.draw(volumetext);
	window.draw(volumecase);
	window.draw(volumecaselevel);
	window.draw(volumetextvalue);
	window.draw(fullscreen);
	window.draw(fullscreen_frame);
	window.draw(back);
	window.draw(savetext);
	window.draw(defaulttext);
	window.draw(caution);
}

bool options::altialiasingchanged()
{
	string transform;
	ifstream settings;
	string antifromfile;
	settings.open("settings\\graphics.dat");
	if (settings.is_open() == 1)
	{
		getline(settings, transform);
	}
	if (transform != intstring(levelanti))
		return true;
	else
		return false;
}

void options::setstring(Text &text, int key, int where)
{
	string keys[61] = { "Escape","LControl","LShift","LAlt","LSystem","RControl","RShift","RAlt",
		"RSystem","Menu","[","]",";",",",".","'","/","\\","`","=","-","Space","Enter","BackSpace",
		"Tab","PageUp","PageDown","End","Home","Instert","Delete","+","-","*","/","Left","Right","Up",
		"Down","Numpad0","Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6",
		"Numpad7", "Numpad8", "Numpad9","F1","F2","F3","F4","F5","F6","F7","F8", "F9", "F10",
		"F11", "F12" };
	if (key <= 25 && key >= 0)
	{
		text.setString(static_cast<char>(key + 65));
	}
	else if (key >= 26 && key <= 35)
	{
		text.setString(static_cast<char>(key + 22));
	}
	else if (key <= 96)
	{
		text.setString(keys[key - 36]);
	}
	else
		text.setString("unknown");
	if (key >= 0 && key <= 96)
		switch (where)
		{
		case 1:
			keyup = key;
			break;
		case 2:
			keydown = key;
			break;
		case 3:
			keyleft = key;
			break;
		case 4:
			keyright = key;
			break;
		case 5:
			keysprint = key;
			break;
		case 6:
			keyfiremode = key;
			break;
		}

}

void options::setantialiasingslider(int value)
{
	antialiasingcaselevel.setSize(Vector2f(value, antialiasingcase.getGlobalBounds().height - antialiasingcase.getOutlineThickness() * 2));
	antialiasingvalue.setString(intstring(value/ ((antialiasingcase.getGlobalBounds().width - 2 * antialiasingcase.getOutlineThickness()) / 8)));
}

void options::setvolumeslider(int value)
{
	volumecaselevel.setSize(Vector2f(value, volumecase.getGlobalBounds().height - volumecase.getOutlineThickness() * 2));
	volumetextvalue.setString(intstring(value/ ((volumecase.getGlobalBounds().width - 2 * volumecase.getOutlineThickness()) / 100)));
}

void options::volumeslidermove(RenderWindow &window)
{
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if ((mouse.x - volumecaselevel.getPosition().x) / ((volumecase.getGlobalBounds().width-2 * volumecase.getOutlineThickness())/ 100) <= 100 && (mouse.x - volumecaselevel.getPosition().x) / (volumecase.getGlobalBounds().width / 100) > 0)
	{
		setvolumeslider(mouse.x - volumecaselevel.getPosition().x);
	}
	else
		if ((mouse.x - volumecaselevel.getPosition().x) / ((volumecase.getGlobalBounds().width - 2 * volumecase.getOutlineThickness()) / 100) > 100)
		{
			setvolumeslider(volumecase.getGlobalBounds().width-2*volumecase.getOutlineThickness()+1);
		}
		else
		{
			setvolumeslider(0);
		}
	volumecaselevel.setFillColor(Color(155, 0, 0));
	window.clear(background);
	draw(window);
	window.display();
}

void options::antialiasingslidermove(RenderWindow &window)
{
		Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		if ((mouse.x - antialiasingcaselevel.getPosition().x) / ((antialiasingcase.getGlobalBounds().width - 2 * antialiasingcase.getOutlineThickness()) / 8) <= 8 && (mouse.x - antialiasingcase.getPosition().x) / ((antialiasingcase.getGlobalBounds().width - 2 * antialiasingcase.getOutlineThickness()) / 8) > 0)
		{
			setantialiasingslider(mouse.x - antialiasingcaselevel.getPosition().x);
		}
		else

			if ((mouse.x - antialiasingcaselevel.getPosition().x) / ((antialiasingcase.getGlobalBounds().width - 2 * antialiasingcase.getOutlineThickness()) / 8) > 8)
			{
				setantialiasingslider(antialiasingcase.getGlobalBounds().width - 2 * antialiasingcase.getOutlineThickness()+1);
			}
			else
			{
				setantialiasingslider(0);
			}
		antialiasingcaselevel.setFillColor(Color(155, 0, 0));
		window.clear(background);
		draw(window);
		window.display();
}

void options::read()
{
	string transform;
	ifstream settings;
	settings.open("settings\\steering.dat");
	if (settings.is_open() == 1)
	{
		getline(settings, transform);
		keyup = stringint(transform);
		getline(settings, transform);
		keydown = stringint(transform);
		getline(settings, transform);
		keyleft = stringint(transform);
		getline(settings, transform);
		keyright = stringint(transform);
		getline(settings, transform);
		keysprint = stringint(transform);
		getline(settings, transform);
		keyfiremode = stringint(transform);
	}
	settings.close();
	setstring(moveupkey, keyup, 1);
	setstring(movedownkey, keydown, 2);
	setstring(moveleftkey, keyleft, 3);
	setstring(moverightkey, keyright, 4);
	setstring(sprintkey, keysprint, 5);
	setstring(firemodekey, keyfiremode, 6);
	
	settings.open("settings\\graphics.dat");
	if (settings.is_open() == 1)
	{
		getline(settings, transform);
		setantialiasingslider(stringint(transform)*(antialiasingcase.getGlobalBounds().width - 2 * antialiasingcase.getOutlineThickness())/8+1);
		levelanti = stringint(transform);
		getline(settings, transform);
		fullscreen_state = stringint(transform);
	}
	settings.close();
	settings.open("settings\\volume.dat");
	if (settings.is_open() == 1)
	{
		getline(settings, transform);
		setvolumeslider(stringint(transform)*(volumecase.getGlobalBounds().width - 2 * volumecase.getOutlineThickness())/100+1);
	}
	settings.close();
}

ContextSettings options::windowsettings()
{
	ContextSettings window;
	string transform;
	ifstream settings;
	settings.open("settings\\graphics.dat");
	if (settings.is_open() == 1)
	{
		getline(settings, transform);
	}
	window.antialiasingLevel = stringint(transform);
	return window;
}

int options::screen_mode()
{
	string videomode;
	string anti;
	ifstream settings;
	settings.open("settings\\graphics.dat");
	if (settings.is_open())
	{
		getline(settings, videomode);
		getline(settings, videomode);
		settings.close();
		if (videomode == "2" || videomode == "3")
		{
			return stringint(videomode);
		}
		else
		{
			settings.open("settings\\graphics.dat");
			getline(settings, anti);
			settings.close();
			ofstream new_settings;
			new_settings.open("settings\\graphics.dat");
			new_settings << anti << endl;
			new_settings << 2 << endl;
			new_settings.close();
			return 2;
		}
	}
	else
	{
		ofstream new_settings;
		new_settings.open("settings\\graphics.dat");
		new_settings << 0 << endl;
		new_settings << 2 << endl;
		new_settings.close();
		return 2;
	}
}

bool options::mouseontextselection(RenderWindow &window, Text &text, Text &text2)
{
	FloatRect boundingBox(text.getPosition().x, text.getPosition().y-padding/2, selection.getLocalBounds().width, text.getGlobalBounds().height+padding);
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if (boundingBox.contains(mouse))
	{
		selection.setOutlineColor(Color::Red);
		change.setOutlineColor(Color::Red);
		selection.setPosition(Vector2f(selection_pos_x, text.getGlobalBounds().top-(longestkey.getGlobalBounds().height+ selection.getOutlineThickness() -text.getGlobalBounds().height)/2));
		change.setPosition(movetextkey.x-change_pos_x, selection.getPosition().y);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			selected.setOutlineColor(Color::Red);
			changed.setOutlineColor(Color::Red);
			changed.setFillColor(Color::Red);
			selected.setPosition(selection.getPosition());
			changed.setPosition(change.getPosition());
		}
		return true;
	}
	else
	{
		selection.setOutlineColor(Color::Transparent);
		change.setOutlineColor(Color::Transparent);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			changed.setFillColor(Color::Transparent);
			changed.setOutlineColor(Color::Transparent);
			selected.setOutlineColor(Color::Transparent);
		}
		return false;
	}
}

void options::selectiondisplay(RenderWindow &window)
{
	if (mouseontextselection(window, moveup, moveupkey) == false)
		if (mouseontextselection(window, movedown, movedownkey) == false)
			if (mouseontextselection(window, moveleft, moveleftkey) == false)
				if (mouseontextselection(window, moveright, moverightkey) == false)
					if (mouseontextselection(window, sprint, sprintkey) == false)
						mouseontextselection(window, firemode, firemodekey);
}

bool options::ischanged(Text &text)
{
	if (changed.getFillColor() == (Color::Red) && (selected.getPosition().y+(longestkey.getGlobalBounds().height + selection.getOutlineThickness() - text.getGlobalBounds().height) / 2) == text.getGlobalBounds().top)
		return true;
	else
		return false;
}

void options::default()
{
	keyup = 22;
	keydown = 18;
	keyleft = 0;
	keyright = 3;
	keysprint = 38;
	keyfiremode = 5;
	save();
	read();
}

void options::movelanguage(bool direction, RenderWindow &window)
{
	string text;
	int longest;
	ifstream lang;
	lang.open("settings\\language.dat");
	if (lang.is_open() == 1)
	{
		getline(lang, text);
		lang.close();
	}
	if (direction == false)
	{
		ofstream languagesave;
		languagesave.open("settings\\language.dat");
		if (languagesave.is_open() == 1)
		{
			if (stringint(text) >= 2)
			{
				languagesave << intstring(stringint(text) - 1);
			}
			else
			{
				languagesave << intstring(numberoflangauges());
			}
			languagesave.close();
		}
	}
	else
	{
		ofstream languagesave;
		languagesave.open("settings\\language.dat");
		if (languagesave.is_open() == 1)
		{
			if (stringint(text) < numberoflangauges())
			{
				languagesave << intstring(stringint(text) + 1);
			}
			else
			{
				languagesave << intstring(1);
			}
			languagesave.close();
		}
	}
	load(language());
	positioning(window);
}

int options::display(RenderWindow &window)
{
	load(language());
	positioning(window);
	positioning(window);
	read();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			selectiondisplay(window);
			if (event.type == sf::Event::MouseButtonPressed && mouseontext(window, back))
			{
				back.setFillColor(Color(80, 0, 0));
				window.draw(back);
				window.display();
				while (Mouse::isButtonPressed(Mouse::Left));
				if (mouseontext(window, back))
					return 1;
			}
			if (event.type == sf::Event::MouseButtonPressed && mouseontext(window, savetext))
			{
				savetext.setFillColor(Color(80, 0, 0));
				window.draw(savetext);
				window.display();
				while (Mouse::isButtonPressed(Mouse::Left));
				if (mouseontext(window, savetext))
				{
					save();
					if (altialiasingchanged() == true)
						return 2;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && mouseontext(window, defaulttext))
			{
				defaulttext.setFillColor(Color(80, 0, 0));
				window.draw(defaulttext);
				window.display();
				while (Mouse::isButtonPressed(Mouse::Left));
				if (mouseontext(window, defaulttext))
				default();
			}
			if (event.type == sf::Event::MouseButtonPressed && mouseonshapecircle(window, leftlanguage))
			{
				leftlanguage.setFillColor(Color(80,0,0));
				window.draw(leftlanguage);
				window.display();
				while (Mouse::isButtonPressed(Mouse::Left));
				leftlanguage.setFillColor(Color::White);
				if (mouseonshapecircle(window, leftlanguage))
					movelanguage(false, window);
			}
			if (event.type == sf::Event::MouseButtonPressed && mouseonshapecircle(window, rightlanguage))
			{
				leftlanguage.setFillColor(Color(80, 0, 0));
				window.draw(rightlanguage);
				window.display();
				while (Mouse::isButtonPressed(Mouse::Left));
				rightlanguage.setFillColor(Color::White);
				if (mouseonshapecircle(window, rightlanguage))
					movelanguage(true, window);
			}
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed && ischanged(moveup)==true)
			{
				setstring(moveupkey, event.key.code, 1);
			}
			if (event.type == Event::KeyPressed && ischanged(movedown) == true)
			{
				setstring(movedownkey, event.key.code, 2);
			}
			if (event.type == Event::KeyPressed && ischanged(moveleft) == true)
			{
				setstring(moveleftkey, event.key.code, 3);
			}
			if (event.type == Event::KeyPressed && ischanged(moveright) == true)
			{
				setstring(moverightkey, event.key.code, 4);
			}
			if (event.type == Event::KeyPressed && ischanged(sprint) == true)
			{
				setstring(sprintkey, event.key.code, 5);
			}
			if (event.type == Event::KeyPressed && ischanged(firemode) == true)
			{
				setstring(firemodekey, event.key.code, 6);
			}
			if (event.type == sf::Event::MouseButtonPressed && mouseonshaperectangle(window, antialiasingcase))
			{
				antialiasingcaselevel.setFillColor(Color(80, 0, 0));
				while (Mouse::isButtonPressed(Mouse::Left))
					antialiasingslidermove(window);
				antialiasingcaselevel.setFillColor(Color::White);
			}
			if (event.type == sf::Event::MouseButtonPressed && mouseonshaperectangle(window, volumecase))
			{
				volumecaselevel.setFillColor(Color(80, 0, 0));
				while (Mouse::isButtonPressed(Mouse::Left))
					volumeslidermove(window);
				volumecaselevel.setFillColor(Color::White);
				shotsound.setVolume(stringint(volumetextvalue.getString()));
				shotsound.play();
			}

		}
		mouseontext(window, back);
		mouseontext(window, savetext);
		mouseontext(window, defaulttext);
		mouseonshapecircle(window, leftlanguage);
		mouseonshapecircle(window, rightlanguage);
		if (mouseonshaperectangle(window, antialiasingcase))
		{
			antialiasingcaselevel.setFillColor(Color::Red);
		}
		else
			antialiasingcaselevel.setFillColor(Color::White);
		if (mouseonshaperectangle(window, volumecase))
			volumecaselevel.setFillColor(Color::Red);
		else
			volumecaselevel.setFillColor(Color::White);
		if (mouseonshaperectangle(window, fullscreen_frame))
		{
			fullscreen_frame.setFillColor(Color::Red);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				fullscreen_frame.setFillColor(Color(80,0,0));
				window.clear(background);
				draw(window);
				window.display();
				while (Mouse::isButtonPressed(Mouse::Left));
				if (fullscreen_state == 2)
				{
					fullscreen_state = 3;
					fullscreen_frame.setFillColor(Color::White);

				}
				else
				{
					fullscreen_state = 2;
					fullscreen_frame.setFillColor(Color::Transparent);
				}
				string text;
				ifstream settings;
				settings.open("settings\\graphics.dat");
				if (settings.is_open() == 1)
				{
					getline(settings, text);
				}
				ofstream graphics;
				graphics.open("settings\\graphics.dat");
				graphics << text << endl;
				graphics << fullscreen_state << endl;
				graphics.close();
				return 2;
			}
		}
		else
		{
			if(fullscreen_state == 2)
				fullscreen_frame.setFillColor(Color::Transparent);
			else
				fullscreen_frame.setFillColor(Color::White);
		}
		window.clear(background);
		draw(window);
		window.display();
	}

}