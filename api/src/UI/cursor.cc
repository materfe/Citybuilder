#include "UI/cursor.h"

#include <SFML/Graphics/Sprite.hpp>

#include "graphics/resource_manager.h"

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(cursor_sprite_, states);
}

//move
void Cursor::MoveCursor(const sf::Window& window)
{
	cursor_sprite_.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

//swap beetween custom and default based on a bool
void Cursor::SwapTexture()
{
	if(is_default_)
	{
		set_custom_cursor();
		is_default_ = false;
	}
	else
	{
		set_default_cursor();
		is_default_ = true;
	}
}

//Cursor
Cursor::Cursor()
{
	is_default_ = true;
}

//set texture to custom (building)
void Cursor::set_custom_cursor()
{
    cursor_sprite_.setTexture(ResourceManager::Get().CursorTexture(ResourceManager::CursorTextures::kCustomCursor));
}

//set texture to default
void Cursor::set_default_cursor()
{
	cursor_sprite_.setTexture(ResourceManager::Get().CursorTexture(ResourceManager::CursorTextures::kDefaultCursor));
}

sf::Vector2f Cursor::position() const
{
	return cursor_sprite_.getGlobalBounds().getPosition();
}
