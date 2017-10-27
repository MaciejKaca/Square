#include "editor.h"
#include "character.h"
#include "weapon.h"
#include "Text_input.h"
#include "help.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include "save_frame.h"
using namespace sf;
using namespace std;
text_input map_name;
help help_frame;
save_frame save_button;
editor::editor()
{
	numberofobstacles = 0;
	safepos_left.setFillColor(Color::Red);
	safepos_right.setFillColor(Color::Red);
	row.setFillColor(Color::Blue);
	column.setFillColor(Color::Blue);
	frame.setFillColor(Color::Transparent);
	menu_frame.setFillColor(Color::Blue);
	obstacle_color = Color::Black;
	obstacle_color_click = Color(204, 0, 204);
	obstacle_color_on_hover = Color(204,0,255);
}

float stringint(string number)
{
	return atof(number.c_str());
}

void editor::positioning(RenderWindow &window)
{
	menu_frame.setSize(Vector2f(window.getSize().x, (11.25 * window.getSize().y) / 100));
	menu_frame.setPosition(Vector2f(0, window.getSize().y - menu_frame.getGlobalBounds().height));
	safepos_left.setSize(Vector2f(ceil((7.8*window.getSize().x)/100), ceil((13.8*window.getSize().y)/100)));
	safepos_left.setPosition(Vector2f(0, ((window.getSize().y - menu_frame.getGlobalBounds().height) / 2) - safepos_left.getGlobalBounds().height / 2));
	safepos_right.setSize(safepos_left.getSize());
	safepos_right.setPosition(Vector2f((window.getSize().x - safepos_right.getGlobalBounds().width), ((window.getSize().y - menu_frame.getGlobalBounds().height) / 2) - safepos_left.getGlobalBounds().height / 2));
	row.setSize(Vector2f(window.getSize().x, 1));
	column.setSize(Vector2f(1, window.getSize().y));
	modifier_thickness = (1.38*window.getSize().y)/100;
	obstacle_min_size = (3.125*window.getSize().x) / 100;
	help_frame.setSize((80 * menu_frame.getGlobalBounds().height) / 100);
	help_frame.setPosition(Vector2f(menu_frame.getPosition().x + 10, menu_frame.getPosition().y + 10));
	help_frame.background_size(Vector2f((80 * window.getSize().x) / 100, (80 * window.getSize().y - menu_frame.getGlobalBounds().height) / 100));
	help_frame.background_position(Vector2f((window.getSize().x/2)-(help_frame.background_bounds().width/2), ((window.getSize().y - menu_frame.getGlobalBounds().height) / 2) - (help_frame.background_bounds().height / 2)));
	map_name.setSize(Vector2f((40 * window.getSize().x) / 100,help_frame.getGlobalBounds().height));
	map_name.setPosition(Vector2f(help_frame.getGlobalBounds().width + help_frame.getPosition().x + (1 * window.getSize().x) / 100, help_frame.getPosition().y));
	save_button.setSize(help_frame.getGlobalBounds().width);
	save_button.setPosition(Vector2f(map_name.getGlobalBounds().width+map_name.getPosition().x+ (1 * window.getSize().x) / 100, help_frame.getPosition().y));
}

void editor::create(RenderWindow &window)
{
	RectangleShape new_obstacle;
	int mousex = Mouse::getPosition(window).x;
	int mousey = Mouse::getPosition(window).y;
	numberofobstacles++;
	new_obstacle.setSize(Vector2f(obstacle_min_size, obstacle_min_size));
	new_obstacle.setPosition(Vector2f(mousex,mousey));
	new_obstacle.setFillColor(Color::Black);
	obstacle.push_back(new_obstacle);
}

