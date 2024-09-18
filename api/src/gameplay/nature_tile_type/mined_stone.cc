#include "gameplay/nature_tile_type/mined_stone.h"


void MinedStone::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kCutStone));
}

void MinedStone::set_texture(const ResourceManager::Resource& resource)
{
	sprite_.setTexture(ResourceManager::Get().Texture(resource));
}

//GET
sf::Vector2f MinedStone::position() const
{
	return sprite_.getGlobalBounds().getPosition();
}
