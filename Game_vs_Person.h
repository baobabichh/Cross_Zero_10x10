#pragma once
#include "Game.h"

namespace cz
{

	class Game_vs_Person : public Game
	{
	public:
		Game_vs_Person(sf::Texture* cross_tx, sf::Texture* zero_tx, sf::Font* font,
			const sf::Vector2i& position,
			const sf::Vector2i& size, const int& len_to_win,
			const sf::Vector2i& field_size_px,
			const int& line_width,
			const int& distance, const int& left_distance);
		~Game_vs_Person();

		virtual void draw(sf::RenderWindow& window);
		virtual void update(const float& dt, sf::RenderWindow& window);


		virtual bool ended();

		virtual void restart();

		virtual void pause();
		virtual void stop();
		virtual void start();
	private:

		cz::Winer winer;
		sf::Color bgc;
		sf::RectangleShape rect;
		sf::Vector2i position;
		sf::Texture* zero_tx;
		sf::Texture* cross_tx;
		sf::Sprite hod_sp;
		sf::Text hod_text, winer_text;
		cz::Draw_Field field;
		cz::Cell first_turn;
		cz::Cell turn;
		bool paused;
		int left_distance;
		bool is_ended;
		float text_scale, sprite_scale;
		virtual void end();
	};
}