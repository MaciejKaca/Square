#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;
class editormenu
{
	public:
		editormenu();
		int display(RenderWindow &window);
	private:
		int textsize(int height);
		bool mouseontext(RenderWindow &window, Text &text);
		Text newtext;
		Text opentext;
		Text back;
		Text open;
		Text editortext;
		void load(string language);
		string language();
		Font retro;
		void positioning(RenderWindow &window);
};