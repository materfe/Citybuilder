#ifndef API_UI_UIBUTTON_H_
#define API_UI_UIBUTTON_H_
#include <functional>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "graphics/resource_manager.h"


//class that wil make a generate_button_ appear in sfml window
class UiButton : public sf::Drawable, public sf::Transformable 
{
private:
	sf::Sprite button_sprite_;
	sf::Texture button_texture_;
	sf::RectangleShape simbol_shape_;
	bool is_clicked_once_;
	
	//text and font
	sf::Text button_text_;

	//setup for constructor
	void SetupButton(sf::Vector2f position);
	void SetupText(sf::Vector2f position, const std::string& name);

protected:
	//draw function
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//constructors
	UiButton() = default;
	UiButton(sf::Vector2f position, const std::string& name);
	UiButton(const UiButton& other) = default;
	UiButton& operator=(const UiButton& other) = default;

	//function that handle events
	void HandleEvent(const sf::Event& event);

	//set other buttons on or off
	void PopOtherButton(UiButton& button);

	//shape
	void SimbolShapeSetup(const ResourceManager::Resource& resource);

	//Set ---------------------------
	void set_scale(float factor_x, float factor_y);
	void set_is_clicked_on();
	void set_is_clicked_off();

	//GET ---------------------------
	bool is_clicked_once() const;
	sf::Sprite shape() const;

	//call back
	std::function<void()> call_back_;
};





#endif //API_UI_UIBUTTON_H_