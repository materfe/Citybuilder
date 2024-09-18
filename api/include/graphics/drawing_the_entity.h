#ifndef API_GRAPHICS_DRAWING_THE_ENTITY_H_
#define API_GRAPHICS_DRAWING_THE_ENTITY_H_
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "resource_manager.h"


class DrawingEntity : public sf::Drawable
{
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void SetupDebugShape();
	//shape
	sf::Sprite sprite_;
	//debug shape
	sf::RectangleShape debug_shape_;

public:

	//drawing
	DrawingEntity(sf::Vector2f pos);
	virtual void DefineTexture() = 0;

};


#endif //API_GRAPHICS_DRAWING_THE_ENTITY_H_
