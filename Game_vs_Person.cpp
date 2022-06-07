#include "Game_vs_Person.h"

namespace cz
{
	Game_vs_Person::Game_vs_Person(sf::Texture* cross_tx, sf::Texture* zero_tx, sf::Font* font,
		const sf::Vector2i& position,
		const sf::Vector2i& size, const int& len_to_win,
		const sf::Vector2i& field_size_px,
		const int& line_width,
		const int& distance, const int& left_distance) : field(cross_tx, zero_tx, sf::Vector2i(position.x + left_distance + MARGIN * 1.5, position.y + MARGIN * 1.5), size.x, size.y, len_to_win, sf::Vector2i(field_size_px.x - MARGIN, field_size_px.y - MARGIN), line_width, distance), turn(cz::Cell::CROSS)
	{
		//color
		this->bgc = sf::Color(246, 172, 189, 200);

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
		sprite_scale = (float)(left_distance - MARGIN * 2) / cross_tx->getSize().x;
		this->hod_sp.setColor(sf::Color::White);
		this->hod_sp.setPosition(hod_text.getGlobalBounds().left, hod_text.getGlobalBounds().top + hod_text.getGlobalBounds().height + MARGIN);
		this->hod_sp.setScale(sprite_scale, sprite_scale);
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
	}
	void Game_vs_Person::draw(sf::RenderWindow& window)
	{
		
		if (!is_ended && !paused)
		{
			window.draw(rect);
			field.draw(window);
			window.draw(hod_text);
			window.draw(hod_sp);
		}
		else if (is_ended)
		{
			winer_text.setScale(winer_text.getLocalBounds().width / window.getSize().x, winer_text.getLocalBounds().width / window.getSize().x);
			window.draw(rect);
			field.draw(window);
			window.draw(hod_text);
			window.draw(hod_sp);
			window.draw(winer_text);
		}
	}
	void Game_vs_Person::update(const float& dt, sf::RenderWindow& window)
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

	void Game_vs_Person::end()
	{
		is_ended = 1;
		paused = 1;
	}
	bool Game_vs_Person::ended()
	{
		return is_ended;
	}

	void Game_vs_Person::restart()
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
		field.reset();
	}

	void Game_vs_Person::pause()
	{
		paused = 1;
	}
	void Game_vs_Person::stop()
	{
		is_ended = 1;
	}
	void Game_vs_Person::start()
	{
		paused = 0;
	}
	Game_vs_Person::~Game_vs_Person()
	{
	}
}
