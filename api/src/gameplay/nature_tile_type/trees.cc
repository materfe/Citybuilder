#include "gameplay/nature_tile_type/Trees.h"

void Tree::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kTree));
}

void Tree::set_texture(const ResourceManager::Resource& resource) 
{
	sprite_.setTexture(ResourceManager::Get().Texture(resource));
}

sf::Vector2f Tree::position() const
{
	return sprite_.getPosition();
}
