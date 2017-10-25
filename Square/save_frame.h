#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;
class save_frame
{
public:
	save_frame();
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
	RectangleShape frame;
	Sprite floppy;
	Texture floppy_tex;
};
