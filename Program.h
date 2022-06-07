#pragma once
#include "Game_vs_Bot.h"
#include "Game_vs_Person.h"
#include "Main_Menu_Bar.h"
#include <SFML/Audio.hpp>
namespace cz
{

	enum class Program_State
	{
		MAIN_MENU,
		GAME_VS_PLAYER,
		GAME_VS_BOT,
		NEED_EXIT,
	};



	class Program
	{
	public:
		Program();
		~Program();


		bool running();
		void render();
	private:
		//window
		sf::Vector2i window_size;
		std::wstring window_name;
		sf::Uint32 window_style;
		sf::ContextSettings window_context_settings;


		//path
		std::string font_path;
		std::string cross_tx_path;
		std::string zero_tx_path;
		std::string bg_tx_path;
		std::string main_menu_song_buffer_path;

		//backgrund sprites
		sf::Sprite bg_sp;


		sf::RenderWindow window;
		sf::Texture cross_tx, zero_tx, bg_tx;
		sf::Font font;

		//menu
		std::map<std::string,cz::Main_Menu_Bar *> main_menu;

		cz::Main_Menu_Bar * exit_button;


		//game
		sf::Vector2i game_size_px;
		sf::Vector2i game_size;
		sf::Vector2i game_position;
		int game_len_to_win;
		int game_left_distance;
		int game_distance;
		int game_line_width;
		cz::Game* current_game;
		sf::Clock clock;
		sf::Event event;

		//sound
		sf::SoundBuffer main_menu_song_buffer;
		sf::Sound main_menu_sound;

		//end
		Program_State program_state;


		//click
		bool prev_clic=0, now_click=0;
	

		void set_path();
		void load_textures();
		void update();
		void draw();
	};

}