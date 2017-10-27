#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;
class text_input
{
	public:
		text_input();
		void setSize(Vector2f size);
		string getString();
		void setPosition(Vector2f position);
		void draw(RenderWindow &window);
		void setColor(Color color);
		void setString(string text);
		void remove();
		void add(char text);
		Vector2f getPosition();
		FloatRect getGlobalBounds();
		Color getColor();
		void empty();
		void load();
	private:
		int lenght();
		int textsize(int height);
		Font retro;
		Text name;
		RectangleShape frame;
		Text test;
		string empty_string;
};