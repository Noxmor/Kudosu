#pragma once

#include "Kudosu/Core.hpp"

namespace Kudosu {

	class Sudoku
	{
	public:
		Sudoku(const std::string& data);
		~Sudoku() = default;

		bool Solve(const uint8_t startIndex = 0);

		void Print() const;
		
	private:
		bool IsValidPlacement(const uint8_t x, const uint8_t y, const uint8_t value) const;

		void SetDigit(const uint8_t x, const uint8_t y, const uint8_t value);
		void ClearDigit(const uint8_t x, const uint8_t y);

	private:
		uint8_t m_Data[SUDOKU_SIZE];

		uint16_t m_RowBitmap[GRID_SIZE] = { 0,0,0,0,0,0,0,0,0 };
		uint16_t m_ColumnBitmap[GRID_SIZE] = { 0,0,0,0,0,0,0,0,0 };
		uint16_t m_BoxBitmap[GRID_SIZE] = { 0,0,0,0,0,0,0,0,0 };
	};

}