#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
class editor
{
	public:
		editor();
		int display(RenderWindow &window, bool mode);
	private:
		Vector2f borders(Vector2f position, int width, int height, RenderWindow &window);
		int numberofobstacles;
		vector <RectangleShape> obstacle;
		void save(RenderWindow &window);
		RectangleShape safepos_left;
		RectangleShape safepos_right;
		RectangleShape row;
		RectangleShape column;
		RectangleShape frame;
		RectangleShape menu_frame;
		bool mouseonsafe(RenderWindow &window, RectangleShape &shape);
		bool mouseonshape(RenderWindow &window, FloatRect boundingBox);
		bool mouseonobstacle(RenderWindow &window, RectangleShape &shape);
		void create(RenderWindow &window);
		Vector2f move(RenderWindow &window, Vector2f grab, RectangleShape shape);
		void draw(RenderWindow &window);
		void open(RenderWindow &window);
		int modifier_thickness;
		bool flag;
		void positioning(RenderWindow &window);
		int obstacle_min_size;
		Color obstacle_color, obstacle_color_click, obstacle_color_on_hover;
};