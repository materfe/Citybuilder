#ifndef API_GRAPHICS_TILE_H_
#define API_GRAPHICS_TILE_H_
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "resource_manager.h"

class Tile : public sf::Drawable
{
private:
	sf::Sprite sprite_;
	bool is_walkable_;
	bool allow_buildings_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//constructor
	Tile(const ResourceManager::Resource& resource, sf::Vector2f position, bool is_walkable, bool allow_buildings);
	

	//Get ------------------------------
	bool is_Walkable() const;
	bool allow_buildings() const;
	sf::Vector2f position() const;

	//Set ------------------------------
	void set_texture(const sf::Texture& texture);
	void set_is_walkable(bool is_walkable);
	void set_allow_building(bool is_buildable);
};


#endif
