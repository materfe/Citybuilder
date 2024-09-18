#ifndef API_GAMEPLAY_BUILDINGS_H_
#define API_GAMEPLAY_BUILDINGS_H_
#include "graphics/drawing_the_entity.h"
#include "graphics/resource_manager.h"


class Building : public DrawingEntity
{
public:
	//constructor
	Building(const sf::Vector2f pos) : DrawingEntity(pos)
	{
		DefineTexture();
	}

	void DefineTexture() override;

	void setTexture(const ResourceManager::Resource& resource);
};



#endif
