#ifndef API_GAMEPLAY_NATURE_TILE_TYPE_TREES_H_
#define API_GAMEPLAY_NATURE_TILE_TYPE_TREES_H_
#include "graphics/drawing_the_entity.h"


class Tree : public DrawingEntity
{
private:


public:
	explicit Tree(const sf::Vector2f pos) : DrawingEntity(pos)
	{
		DefineTexture();
	}

	void DefineTexture() override;

	void set_texture(const ResourceManager::Resource& resource);

	//Get ------------------------
	sf::Vector2f position() const;
};




#endif //API_GAMEPLAY_NATURE_TILE_TYPE_TREES_H_