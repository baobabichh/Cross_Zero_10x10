#include "Main_Menu_Bar.h"

namespace cz
{

	Main_Menu_Bar::~Main_Menu_Bar()
	{
	}
	Main_Menu_Bar::Main_Menu_Bar(sf::Font* font, const  std::wstring& text, const sf::Vector2i& position) 
	{
		this->anim_state = cz::Anim_State::NONE;
		this->_hiden = 0;
		this->pos = position;
		this->scale_value_default = 1.0;
		this->scale_value_end = 1.5;
		
		//anim setup
		this->max_frames = 50;
		this->current_frame = 0;
		this->prev_frame = 0;
		this->anim_speed = 400;



		//text
		this->text.setFont(*font);
		this->text.setString(text);
		this->text.setCharacterSize(40);
		this->text.setFillColor(sf::Color::Yellow);
		this->text.setStyle(sf::Text::Bold);
		this->text.setScale(scale_value_default, scale_value_default);
		this->text.setPosition(this->pos.x , this->pos.y);
		this->text.setOutlineThickness(1);
		this->text.setOutlineColor(sf::Color::Black);
		this->start_bounds = sf::IntRect(this->text.getGlobalBounds().left, this->text.getGlobalBounds().top, this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);

		//anim 
		text_scales.resize(max_frames);
		text_scales[0] = std::make_pair(sf::Vector2f(scale_value_default, scale_value_default), sf::Vector2i(pos.x, pos.y));
		for (int i = 1; i < text_scales.size() ; i++)
		{
			text_scales[i].first = sf::Vector2f(((scale_value_end - scale_value_default) / (float)max_frames) * i + scale_value_default, ((scale_value_end - scale_value_default) / (float)max_frames) * i + scale_value_default);
			text_scales[i].second = sf::Vector2i(pos.x - ((float)start_bounds.width * text_scales[i].first.x - (float)start_bounds.width) / 2.0, pos.y - ((float)start_bounds.height * text_scales[i].first.y - (float)start_bounds.height) / 2.0);
		}
		//this->text.setPosition(text_scales[0].second.x, text_scales[0].second.y);
	}

	void Main_Menu_Bar::draw(sf::RenderWindow& window)
	{
		if (!_hiden)
		{
			//sf::RectangleShape r;
			//r.setPosition(start_bounds.left, start_bounds.top);
			//r.setFillColor(sf::Color(100, 000, 000, 100));
			//r.setSize(sf::Vector2f( start_bounds.width, start_bounds.height));
			//window.draw(r);
			window.draw(text);

		}
	}
	void Main_Menu_Bar::update(sf::RenderWindow& window, const float& dt)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			prev_clic = now_click;
			now_click = 1;
		}
		else
		{
			prev_clic = now_click;
			now_click = 0;
		}
		if (!_hiden)
		{

			if (start_bounds.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && window.hasFocus())
			{
				anim_state = cz::Anim_State::INCREASES;

				if ((int)current_frame != (int)prev_frame)
				{
					text.setScale(text_scales.at(current_frame).first);
					text.setPosition(text_scales.at(current_frame).second.x, text_scales.at(current_frame).second.y);
				}
				if ((int)current_frame <= max_frames - 1)
				{
					prev_frame = current_frame;
					current_frame += 1.0 * dt * anim_speed;
				}
				if ((int)current_frame > max_frames - 1)
				{
					current_frame = max_frames - 1;
					prev_frame = current_frame;
				}

			}
			else if (anim_state == cz::Anim_State::INCREASES)
			{
				anim_state = cz::Anim_State::DECREASES;
			}
			else if(anim_state == cz::Anim_State::DECREASES)
			{

				if ((int)current_frame != (int)prev_frame ||(current_frame == max_frames-1 && prev_frame == max_frames - 1) || (current_frame == 0 && prev_frame == 0))
				{
					text.setScale(text_scales.at(current_frame).first);
					text.setPosition(text_scales.at(current_frame).second.x, text_scales.at(current_frame).second.y);
				}
				if (current_frame >= 0)
				{
					prev_frame = current_frame;
					current_frame -= 1.0 * dt * anim_speed;
				}
				if((int)current_frame < 0)
				{
					anim_state = cz::Anim_State::NONE;
					current_frame = 0;
					prev_frame = 0;
				}
			}
			else if (anim_state == cz::Anim_State::NONE)
			{
				this->text.setPosition(pos.x, pos.y);
				this->text.setScale(scale_value_default, scale_value_default);
			}
		}
	}
	bool Main_Menu_Bar::is_pressed(sf::RenderWindow& window)
	{
		if ( text.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && window.hasFocus() &&prev_clic && !now_click)
		{
			return 1;
		}
		return 0;
	}

	void Main_Menu_Bar::set_text(const std::wstring& text)
	{
		this->text.setString(text);


		//text
		this->text.setCharacterSize(40);
		this->text.setFillColor(sf::Color::Yellow);
		this->text.setStyle(sf::Text::Bold);
		this->text.setScale(scale_value_default, scale_value_default);
		this->text.setPosition(this->pos.x, this->pos.y);
		this->start_bounds = sf::IntRect(this->text.getGlobalBounds().left, this->text.getGlobalBounds().top, this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);

		text_scales.resize(max_frames);
		for (int i = 1; i < text_scales.size() + 1; i++)
		{
			text_scales[i - 1].first = sf::Vector2f(((scale_value_end - scale_value_default) / (float)max_frames) * i + scale_value_default, ((scale_value_end - scale_value_default) / (float)max_frames) * i + scale_value_default);
			text_scales[i - 1].first = sf::Vector2f((this->text.getGlobalBounds().width / 2 - start_bounds.width / 2), (this->text.getGlobalBounds().top / 2 - start_bounds.top / 2));
		}
	}
	const std::wstring& Main_Menu_Bar::get_text()const
	{
		return text.getString();
	}

	void Main_Menu_Bar::set_position(const sf::Vector2i& position)
	{
		this->pos = position;
		this->start_bounds.left = pos.x;
		this->start_bounds.top = pos.y;
		//anim 
		text_scales.resize(max_frames);
		text_scales[0] = std::make_pair(sf::Vector2f(scale_value_default, scale_value_default), sf::Vector2i(pos.x, pos.y));
		for (int i = 1; i < text_scales.size(); i++)
		{
			text_scales[i].first = sf::Vector2f(((scale_value_end - scale_value_default) / (float)max_frames) * i + scale_value_default, ((scale_value_end - scale_value_default) / (float)max_frames) * i + scale_value_default);
			text_scales[i].second = sf::Vector2i(pos.x - ((float)start_bounds.width * text_scales[i].first.x - (float)start_bounds.width) / 2.0, pos.y - ((float)start_bounds.height * text_scales[i].first.y - (float)start_bounds.height) / 2.0);
		}
	}
	const sf::Vector2i& Main_Menu_Bar::get_position()const
	{
		return pos;
	}

	void Main_Menu_Bar::show()
	{
		_hiden = 0;
	}
	void Main_Menu_Bar::hide()
	{
		_hiden = 1;
	}

	bool Main_Menu_Bar::is_hiden()const
	{
		return this->_hiden;
	}

	sf::IntRect Main_Menu_Bar::get_global_bounds()const
	{
		return sf::IntRect(text.getGlobalBounds().left, text.getGlobalBounds().top, text.getGlobalBounds().width, text.getGlobalBounds().height);
	}
	sf::IntRect Main_Menu_Bar::get_local_bounds()const
	{
		return start_bounds;
	}
}