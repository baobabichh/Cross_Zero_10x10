#include "Program.h"

namespace cz 
{

	Program::Program() : program_state(cz::Program_State::MAIN_MENU)
	{
		//___________________________________
		//--------------PATH-----------------

		this->set_path();

		//___________________________________
		//--------------WINDOW---------------

		window_name = L"Крестики нолики 10 на 10";
		window_size = sf::Vector2i(1000, 750);
		window_style = sf::Style::Close;
		window_context_settings.antialiasingLevel = 12;
		

		window.create(sf::VideoMode(window_size.x, window_size.y), window_name, window_style);
		window.setFramerateLimit(60);
		window.setKeyRepeatEnabled(false);

		//___________________________________
		//--------------TEXTURES-------------

		this->bg_tx.loadFromFile(bg_tx_path);
		this->cross_tx.loadFromFile(cross_tx_path);
		this->zero_tx.loadFromFile(zero_tx_path);

		this->main_menu_song_buffer.loadFromFile(main_menu_song_buffer_path);
		main_menu_sound.setBuffer(main_menu_song_buffer);
		main_menu_sound.setLoop(1);
		main_menu_sound.play();
		

		//___________________________________
		//--------------FONT-----------------

		this->font.loadFromFile(font_path);

		//___________________________________
		//--------------SPRITES--------------

		bg_sp.setTexture(bg_tx);
		bg_sp.setScale((float)window.getSize().x / (float)bg_tx.getSize().x, (float)window.getSize().y / (float)bg_tx.getSize().y);
		bg_sp.setPosition(0, 0);
		

		//___________________________________
		//--------------MENU-----------------
		main_menu["PLAY_WITH_BOT"] = new cz::Main_Menu_Bar(&font, L"Играть с ботом", sf::Vector2i(100, 100));
		main_menu["PLAY_WITH_PLAYER"] = new cz::Main_Menu_Bar(&font, L"Играть с другом", sf::Vector2i(100, 200));
		main_menu["EXIT"] = new cz::Main_Menu_Bar(&font, L"Выход", sf::Vector2i(100, 300));


		//exit button
		exit_button = new Main_Menu_Bar(&font, L"Выйти в меню", sf::Vector2i(0, 0));
		exit_button->set_position(sf::Vector2i(window_size.x/2 - exit_button->get_local_bounds().width / 2, 600));
		exit_button->hide();
			


		//___________________________________
		//--------------GAME-----------------

		this->current_game = nullptr;
		this->game_size_px = sf::Vector2i(700, 700);
		this->game_size = sf::Vector2i(10, 10);
		this->game_position = sf::Vector2i(0, 0);
		this->game_len_to_win = 5;
		this->game_left_distance = 250;
		this->game_distance = 1;
		this->game_line_width = 1;

	}

	Program::~Program()
	{
		//delete current_game;
		for (auto&& it : main_menu)
		{
			delete it.second;
		}
		delete exit_button;
		window.close();
	}
	void Program::set_path()
	{
		this->font_path = "resources\\font.ttf";
		this->bg_tx_path = "resources\\background.jpg";
		this->cross_tx_path = "resources\\cross.png";
		this->zero_tx_path = "resources\\zero.png";
		this->main_menu_song_buffer_path = "resources\\main_menu_sound.wav";
	}
	void Program::load_textures()
	{
		font.loadFromFile(font_path);
		cross_tx.loadFromFile(bg_tx_path);
		zero_tx.loadFromFile(cross_tx_path);
		bg_tx.loadFromFile(zero_tx_path);
		main_menu_song_buffer.loadFromFile(main_menu_song_buffer_path);
	}

	/////////////////////////////////////////
	/////////////MAIN FUNCTIONS//////////////
	/////////////////////////////////////////

	void Program::render()
	{
		this->update();
		this->draw();
	}

	void Program::update()
	{
		
		bool wait_for_restart = 0;


		

		if (window.isOpen())
		{
			{
				window.pollEvent(event);
				if (event.type == sf::Event::Closed)
				{
					window.close();
					program_state = cz::Program_State::NEED_EXIT;
				}

				sf::Time elapsed = clock.restart();

				//------------------------------------------------
				//--------------------UPDATE----------------------

				if (this->program_state == cz::Program_State::MAIN_MENU)
				{
					for (auto&& it : main_menu)
					{
						it.second->show();
						it.second->update(window, elapsed.asSeconds());
						if (it.second->is_pressed(window))
						{
							if (it.first == "PLAY_WITH_BOT")
							{
								program_state = cz::Program_State::GAME_VS_BOT;
								this->current_game = new cz::Game_vs_Bot(&cross_tx, &zero_tx, &font, game_position, game_size, game_len_to_win, game_size_px, game_line_width, game_distance, game_left_distance);
							}
							else if (it.first == "PLAY_WITH_PLAYER")
							{
								program_state = cz::Program_State::GAME_VS_PLAYER;
								this->current_game = new cz::Game_vs_Person(&cross_tx, &zero_tx, &font, game_position, game_size, game_len_to_win, game_size_px, game_line_width, game_distance, game_left_distance);
							}
							else if (it.first == "EXIT")
							{
								program_state = cz::Program_State::NEED_EXIT;
							}
							for (auto&& it : main_menu)
							{
								it.second->hide();
							}
						}
					}
				}
				if (this->program_state == cz::Program_State::GAME_VS_PLAYER)
				{
					current_game->update(elapsed.asSeconds(), window);
					if (current_game->ended())
					{
						exit_button->show();
						exit_button->update(window, elapsed.asSeconds());
						if (exit_button->is_pressed(window))
						{
							exit_button->hide();
							program_state = cz::Program_State::MAIN_MENU;
							delete current_game;
						}
					}
				}
				else if (this->program_state == cz::Program_State::GAME_VS_BOT)
				{
					current_game->update(elapsed.asSeconds(), window);
					if (current_game->ended())
					{
						exit_button->show();
						exit_button->update(window, elapsed.asSeconds());
						if (exit_button->is_pressed(window))
						{
							exit_button->hide();
							program_state = cz::Program_State::MAIN_MENU;
							delete current_game;
						}
					}
				}


				if (current_game != nullptr)
				{

				}

				//------------------------------------------------
				//------------------------------------------------
			}
		}
	}

	void Program::draw()
	{
		//------------------------------------------------
		//------------------------------------------------

		window.clear(sf::Color(145, 219, 121));
		window.draw(bg_sp);

		//------------------------------------------------
		//-------------------DRAW-------------------------

		if (program_state == cz::Program_State::MAIN_MENU)
		{
			for (auto&& it : main_menu)
			{
				it.second->draw(window);
			}
		}
		else if (program_state == cz::Program_State::GAME_VS_BOT || program_state == cz::Program_State::GAME_VS_PLAYER && current_game!=nullptr)
		{
			current_game->draw(window);
		}
		exit_button->draw(window);


		//------------------------------------------------
		//------------------------------------------------
		window.display();
	}
	bool Program::running()
	{
		if (program_state == cz::Program_State::NEED_EXIT)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

}


