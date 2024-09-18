#include "graphics/view.h"

#include "UI/cursor.h"


void ViewPoint::InitVariables()
{
	dead_zone_ = sf::Vector2f(1875.f, 1075.f);
	camera_speed_ = sf::Vector2f(0.010f, 0.015f);
	pos_ = sf::Vector2f(800, 600);
	max_zoom_ = 0.5f;
	min_zoom_ = 1.5f;
	zoom_ = 1.0f;
	camera_modification_ = false;
}

ViewPoint::ViewPoint(Tilemap& tilemap) : tile_map_(tilemap)
{
	//setup
	InitVariables();

	view_.setSize(700, 500);
	view_.setCenter(pos_);
}

bool ViewPoint::IsWithinBounds(const sf::Vector2f& center) const
{
	const float half_view_width = view_.getSize().x / 2.0f;
	const float half_view_height = view_.getSize().y / 2.0f;

	if (center.x - half_view_width < 0 || center.x + half_view_width > tile_map_.playground_size_u().x * tile_map_.playground_tile_size_u().x ||
		center.y - half_view_height < 0 || center.y + half_view_height > tile_map_.playground_size_u().y * tile_map_.playground_tile_size_u().y)
	{
		return false;
	}
	return true;
}

sf::Vector2f ViewPoint::ClampCenterToBounds(const sf::Vector2f& center) const
{
	const float half_view_width = view_.getSize().x / 2.0f;
	const float half_view_height = view_.getSize().y / 2.0f;

	sf::Vector2f clamped_center = center;

	// Clamp the X coordinate
	if (clamped_center.x - half_view_width < 0)
	{
		clamped_center.x = half_view_width;
	}
	else if (clamped_center.x + half_view_width > tile_map_.playground_size_u().x * tile_map_.playground_tile_size_u().x)
	{
		clamped_center.x = tile_map_.playground_size_u().x * tile_map_.playground_tile_size_u().x - half_view_width;
	}

	// Clamp the Y coordinate
	if (clamped_center.y - half_view_height < 0)
	{
		clamped_center.y = half_view_height;
	}
	else if (clamped_center.y + half_view_height > tile_map_.playground_size_u().y * tile_map_.playground_tile_size_u().y)
	{
		clamped_center.y = tile_map_.playground_size_u().y * tile_map_.playground_tile_size_u().y - half_view_height;
	}

	return clamped_center;
}


void ViewPoint::Move(const sf::Event& event)
{
	sf::Vector2f center = view_.getCenter();

	if (event.type == sf::Event::KeyPressed)
	{
		sf::Vector2f movement(0, 0);

		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			movement.y = -8;  // Move view up
		}
		if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			movement.y = 8;   // Move view down
		}
		if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
		{
			movement.x = -8;  // Move view left
		}
		if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
		{
			movement.x = 8;   // Move view right
		}

		const sf::Vector2f new_center = view_.getCenter() + movement;

		if (IsWithinBounds(new_center))
		{
			view_.setCenter(new_center);
			pos_ = new_center;
		}
		else //keep camera in bounds
		{
			view_.setCenter(center);
			pos_ = center;
		}
	}
}

void ViewPoint::Zoom(const sf::Event& event, const sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		// Get the current mouse position in window coordinates
		const sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
		// Convert it to world coordinates
		const sf::Vector2f world_pos = window.mapPixelToCoords(pixel_pos);

		camera_modification_ = false;

		if (event.mouseWheelScroll.delta > 0 && zoom_ > max_zoom_)
		{
			zoom_ *= 0.9f;  // Zoom in
			camera_modification_ = true;
		}

		if (event.mouseWheelScroll.delta < 0 && zoom_ < min_zoom_)
		{
			zoom_ *= 1.1f;  // Zoom out
			camera_modification_ = true;
		}

		// Calculate the new center of the view to zoom at the mouse position
		if (camera_modification_)
		{
			// Adjust the view size based on the new zoom level
			view_.setSize(1500 * zoom_, 800 * zoom_);

			sf::Vector2f new_center = world_pos + (view_.getCenter() - world_pos) * ((event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f);

			new_center = ClampCenterToBounds(new_center);

			view_.setCenter(new_center);
			pos_ = new_center;
		}
	}
}

void ViewPoint::MoveViewByMouse(const sf::RenderWindow& window)
{
	const sf::Vector2f center = view_.getCenter();

	// Get the current mouse position in window coordinates
	const auto pixel_pos = sf::Mouse::getPosition(window);

	// Get the center of the window
	const sf::Vector2u window_size = window.getSize();
	const sf::Vector2f window_center(window_size.x / 2.0f, window_size.y / 2.0f);

	// Calculate the distance from the mouse to the window center
	const sf::Vector2f mouse_delta(pixel_pos.x - window_center.x, pixel_pos.y - window_center.y);

	// Check if the mouse is outside the dead zone
	if (abs(mouse_delta.x) > dead_zone_.x / 2.0f || abs(mouse_delta.y) > dead_zone_.y / 2.0f)
	{
		// Move the view center based on mouse movement outside the dead zone
		if (abs(mouse_delta.x) > dead_zone_.x / 2.0f)
		{
			pos_.x += mouse_delta.x * camera_speed_.x;  // Speed value, Adjust the factor as needed
		}
		if (abs(mouse_delta.y) > dead_zone_.y / 2.0f)
		{
			pos_.y += mouse_delta.y * camera_speed_.y;  // Speed value, Adjust the factor as needed
		}

		
		if (IsWithinBounds(pos_))
		{
			view_.setCenter(pos_);
		}
		else
		{
			view_.setCenter(center);
			pos_ = center;
		}
	}
}