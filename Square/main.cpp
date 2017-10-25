#include "character.h"
#include "weapon.h"
#include "menu.h"
#include "options.h"
#include "editormenu.h"
#include "editor.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
character player;
weapon rifle;
menu mainmenu;
options option;
editormenu mapeditormenu;
editor mapeditor;
bool quit;
int main()
{	
		RenderWindow window(VideoMode(1280,720), "Square", 1 << option.screen_mode(), option.windowsettings());
		window.setFramerateLimit(150);
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			switch (mainmenu.menudisplay(window))
			{
				case 1:
					player.read();
					rifle.read();
					while (!Keyboard::isKeyPressed(Keyboard::Escape))
					{
						Event movement;
						while (window.pollEvent(movement))
						{
							if (movement.type == Event::Closed)
								window.close();
						}
						window.clear(Color(255, 255, 255));
						player.display(window);
						rifle.display(window, player.position());
						window.display();
					}
					break;
				case 2:
					quit = false;
					while (quit == false)
					{
						switch (mapeditormenu.display(window))
						{
						case 3:
							quit = true;
							break;
						case 1:
							mapeditor.display(window, 0);
							break;
						case 2:
							mapeditor.display(window, 1);
							break;
						default:
							break;
						}
						break;
					}
					break;
				case 3:
					quit = false;
					while (quit == false)
					{
						switch (option.display(window))
						{
						case 1:
							quit = true;
							break;
						case 2:
							window.close();
							window.create(VideoMode(1280, 720), "Square", 1 << option.screen_mode(), option.windowsettings());
							window.setFramerateLimit(150);
							break;
						default:
							break;
						}
					}
					break;
				case 4:
					window.close();
					break;
				default:
					std::cout << "Error01";
			}
		}
	return 0;
}