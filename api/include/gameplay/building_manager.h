#ifndef API_GAMEPLAY_BUILDING_MANAGER_H_
#define API_GAMEPLAY_BUILDING_MANAGER_H_
#include "buildings.h"
#include "economy_manager.h"
#include "mining_worker.h"
#include "woodsman.h"
#include "graphics/tilemap.h"


class Tilemap;

class BuildingManager : public sf::Drawable
{
private:
	//all bools
	bool is_active_;
	bool is_wood_house_mode_on_;
	bool is_stone_house_mode_on_;

	//other stuff so that it speaks in other classes
	size_t normal_build_cost_;
	Tilemap& tilemap_;
	EconomyManager& economy_manager_;
	

	//vectors
	std::vector<WoodsMan> woods_man_;
	std::vector<MiningWorker> workers_;
	std::vector<Building> buildings_;

	//check if it's possible
	[[nodiscard]] bool CheckIfBuildable(sf::Vector2i mouse_pos) const;

	//pop a guy
	void PopAWoodMan(const sf::Vector2f& pos);
	void PopAStoneMan(const sf::Vector2f& pos);

	//setup building
	void SetupNewBuilding(sf::Vector2i pos, ResourceManager::Resource resource, Building& new_building) const;
	void SetBuildingTexture(ResourceManager::Resource resource, sf::Vector2f position, sf::Vector2i second_position);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

	//do Tick() for all walkers
	void DoCharactersTick();

	//put building
	void AddBuilding(sf::Vector2i pos);

	//constructor
	explicit BuildingManager(Tilemap& tilemap, EconomyManager& economy);

	//reset all
	void DestroyAllBuildings();

	//Set -------------------------
	void set_is_active();
	void set_is_wood_house_mode_on();
	void set_is_wood_house_mode_off();
	void set_is_stone_house_mode_on();
	void set_is_stone_house_mode_off();
	void DeSetAll();

	//Get -------------------------
	[[nodiscard]] bool is_active() const;
	[[nodiscard]] Tilemap& map() const;
	[[nodiscard]] std::vector<WoodsMan> woodman() const;
};
#endif