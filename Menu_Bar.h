#pragma once
#include <SFML/Graphics.hpp>
#include <corecrt_wstring.h>
namespace cz 
{
	class Menu_Bar
	{
	public:
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual void update(sf::RenderWindow& window, const float& dt) = 0;
		virtual bool is_pressed(sf::RenderWindow& window) = 0;

		virtual void set_text(const std::wstring& text) = 0;
		virtual const std::wstring& get_text()const = 0;

		virtual void set_position(const sf::Vector2i& position) = 0;
		virtual const sf::Vector2i& get_position()const = 0;

		virtual void show() = 0;
		virtual void hide() = 0;

		virtual  sf::IntRect get_global_bounds()const = 0;
		virtual  sf::IntRect get_local_bounds()const = 0;

		virtual bool is_hiden()const = 0;

	private:

	};
}

