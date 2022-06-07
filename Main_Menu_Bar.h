#pragma once
#include "Menu_Bar.h"
namespace cz 
{
	enum class Anim_State
	{
		NONE,
		INCREASES,
		DECREASES,
	};


	class Main_Menu_Bar
	{
	public:
		Main_Menu_Bar(sf::Font* font, const  std::wstring& text, const sf::Vector2i& position);
		~Main_Menu_Bar();

		virtual void draw(sf::RenderWindow& window);
		virtual void update(sf::RenderWindow& window, const float& dt);
		virtual bool is_pressed(sf::RenderWindow& window);

		virtual void set_text(const std::wstring& text);
		virtual const std::wstring& get_text()const;

		virtual void set_position(const sf::Vector2i& position);
		virtual const sf::Vector2i& get_position()const;

		virtual void show();
		virtual void hide();

		virtual bool is_hiden()const;

		virtual  sf::IntRect get_global_bounds()const;
		virtual  sf::IntRect get_local_bounds()const;

	private:
		sf::Text text;
		sf::Vector2i pos;
		sf::IntRect start_bounds;
		float scale_value_default , scale_value_anim , scale_value_end;
		int max_frames;
		float current_frame , prev_frame;
		float anim_speed;
		std::vector<std::pair<sf::Vector2f , sf::Vector2i>> text_scales;
		sf::RectangleShape rect;
		bool _hiden;
		cz::Anim_State anim_state;

		bool prev_clic =0, now_click=0;
	};
}
