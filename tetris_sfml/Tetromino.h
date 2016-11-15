#pragma once

#include <vector>
#include "TetrominoType.h"
#include "TetrominoColor.h"
#include "Rotation.h"

namespace tetris
{
	class Tetromino
	{
		std::vector<bool> m_solid;
		TetrominoType m_type;
		TetrominoColor m_color;
		int m_width, m_height;
		int m_paddingTop, m_paddingBottom;
		int m_paddingLeft, m_paddingRight;
		Rotation m_rotation;

		void calculatePadding();
	public:
		Tetromino();
		Tetromino(TetrominoType type);
		void rotate();
		void setRotation(Rotation rotation);
		void setType(TetrominoType type);
		void setType(TetrominoType type, Rotation rotation);
		bool isSolid(int x, int y) const;
		bool isValid() const;
		int getWidth() const;
		int getHeight() const;
		int getPaddingTop() const;
		int getPaddingBottom() const;
		int getPaddingLeft() const;
		int getPaddingRight() const;
		TetrominoType getType() const;
		TetrominoColor getColor() const;
		Rotation getRotation() const;
	};
}