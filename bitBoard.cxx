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
		void set_cell_bit(const std::size_t bit) { board[bit / 8] |= (1 << (bit % 8)); }
		// TODO: kindes of forces
		// TODO: in which possitions  
	public:
		Board() {}
		int get_cell(const std::size_t& pos) const;
		void set_cell(const int& pos, const int& side);	
		void diagnostic() const;	
	};

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
		if (!get_cell_bit(pos))
			return 0;
		if (get_cell_bit(pos) && get_cell_bit(pos * 2))
			return 1;
		if (get_cell_bit(pos) && !get_cell_bit(pos * 2))
			return 2;
	}
	
	template <int X, int Y>
	void Board<X, Y>::set_cell(const int& pos, const int& side)
	{
		if (side == 0)
			set_cell_bit(pos);
		if (side == 1)
		{
			set_cell_bit(pos);
			set_cell_bit(pos * 2);
		}
	}
}

int main(int argc, char* argv[])
{
	Game::Board<8, 8> obj;
	obj.set_cell(3, 0);
	obj.set_cell(60, 1);
	obj.diagnostic();

	std::cout << "\nsizeof(obj):\n";
	std::cout << sizeof(obj) << '\n';
	
	return 0;
}




