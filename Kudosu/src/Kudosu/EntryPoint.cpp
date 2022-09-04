#include "kdspch.hpp"

#include "Kudosu/Sudoku.hpp"

int main(int argc, char** argv)
{
	//if (argc < 2)
	//{
	//	std::cout << "[Kudosu]: No arguments specified!\n";
	//	return 1;
	//}
	//
	//for (size_t i = 1; i < argc; i++)
	//{
	//	//Do something with argv[i]
	//}

	const std::string exampleInput = R"(
		530070000
		600195000
		098000060
		800060003
		400803001
		700020006
		060000280
		000419005
		000080079
	)";

	std::string result;
	for (const char c : exampleInput)
	{
		if (std::isdigit(c))
			result += c;
	}

	Kudosu::Sudoku sudoku(result);
	std::cout << "Input Sudoku was:\n\n";
	sudoku.Print();
	std::cout << '\n';

	std::cout << (sudoku.Solve() ? "Sudoku was solved!\n" : "Sudoku was unsolvable!\n");
	std::cout << '\n';

	sudoku.Print();

	system("pause");
	return 0;
}