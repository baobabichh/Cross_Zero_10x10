#pragma once
#include "Game.h"
#include <unordered_map>

namespace cz
{

	bool operator<(const sf::Vector2i& v1, const sf::Vector2i& v2 );

	enum class Lines
	{
		LEFTRIGHT,
		UPDOWN,
		UPLEFT,
		UPRIGHT,
	};


	class Game_vs_Bot : public Game
	{
	public:
		Game_vs_Bot( sf::Texture* cross_tx, sf::Texture* zero_tx, sf::Font* font,
						const sf::Vector2i& position,
						const sf::Vector2i& size, const int& len_to_win,
						const sf::Vector2i& field_size_px,
						const int& line_width,
						const int& distance, const int& left_distance);
		~Game_vs_Bot();

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
		sf::Sprite hod_sp , bot_sp , player_sp;
		sf::Text hod_text, winer_text , who_player_text , who_bot_text ;
		cz::Draw_Field field;
		cz::Cell first_turn;
		cz::Cell turn;
		cz::Cell bot_value , player_value;
		bool paused;
		int left_distance;
		bool is_ended , full_end;
		float text_scale, sprite_scale;

		virtual void end();
		sf::Vector2i get_bot_move();

		sf::Vector2i find_way_to_win();
		sf::Vector2i contering();
		sf::Vector2i any_move();

		bool winable(const sf::Vector2i & pos ,cz::Lines line );
		bool winable(const sf::Vector2i& pos, cz::Lines line , cz::Cell turn);
		sf::Vector2i need_conter(const sf::Vector2i & pos);
		void need_conter(const sf::Vector2i& pos, std::vector<int>& values);
	};





}

