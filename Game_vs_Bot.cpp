#include "Game_vs_Bot.h"

namespace cz
{
	bool operator<(const sf::Vector2i& v1, const sf::Vector2i& v2)
	{
		return (v1.x < v2.x) && (v1.y < v2.y);
	}

	Game_vs_Bot::Game_vs_Bot(sf::Texture* cross_tx, sf::Texture* zero_tx, sf::Font* font,
		const sf::Vector2i& position,
		const sf::Vector2i& size, const int& len_to_win,
		const sf::Vector2i& field_size_px,
		const int& line_width,
		const int& distance, const int& left_distance) : field(cross_tx, zero_tx, sf::Vector2i(position.x + left_distance + MARGIN * 1.5, position.y + MARGIN * 1.5), size.x, size.y, len_to_win, sf::Vector2i(field_size_px.x - MARGIN, field_size_px.y - MARGIN), line_width, distance), turn(cz::Cell::CROSS)
	{
		//color
		this->bgc = sf::Color(246, 172, 189 , 200);

		this->full_end = 0;
		this->is_ended = 0;
		this->cross_tx = cross_tx;
		this->zero_tx = zero_tx;
		this->position = position;
		this->left_distance = left_distance;
		//rect
		rect.setFillColor(bgc);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(3);
		rect.setPosition(position.x + left_distance + MARGIN / 2, position.y + MARGIN / 2);
		rect.setSize(sf::Vector2f(field_size_px.x + MARGIN, field_size_px.y + MARGIN));
		//text

		this->hod_text.setFont(*font);
		this->hod_text.setString(L"Сейчас ходит");
		this->hod_text.setCharacterSize(40);
		this->hod_text.setFillColor(sf::Color::Black);
		this->hod_text.setStyle(sf::Text::Bold);
		this->hod_text.setPosition(position.x + MARGIN, position.y + MARGIN);
		text_scale = (float)(left_distance - MARGIN * 2) / (float)hod_text.getGlobalBounds().width;
		this->hod_text.setScale(text_scale, text_scale);
		
		this->winer_text.setFont(*font); // you win;
		this->winer_text.setString(L"");
		this->winer_text.setCharacterSize(100);
		this->winer_text.setFillColor(sf::Color::Yellow);
		this->winer_text.setStyle(sf::Text::Bold);
		this->winer_text.setOutlineColor(sf::Color::Black);
		this->winer_text.setOutlineThickness(4);

		//sp
		sprite_scale = (float)(left_distance - MARGIN * 2)/3 / cross_tx->getSize().x;
		this->hod_sp.setColor(sf::Color::White);
		this->hod_sp.setPosition(position.x+MARGIN+((left_distance - MARGIN*2 )/2 - (cross_tx->getSize().x * sprite_scale)/2), hod_text.getGlobalBounds().top + hod_text.getGlobalBounds().height + MARGIN);
		this->hod_sp.setScale(sprite_scale, sprite_scale);

		//text
		this->who_bot_text.setFont(*font); // who bot
		this->who_bot_text.setString(L"Бот ");
		this->who_bot_text.setCharacterSize(40);
		this->who_bot_text.setFillColor(sf::Color::Black);
		this->who_bot_text.setStyle(sf::Text::Bold);
		this->who_bot_text.setPosition(position.x + MARGIN,  hod_sp.getPosition().y + cross_tx->getSize().y*sprite_scale + MARGIN);
		this->who_bot_text.setScale(text_scale, text_scale);
		//sp who bot
		float sprite_scale_bot = (float)who_bot_text.getGlobalBounds().height / (float)cross_tx->getSize().y;
		this->bot_sp.setColor(sf::Color::White);
		this->bot_sp.setPosition(who_bot_text.getGlobalBounds().left+ who_bot_text.getGlobalBounds().width , who_bot_text.getGlobalBounds().top);
		this->bot_sp.setScale(sprite_scale_bot, sprite_scale_bot);


		//text
		this->who_player_text.setFont(*font); // who player
		this->who_player_text.setString(L"Игрок ");
		this->who_player_text.setCharacterSize(40);
		this->who_player_text.setFillColor(sf::Color::Black);
		this->who_player_text.setStyle(sf::Text::Bold);
		this->who_player_text.setPosition(position.x + MARGIN, who_bot_text.getGlobalBounds().top + who_bot_text.getGlobalBounds().height + MARGIN);
		this->who_player_text.setScale(text_scale , text_scale);
		//sp who bot
		sprite_scale_bot = (float)who_bot_text.getGlobalBounds().height / (float)cross_tx->getSize().y;
		this->player_sp.setColor(sf::Color::White);
		this->player_sp.setPosition(who_player_text.getGlobalBounds().left + who_player_text.getGlobalBounds().width, who_player_text.getGlobalBounds().top);
		this->player_sp.setScale(sprite_scale_bot, sprite_scale_bot);
		

		//text
		
		//field

		//first 
		int first = rand() % 2;
		if (first)
		{
			turn = cz::Cell::CROSS;
		}
		else if (!first)
		{
			turn = cz::Cell::ZERO;
		}
		this->first_turn = turn;
		//bot
		first = rand() % 2;
		if (first)
		{
			bot_value = cz::Cell::CROSS;
			this->bot_sp.setTexture(*cross_tx);
			player_value = cz::Cell::ZERO;
			this->player_sp.setTexture(*zero_tx);
		}
		else if (!first)
		{
			bot_value = cz::Cell::ZERO;
			this->bot_sp.setTexture(*zero_tx);
			player_value = cz::Cell::CROSS;
			this->player_sp.setTexture(*cross_tx);
		}
		
		
	}
	void Game_vs_Bot::draw(sf::RenderWindow& window)
	{
		
		if (!is_ended && !paused)
		{
			window.draw(rect);
			field.draw(window);
			window.draw(hod_text);
			window.draw(hod_sp);
			window.draw(who_bot_text);
			window.draw(who_player_text);
			window.draw(player_sp);
			window.draw(bot_sp);
		}
		else if (is_ended)
		{
			winer_text.setScale(winer_text.getLocalBounds().width / window.getSize().x, winer_text.getLocalBounds().width / window.getSize().x);
			window.draw(rect);
			field.draw(window);
			window.draw(hod_text);
			window.draw(hod_sp);
			window.draw(who_bot_text);
			window.draw(who_player_text);
			window.draw(player_sp);
			window.draw(bot_sp);
			window.draw(winer_text);
			full_end = 1;
		}
	}
	void Game_vs_Bot::update(const float& dt, sf::RenderWindow& window)
	{


		if (!full_end)
		{
			if (is_ended)
			{
				if (winer == cz::Winer::CROSS)
				{
					winer_text.setString(L"Победил крестик!");
				}
				else if (winer == cz::Winer::ZERO)
				{
					winer_text.setString(L"Победил нолик!");
				}
				else if (winer == cz::Winer::TIE)
				{
					winer_text.setString(L"Ничия!");
				}
				winer_text.setPosition((window.getSize().x - winer_text.getGlobalBounds().width) / 2, (window.getSize().y - winer_text.getGlobalBounds().height) / 2);
			}
			else if (!is_ended && !paused)
			{
				if (turn == cz::Cell::CROSS)
				{
					hod_sp.setTexture(*cross_tx);
				}
				else if (turn == cz::Cell::ZERO)
				{
					hod_sp.setTexture(*zero_tx);
				}
				if (turn == bot_value)
				{
					turn = player_value;
					sf::Vector2i bot_move = this->get_bot_move();
					field.set_value(bot_move.x, bot_move.y, bot_value);
				}
				field.update(dt, window, turn);

				winer = field.check_winer();
				if (winer != cz::Winer::NONE)
				{
					is_ended = 1;
					if (winer == cz::Winer::CROSS)
					{
						winer_text.setString(L"Победил крестик!");
					}
					else if (winer == cz::Winer::ZERO)
					{
						winer_text.setString(L"Победил нолик!");
					}
					else if (winer == cz::Winer::TIE)
					{
						winer_text.setString(L"Ничия!");
					}
					winer_text.setPosition((window.getSize().x - winer_text.getGlobalBounds().width) / 2, (window.getSize().y - winer_text.getGlobalBounds().height) / 2);
				}
			}
		}
		

	}

