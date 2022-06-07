#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


namespace cz
{
	enum class Cell : char
	{
		CROSS = 'X',
		ZERO = 'O',
		NONE = ' ',
		ERROR = '#',
	};

	std::ostream& operator<<(std::ostream& out, const Cell& value);
	std::istream& operator>>(std::istream& in, Cell& value);

	enum class Winer : char
	{
		CROSS = 'X',
		ZERO = 'O',
		NONE = ' ',
		TIE = 'T',
	};

	std::ostream& operator<<(std::ostream& out, const Winer& value);



	/*
	+-------x-------->
	|
	|
	y
	|
	|
	|
	*/

	class Field
	{
	private:
		std::vector<Cell> field;
		int size_x, size_y;
		int len_to_win;
	public:
		Field();
		Field(const int& size_x, const int& size_y, const int& len_to_win);
		~Field();

		virtual void set_value(const int& x, const int& y, const Cell& value);
		const Cell& get_value(const int& x, const int& y);
		const Cell& get_value(const int& i);

		void to_stream(std::ostream& out);
		const Winer& check_winer();

		virtual void reset();

		//set

		void set_size(const int& size_x, const int& size_y);
		void set_len_to_win(const int& len_to_win);

		//get
		sf::Vector2i get_size() ;
		const int& get_len_to_win();
	};
}


