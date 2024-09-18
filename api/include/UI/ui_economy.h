#ifndef API_UI_UI_ECONOMY_H_
#define API_UI_UI_ECONOMY_H_
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "gameplay/economy_manager.h"


class UiEconomy : public sf::Drawable
{
private:
	sf::Text wood_economy_text_;
	sf::Text stone_economy_text_;
	sf::Sprite wood_shape_;
	sf::Sprite stone_shape_;
	sf::Sprite background_shape_;
	EconomyManager& economy_manager_;
	size_t wood_economy_amount_;
	size_t stone_economy_amount_;
	bool is_clicked_once_;

	

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//constructor
	UiEconomy(EconomyManager& economy);

	//setup ui text
	void SetupUiEconomyText();
	void SetupUiEconomyImage();
};

#endif //API_UI_UI_ECONOMY_H_