#ifndef API_GAMEPLAY_NATURE_MAP_H_
#define API_GAMEPLAY_NATURE_MAP_H_
#include <vector>
#include "nature_tile_type/cut_trees.h"
#include "nature_tile_type/mined_stone.h"
#include "nature_tile_type/stone.h"
#include "nature_tile_type/Trees.h"

class Nature final: public sf::Drawable
{
private:
	std::vector<Tree> all_trees_;
	std::vector<CutTree> all_cut_trees_;
	std::vector<Stone> all_stones_;
	std::vector<MinedStone> all_cut_stones_;

	//cooldown
	sf::Time interval_;
	sf::Clock wood_clock_;
	sf::Clock stone_clock_;

	//repop stuff -> take a random entity and repop it
	void GrowTree();
	void GrowStone();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Nature();

	//add stuff
	void AddATreeAt(sf::Vector2f position);
	void AddAStoneAt(sf::Vector2f position);
	void AddACutTree(sf::Vector2f position);
	void AddACutStone(sf::Vector2f position);

	//gather a tree and cut it
	bool GatherTree(sf::Vector2f pos);
	bool GatherStone(sf::Vector2f pos);

	//repop system
	void RepopTree();
	void RepopStone();
	void UpdateRepopCd(const float woodsman_size);

	//return a tree
	sf::Vector2f GetATreeTilePosition(sf::Vector2f starting_pos);
	sf::Vector2f GetAStoneTilePosition(sf::Vector2f starting_pos);

	//Get ----------------
	[[nodiscard]] std::vector<CutTree> all_cut_trees() const;
	[[nodiscard]] std::vector<MinedStone> all_cut_rocks() const;
};




#endif //API_GAMEPLAY_NATURE_MAP_H_
