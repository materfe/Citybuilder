#ifndef API_GRAPHICS_RESOURCE_MANAGER_H_
#define API_GRAPHICS_RESOURCE_MANAGER_H_

#include <array>
#include <SFML/Graphics.hpp>

class ResourceManager
{

public:
	enum class Resource
	{
		kYellowButton,
		kGreyButton,
		kBuildingSprite,
		kTerrainGround,
		kWoodHouse,
		kStoneHouse,
		kTerrainSunflowerGround,
		kTerrainBasicGround,
		kWoodsMan,
		kStoneMan,
		kTree,
		kCutTree,
		kStone,
		kCutStone,
		kBackPanel,
		kLength
	};

	enum class CursorTextures
	{
		kCustomCursor,
		kDefaultCursor,
		kLength
	};


	enum class FontsEnum
	{
		kButtonFont,
		kArial,
		kLength
	};

private:
	//textures
	std::array<sf::Texture, static_cast<int>(Resource::kLength)> textures_array_;
	sf::Texture blank_texture_;

	//fonts
	std::array<sf::Font, static_cast<int>(FontsEnum::kLength)> font_array_;
	sf::Font default_font_;

	//cursor texture
	std::array<sf::Texture, static_cast<int>(CursorTextures::kLength)> cursor_array_;
	sf::Texture default_cursor_texture_;

	//load all textures
	void LoadAllTextures();

	//load all fonts
	void LoadAllFonts();

	//load all cursors textures
	void LoadAllCursorTextures();

public:

	//all constructor and stuff
	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	~ResourceManager();
	//static ResourceManager* instantce_ = nullptr;

	//Get -----------------------
	static ResourceManager& Get();
	sf::Texture& Texture(Resource resource_id);
	sf::Font& Font(FontsEnum font_id);
	sf::Texture& CursorTexture(CursorTextures cursor_texture_id);
};

#endif