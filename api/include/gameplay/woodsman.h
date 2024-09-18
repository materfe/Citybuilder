#ifndef API_GAMEPLAY_WOODSMAN_H_
#define API_GAMEPLAY_WOODSMAN_H_
#include "economy_manager.h"
#include "walker.h"
#include "behavior_tree/bt_tree.h"
#include "graphics/tilemap.h"


class WoodsMan : public Walker
{
private:
	behavior_tree::Tree tree_;
	Tilemap& map_;
	EconomyManager& economy_;
	sf::Vector2f destination_;
	sf::Vector2f home_destination_;


	int stamina_;

	//seek wood method for behavior tree
	behavior_tree::Status SeekWood();
	behavior_tree::Status GoBackHome();
	behavior_tree::Status GatherWood() const;
public:
	//constructor
	WoodsMan(const sf::Vector2f& pos, float speed, Tilemap& map, EconomyManager& economy);
	WoodsMan(const WoodsMan& w);

	//init behavior tree
	void SetBehaviorTreeNode();

	

	//Tick()
	void Tick();

	//override
	void DefineTexture() override;
};


#endif //API_GAMEPLAY_WOODSMAN_H_
