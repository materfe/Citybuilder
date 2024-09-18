#ifndef UI_HOVERED_TILE_H_
#define UI_HOVERED_TILE_H_
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class HoveredTile: public sf::Drawable
{
private:
	sf::RectangleShape tile_shape_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//constructors
	HoveredTile() = default;
	explicit HoveredTile(sf::Vector2f size);
	HoveredTile(const HoveredTile& other) = default;
	HoveredTile& operator=(const HoveredTile& other) = default;

	//allow feedbacks on if tile is buildable or not
	void ChangeColor(sf::Vector2i pos, bool is_active, bool is_buildable);

	//Set -------------------------------
	void set_position(sf::Vector2f position);
	void set_color(sf::Color color);
};




#endif
