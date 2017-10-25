#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
using namespace sf;
using namespace std;
class weapon
{
	private:
		RectangleShape weaponShape;
		RectangleShape weaponBarrel;
		RectangleShape weaponChamber;
		RectangleShape weaponBody;
		int FireCountMove;
		bool FireFinished;
		bool MousePressed;
		bool autofire;
		bool firebutton;
		Text mode;
		Text type;
		Font font;
		Keyboard::Key keyfiremode;
		int stringint(string number);
		SoundBuffer shot;
		Sound shotsound;
	public:
		weapon();
		void display(RenderWindow &window, Vector2f user);
		void fireanimation();
		void fireactionmouse();
		void read();
};