bool editor::mouseonsafe(RenderWindow &window, RectangleShape &shape)
{
	FloatRect boundingBox = shape.getGlobalBounds();
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	if (mouse.y < shape.getPosition().y)
		mouse.y += 50;
	if (mouse.x < shape.getPosition().x)
		mouse.x += 50;
	if (boundingBox.contains(mouse))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool editor::mouseonshape(RenderWindow &window, FloatRect boundingBox)
{
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

bool editor::mouseonobstacle(RenderWindow &window, RectangleShape &shape)
{
	FloatRect boundingBox(shape.getPosition().x+modifier_thickness, shape.getPosition().y+ modifier_thickness, shape.getGlobalBounds().width-2*modifier_thickness, shape.getGlobalBounds().height-2*modifier_thickness);
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

Vector2f editor::borders(Vector2f position, int width, int height, RenderWindow &window)
{
	Vector2f positions = position;
	if (position.y <= 0 || position.y + height >= window.getSize().y-menu_frame.getGlobalBounds().height)
	{
		if (position.y+height/2 < ((window.getSize().y - menu_frame.getGlobalBounds().height) / 2))
			positions = Vector2f(position.x, 0);
		else
			positions = Vector2f(position.x, window.getSize().y - menu_frame.getGlobalBounds().height - height);
	}
	if (position.x < 0 || position.x > window.getSize().x - width)
	{
		if (position.x + width/2 < window.getSize().x/2)
			positions = Vector2f(0, positions.y);
		else
			positions = Vector2f(window.getSize().x - width, positions.y);
	}
	return positions;
}

Vector2f editor::move(RenderWindow &window, Vector2f grab, RectangleShape shape)
{
	int i;
	bool flag = false;
	Vector2f mouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	RectangleShape testshape;
	testshape.setSize(Vector2f(shape.getGlobalBounds().width, shape.getGlobalBounds().height));
	testshape.setPosition(Vector2f(mouse.x - grab.x, mouse.y - grab.y));
	if (mouse.x <= window.getSize().x && mouse.x >= 0 && mouse.y >= 0 && mouse.y <= window.getSize().y)
	{
		if (!testshape.getGlobalBounds().intersects(safepos_left.getGlobalBounds()) &&
			!testshape.getGlobalBounds().intersects(safepos_right.getGlobalBounds()))
		{
			testshape.setPosition(borders(Vector2f(mouse.x - grab.x, mouse.y - grab.y), testshape.getGlobalBounds().width, testshape.getGlobalBounds().height, window));
		}
		if (testshape.getGlobalBounds().intersects(safepos_left.getGlobalBounds()) ||
			testshape.getGlobalBounds().intersects(safepos_right.getGlobalBounds()))
		{
			if (shape.getPosition().x >= safepos_left.getGlobalBounds().width &&
				shape.getPosition().x + testshape.getGlobalBounds().width <= safepos_right.getPosition().x)
			{
				if (testshape.getPosition().x+testshape.getGlobalBounds().width/2 < window.getSize().x / 2)
				{
					testshape.setPosition(borders(Vector2f(safepos_left.getPosition().x + safepos_left.getGlobalBounds().width, mouse.y - grab.y), testshape.getGlobalBounds().width, testshape.getGlobalBounds().height, window));
				}
				else
				{
					testshape.setPosition(borders(Vector2f(safepos_right.getPosition().x - testshape.getGlobalBounds().width, mouse.y - grab.y), testshape.getGlobalBounds().width, testshape.getGlobalBounds().height, window));
				}
			}
			else
			{
				if (testshape.getPosition().y < safepos_left.getPosition().y)
				{
					testshape.setPosition(borders(Vector2f(mouse.x - grab.x, safepos_left.getPosition().y - testshape.getGlobalBounds().height), testshape.getGlobalBounds().width, testshape.getGlobalBounds().height, window));
				}
				if (testshape.getPosition().y >= safepos_left.getPosition().y)
				{
					testshape.setPosition(borders(Vector2f(mouse.x - grab.x, safepos_left.getPosition().y + safepos_left.getGlobalBounds().height), testshape.getGlobalBounds().width, testshape.getGlobalBounds().height, window));
				}
			}
		}
		return testshape.getPosition();
	}
	else
		return shape.getPosition();
}

void editor::open(RenderWindow &window)
{
	ifstream map;
	string data;
	RectangleShape new_obstacle;
	map.open("maps\\map.dat");
	if (map.is_open() == 1)
	{
		getline(map, data);
		int number = stringint(data);
		for (int i = 0; i < number; i++)
		{
			getline(map, data);
			new_obstacle.setPosition(Vector2f((stringint(data)*window.getSize().x) / 100, 0));
			getline(map, data);
			new_obstacle.setPosition(Vector2f(new_obstacle.getPosition().x, (stringint(data)*window.getSize().y) / 100));
			getline(map, data);
			new_obstacle.setSize(Vector2f((stringint(data)*window.getSize().x)/100, 0));
			getline(map, data);
			new_obstacle.setSize(Vector2f(new_obstacle.getGlobalBounds().width, (stringint(data)*window.getSize().y)/100));
			obstacle.push_back(new_obstacle);
		}
		map.close();
	}
}

void editor::save(RenderWindow &window)
{
	if (map_name.getString().length() > 0)
	{
		ofstream map;
		string name;
		name = "maps\\" + map_name.getString() + ".map";
		map.open(name);
		map << obstacle.size() << endl;
		for (int i = 0; i < obstacle.size(); i++)
		{
			map << (obstacle.at(i).getPosition().x * 100) / window.getSize().x << endl;
			map << (obstacle.at(i).getPosition().y * 100) / window.getSize().y << endl;
			map << (obstacle.at(i).getGlobalBounds().width * 100) / window.getSize().x << endl;
			map << (obstacle.at(i).getGlobalBounds().height * 100) / window.getSize().y << endl;
		}
		map.close();
	}
	else
	{
		map_name.setString("Empty!!!");
		map_name.draw(window);
		window.display();
		while (Mouse::isButtonPressed(sf::Mouse::Left));
		map_name.setString("");
	}
}

void editor::draw(RenderWindow &window)
{
	int i;
	window.clear(Color::White);
	for (i = 1; i <= ((3.125*window.getSize().x)/100); i++)
	{
		row.setPosition(Vector2f(0, i * ((3.125*window.getSize().x) / 100) - row.getGlobalBounds().height / 2));
		window.draw(row);
	}
	for (i = 1; i <= ceil((3.125*window.getSize().x) / 100); i++)
	{
		column.setPosition(Vector2f(i * ((3.125*window.getSize().x) / 100) - column.getGlobalBounds().width / 2, 0));
		window.draw(column);
	}
	window.draw(safepos_left);
	window.draw(safepos_right);
	for (i = 0; i < obstacle.size(); i++)
	{
		window.draw(obstacle.at(i));
	}
	for (i = 0; i < obstacle.size(); i++)
	{
		if (obstacle.at(i).getFillColor() == obstacle_color_on_hover || obstacle.at(i).getFillColor() == obstacle_color_click)
		{
			window.draw(obstacle.at(i));
			break;
		}
	}
	if (flag == true)
		window.draw(frame);
	window.draw(menu_frame);
	help_frame.display(window);
	map_name.draw(window);
	save_button.display(window);
	window.display();
}

Vector2f grab(RenderWindow &window, RectangleShape shape)
{
	return Vector2f(Mouse::getPosition(window).x - shape.getPosition().x, Mouse::getPosition(window).y - shape.getPosition().y);
}

int editor::display(RenderWindow &window, bool mode)
{
	help_frame.load();
	obstacle.clear();
	if (mode == 1)
	{
		open(window);
	}
	int i;
	RectangleShape testshape;
	positioning(window);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
			{
				while (Mouse::isButtonPressed(sf::Mouse::Right));
				if(!mouseonsafe(window,safepos_left) && !mouseonsafe(window, safepos_right))
					create(window);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				return 1;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace && map_name.getColor() == Color::Red)
			{
					map_name.remove();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (mouseonshape(window, save_button.getGlobalBounds()))
				{
					save(window);
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (mouseonshape(window, map_name.getGlobalBounds()))
				{
					map_name.setColor(Color::Red);
				}
				else
				{
					map_name.setColor(Color::White);
				}
			}
			if (event.type == sf::Event::KeyPressed && map_name.getColor() == Color::Red)
			{
				if (event.key.code >= 0 && event.key.code <= 25)
				{
					if (Keyboard::isKeyPressed(Keyboard::LShift))
					{
						map_name.add(static_cast<char>(event.key.code + 65));
					}
					else
					{
						map_name.add(static_cast<char>(event.key.code + 97));
					}
				}
				else if (event.key.code >= 26 && event.key.code <= 35)
				{
					map_name.add(static_cast<char>(event.key.code + 22));
				}
			}
		}
		flag = false;
		for (i = 0; i < obstacle.size(); i++)
		{
			if (mouseonshape(window, obstacle.at(i).getGlobalBounds()))
			{

				obstacle.at(i).setFillColor(obstacle_color_on_hover);
				int selected = i;
				while (mouseonshape(window, obstacle.at(i).getGlobalBounds()))
				{

					Event mouse_shape;
					while (window.pollEvent(mouse_shape))
					{
						if (mouse_shape.type == Event::Closed)
						{
							window.close();
						}
						if (mouse_shape.type == Event::MouseButtonPressed && mouse_shape.mouseButton.button == sf::Mouse::Right)
						{
							while (Mouse::isButtonPressed(sf::Mouse::Right));
							obstacle.erase(obstacle.begin() + selected);
						}
					}
					if (obstacle.size() < selected + 1)
						break;
					flag = false;
					if (obstacle.size() >= selected + 1)
					{
						while (mouseonobstacle(window, obstacle.at(selected)))
						{
							Event mouse_obstacle;
							while (window.pollEvent(mouse_obstacle))
							{
								if (mouse_obstacle.type == Event::Closed)
								{
									window.close();
								}
								if (mouse_obstacle.type == Event::MouseButtonPressed && mouse_obstacle.mouseButton.button == sf::Mouse::Left)
								{
									Vector2f obstacle_grab = grab(window, obstacle.at(selected));
									obstacle.at(selected).setFillColor(obstacle_color_click);
									while (Mouse::isButtonPressed(sf::Mouse::Left))
									{
										Event clicked_obstacle;
										while (window.pollEvent(clicked_obstacle))
										{
											if (clicked_obstacle.type == Event::Closed)
											{
												window.close();
											}
										}
										obstacle.at(selected).setPosition(move(window, obstacle_grab, obstacle.at(selected)));
										draw(window);
									}
									obstacle.at(selected).setFillColor(obstacle_color_on_hover);
								}
								if (mouse_obstacle.type == Event::MouseButtonPressed && mouse_obstacle.mouseButton.button == sf::Mouse::Right)
								{
									while (Mouse::isButtonPressed(sf::Mouse::Right));
									obstacle.erase(obstacle.begin() + selected);
								}
							}
							if (obstacle.size() < selected + 1)
								break;
							draw(window);
						}
						if (obstacle.size() < selected + 1)
							break;
						if (obstacle.size() >= selected + 1) {
							if (Mouse::getPosition(window).y < obstacle.at(selected).getPosition().y + modifier_thickness
								&& Mouse::getPosition(window).x > obstacle.at(selected).getPosition().x + modifier_thickness
								&& Mouse::getPosition(window).x < obstacle.at(selected).getPosition().x - modifier_thickness + obstacle.at(selected).getGlobalBounds().width)
							{

								frame.setPosition(obstacle.at(selected).getPosition());
								frame.setSize(Vector2f(obstacle.at(selected).getGlobalBounds().width, modifier_thickness));
								frame.setFillColor(Color(104, 0, 205));
								flag = true;
								if (Mouse::isButtonPressed(sf::Mouse::Left))
								{
									frame.setFillColor(Color(104, 0, 105));
									Vector2f frame_grab = grab(window, frame);
									int bottom = obstacle.at(selected).getPosition().y + obstacle.at(selected).getGlobalBounds().height;
									while (Mouse::isButtonPressed(sf::Mouse::Left))
									{
										frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x, move(window, frame_grab, frame).y));
										obstacle.at(selected).setSize(Vector2f(obstacle.at(selected).getGlobalBounds().width,
											bottom - frame.getPosition().y));
										obstacle.at(selected).setPosition(Vector2f(obstacle.at(selected).getPosition().x, frame.getPosition().y));
										if (obstacle.at(selected).getGlobalBounds().intersects(safepos_left.getGlobalBounds()))
										{
											frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x, safepos_left.getPosition().y + safepos_left.getGlobalBounds().height));
											obstacle.at(selected).setSize(Vector2f(obstacle.at(selected).getGlobalBounds().width,
												bottom - frame.getPosition().y));
											obstacle.at(selected).setPosition(Vector2f(obstacle.at(selected).getPosition().x, frame.getPosition().y));

										}
										if (obstacle.at(selected).getGlobalBounds().height < obstacle_min_size || frame.getPosition().y>bottom)
										{
											obstacle.at(selected).setSize(Vector2f(obstacle.at(selected).getGlobalBounds().width, obstacle_min_size));
											obstacle.at(selected).setPosition(Vector2f(obstacle.at(selected).getPosition().x, bottom - obstacle.at(selected).getGlobalBounds().height));
											frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x, obstacle.at(selected).getPosition().y));
										}
										draw(window);
									}
								}
							}
							if (Mouse::getPosition(window).y > obstacle.at(selected).getPosition().y + obstacle.at(selected).getGlobalBounds().height - modifier_thickness
								&& Mouse::getPosition(window).x > obstacle.at(selected).getPosition().x + modifier_thickness
								&& Mouse::getPosition(window).x < obstacle.at(selected).getPosition().x - modifier_thickness + obstacle.at(selected).getGlobalBounds().width)
							{
								frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x, obstacle.at(selected).getPosition().y + obstacle.at(selected).getGlobalBounds().height - modifier_thickness));
								frame.setSize(Vector2f(obstacle.at(selected).getGlobalBounds().width, modifier_thickness));
								frame.setFillColor(Color(104, 0, 205));
								flag = true;
								if (Mouse::isButtonPressed(sf::Mouse::Left))
								{
									frame.setFillColor(Color(104, 0, 105));
									Vector2f frame_grab = grab(window, frame);
									while (Mouse::isButtonPressed(sf::Mouse::Left))
									{

										frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x, move(window, frame_grab, frame).y));
										obstacle.at(selected).setSize(Vector2f(obstacle.at(selected).getGlobalBounds().width,
											frame.getPosition().y - obstacle.at(selected).getPosition().y + modifier_thickness));
										if (obstacle.at(selected).getGlobalBounds().intersects(safepos_left.getGlobalBounds()))
										{
											frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x, safepos_left.getPosition().y - modifier_thickness));
											obstacle.at(selected).setSize(Vector2f(obstacle.at(selected).getGlobalBounds().width,
												frame.getPosition().y - obstacle.at(selected).getPosition().y + modifier_thickness));
										}
										if (obstacle.at(selected).getGlobalBounds().height < obstacle_min_size || frame.getPosition().y < obstacle.at(selected).getPosition().y)
										{
											obstacle.at(selected).setSize(Vector2f(obstacle.at(selected).getGlobalBounds().width, obstacle_min_size));
											frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x, obstacle.at(selected).getPosition().y - modifier_thickness + obstacle.at(selected).getGlobalBounds().height));
										}
										draw(window);
									}
								}
							}
							if (Mouse::getPosition(window).x < obstacle.at(selected).getPosition().x + modifier_thickness
								&& Mouse::getPosition(window).y > obstacle.at(selected).getPosition().y + modifier_thickness
								&& Mouse::getPosition(window).y < obstacle.at(selected).getPosition().y + obstacle.at(selected).getGlobalBounds().height - modifier_thickness)
							{
								frame.setPosition(obstacle.at(selected).getPosition());
								frame.setSize(Vector2f(modifier_thickness, obstacle.at(selected).getGlobalBounds().height));
								frame.setFillColor(Color(104, 0, 205));
								flag = true;
								if (Mouse::isButtonPressed(sf::Mouse::Left))
								{
									frame.setFillColor(Color(104, 0, 105));
									Vector2f frame_grab = grab(window, frame);
									int left = obstacle.at(selected).getPosition().x + obstacle.at(selected).getGlobalBounds().width;
									while (Mouse::isButtonPressed(sf::Mouse::Left))
									{
										frame.setPosition(Vector2f(move(window, frame_grab, frame).x, obstacle.at(selected).getPosition().y));
										obstacle.at(selected).setSize(Vector2f(left - frame.getPosition().x, obstacle.at(selected).getGlobalBounds().height));
										obstacle.at(selected).setPosition(Vector2f(frame.getPosition().x, obstacle.at(selected).getPosition().y));
										if (obstacle.at(selected).getGlobalBounds().width < obstacle_min_size || frame.getPosition().x>left)
										{
											obstacle.at(selected).setSize(Vector2f(obstacle_min_size, obstacle.at(selected).getGlobalBounds().height));
											obstacle.at(selected).setPosition(Vector2f(left - obstacle.at(selected).getGlobalBounds().width, obstacle.at(selected).getPosition().y));
											frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x, obstacle.at(selected).getPosition().y));
										}
										draw(window);
									}
								}
							}
							if (Mouse::getPosition(window).x > obstacle.at(selected).getPosition().x + obstacle.at(selected).getGlobalBounds().width - modifier_thickness
								&& Mouse::getPosition(window).y > obstacle.at(selected).getPosition().y + modifier_thickness
								&& Mouse::getPosition(window).y < obstacle.at(selected).getPosition().y + obstacle.at(selected).getGlobalBounds().height - modifier_thickness)
							{
								frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x + obstacle.at(selected).getGlobalBounds().width - modifier_thickness, obstacle.at(selected).getPosition().y));
								frame.setSize(Vector2f(modifier_thickness, obstacle.at(selected).getGlobalBounds().height));
								frame.setFillColor(Color(104, 0, 205));
								flag = true;
								if (Mouse::isButtonPressed(sf::Mouse::Left))
								{
									frame.setFillColor(Color(104, 0, 105));
									Vector2f frame_grab = grab(window, frame);
									while (Mouse::isButtonPressed(sf::Mouse::Left))
									{

										frame.setPosition(Vector2f(move(window, frame_grab, frame).x, obstacle.at(selected).getPosition().y));
										obstacle.at(selected).setSize(Vector2f(frame.getPosition().x - obstacle.at(selected).getPosition().x + modifier_thickness, obstacle.at(selected).getGlobalBounds().height));
										if (obstacle.at(selected).getGlobalBounds().width < obstacle_min_size || frame.getPosition().x < obstacle.at(selected).getPosition().x)
										{
											obstacle.at(selected).setSize(Vector2f(obstacle_min_size, obstacle.at(selected).getGlobalBounds().height));
											frame.setPosition(Vector2f(obstacle.at(selected).getPosition().x + obstacle.at(selected).getGlobalBounds().width - modifier_thickness, obstacle.at(selected).getPosition().y));
										}
										draw(window);
									}
								}
							}
						}
						draw(window);
					}
				}
			}
			else
			{
				obstacle.at(i).setFillColor(Color::Black);
			}
		}
		help_frame.onShape(window);
		save_button.onShape(window);
		draw(window);
	}
}