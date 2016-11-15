#include <unordered_map>
#include "Tetromino.h"

using namespace tetris;

static std::unordered_map<TetrominoType, std::unordered_map<Rotation, std::vector<bool>>> TETROMINOS 
{
	{ 
		TetrominoType::I, 
		{ 
			{ Rotation::R0,   { false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false } },
			{ Rotation::R90,  { false, false, true, false, false, false, true, false, false, false, true, false, false, false, true, false } },
			{ Rotation::R180, { false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false } },
			{ Rotation::R270, { false, true, false, false, false, true, false, false, false, true, false, false, false, true, false, false } },
		}
	},
	{
		TetrominoType::J,
		{
			{ Rotation::R0,   { true, false, false, true, true, true, false, false, false } },
			{ Rotation::R90,  { false, true, true, false, true, false, false, true, false } },
			{ Rotation::R180, { false, false, false, true, true, true, false, false, true } },
			{ Rotation::R270, { false, true, false, false, true, false, true, true, false } },
		}
	},
	{
		TetrominoType::L,
		{
			{ Rotation::R0,   { false, false, true, true, true, true, false, false, false } },
			{ Rotation::R90,  { false, true, false, false, true, false, false, true, true } },
			{ Rotation::R180, { false, false, false, true, true, true, true, false, false } },
			{ Rotation::R270, { true, true, false, false, true, false, false, true, false } },
		}
	},
	{
		TetrominoType::O,
		{
			{ Rotation::R0,   { true, true, true, true } },
			{ Rotation::R90,  { true, true, true, true } },
			{ Rotation::R180, { true, true, true, true } },
			{ Rotation::R270, { true, true, true, true } },
		}
	},
	{
		TetrominoType::S,
		{
			{ Rotation::R0,   { false, true, true, true, true, false, false, false, false } },
			{ Rotation::R90,  { false, true, false, false, true, true, false, false, true } },
			{ Rotation::R180, { false, false, false, false, true, true, true, true, false } },
			{ Rotation::R270, { true, false, false, true, true, false, false, true, false } },
		}
	},
	{
		TetrominoType::T,
		{
			{ Rotation::R0,   { false, true, false, true, true, true, false, false, false } },
			{ Rotation::R90,  { false, true, false, false, true, true, false, true, false } },
			{ Rotation::R180, { false, false, false, true, true, true, false, true, false } },
			{ Rotation::R270, { false, true, false, true, true, false, false, true, false } },
		}
	},
	{
		TetrominoType::Z,
		{
			{ Rotation::R0,   { true, true, false, false, true, true, false, false, false } },
			{ Rotation::R90,  { false, false, true, false, true, true, false, true, false } },
			{ Rotation::R180, { false, false, false, true, true, false, false, true, true } },
			{ Rotation::R270, { false, true, false, true, true, false, true, false, false } },
		}
	}
};


Tetromino::Tetromino()
{
	m_paddingTop = m_paddingBottom = 0;
	m_paddingLeft = m_paddingRight = 0;
	m_rotation = Rotation::R0;
	setType(TetrominoType::None);
}

Tetromino::Tetromino(TetrominoType type)
{
	m_paddingTop = m_paddingBottom = 0;
	m_paddingLeft = m_paddingRight = 0;
	m_rotation = Rotation::R0;
	setType(type);
}

void Tetromino::calculatePadding()
{
	for(int y = 0; y < m_height; y++)
	{
		for(int x = 0; x < m_width; x++)
		{
			if(m_solid[y * m_width + x])
			{
				m_paddingTop = y;
				y = m_height;
				break;
			}
		}
	}

	for(int y = m_height - 1; y >= 0; y--)
	{
		for(int x = 0; x < m_width; x++)
		{
			if(m_solid[y * m_width + x])
			{
				m_paddingBottom = (m_height - 1) - y;
				y = -1;
				break;
			}
		}
	}

	for(int x = 0; x < m_width; x++)
	{
		for(int y = 0; y < m_height; y++)
		{
			if(m_solid[y * m_width + x])
			{
				m_paddingLeft = x;
				x = m_width;
				break;
			}
		}
	}

	for(int x = m_width - 1; x >= 0; x--)
	{
		for(int y = 0; y < m_height; y++)
		{
			if(m_solid[y * m_width + x])
			{
				m_paddingRight = (m_width - 1) - x;
				x = -1;
				break;
			}
		}
	}
}

void Tetromino::rotate()
{
	Rotation rotation = m_rotation;
	switch(rotation)
	{
	case tetris::Rotation::R0:
		rotation = Rotation::R90;
		break;
	case tetris::Rotation::R90:
		rotation = Rotation::R180;
		break;
	case tetris::Rotation::R180:
		rotation = Rotation::R270;
		break;
	case tetris::Rotation::R270:
		rotation = Rotation::R0;
		break;
	}

	setType(m_type, rotation);
}

void Tetromino::setRotation(Rotation rotation)
{
	setType(m_type, rotation);
}

void Tetromino::setType(TetrominoType type)
{
	setType(type, m_rotation);
}

void Tetromino::setType(TetrominoType type, Rotation rotation)
{
	m_type = type;
	m_rotation = rotation;

	if(type != TetrominoType::None)
		m_solid = TETROMINOS[type][m_rotation];
	else
		m_solid.clear();

	switch(type)
	{
	case tetris::TetrominoType::I:
		m_width = m_height = 4;
		m_color = TetrominoColor::Gray;
		break;
	case tetris::TetrominoType::J:
		m_width = m_height = 3;
		m_color = TetrominoColor::Purple;
		break;
	case tetris::TetrominoType::L:
		m_width = m_height = 3;
		m_color = TetrominoColor::Blue;
		break;
	case tetris::TetrominoType::O:
		m_width = m_height = 2;
		m_color = TetrominoColor::Yellow;
		break;
	case tetris::TetrominoType::S:
		m_width = m_height = 3;
		m_color = TetrominoColor::Green;
		break;
	case tetris::TetrominoType::T:
		m_width = m_height = 3;
		m_color = TetrominoColor::Pink;
		break;
	case tetris::TetrominoType::Z:
		m_width = m_height = 3;
		m_color = TetrominoColor::Red;
		break;
	default:
		m_width = m_height = 0;
		m_color = TetrominoColor::None;
		break;
	}

	calculatePadding();
}

bool Tetromino::isSolid(int x, int y) const
{
	if(x >= 0 && x < m_width && y >= 0 && y < m_height)
		return m_solid[y * m_width + x];

	return false;
}

bool Tetromino::isValid() const
{
	return m_type != TetrominoType::None && m_color != TetrominoColor::None;
}

int Tetromino::getWidth() const
{
	return m_width;
}

int Tetromino::getHeight() const
{
	return m_height;
}

int Tetromino::getPaddingTop() const
{
	return m_paddingTop;
}

int Tetromino::getPaddingBottom() const
{
	return m_paddingBottom;
}

int Tetromino::getPaddingLeft() const
{
	return m_paddingLeft;
}

int Tetromino::getPaddingRight() const
{
	return m_paddingRight;
}

TetrominoType Tetromino::getType() const
{
	return m_type;
}

TetrominoColor Tetromino::getColor() const
{
	return m_color;
}

Rotation Tetromino::getRotation() const
{
	return m_rotation;
}