	void Game_vs_Bot::end()
	{
		is_ended = 1;
		paused = 1;
	}
	bool Game_vs_Bot::ended()
	{
		return full_end;
	}

	void Game_vs_Bot::restart()
	{
		if (first_turn == cz::Cell::ZERO)
		{
			turn = cz::Cell::CROSS;
		}
		else if (first_turn == cz::Cell::CROSS)
		{
			turn = cz::Cell::ZERO;
		}
		first_turn = turn;
		this->is_ended = 0;
		this->paused = 0;
		this->full_end = 0;
		field.reset();
	}

	void Game_vs_Bot::pause()
	{
		paused = 1;
	}
	void Game_vs_Bot::stop()
	{
		is_ended = 1;
	}
	void Game_vs_Bot::start()
	{
		paused = 0;
	}
	Game_vs_Bot::~Game_vs_Bot()
	{
	}

	sf::Vector2i Game_vs_Bot::get_bot_move()
	{
		sf::Vector2i way_to_win =find_way_to_win();
		if (way_to_win.x != -1)
		{
			std::cout << "way_to_win , x=" << way_to_win.x << " , y=" << way_to_win.y << std::endl;
			return way_to_win;
		}

		sf::Vector2i contering = this->contering();
		if (contering.x != -1)
		{
			std::cout << "contering , x=" << way_to_win.x << " , y=" << way_to_win.y << std::endl;
			return contering;
		}
		
		way_to_win = any_move();
		std::cout << "any_move , x=" << way_to_win.x << " , y=" << way_to_win.y << std::endl;
		return way_to_win;

		
	}

