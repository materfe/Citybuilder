#include "UI/ui_economy.h"

#include <tracy/Tracy.hpp>

#include "graphics/resource_manager.h"

//change text
void UiEconomy::SetupUiEconomyText()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	//little calcul
	const auto text_pos = sf::Vector2f(0.0f, 0.0f);

	//setup wood text
	wood_economy_text_.setFont(ResourceManager::Get().Font(ResourceManager::FontsEnum::kArial));
	wood_economy_text_.setCharacterSize(16);
	wood_economy_text_.setFillColor(sf::Color::Black);
	wood_economy_text_.setPosition(sf::Vector2f(text_pos.x + wood_shape_.getGlobalBounds().getSize().x, text_pos.y));
	//setup stone text
	stone_economy_text_.setFont(ResourceManager::Get().Font(ResourceManager::FontsEnum::kArial));
	stone_economy_text_.setCharacterSize(16);
	stone_economy_text_.setFillColor(sf::Color::Black);
	stone_economy_text_.setPosition(sf::Vector2f(text_pos.x + stone_shape_.getGlobalBounds().getSize().x,
		text_pos.y + stone_shape_.getGlobalBounds().getSize().y));


	//set economy and texts
	wood_economy_amount_ = economy_manager_.wood_economy();
	wood_economy_text_.setString(std::to_string(wood_economy_amount_));
	stone_economy_amount_ = economy_manager_.stone_economy();
	stone_economy_text_.setString(std::to_string(stone_economy_amount_));
}

//set images
void UiEconomy::SetupUiEconomyImage()
{
	const auto wood_shape_position = sf::Vector2f(0.0f, 0.0f);
	const auto color = sf::Color::White;



	//wood
	wood_shape_.setPosition(wood_shape_position);
	wood_shape_.setColor(color);
	wood_shape_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kTree));
	//stone
	const auto stone_shape_position = sf::Vector2f(wood_shape_position.x,
		wood_shape_position.y + wood_shape_.getGlobalBounds().getSize().y);
	stone_shape_.setPosition(stone_shape_position);
	stone_shape_.setColor(color);
	stone_shape_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kStone));
	//background
	background_shape_.setPosition(wood_shape_position);
	background_shape_.setColor(color);
	background_shape_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kBackPanel));
}

//draw
void UiEconomy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_shape_, states);
	target.draw(wood_economy_text_, states);
	target.draw(stone_economy_text_, states);
	target.draw(wood_shape_, states);
	target.draw(stone_shape_, states);
}

//constructor
UiEconomy::UiEconomy(EconomyManager& economy) : economy_manager_(economy)
{
	SetupUiEconomyImage();
	SetupUiEconomyText();
}