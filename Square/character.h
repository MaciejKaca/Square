#pragma once
#include <SFML\Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
class character
{
	public:
		CircleShape characterShape;
		void display(RenderWindow &window);
		Vector2f position();
		character();
		void read();
	private:
		int stringint(string number);
		void left();
		void right();
		void up();
		void down();
		void steering();
		Keyboard::Key keyup;
		Keyboard::Key keydown;
		Keyboard::Key keyleft;
		Keyboard::Key keyright;
		Keyboard::Key keysprint;
		Keyboard::Key test;
};