#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;
class help
{
	public:
		help();
		void setSize(int size);
		FloatRect getGlobalBounds();
		void setFillColor(Color color);
		void setPosition(Vector2f position);
		void display(RenderWindow &window);
		Vector2f getPosition();
		void onShape(RenderWindow &window);
		void background_size(Vector2f size);
		void background_position(Vector2f position);
		FloatRect background_bounds();
		void load();
	private:
		int textsize(int height);
		Font retro;
		void text_position(Vector2f position, Text &text);
		Text quote;
		RectangleShape frame;
		RectangleShape background;
		Sprite ppm;
		Sprite lpm;
		Texture mouse_L;
		Texture mouse_P;
		Text or[2];
		Text move;
		Text resize;
		Text create;
		Text remove;
		Text PPM_text[2];
		Sprite mouse_sprite;
		Texture coursor;
		RectangleShape obstacle;
		RectangleShape modificator;
};