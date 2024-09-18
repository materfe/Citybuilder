#include "graphics/resource_manager.h"

#include <tracy/Tracy.hpp>

void ResourceManager::LoadAllTextures()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	blank_texture_ = sf::Texture();
	// Textures -----------------
	textures_array_[static_cast<int>(Resource::kYellowButton)].loadFromFile("resources/PNG/button_blue_corner.png");
	textures_array_[static_cast<int>(Resource::kGreyButton)].loadFromFile("resources/PNG/grey_button.png");
	textures_array_[static_cast<int>(Resource::kBuildingSprite)].loadFromFile("resources/PNG/building_sprite.png");
	textures_array_[static_cast<int>(Resource::kTerrainGround)].loadFromFile("resources/PNG/ground.png");
	textures_array_[static_cast<int>(Resource::kWoodHouse)].loadFromFile("resources/PNG/basic_blue_house.png");
	textures_array_[static_cast<int>(Resource::kStoneHouse)].loadFromFile("resources/PNG/wood_house.png");
	textures_array_[static_cast<int>(Resource::kTerrainSunflowerGround)].loadFromFile("resources/PNG/sunflower_ground.png");
	textures_array_[static_cast<int>(Resource::kTerrainBasicGround)].loadFromFile("resources/PNG/basic_ground.png");
	textures_array_[static_cast<int>(Resource::kWoodsMan)].loadFromFile("resources/PNG/woodsman.png");
	textures_array_[static_cast<int>(Resource::kStoneMan)].loadFromFile("resources/PNG/stoneman.png");
	textures_array_[static_cast<int>(Resource::kTree)].loadFromFile("resources/PNG/tree.png");
	textures_array_[static_cast<int>(Resource::kCutTree)].loadFromFile("resources/PNG/cut_tree.png");
	textures_array_[static_cast<int>(Resource::kStone)].loadFromFile("resources/PNG/stone.png");
	textures_array_[static_cast<int>(Resource::kCutStone)].loadFromFile("resources/PNG/mined_stone.png");
	textures_array_[static_cast<int>(Resource::kBackPanel)].loadFromFile("resources/PNG/grey_panel.png");
}

void ResourceManager::LoadAllFonts()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	default_font_ = sf::Font();
	// Fonts -------------------
	font_array_[static_cast<int>(FontsEnum::kButtonFont)].loadFromFile("resources/fonts/Super Festival Personal Use.ttf");
	font_array_[static_cast<int>(FontsEnum::kArial)].loadFromFile("resources/fonts/arial.ttf");
}

void ResourceManager::LoadAllCursorTextures()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	default_cursor_texture_ = sf::Texture();
	//Cursor textures ------------------------
	cursor_array_[static_cast<int>(CursorTextures::kDefaultCursor)].loadFromFile("resources/PNG/custom_basic_cursor.png");
	cursor_array_[static_cast<int>(CursorTextures::kCustomCursor)].loadFromFile("resources/PNG/custom_cursor.png");
}

static ResourceManager* instance = nullptr;
//constructor
ResourceManager::ResourceManager()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	instance = this;

	LoadAllTextures();

	LoadAllFonts();

	LoadAllCursorTextures();
}

//Destructor -> destroy instance
ResourceManager::~ResourceManager()
{
	instance = nullptr;
}

ResourceManager& ResourceManager::Get()
{
	return *instance;
}

//get texture and returns it
sf::Texture& ResourceManager::Texture(Resource resource_id)
{
	if (static_cast<size_t>(resource_id) <= textures_array_.size() && static_cast<int>(resource_id) >= 0)
	{
		return textures_array_.at(static_cast<int>(resource_id));
	}
	else
	{
		return blank_texture_;
	}
}

//get font and return it
sf::Font& ResourceManager::Font(FontsEnum font_id)
{
	if (static_cast<size_t>(font_id) <= font_array_.size() && static_cast<int>(font_id) >= 0)
	{
		return font_array_.at(static_cast<int>(font_id));
	}
	else
	{
		return default_font_;
	}
}

//get cursor texture and return it
sf::Texture& ResourceManager::CursorTexture(CursorTextures cursor_texture_id)
{
	if (static_cast<size_t>(cursor_texture_id) <= cursor_array_.size() && static_cast<int>(cursor_texture_id) >= 0)
	{
		return cursor_array_.at(static_cast<int>(cursor_texture_id));
	}
	else
	{
		return default_cursor_texture_;
	}
}
