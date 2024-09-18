#include "graphics/drawing_the_entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

//draw
void DrawingEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
	//target.draw(debug_shape_, states);
}

void DrawingEntity::SetupDebugShape()
{
	debug_shape_.setPosition(sprite_.getGlobalBounds().getPosition());
	debug_shape_.setSize(sprite_.getGlobalBounds().getSize());
	debug_shape_.setFillColor(sf::Color::Transparent);
	debug_shape_.setOutlineColor(sf::Color::White);
	debug_shape_.setOutlineThickness(-1);
}

DrawingEntity::DrawingEntity(const sf::Vector2f pos)
{
	sprite_.setPosition(pos);

	SetupDebugShape();
}
