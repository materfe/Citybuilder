#ifndef API_GAMEPLAY_TILE_TYPE_CUT_TREES_H_
#define API_GAMEPLAY_TILE_TYPE_CUT_TREES_H_

#include "graphics/drawing_the_entity.h"


class CutTree : public DrawingEntity
{
private:


public:
	explicit CutTree(const sf::Vector2f pos) : DrawingEntity(pos)
	{
		DefineTexture();
	}

	void DefineTexture() override;

	void set_texture(const ResourceManager::Resource& resource);

	//Get ------------------------
	sf::Vector2f position() const;
};




#endif //API_GAMEPLAY_TILE_TYPE_CUT_TREES_H_
