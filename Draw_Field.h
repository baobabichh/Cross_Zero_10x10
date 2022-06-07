#pragma once
#include "Field.h"

namespace cz
{
	class Draw_Field : public Field
	{
	public:
		Draw_Field(sf::Texture* cross_tx, sf::Texture* zero_tx, const sf::Vector2i& position, const int& size_x, const int& size_y, const int& len_to_win, const sf::Vector2i& field_size, const int& line_width, const int& distance);
		~Draw_Field();

		virtual void reset();

		void draw(sf::RenderWindow& window);
		void update(const float& dt , sf::RenderWindow& window , cz::Cell& turn );

		void set_position(const sf::Vector2i& position);
		const  sf::Vector2i& get_position() const;

		void set_line_width(const int& line_width);
		const int& get_line_width()const;

		void set_distance(const int& distance);
		const int& get_distance()const;

		void set_field_size(const sf::Vector2i& field_size);
		const sf::Vector2i& get_field_size()const;


		

		virtual void set_value(const int& x, const int& y, const Cell& value);
	private:
		sf::Vector2i field_size, cell_size_start, cell_size_end, position;
		int line_width, distance;
		float scale_x, scale_y;
		sf::Texture* cross_tx;
		sf::Texture* zero_tx;
		std::vector<sf::Sprite> sprites;
		std::vector<sf::RectangleShape> lines;
		sf::Vector2i prev_hover;
		sf::Color line_color;
		sf::Sprite hover_sp;
		bool prev_pkm;
	};
}