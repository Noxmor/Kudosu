#include "kdspch.hpp"

#include "Sudoku.hpp"

namespace Kudosu {

	Sudoku::Sudoku(const std::string& data)
	{
		if (data.size() != SUDOKU_SIZE)
		{
			std::memset(m_Data, 0, SUDOKU_SIZE * sizeof(uint8_t));
			return;
		}

		for (uint8_t i = 0; i < SUDOKU_SIZE; i++)
		{
			const uint8_t digit = std::isdigit(data[i]) ? data[i] - '0' : 0;
			m_Data[i] = digit;

			if (!digit)
				continue;

			m_RowBitmap[i / GRID_SIZE] |= BIT(digit - 1);
			m_ColumnBitmap[i % GRID_SIZE] |= BIT(digit - 1);
			m_BoxBitmap[((i / GRID_SIZE) / 3) * 3 + ((i % GRID_SIZE) / 3)] |= BIT(digit - 1);
		}
	}

	bool Sudoku::Solve(const uint8_t startIndex)
	{
		for (uint8_t i = startIndex; i < SUDOKU_SIZE; i++)
		{
			if (m_Data[i])
				continue;

			const uint8_t x = i % GRID_SIZE;
			const uint8_t y = i / GRID_SIZE;

			for (uint8_t n = 1; n <= 9; n++)
			{
				if (!IsValidPlacement(x, y, n))
					continue;

				SetDigit(x, y, n);

				if (Solve(i))
					return true;

				ClearDigit(x, y);
			}

			return false;
		}

		return true;
	}

	void Sudoku::Print() const
	{
		for (uint8_t i = 0; i < SUDOKU_SIZE; i++)
		{
			std::cout << char(m_Data[i] + '0');

			if ((i + 1) % GRID_SIZE == 0)
				std::cout << '\n';
		}
	}

	bool Sudoku::IsValidPlacement(const uint8_t x, const uint8_t y, const uint8_t digit) const
	{
		return !(m_RowBitmap[y] & BIT(digit - 1) || m_ColumnBitmap[x] & BIT(digit - 1) || m_BoxBitmap[(y / 3) * 3 + (x / 3)] & BIT(digit - 1));
	}

	void Sudoku::SetDigit(const uint8_t x, const uint8_t y, const uint8_t digit)
	{
		m_Data[y * GRID_SIZE + x] = digit;
		m_RowBitmap[y] |= BIT(digit - 1);
		m_ColumnBitmap[x] |= BIT(digit - 1);
		m_BoxBitmap[(y / 3) * 3 + (x / 3)] |= BIT(digit - 1);
	}

	void Sudoku::ClearDigit(const uint8_t x, const uint8_t y)
	{
		const uint8_t digit = m_Data[y * GRID_SIZE + x];
		m_Data[y * GRID_SIZE + x] = 0;
		m_RowBitmap[y] &= ~BIT(digit - 1);
		m_ColumnBitmap[x] &= ~BIT(digit - 1);
		m_BoxBitmap[(y / 3) * 3 + (x / 3)] &= ~BIT(digit - 1);
	}

}