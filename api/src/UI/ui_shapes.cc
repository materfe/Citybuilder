#include "UI/ui_shapes.h"

void UiShapes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& s : all_shapes_)
	{
		target.draw(s, states);
	}
	for (auto& t : all_texts_)
	{
		target.draw(t, states);
	}
}

UiShapes::UiShapes()
{
	constexpr size_t max_capacity = 500;

	all_shapes_.reserve(max_capacity);
	all_texts_.reserve(max_capacity);
}

//set and add
void UiShapes::SetAndAddAShape(const sf::Vector2f position,const sf::Vector2f size, const ResourceManager::Resource& resource)
{
	sf::RectangleShape new_shape;
	new_shape.setTexture(&ResourceManager::Get().Texture(resource));
	new_shape.setPosition(position);
	new_shape.setSize(size);

	all_shapes_.emplace_back(new_shape);
}
//set and add
void UiShapes::SetAndAddAText(const sf::Vector2f position, const std::string& string)
{
	sf::Text new_text;
	new_text.setFont(ResourceManager::Get().Font(ResourceManager::FontsEnum::kArial));
	new_text.setString(string);
	new_text.setPosition(position);
	new_text.setCharacterSize(16.0f);
	new_text.setColor(sf::Color::Black);

	all_texts_.emplace_back(new_text);
}
