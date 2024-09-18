#ifndef API_GAMEPLAY_GAME_H_
#define API_GAMEPLAY_GAME_H_
#include <SFML/Graphics/RenderWindow.hpp>

#include "building_manager.h"
#include "gameplay/nature_map.h"
#include "graphics/tilemap.h"
#include "graphics/view.h"
#include "UI/cursor.h"
#include "UI/hovered_tile.h"
#include "UI/uibutton.h"
#include "UI/ui_economy.h"
#include "UI/ui_shapes.h"

class Game
{
private:
	//window
	sf::RenderWindow window_;
	sf::View fix_view_;
	ViewPoint view_;

	//Resources
	ResourceManager resource_;

	//tilemap data
	Tilemap tilemap_;
	Nature nature_;
	sf::Vector2i tile_size_;
	
	//generate_button_ data
	UiButton pop_other_button_button_;
	UiButton build_mode_wood_house_;
	UiButton build_mode_stone_house_;

	//Hovered tile frame setup
	HoveredTile hover_;

	//building manager
	BuildingManager build_;

	//mouse position
	sf::Vector2i mouse_pos_;
	sf::Vector2i mouse_tile_coord_;

	//cursor
	Cursor cursor_;

	//UI
	UiEconomy ui_economy_;
	UiShapes ui_shapes_;

	//wood_economy
	EconomyManager economy_;

	//setup bools
	bool is_active_;
	bool is_buildable_;


	void PrepareCallBacks();
	void UiGraphic();
	void SetAllUiShapesForFeedBack();
	void Events(const sf::Event& event);
	void CalculateMousePosition();
	void SetupCursorAndHoverPositionBasedOnMousePos();
	void GraphicSetup();
	void HoverColorSetup(bool& is_active, bool& is_buildable);

public:
	//constructor
	Game();

	void GameLoop();


};


#endif //API_GAMEPLAY_GAME_H_
