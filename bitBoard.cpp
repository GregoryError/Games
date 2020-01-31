#include <iostream>
#include <cstdint>
#include <cmath>

namespace Game 
{
	template <int X, int Y>
	class Board
	{
	private:
		const static std::size_t space_for_cells = ((X * Y / 8) + 1) * 2;
		std::uint8_t board[space_for_cells] = {};
		bool get_cell_bit(const std::size_t bit) const { return board[bit / 8] & (1 << (bit % 8)); }
		void set_cell_bit(const std::size_t bit, const bool&  bit_val)
		{
			if (bit_val)
				board[bit / 8] |= (1 << (bit % 8));
			else 
				board[bit / 8] &= ~(1 << (bit % 8));
		}
		// TODO: kindes of forces
		// TODO: in which possitions  
	public:
		Board() {}
		int get_cell(const std::size_t& pos) const; // "0" - empty, "1" - filled with side 1, "2" - filled with side 2
		void set_cell(const int& pos, const int& side);	
		void diagnostic() const;
		void make_move(const int& posFrom, const int& posTo);	
	};

	template <int X, int Y>
	void Board<X, Y>::make_move(const int& posFrom, const int& posTo)
	{
		if(get_cell_bit(posFrom))
		{
			if (get_cell(posFrom) == 1)
				set_cell(posTo, 0);
			
			if (get_cell(posFrom) == 2)
				set_cell(posTo, 1);

			set_cell_bit(posFrom, false);
		}
		else
			return;		
	}

	template <int X, int Y>
	void Board<X, Y>::diagnostic() const
	{
		std::cout << "\nDiagnostic output:\n";
		std::cout << "GameBoard:\n";
		for (int i = 0; i < X * Y; ++i)
		{
	       		 std::cout << get_cell_bit(i) << " ";
		        	 if ((i + 1)  % X  == 0)
			 		std::cout << '\n';
		}
	}

	template <int X, int Y>	
	int Board<X, Y>::get_cell(const std::size_t& pos) const
	{
		if (get_cell_bit(pos) && get_cell_bit(pos * 2))
			return 1;
		if (get_cell_bit(pos) && !get_cell_bit(pos * 2))
			return 2;
		return 0;
	}
	
	template <int X, int Y>
	void Board<X, Y>::set_cell(const int& pos, const int& side)
	{
		if (side == 0)
		{
			set_cell_bit(pos, true);
			set_cell_bit(pos + X * Y, false);
		}
		if (side == 1)
		{
			set_cell_bit(pos, true);
			set_cell_bit(pos + X * Y, true);
		}
	}
}

int main(int argc, char* argv[])
{
	Game::Board<8, 8> obj;
	
	for (int i = 0; i < 16; ++i)
	{
		obj.set_cell(i, 0);
		obj.set_cell(63 - i, 1);
	}

	obj.diagnostic();
	
	std::cout << "Enter your move:\n";
	int x, y;
	while (std::cin >> x >> y)
	{
		std::cout << "\033[2J\033[1;1H";
		obj.make_move(x, y);
		obj.diagnostic();
		std::cout << "Enter your move:\n";
	}
	
	
//	obj.diagnostic();

//	std::cout << obj.get_cell(3) << '\n';

//	obj.make_move(3, 11);

//	obj.make_move(11, 12);

//	obj.make_move(3, 11);
	
//	obj.make_move(60, 54);

//	obj.diagnostic();






//	std::cout << obj.get_cell(0) << '\n';
//	std::cout << obj.get_cell(3) << '\n';
//	std::cout << obj.get_cell(60) << '\n';

	std::cout << "\nsizeof(obj):\n";
	std::cout << sizeof(obj) << '\n';
	
	return 0;
}

