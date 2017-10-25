#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;
class menu
{
	private:
		ContextSettings settings;
		Color background;
		Text tittle;
		Text play;
		Text options;
		Text autor;
		Text exit;
		Text editor;
		Font retro;
		RectangleShape line;
		bool mouseontext(RenderWindow &window, Text &text);
		int choice;
		void load(string language);
		string language();
		void positioning(RenderWindow &window);
		int textsize(int height);
	public:
		menu();
		int menudisplay(RenderWindow &window);
		bool choiced;
};