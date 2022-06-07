#include "Field.h"

//overload
namespace cz {
	std::ostream& operator<<(std::ostream& out, const Winer& value)
	{
		if (value == Winer::CROSS)
		{
			out << 'X';
		}
		else if (value == Winer::ZERO)
		{
			out << 'O';
		}
		else if (value == Winer::NONE)
		{
			out << ' ';
		}
		else
		{
			out << "TIE";
		}
		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Cell& value)
	{
		if (value == Cell::CROSS)
		{
			out << 'X';
		}
		else if (value == Cell::ZERO)
		{
			out << 'O';
		}
		else if (value == Cell::NONE)
		{
			out << ' ';
		}
		else
		{
			out << "ERROR";
		}
		return out;
	}
	std::istream& operator>>(std::istream& in, Cell& value)
	{
		char q;
		in >> q;
		value = static_cast<Cell>(q);
		return in;
	}

	//field
	Field::Field()
	{
		this->size_x = 10;
		this->size_y = 10;
		this->len_to_win = 5;

		field.resize(size_x * size_y);

		for (auto&& it : field)
		{
			it = Cell::NONE;
		}
	}
	const Cell& Field::get_value(const int& i)
	{
		if (i >= 0 && i < this->size_x)
		{
			return field[i];
		}
		else
		{
			return Cell::ERROR;
		}
	}
	Field::Field(const int& size_x, const int& size_y, const int& len_to_win)
	{
		this->size_x = size_x;
		this->size_y = size_y;
		this->len_to_win = len_to_win;

		field.resize(size_x * size_y);

		for (auto&& it : field)
		{
			it = Cell::NONE;
		}
	}

	//
	void Field::reset()
	{
		for (auto&& it : field)
		{
			it = Cell::NONE;
		}
	}

