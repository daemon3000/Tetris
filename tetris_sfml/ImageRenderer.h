#pragma once

#include <TGUI/Renderers/WidgetRenderer.hpp>

namespace tetris
{
	namespace ui
	{
		struct ImageRenderer : public tgui::WidgetRenderer
		{
			void setBorders(const tgui::Borders& borders);
			tgui::Borders getBorders() const;

			void setSlicedScaling(bool slicedScaling);
			bool getSlicedScaling() const;
		};
	}
}
