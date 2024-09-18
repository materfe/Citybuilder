#include "gameplay/nature_tile_type/stone.h"


void Stone::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kStone));
}

void Stone::set_texture(const ResourceManager::Resource& resource)
{
	sprite_.setTexture(ResourceManager::Get().Texture(resource));
}

sf::Vector2f Stone::position() const
{
	return sprite_.getPosition();
}
