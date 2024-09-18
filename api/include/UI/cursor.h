#ifndef API_UI_CURSOR_H_
#define API_UI_CURSOR_H_
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>



class Cursor : public sf::Drawable
{
private:
	sf::Sprite cursor_sprite_;
	bool is_default_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//constructor
	Cursor();

	//move cursor
	void MoveCursor(const sf::Window& window);

	//swap texture
	void SwapTexture();

	//Set ----------------------
	void set_custom_cursor();
	void set_default_cursor();

	//Get ----------------------
	sf::Vector2f position() const;
};
#endif