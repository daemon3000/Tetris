#include "ImageRenderer.h"

using namespace tetris::ui;

void ImageRenderer::setBorders(const tgui::Borders& borders)
{
	setProperty("Borders", borders);
}

tgui::Borders ImageRenderer::getBorders() const
{
	auto it = m_data->propertyValuePairs.find("Borders");
	if(it != m_data->propertyValuePairs.end())
		return it->second.getOutline();
	else
		return {};
}

void ImageRenderer::setSlicedScaling(bool slicedScaling)
{
	setProperty("SlicedScaling", slicedScaling ? "true" : "false");
}

bool ImageRenderer::getSlicedScaling() const
{
	auto it = m_data->propertyValuePairs.find("Borders");
	if(it != m_data->propertyValuePairs.end())
	{
		std::string str = it->second.getString();
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str == "true";
	}
	
	return false;
}