	sf::Vector2i Game_vs_Bot::find_way_to_win()
	{
		sf::Vector2i pos(0, 0);
		for (pos.x = 0; pos.x < field.get_size().x ; pos.x++)
		{
			for (pos.y = 0; pos.y < field.get_size().y ; pos.y++)
			{
				int i = pos.x, j = pos.y;

				cz::Cell val = field.get_value(pos.x, pos.y);


				if ( val == cz::Cell::ERROR || val == player_value)
				{
					continue;
				}
				//left_right
				{
					int free_cells = 0, len = 0, x = 0, y = 0;
					bool winable = 1, last = 0;
					sf::Vector2i res(-1, -1);
					for (int k = 0; k < field.get_len_to_win(); k++)
					{
						x = i + k; y = j;
						if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == player_value)
						{
							winable = 0;
							break;
						}
						if (field.get_value(x, y) == cz::Cell::NONE)
						{
							free_cells++;
							res = sf::Vector2i(x, y);
						}
					}
					if (winable && free_cells == 1)
					{
						return res;
					}
				}
				//up down
				{
					int free_cells = 0, len = 0, x = 0, y = 0;
					bool winable = 1, last = 0;
					sf::Vector2i res(-1, -1);
					for (int k = 0; k < field.get_len_to_win(); k++)
					{
						x = i ; y = j+k;
						if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == player_value)
						{
							winable = 0;
							break;
						}
						if (field.get_value(x, y) == cz::Cell::NONE)
						{
							free_cells++;
							res = sf::Vector2i(x, y);
						}
					}
					if (winable && free_cells == 1)
					{
						return res;
					}
				}
				//up left
				{
					int free_cells = 0, len = 0, x = 0, y = 0;
					bool winable = 1, last = 0;
					sf::Vector2i res(-1, -1);
					for (int k = 0; k < field.get_len_to_win(); k++)
					{
						x = i+k; y = j + k;
						if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == player_value)
						{
							winable = 0;
							break;
						}
						if (field.get_value(x, y) == cz::Cell::NONE)
						{
							free_cells++;
							res = sf::Vector2i(x, y);
						}
					}
					if (winable && free_cells == 1)
					{
						return res;
					}
				}
				//up right
				{
					int free_cells = 0, len = 0, x = 0, y = 0;
					bool winable = 1, last = 0;
					sf::Vector2i res(-1, -1);
					for (int k = 0; k < field.get_len_to_win(); k++)
					{
						x = i-k; y = j + k;
						if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == player_value)
						{
							winable = 0;
							break;
						}
						if (field.get_value(x, y) == cz::Cell::NONE)
						{
							free_cells++;
							res = sf::Vector2i(x, y);
						}
					}
					if (winable && free_cells == 1)
					{
						return res;
					}
				}
				
			}
		}
		return sf::Vector2i(-1, -1);

	}

	sf::Vector2i Game_vs_Bot::contering()
	{
		
			std::vector<std::pair<sf::Vector2i ,int>> values;
			values.resize(field.get_size().x * field.get_size().y);

			for (auto&& it : values)
			{
				it = std::make_pair(sf::Vector2i(0, 0), 0);
			}
			//if last cell needed
			for (int i = 0; i < field.get_size().x; i++)
			{
				for (int j = 0; j < field.get_size().y; j++)
				{
					if (field.get_value(i, j) == cz::Cell::ERROR || field.get_value(i, j) == bot_value)
					{
						continue;
					}
					//left right
					{
						int free_cells = 0, len = 0, x = 0, y = 0;
						bool winable = 1, last = 0;
						sf::Vector2i res(-1, -1);
						for (int k = 0; k < field.get_len_to_win(); k++)
						{
							x = i + k; y = j;
							if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == bot_value)
							{
								winable = 0;
								break;
							}
							if (field.get_value(x, y) == cz::Cell::NONE)
							{
								free_cells++;
								res = sf::Vector2i(x, y);
							}
	
						}
						if (free_cells == 1 && winable)
						{
							return res;
						}
					}
					//up down
					{
						int free_cells = 0, len = 0, x = 0, y = 0;
						bool winable = 1, last = 0;
						sf::Vector2i res(-1, -1);
						for (int k = 0; k < field.get_len_to_win(); k++)
						{
							x = i; y = j + k;
							if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == bot_value)
							{
								winable = 0;
								break;
							}
							if (field.get_value(x, y) == cz::Cell::NONE)
							{
								free_cells++;
								res = sf::Vector2i(x, y);
							}

						}
						if (free_cells == 1 && winable)
						{
							return res;
						}
					}
					//up left
					{
						int free_cells = 0, len = 0, x = 0, y = 0;
						bool winable = 1, last = 0;
						sf::Vector2i res(-1, -1);
						for (int k = 0; k < field.get_len_to_win(); k++)
						{
							x = i + k; y = j + k;
							if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == bot_value)
							{
								winable = 0;
								break;
							}
							if (field.get_value(x, y) == cz::Cell::NONE)
							{
								free_cells++;
								res = sf::Vector2i(x, y);
							}

						}
						if (free_cells == 1 && winable)
						{
							return res;
						}
						
					}
					//up right
					{
						int free_cells = 0, len = 0, x = 0, y = 0;
						bool winable = 1, last = 0;
						sf::Vector2i res(-1, -1);
						for (int k = 0; k < field.get_len_to_win(); k++)
						{
							x = i - k; y = j + k;
							if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == bot_value)
							{
								winable = 0;
								break;
							}
							if (field.get_value(x, y) == cz::Cell::NONE)
							{
								free_cells++;
								res = sf::Vector2i(x, y);
							}

						}
						if (free_cells == 1 && winable)
						{
							return res;
						}
						
					}
				}
			}

			//the best conter
			for (int i = 0; i < field.get_size().x; i++)
			{
				for (int j = 0; j < field.get_size().y; j++)
				{
					if (field.get_value(i, j) == cz::Cell::ERROR || field.get_value(i, j) == bot_value)
					{
						continue;
					}
					//left right
					{
						int free_cells = 0, len = 0, x = 0, y = 0;
						bool winable = 1, last = 0;
						sf::Vector2i res(-1, -1);
						for (int k = 0; k < field.get_len_to_win(); k++)
						{
							x = i + k; y = j;
							if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == bot_value)
							{
								winable = 0;
								break;
							}
							if (field.get_value(x, y) == cz::Cell::NONE)
							{
								free_cells++;
							}
						}
						if (winable && free_cells <=2)
						{
							for (int k = 0; k < field.get_len_to_win(); k++)
							{
								x = i + k; y = j;
								if (field.get_value(x, y) == cz::Cell::NONE)
								{
									values.at(x * field.get_size().x + y).first = sf::Vector2i(x,y);
									values.at(x * field.get_size().x + y).second ++;
								}
							}
						}
					}
					//up down
					{
						int free_cells = 0, len = 0, x = 0, y = 0;
						bool winable = 1, last = 0;
						sf::Vector2i res(-1, -1);
						for (int k = 0; k < field.get_len_to_win(); k++)
						{
							x = i ; y = j+k;
							if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == bot_value)
							{
								winable = 0;
								break;
							}
							if (field.get_value(x, y) == cz::Cell::NONE)
							{
								free_cells++;
							}
						}
						if (winable && free_cells <= 2)
						{
							for (int k = 0; k < field.get_len_to_win(); k++)
							{
								x = i ; y = j+k;
								if (field.get_value(x, y) == cz::Cell::NONE)
								{
									values.at(x* field.get_size().x + y).first = sf::Vector2i(x, y);
									values.at(x* field.get_size().x + y).second++;
								}
							}
						}
					}
					//up left
					{
						int free_cells = 0, len = 0, x = 0, y = 0;
						bool winable = 1, last = 0;
						sf::Vector2i res(-1, -1);
						for (int k = 0; k < field.get_len_to_win(); k++)
						{
							x = i+k; y = j + k;
							if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == bot_value)
							{
								winable = 0;
								break;
							}
							if (field.get_value(x, y) == cz::Cell::NONE)
							{
								free_cells++;
							}
						}
						if (winable && free_cells <= 2)
						{
							for (int k = 0; k < field.get_len_to_win(); k++)
							{
								x = i+k; y = j + k;
								if (field.get_value(x, y) == cz::Cell::NONE)
								{
									values.at(x* field.get_size().x + y).first = sf::Vector2i(x, y);
									values.at(x* field.get_size().x + y).second++;
								}
							}
						}
					}
					//up right
					{
						int free_cells = 0, len = 0, x = 0, y = 0;
						bool winable = 1, last = 0;
						sf::Vector2i res(-1, -1);
						for (int k = 0; k < field.get_len_to_win(); k++)
						{
							x = i -k; y = j + k;
							if (field.get_value(x, y) == cz::Cell::ERROR || field.get_value(x, y) == bot_value)
							{
								winable = 0;
								break;
							}
							if (field.get_value(x, y) == cz::Cell::NONE)
							{
								free_cells++;
							}
						}
						if (winable && free_cells <= 2)
						{
							for (int k = 0; k < field.get_len_to_win(); k++)
							{
								x = i -k; y = j + k;
								if (field.get_value(x, y) == cz::Cell::NONE)
								{
									values.at(x* field.get_size().x + y).first = sf::Vector2i(x, y);
									values.at(x* field.get_size().x + y).second++;
								}
							}
						}
					}
				}
			}
			std::pair<sf::Vector2i, int> max = values[0];

			/*std::cout << "/////////////////////////////////\n";
			for (int i = 0; i < field.get_size().x; i++)
			{
				for (int j = 0; j < field.get_size().y; j++)
				{
					std::cout << values[j * field.get_size().x + i].second<<'\t';
				}
				std::cout << "\n";
			}
			std::cout << "/////////////////////////////////\n";*/

			for (auto&& it : values)
			{
				if (it.second > max.second)
				{
					max = it;
				}
			}

			if (max.second == 0)
			{
				return sf::Vector2i(-1, -1);
			}
			else
			{
				return max.first;
			}
			
		
	}

	sf::Vector2i Game_vs_Bot::any_move()
	{

		std::vector<sf::Vector2i>none_positions;
		std::vector<std::pair<sf::Vector2i, int> > variants;
		for (int i = 0; i < field.get_size().x; i++)
		{
			for (int j = 0; j < field.get_size().y; j++)
			{
				if (field.get_value(i, j) == cz::Cell::NONE)
				{
					none_positions.push_back(sf::Vector2i(i, j));
				}
				//any move
				if (field.get_value(i, j) == bot_value)
				{
					int len = 1;
					int k1 = 0, k2 = 0;
					//left-right
					if (winable(sf::Vector2i(i, j), cz::Lines::LEFTRIGHT))
					{

						for (k1 = 0;; k1++)
						{
							if (field.get_value(i + k1, j) == bot_value)
								len++;
							else
								break;
						}
						for (k2 = 0;; k2++)
						{
							if (field.get_value(i - k2, j) == bot_value)
								len++;
							else
								break;
						}


						if (field.get_value(i + k1, j) == cz::Cell::NONE)
						{
							variants.push_back(std::make_pair(sf::Vector2i(i + k1, j), len));
						}
						else if (field.get_value(i - k2, j) == cz::Cell::NONE)
						{
							variants.push_back(std::make_pair(sf::Vector2i(i - k2, j), len));
						}
					}
					//up-down
					if (winable(sf::Vector2i(i, j), cz::Lines::UPDOWN))
					{
						len = 1;
						k1 = 0, k2 = 0;
						for (k1 = 0;; k1++)
						{
							if (field.get_value(i, j + k1) == bot_value)
								len++;
							else
								break;
						}
						for (k2 = 0;; k2++)
						{
							if (field.get_value(i, j - k2) == bot_value)
								len++;
							else
								break;
						}


						if (field.get_value(i, j + k1) == cz::Cell::NONE)
						{
							variants.push_back(std::make_pair(sf::Vector2i(i, j + k1), len));
						}
						else if (field.get_value(i, j - k2) == cz::Cell::NONE)
						{
							variants.push_back(std::make_pair(sf::Vector2i(i, j - k2), len));
						}
					}
					//up left - down right
					if (winable(sf::Vector2i(i, j), cz::Lines::UPLEFT))
					{
						len = 1;
						k1 = 0, k2 = 0;
						for (k1 = 0;; k1++)
						{
							if (field.get_value(i - k1, j - k1) == bot_value)
								len++;
							else
								break;
						}
						for (k2 = 0;; k2++)
						{
							if (field.get_value(i + k2, j + k2) == bot_value)
								len++;
							else
								break;
						}


						if (field.get_value(i - k1, j - k1) == cz::Cell::NONE)
						{
							variants.push_back(std::make_pair(sf::Vector2i(i - k1, j - k1), len));
						}
						else if (field.get_value(i + k2, j + k2) == cz::Cell::NONE)
						{
							variants.push_back(std::make_pair(sf::Vector2i(i + k2, j + k2), len));
						}
					}
					//up right - down left
					if (winable(sf::Vector2i(i, j), cz::Lines::UPRIGHT))
					{
						len = 1;
						k1 = 0, k2 = 0;
						for (k1 = 0;; k1++)
						{
							if (field.get_value(i + k1, j - k1) == bot_value)
								len++;
							else
								break;
						}
						for (k2 = 0;; k2++)
						{
							if (field.get_value(i - k2, j + k2) == bot_value)
								len++;
							else
								break;
						}


						if (field.get_value(i + k1, j - k1) == cz::Cell::NONE)
						{
							variants.push_back(std::make_pair(sf::Vector2i(i + k1, j - k1), len));
						}
						else if (field.get_value(i - k2, j + k2) == cz::Cell::NONE)
						{
							variants.push_back(std::make_pair(sf::Vector2i(i - k2, j + k2), len));
						}
					}
				}
			}

		}
		struct {
			bool operator()(std::pair<sf::Vector2i, int> a, std::pair<sf::Vector2i, int> b) const { return a.second < b.second; }
		} map_sorting_f;
		if (!variants.empty())
		{
			std::sort(variants.begin(), variants.end(), map_sorting_f);
			return  (variants.end() - 1)->first;
		}
		int rand_i = rand() % (none_positions.size());
		return none_positions[rand_i];

	}

	bool  Game_vs_Bot::winable(const sf::Vector2i& pos, cz::Lines line )
	{
		cz::Cell val = field.get_value(pos.x, pos.y);
		if (line == cz::Lines::LEFTRIGHT)
		{
			int len = 1;
			
			for (int i = 1;; i++)
			{
				int x = pos.x-i, y = pos.y;
				if (field.get_value(x,y) == cz::Cell::NONE || field.get_value(x,y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			for (int i = 1;; i++)
			{
				int x = pos.x + i, y = pos.y;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			if (len >= field.get_len_to_win())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (line == cz::Lines::UPDOWN)
		{
			int len = 1;

			for (int i = 1;; i++)
			{
				int x = pos.x , y = pos.y-i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			for (int i = 1;; i++)
			{
				int x = pos.x , y = pos.y+i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			if (len >= field.get_len_to_win())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (line == cz::Lines::UPLEFT)
		{
			int len = 1;

			for (int i = 1;; i++)
			{
				int x = pos.x -i, y = pos.y - i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			for (int i = 1;; i++)
			{
				int x = pos.x+i, y = pos.y + i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			if (len >= field.get_len_to_win())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (line == cz::Lines::UPRIGHT)
		{
		int len = 1;

		for (int i = 1;; i++)
		{
			int x = pos.x - i, y = pos.y + i;
			if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
			{
				len++;
			}
			else
			{
				break;
			}
		}
		for (int i = 1;; i++)
		{
			int x = pos.x + i, y = pos.y - i;
			if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
			{
				len++;
			}
			else
			{
				break;
			}
		}
		if (len >= field.get_len_to_win())
		{
			return 1;
		}
		else
		{
			return 0;
		}
		}
	}
	bool  Game_vs_Bot::winable(const sf::Vector2i& pos, cz::Lines line , cz::Cell val)
	{
		if (line == cz::Lines::LEFTRIGHT)
		{
			int len = 1;

			for (int i = 1;; i++)
			{
				int x = pos.x - i, y = pos.y;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			for (int i = 1;; i++)
			{
				int x = pos.x + i, y = pos.y;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			if (len >= field.get_len_to_win())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (line == cz::Lines::UPDOWN)
		{
			int len = 1;

			for (int i = 1;; i++)
			{
				int x = pos.x, y = pos.y - i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			for (int i = 1;; i++)
			{
				int x = pos.x, y = pos.y + i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			if (len >= field.get_len_to_win())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (line == cz::Lines::UPLEFT)
		{
			int len = 1;

			for (int i = 1;; i++)
			{
				int x = pos.x - i, y = pos.y - i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			for (int i = 1;; i++)
			{
				int x = pos.x + i, y = pos.y + i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			if (len >= field.get_len_to_win())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if (line == cz::Lines::UPRIGHT)
		{
			int len = 1;

			for (int i = 1;; i++)
			{
				int x = pos.x - i, y = pos.y + i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			for (int i = 1;; i++)
			{
				int x = pos.x + i, y = pos.y - i;
				if (field.get_value(x, y) == cz::Cell::NONE || field.get_value(x, y) == val)
				{
					len++;
				}
				else
				{
					break;
				}
			}
			if (len >= field.get_len_to_win())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	void Game_vs_Bot::need_conter(const sf::Vector2i& pos , std::vector<int>& values) // checks right down
	{


		cz::Cell val = field.get_value(pos.x, pos.y);
		

		
		if ( val == cz::Cell::ERROR || val == bot_value)
		{
			return;
		}

		//left - right
		if (winable(pos, cz::Lines::LEFTRIGHT,val))
		{
			int k1 = 0, len = 0, free_field = 0;

			for (k1 = 1; k1 < field.get_len_to_win(); k1++)
			{
				int x = pos.x + k1, y = pos.y;
				if (field.get_value(x, y) == cz::Cell::NONE)
				{
					free_field++;
				}
			}
			for (k1 = 1; k1 < field.get_len_to_win(); k1++)
			{
				int x = pos.x + k1, y = pos.y;
				if (field.get_value(x, y) == cz::Cell::NONE)
				{
					values[x * field.get_size().x + y] += field.get_len_to_win() - free_field;
				}
			}
		}
		if (winable(pos, cz::Lines::UPDOWN , val))
		{
			int k1 = 0, len = 0, free_field = 0;

			for (k1 = 1; k1 < field.get_len_to_win(); k1++)
			{
				int x = pos.x , y = pos.y + k1;
				if (field.get_value(x, y) == cz::Cell::NONE)
				{
					free_field++;
				}
			}
			for (k1 = 1; k1 < field.get_len_to_win(); k1++)
			{
				int x = pos.x , y = pos.y + k1;
				if (field.get_value(x, y) == cz::Cell::NONE)
				{
					values[x * field.get_size().x + y] += field.get_len_to_win() - free_field;
				}
			}
		}
		if (winable(pos, cz::Lines::UPLEFT , val))
		{
			int k1 = 0, len = 0, free_field = 0;

			for (k1 = 1; k1 < field.get_len_to_win(); k1++)
			{
				int x = pos.x + k1, y = pos.y + k1;
				if (field.get_value(x, y) == cz::Cell::NONE)
				{
					free_field++;
				}
			}
			for (k1 = 1; k1 < field.get_len_to_win(); k1++)
			{
				int x = pos.x + k1, y = pos.y + k1;
				if (field.get_value(x, y) == cz::Cell::NONE)
				{
					values[x * field.get_size().x + y] += field.get_len_to_win() - free_field;
				}
			}
		}
		if (winable(pos, cz::Lines::UPRIGHT , val))
		{
			bool reverse = 0;
			int k1 = 0, len = 0, free_field = 0;

			for (k1 = 1; k1 < field.get_len_to_win(); k1++)
			{
				int x = pos.x - k1, y = pos.y + k1;
				if (field.get_value(x, y) == cz::Cell::NONE)
				{
					free_field++;
				}
				if (field.get_value(x, y) == cz::Cell::ERROR)
				{
					reverse = 1;
					break;
				}
			}
			if (reverse)
			{
				k1 = 0; len = 0; free_field = 0;
				for (k1 = 1; k1 < field.get_len_to_win(); k1++)
				{
					int x = pos.x + k1, y = pos.y - k1;
					if (field.get_value(x, y) == cz::Cell::NONE)
					{
						free_field++;
					}
					if (field.get_value(x, y) == cz::Cell::ERROR)
					{
						reverse = 1;
						break;
					}
				}
				for (k1 = 1; k1 < field.get_len_to_win(); k1++)
				{
					int x = pos.x + k1, y = pos.y - k1;
					if (field.get_value(x, y) == cz::Cell::NONE)
					{
						values[x * field.get_size().x + y] += field.get_len_to_win() - free_field;
					}
				}
			}
			if (!reverse)
			{
				for (k1 = 1; k1 < field.get_len_to_win(); k1++)
				{
					int x = pos.x - k1, y = pos.y + k1;
					if (field.get_value(x, y) == cz::Cell::NONE)
					{
						values[x * field.get_size().x + y] += field.get_len_to_win() - free_field;
					}
				}
			}
		}
		
	
	}
}
