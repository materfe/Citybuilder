#ifndef API_GAMEPLAY_MINING_WORKER_H_
#define API_GAMEPLAY_MINING_WORKER_H_
#include "economy_manager.h"
#include "walker.h"
#include "behavior_tree/bt_node.h"
#include "behavior_tree/bt_tree.h"
#include "graphics/Tilemap.h"

class MiningWorker : public Walker
{
private:
	behavior_tree::Tree tree_;
	Tilemap& map_;
	EconomyManager& economy_;
	sf::Vector2f destination_;
	sf::Vector2f home_destination_;


	int stamina_;

	//seek wood method for behavior tree
	behavior_tree::Status SeekStone();
	behavior_tree::Status GoBackHome();
	behavior_tree::Status GatherStone() const;
public:
	//constructor
	MiningWorker(const sf::Vector2f& pos, float speed, Tilemap& map, EconomyManager& economy);
	MiningWorker(const MiningWorker& w);

	//init behavior tree
	void SetBehaviorTreeNode();

	//Tick()
	void Tick();

	//override
	void DefineTexture() override;
};






#endif //API_GAMEPLAY_MINING_WORKER_H_