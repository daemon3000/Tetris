#include <fstream>
#include "TextAsset.h"

using namespace tetris;

bool TextAsset::loadFromFile(const std::string &filename)
{
	try
	{
		std::ifstream file;

		file.open(filename);
		if(file.is_open())
		{
			m_text = { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
		}
		else
		{
			m_text = "";
			return false;
		}

		file.close();
		return true;
	}
	catch(const std::exception&)
	{
		m_text = "";
		return false;
	}
}

std::string TextAsset::getText() const
{
	return m_text;
}