#pragma once

#include <TGUI/Widgets/ClickableWidget.hpp>
#include "ImageRenderer.h"

namespace tetris
{
	namespace ui
	{
		class Image : public tgui::ClickableWidget
		{
		public:

			typedef std::shared_ptr<Image> Ptr;
			typedef std::shared_ptr<const Image> ConstPtr;

			Image();
			Image(const tgui::Texture& texture, bool fullyClickable = true);
			static Image::Ptr create(const tgui::Texture& texture = {}, bool fullyClickable = true);
			static Image::Ptr copy(Image::ConstPtr picture);
			void setTexture(const tgui::Texture& texture, bool fullyClickable = true);
			const sf::String& getLoadedFilename() const;
			virtual void setSize(const tgui::Layout2d& size) override;
			using Transformable::setSize;
			void setSmooth(bool smooth = true);
			bool isSmooth() const;
			virtual bool mouseOnWidget(sf::Vector2f pos) const override;
			virtual void leftMouseReleased(sf::Vector2f pos) override;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			virtual void rendererChanged(const std::string& property, tgui::ObjectConverter& value) override;
			ImageRenderer* getRenderer() const;

		protected:
			virtual void rendererChanged(const std::string& property, tgui::ObjectConverter& value) override;
			virtual void update(sf::Time elapsedTime) override;
			virtual Widget::Ptr clone() const override
			{
				return std::make_shared<Image>(*this);
			}

		protected:
			tgui::Texture m_texture;
			tgui::Sprite  m_sprite;
			bool m_fullyClickable = true;
			bool m_possibleDoubleClick = false;
		};
	}
}