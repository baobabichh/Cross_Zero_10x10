#include "Draw_Field.h"


namespace cz
{
	Draw_Field::~Draw_Field()
	{
	}

	Draw_Field::Draw_Field(sf::Texture* cross_tx, sf::Texture* zero_tx,
		const sf::Vector2i& position,
		const int& size_x, const int& size_y,
		const int& len_to_win, const sf::Vector2i& field_size,
		const int& line_width, const int& distance) : Field(size_x, size_y, len_to_win)
	{
		prev_pkm = 0;
		this->position = position;

		std::cout << "size : " << size_x * size_y << std::endl;
		line_color = sf::Color::Black;

		prev_hover.x = -1;
		prev_hover.y = -1;

		this->cross_tx = cross_tx;
		this->zero_tx = zero_tx;

		this->set_len_to_win(len_to_win);
		this->set_size(size_x, size_y);

		this->line_width = line_width;
		this->distance = distance;

		this->field_size = field_size;

		//img setup

		sf::Sprite sp;
		sp.setTexture(*cross_tx);

		this->cell_size_start.x = sp.getGlobalBounds().width;
		this->cell_size_start.y = sp.getGlobalBounds().height;

		cell_size_end.x = (field_size.x - (size_x - 1) * line_width - (size_x * 2) * distance) / size_x;
		cell_size_end.y = (field_size.y - (size_y - 1) * line_width - (size_y * 2) * distance) / size_y;

		scale_x = (float)cell_size_end.x / (float)cell_size_start.x;
		scale_y = (float)cell_size_end.y / (float)cell_size_start.y;

		//lines
		lines.resize(size_x - 1 + size_y - 1);

		for (int i = 0; i < size_x - 1; i++)
		{
			lines[i].setPosition(sf::Vector2f((distance * 2 + cell_size_end.x) * (i + 1) + line_width * (i), 0));
			lines[i].move(position.x, position.y);
			lines[i].setSize(sf::Vector2f(line_width, field_size.y));
			lines[i].setFillColor(line_color);
		}
		for (int i = size_x - 1; i < size_x - 1 + size_y - 1; i++)
		{
			lines[i].setPosition(sf::Vector2f(0, (distance * 2 + cell_size_end.y) * (i - size_x + 2) + line_width * (i - size_x + 1)));
			lines[i].move(position.x, position.y);
			lines[i].setSize(sf::Vector2f(field_size.x, line_width));
			lines[i].setFillColor(line_color);
			//lines[i].setTextureRect(sf::IntRect( 0, (distance * 2 + cell_size_end.y) * (i + 1), field_size.x ,line_width));
		}
		//sprites
		sprites.resize(size_x * size_y);
		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < size_y; j++)
			{
				sprites[i * get_size().x + j].setTextureRect(sf::IntRect(0, 0, cell_size_start.x, cell_size_start.y));
				sprites[i * size_x + j].setPosition((distance + i * (distance * 2 + line_width + cell_size_end.x)), (distance + j * (distance * 2 + line_width + cell_size_end.y)));
				sprites[i * size_x + j].move(position.x, position.y);
			}
		}
		for (auto&& it : sprites)
		{
			it.setColor(sf::Color::White);
			it.setScale(scale_x, scale_y);

		}
		hover_sp.setColor(sf::Color::White);
		hover_sp.setScale(scale_x, scale_y);
	}
	void  Draw_Field::set_value(const int& x, const int& y, const Cell& value)
	{
		Field::set_value(x, y, value);
		if (x * get_size().x + y >= 0 && x * get_size().x + y < this->get_size().x * this->get_size().y)
		{
			sprites[x * get_size().x + y].setColor(sf::Color::White);
			if (value == Cell::CROSS)
			{
				sprites[x * get_size().x + y].setTexture(*this->cross_tx);
			}
			else if (value == Cell::ZERO)
			{
				sprites[x * get_size().x + y].setTexture(*this->zero_tx);
			}
			else if (value == Cell::NONE)
			{
				sprites[x * get_size().x + y].setTexture(sf::Texture());
			}
		}
	}
	void  Draw_Field::reset()
	{
		Field::reset();
		for (auto&& it : sprites)
		{
			it.setTexture(sf::Texture());
			//it.setTextureRect(sf::IntRect(0,0,0,0));
			it.setColor(sf::Color::Transparent);
		}
		hover_sp.setColor(sf::Color::White);
	}

	void Draw_Field::draw(sf::RenderWindow& window)
	{
		for (auto&& it : lines)
		{
			window.draw(it);
		}
		for (auto && it : sprites)
		{
			window.draw(it);
		}
		window.draw(hover_sp);
	}
	void Draw_Field::update(const float& dt , sf::RenderWindow& window, cz::Cell& turn)
	{
		sf::Event event;
		window.pollEvent(event);

			for (int i = 0; i < get_size().x; i++)
			{
				for (int j = 0; j < get_size().y; j++)
				{


					if (sprites[i * get_size().x + j].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && get_value(i, j) == cz::Cell::NONE)
					{
						hover_sp.setColor(sf::Color::White);
						hover_sp.setPosition(sprites[i * get_size().x + j].getPosition());
						if (turn == cz::Cell::CROSS)
						{
							hover_sp.setTexture(*cross_tx);
						}
						else if (turn == cz::Cell::ZERO)
						{
							hover_sp.setTexture(*zero_tx);
						}
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !prev_pkm)
						{
							prev_pkm = 1;
							set_value(i, j, turn);
							if (turn == cz::Cell::CROSS)
							{
								turn = cz::Cell::ZERO;
							}
							else if (turn == cz::Cell::ZERO)
							{
								turn = cz::Cell::CROSS;
							}


						}
						else
						{
							prev_pkm = 0;
						}

					}
					else if (sprites[i * get_size().x + j].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && (get_value(i, j) == cz::Cell::ZERO || get_value(i, j) == cz::Cell::CROSS))
					{
						hover_sp.setColor(sf::Color::Transparent);
					}

				
			}
		}
	}




	
	void Draw_Field::set_position(const sf::Vector2i& position)
	{
		
		for (auto&& it : lines)
		{
			it.move(position.x - this->position.x, position.y - this->position.y);
		}
		for (auto&& it : sprites)
		{
			it.move(position.x - this->position.x, position.y - this->position.y);
		}
		this->position = position;
	}
	const  sf::Vector2i& Draw_Field::get_position() const
	{
		return position;
	}

	void Draw_Field::set_line_width(const int& line_width)
	{
		this->line_width = line_width;
		//img setup

		cell_size_end.x = (field_size.x - (get_size().x - 1) * line_width - (get_size().x * 2) * distance) / get_size().x;
		cell_size_end.y = (field_size.y - (get_size().y - 1) * line_width - (get_size().y * 2) * distance) / get_size().y;

		scale_x = (float)cell_size_end.x / (float)cell_size_start.x;
		scale_y = (float)cell_size_end.y / (float)cell_size_start.y;


		//lines

		for (int i = 0; i < get_size().x - 1; i++)
		{
			lines[i].setPosition(sf::Vector2f((distance * 2 + cell_size_end.x) * (i + 1) + line_width * (i), 0));
			lines[i].move(position.x, position.y);
			lines[i].setSize(sf::Vector2f(line_width, field_size.y));
		}
		for (int i = get_size().x - 1; i < get_size().x - 1 + get_size().y - 1; i++)
		{
			lines[i].setPosition(sf::Vector2f(0, (distance * 2 + cell_size_end.y) * (i - get_size().x + 2) + line_width * (i - get_size().x + 1)));
			lines[i].move(position.x, position.y);
			lines[i].setSize(sf::Vector2f(field_size.x, line_width));
		}
		for (int i = 0; i < get_size().x; i++)
		{
			for (int j = 0; j < get_size().y; j++)
			{
				sprites[i * get_size().x + j].setTextureRect(sf::IntRect(0, 0, cell_size_start.x, cell_size_start.y));
				sprites[i * get_size().x + j].setPosition((distance + i * (distance * 2 + line_width + cell_size_end.x)), (distance + j * (distance * 2 + line_width + cell_size_end.y)));
				sprites[i * get_size().x + j].move(position.x, position.y);
			}
		}
		for (auto&& it : sprites)
		{
			it.setScale(scale_x, scale_y);
		}
	}
	const int& Draw_Field::get_line_width()const
	{
		return line_width;
	}

	void Draw_Field::set_distance(const int& distance)
	{
		this->distance = distance;
		//img setup

		cell_size_end.x = (field_size.x - (get_size().x - 1) * line_width - (get_size().x * 2) * distance) / get_size().x;
		cell_size_end.y = (field_size.y - (get_size().y - 1) * line_width - (get_size().y * 2) * distance) / get_size().y;

		scale_x = (float)cell_size_end.x / (float)cell_size_start.x;
		scale_y = (float)cell_size_end.y / (float)cell_size_start.y;


		//lines

		for (int i = 0; i < get_size().x - 1; i++)
		{
			lines[i].setPosition(sf::Vector2f((distance * 2 + cell_size_end.x) * (i + 1) + line_width * (i), 0));
			lines[i].move(position.x, position.y);
			lines[i].setSize(sf::Vector2f(line_width, field_size.y));
		}
		for (int i = get_size().x - 1; i < get_size().x - 1 + get_size().y - 1; i++)
		{
			lines[i].setPosition(sf::Vector2f(0, (distance * 2 + cell_size_end.y) * (i - get_size().x + 2) + line_width * (i - get_size().x + 1)));
			lines[i].move(position.x, position.y);
			lines[i].setSize(sf::Vector2f(field_size.x, line_width));
		}
		for (int i = 0; i < get_size().x; i++)
		{
			for (int j = 0; j < get_size().y; j++)
			{
				sprites[i * get_size().x + j].setTextureRect(sf::IntRect(0, 0, cell_size_start.x, cell_size_start.y));
				sprites[i * get_size().x + j].setPosition((distance + i * (distance * 2 + line_width + cell_size_end.x)), (distance + j * (distance * 2 + line_width + cell_size_end.y)));
				sprites[i * get_size().x + j].move(position.x, position.y);
			}
		}
		for (auto&& it : sprites)
		{
			it.setScale(scale_x, scale_y);
		}
	}
	const int& Draw_Field::get_distance()const
	{
		return distance;
	}

	void Draw_Field::set_field_size(const sf::Vector2i& field_size)
	{
		this->field_size = field_size;

		cell_size_end.x = (field_size.x - (get_size().x - 1) * line_width - (get_size().x * 2) * distance) / get_size().x;
		cell_size_end.y = (field_size.y - (get_size().y - 1) * line_width - (get_size().y * 2) * distance) / get_size().y;

		scale_x = (float)cell_size_end.x / (float)cell_size_start.x;
		scale_y = (float)cell_size_end.y / (float)cell_size_start.y;


		//lines

		for (int i = 0; i < get_size().x - 1; i++)
		{
			lines[i].setPosition(sf::Vector2f((distance * 2 + cell_size_end.x) * (i + 1) + line_width * (i), 0));
			lines[i].move(position.x, position.y);
			lines[i].setSize(sf::Vector2f(line_width, field_size.y));
		}
		for (int i = get_size().x - 1; i < get_size().x - 1 + get_size().y - 1; i++)
		{
			lines[i].setPosition(sf::Vector2f(0, (distance * 2 + cell_size_end.y) * (i - get_size().x + 2) + line_width * (i - get_size().x + 1)));
			lines[i].move(position.x, position.y);
			lines[i].setSize(sf::Vector2f(field_size.x, line_width));
		}
		for (int i = 0; i < get_size().x; i++)
		{
			for (int j = 0; j < get_size().y; j++)
			{
				sprites[i * get_size().x + j].setTextureRect(sf::IntRect(0, 0, cell_size_start.x, cell_size_start.y));
				sprites[i * get_size().x + j].setPosition((distance + i * (distance * 2 + line_width + cell_size_end.x)), (distance + j * (distance * 2 + line_width + cell_size_end.y)));
				sprites[i * get_size().x + j].move(position.x, position.y);
			}
		}
		for (auto&& it : sprites)
		{
			it.setScale(scale_x, scale_y);
		}
	}
	const sf::Vector2i& Draw_Field::get_field_size()const
	{
		return field_size;
	}
}