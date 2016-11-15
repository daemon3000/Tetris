#include "DataAsset.h"

using namespace tetris;

bool DataAsset::loadFromFile(const std::string &filename)
{
	return m_document.load_file(filename.c_str());
}

std::string DataAsset::getString(const std::string &name, std::string def)
{
	auto node = m_document.document_element().child(name.c_str());
	if(node)
	{
		auto value = node.attribute("value");
		if(value)
		{
			return value.value();
		}
	}

	return def;
}

float DataAsset::getFloat(const std::string &name, float def)
{
	auto node = m_document.document_element().child(name.c_str());
	if(node)
	{
		auto value = node.attribute("value");
		if(value)
		{
			return value.as_float();
		}
	}
	
	return def;
}

int DataAsset::getInteger(const std::string &name, int def)
{
	auto node = m_document.document_element().child(name.c_str());
	if(node)
	{
		auto value = node.attribute("value");
		if(value)
		{
			return value.as_int();
		}
	}

	return def;
}

bool DataAsset::getBool(const std::string &name, bool def)
{
	auto node = m_document.document_element().child(name.c_str());
	if(node)
	{
		auto value = node.attribute("value");
		if(value)
		{
			return value.as_bool();
		}
	}

	return def;
}
