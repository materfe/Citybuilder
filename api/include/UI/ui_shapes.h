#ifndef API_UI_UI_SHAPES_H_
#define API_UI_UI_SHAPES_H_
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

#include "graphics/resource_manager.h"


class UiShapes : public sf::Drawable
{
private:

	std::vector<sf::RectangleShape> all_shapes_;
	std::vector<sf::Text> all_texts_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public :
	//constructor
	UiShapes();

	//create and add a shape with parameters
	void SetAndAddAShape(const sf::Vector2f position, const sf::Vector2f size, const ResourceManager::Resource& resource);

	//create and add a text with parameters
	void SetAndAddAText(const sf::Vector2f position, const std::string& string);
};

#endif // API_UI_UI_SHAPES_H_