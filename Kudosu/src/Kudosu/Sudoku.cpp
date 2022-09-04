#include "kdspch.hpp"

#include "Sudoku.hpp"

namespace Kudosu {

	Sudoku::Sudoku(const std::string& data)
	{
		if (data.size() != SUDOKU_SIZE)
		{
			std::memset(m_Data, 0, SUDOKU_SIZE * sizeof(uint8_t));
			std::cout << "Invalid input size! Size was: " << data.size() << ", but expected " << SUDOKU_SIZE << "!\n";
			return;
		}

		std::cout << "Initializing Sudoku...\n";
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

		std::cout << "Initialization complete!\n";
	}

	bool Sudoku::Solve(uint8_t i)
	{
		for (; i < SUDOKU_SIZE; i++)
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
		for (uint8_t y = 0; y < GRID_SIZE; y++)
		{
			if (y % 3 == 0)
				std::cout << "-------------\n";
			
			for (uint8_t x = 0; x < GRID_SIZE; x++)
			{
				if (x % 3 == 0)
					std::cout << '|';

				std::cout << char(m_Data[y * GRID_SIZE + x] + '0');

				if (x + 1 == GRID_SIZE)
					std::cout << '|';
			}

			std::cout << '\n';
		}

		std::cout << "-------------\n";
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