	void Field::set_value(const int& x, const int& y, const Cell& value)
	{
		if (x >= 0 && x < this->size_x && y >= 0 && y < this->size_y)
		{
			field[x * size_x + y] = value;
		}
		else
		{
			return;
		}
	}
	const Cell& Field::get_value(const int& x, const int& y)
	{
		if (x >= 0 && x < this->size_x && y >= 0 && y < this->size_y)
		{
			return field[x * size_x + y];
		}
		else
		{
			return Cell::ERROR;
		}
	}
	void Field::to_stream(std::ostream& out)
	{
		for (int i = 0; i < field.size(); i++)
		{
			if (i % size_x == 0)
			{
				out << std::endl;
			}
			out << std::setw(3) << field[i];
		}
	}
	const Winer& Field::check_winer()
	{
		cz::Cell turn = cz::Cell::CROSS;
		cz::Cell turn2 = cz::Cell::CROSS;
		cz::Winer res = cz::Winer::NONE;

		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < size_y; j++)
			{
				//cross
				turn = cz::Cell::CROSS;
				//left right
				{
					int free_cells = 0, len = 0, x = 0, y = 0; bool winable = 1, last = 0;
					for (int k = 0; k < get_len_to_win(); k++)
					{
						x = i + k; y = j;
						if (get_value(x, y) != turn)
						{
							winable = 0;
							break;
						}
						if (get_value(x, y) == turn)
						{
							len++;
						}
					}
					if (len == get_len_to_win() && winable)
					{
						if (turn == cz::Cell::CROSS)
							res = cz::Winer::CROSS;
						else if (turn == cz::Cell::ZERO)
							res = cz::Winer::ZERO;
						return res;
					}
				}
				//up down
				{
					int free_cells = 0, len = 0, x = 0, y = 0; bool winable = 1, last = 0;
					for (int k = 0; k < get_len_to_win(); k++)
					{
						x = i; y = j + k;
						if (get_value(x, y) != turn)
						{
							winable = 0;
							break;
						}
						if (get_value(x, y) == turn)
						{
							len++;
						}
					}
					if (len == get_len_to_win() && winable)
					{
						if (turn == cz::Cell::CROSS)
							res = cz::Winer::CROSS;
						else if (turn == cz::Cell::ZERO)
							res = cz::Winer::ZERO;
						return res;
					}
				}
				//left up
				{
					int free_cells = 0, len = 0, x = 0, y = 0; bool winable = 1, last = 0;
					for (int k = 0; k < get_len_to_win(); k++)
					{
						x = i + k; y = j + k;
						if (get_value(x, y) != turn)
						{
							winable = 0;
							break;
						}
						if (get_value(x, y) == turn)
						{
							len++;
						}
					}
					if (len == get_len_to_win() && winable)
					{
						if (turn == cz::Cell::CROSS)
							res = cz::Winer::CROSS;
						else if (turn == cz::Cell::ZERO)
							res = cz::Winer::ZERO;
						return res;
					}
				}
				//up right
				{
					int free_cells = 0, len = 0, x = 0, y = 0; bool winable = 1, last = 0;
					for (int k = 0; k < get_len_to_win(); k++)
					{
						x = i - k; y = j + k;
						if (get_value(x, y) != turn)
						{
							winable = 0;
							break;
						}
						if (get_value(x, y) == turn)
						{
							len++;
						}
					}
					if (len == get_len_to_win() && winable)
					{
						if (turn == cz::Cell::CROSS)
							res = cz::Winer::CROSS;
						else if (turn == cz::Cell::ZERO)
							res = cz::Winer::ZERO;
						return res;
					}
				}

				//zero
				turn = cz::Cell::ZERO;
					//left right
				{
					int free_cells = 0, len = 0, x = 0, y = 0; bool winable = 1, last = 0;
					for (int k = 0; k < get_len_to_win(); k++)
					{
						x = i + k; y = j;
						if (get_value(x, y) != turn)
						{
							winable = 0;
							break;
						}
						if (get_value(x, y) == turn)
						{
							len++;
						}
					}
					if (len == get_len_to_win() && winable)
					{
						if (turn == cz::Cell::CROSS)
							res = cz::Winer::CROSS;
						else if (turn == cz::Cell::ZERO)
							res = cz::Winer::ZERO;
						return res;
					}
				}
					//up down
				{
					int free_cells = 0, len = 0, x = 0, y = 0; bool winable = 1, last = 0;
					for (int k = 0; k < get_len_to_win(); k++)
					{
						x = i; y = j + k;
						if (get_value(x, y) != turn)
						{
							winable = 0;
							break;
						}
						if (get_value(x, y) == turn)
						{
							len++;
						}
					}
					if (len == get_len_to_win() && winable)
					{
						if (turn == cz::Cell::CROSS)
							res = cz::Winer::CROSS;
						else if (turn == cz::Cell::ZERO)
							res = cz::Winer::ZERO;
						return res;
					}
				}
				//left up
				{
					int free_cells = 0, len = 0, x = 0, y = 0; bool winable = 1, last = 0;
					for (int k = 0; k < get_len_to_win(); k++)
					{
						x = i + k; y = j + k;
						if (get_value(x, y) != turn)
						{
							winable = 0;
							break;
						}
						if (get_value(x, y) == turn)
						{
							len++;
						}
					}
					if (len == get_len_to_win() && winable)
					{
						if (turn == cz::Cell::CROSS)
							res = cz::Winer::CROSS;
						else if (turn == cz::Cell::ZERO)
							res = cz::Winer::ZERO;
						return res;
					}
				}
				//up right
				{
					int free_cells = 0, len = 0, x = 0, y = 0; bool winable = 1, last = 0;
					for (int k = 0; k < get_len_to_win(); k++)
					{
						x = i - k; y = j + k;
						if (get_value(x, y) != turn)
						{
							winable = 0;
							break;
						}
						if (get_value(x, y) == turn)
						{
							len++;
						}
					}
					if (len == get_len_to_win() && winable)
					{
						if (turn == cz::Cell::CROSS)
							res = cz::Winer::CROSS;
						else if (turn == cz::Cell::ZERO)
							res = cz::Winer::ZERO;
						return res;
					}
				}
			}
		}
	
		bool is_tie = 1;
		for (auto&& it : field)
		{
			if (it == cz::Cell::NONE)
			{
				is_tie = 0;
			}
		}
		if (is_tie)
		{
			return cz::Winer::TIE;
		}
		return Winer::NONE;
	}
	///
	//set
	void Field::set_size(const int& size_x, const int& size_y)
	{
		this->size_x = size_x;
		this->size_y = size_y;
	}
	void Field::set_len_to_win(const int& len_to_win)
	{
		this->len_to_win = len_to_win;
	}
	sf::Vector2i Field::get_size()
	{
		sf::Vector2i res(size_x, size_y);
		return res;
	}
	//get
	const int& Field::get_len_to_win()
	{
		return this->len_to_win;
	}

	//


	Field::~Field()
	{

	}
}