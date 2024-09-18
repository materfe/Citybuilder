#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <tracy/Tracy.hpp>
#include <UI/uibutton.h>
#include "graphics/resource_manager.h"

//constructor init
UiButton::UiButton(const sf::Vector2f position, const std::string& name)
{
	SetupButton(position);

	SetupText(position, name);

	is_clicked_once_ = false;
}

/**
 * \brief setup the button and how he looks
 */
void UiButton::SetupButton(const sf::Vector2f position)
{
	//setup button 1 -> generate map
	button_sprite_.setColor(sf::Color::White);
	button_sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kGreyButton));
	button_sprite_.setOrigin(button_sprite_.getLocalBounds().getSize().x / 2.0f, button_sprite_.getLocalBounds().getSize().y / 2.0f);
	button_sprite_.setPosition(position);
}

/**
 * \brief setup text on the button and how it looks
 */
void UiButton::SetupText(const sf::Vector2f position, const std::string& name)
{
	constexpr int offset = 10;

	//position of the text based on the button's position
	const auto text_position = sf::Vector2f(position.x - button_sprite_.getGlobalBounds().getSize().x / 2.0f + offset,
		position.y - button_sprite_.getGlobalBounds().getSize().y / 2.0f + offset);

	//text
	button_text_.setFont(ResourceManager::Get().Font(ResourceManager::FontsEnum::kButtonFont));
	button_text_.setString(name);
	button_text_.setCharacterSize(24);
	button_text_.setFillColor(sf::Color::Black);
	button_text_.setStyle(sf::Text::Bold);
	button_text_.setPosition(text_position);
}

//inplemantation of the draw function 
void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(button_sprite_, states);
	target.draw(button_text_, states);
	target.draw(simbol_shape_, states);
}

//handle event init
void UiButton::HandleEvent(const sf::Event& event)
{

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	//button 1
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			const auto mouse_x = static_cast<float>(event.mouseButton.x);
			const auto mouse_y = static_cast<float>(event.mouseButton.y);

			if (button_sprite_.getGlobalBounds().contains(mouse_x, mouse_y))
			{
				set_scale(1.0f, 1.0f);
				button_sprite_.setColor(sf::Color::White);
			}
		}
	}
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			const auto mouse_x = static_cast<float>(event.mouseButton.x);
			const auto mouse_y = static_cast<float>(event.mouseButton.y);

			if (button_sprite_.getGlobalBounds().contains(mouse_x, mouse_y))
			{
				set_scale(0.9f, 0.9f);
				button_sprite_.setColor(sf::Color::Green);
				call_back_();
			}
		}
	}
}

void UiButton::PopOtherButton(UiButton& button)
{
	if (button.getScale() == sf::Vector2f(0.0f, 0.0f))
	{
		button.setScale(1.0f, 1.0f);
	}
	else
	{
		button.setScale(0.0f, 0.0f);
	}
}

//setupp shape
void UiButton::SimbolShapeSetup(const ResourceManager::Resource& resource)
{
	const auto offset = sf::Vector2f(shape().getGlobalBounds().getSize().x / 2 - 7, shape().getGlobalBounds().getSize().y / 2 - 7);

	simbol_shape_.setTexture(&ResourceManager::Get().Texture(resource));
	simbol_shape_.setSize(sf::Vector2f(16.0f, 16.0f));
	simbol_shape_.setPosition(shape().getGlobalBounds().getPosition() + offset);
	simbol_shape_.setScale(1.0f, 1.0f);
}


//GET
bool UiButton::is_clicked_once() const
{
	return is_clicked_once_;
}

sf::Sprite UiButton::shape() const
{
	return button_sprite_;
}


//SET
void UiButton::set_scale(const float factor_x, const float factor_y)
{
	button_sprite_.setScale(factor_x, factor_y);
}
void UiButton::set_is_clicked_on()
{
	is_clicked_once_ = true;
}
void UiButton::set_is_clicked_off()
{
	is_clicked_once_ = false;
}
