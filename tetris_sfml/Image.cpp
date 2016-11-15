#include "Image.h"

using namespace tetris::ui;

Image::Image()
{
	m_type = "Image";
	m_callback.widgetType = "Image";

	addSignal("DoubleClicked");

	m_renderer = aurora::makeCopied<ImageRenderer>();
	setRenderer(m_renderer->getData());

	getRenderer()->setBorders(0);
	getRenderer()->setSlicedScaling(false);
}

Image::Image(const tgui::Texture& texture, bool fullyClickable) :
	Image{}
{
	setTexture(texture, fullyClickable);
}

Image::Ptr Image::create(const tgui::Texture& texture, bool fullyClickable)
{
	return std::make_shared<Image>(texture, fullyClickable);
}

Image::Ptr Image::copy(Image::ConstPtr image)
{
	if(image)
		return std::static_pointer_cast<Image>(image->clone());
	else
		return nullptr;
}

void Image::setTexture(const tgui::Texture& texture, bool fullyClickable)
{
	if(!m_sprite.isSet())
		setSize(texture.getImageSize());

	m_fullyClickable = fullyClickable;
	m_texture = texture;
	m_sprite.setTexture(texture);
	m_sprite.setPosition(getPosition());
	m_sprite.setOpacity(getRenderer()->getOpacity());
}

const sf::String& Image::getLoadedFilename() const
{
	return m_texture.getId();
}

void Image::setSize(const tgui::Layout2d& size)
{
	Widget::setSize(size);

	m_sprite.setSize(getSize());
}

void Image::setSmooth(bool smooth)
{
	m_texture.setSmooth(smooth);
}

bool Image::isSmooth() const
{
	return m_texture.isSmooth();
}

bool Image::mouseOnWidget(sf::Vector2f pos) const
{
	// Check if the mouse is on top of the image
	if(sf::FloatRect{ 0, 0, getSize().x, getSize().y }.contains(pos))
	{
		// We sometimes want clicks to go through transparent parts of the image
		if(!m_fullyClickable && m_sprite.isTransparentPixel(pos))
			return false;
		else
			return true;
	}

	return false;
}

void Image::leftMouseReleased(sf::Vector2f pos)
{
	bool mouseDown = m_mouseDown;

	ClickableWidget::leftMouseReleased(pos);

	if(mouseDown)
	{
		// Check if you double-clicked
		if(m_possibleDoubleClick)
		{
			m_possibleDoubleClick = false;

			m_callback.mouse.x = static_cast<int>(pos.x);
			m_callback.mouse.y = static_cast<int>(pos.y);
			sendSignal("DoubleClicked", pos);
		}
		else // This is the first click
		{
			m_animationTimeElapsed = {};
			m_possibleDoubleClick = true;
		}
	}
}

void Image::rendererChanged(const std::string& property, tgui::ObjectConverter& value)
{
	if(property == "opacity")
		m_sprite.setOpacity(value.getNumber());
	else
		Widget::rendererChanged(property, value);
}

void Image::update(sf::Time elapsedTime)
{
	Widget::update(elapsedTime);

	// When double-clicking, the second click has to come within 500 milliseconds
	if(m_animationTimeElapsed >= sf::milliseconds(500))
	{
		m_animationTimeElapsed = {};
		m_possibleDoubleClick = false;
	}
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(getPosition());
	m_sprite.draw(target, states);
}

void Image::rendererChanged(const std::string& property, tgui::ObjectConverter& value)
{
	if(property == "Borders" || property == "SlicedScaling")
	{
		updateSize();
	}
	else
	{
		ClickableWidget::rendererChanged(property, value);
	}
}

ImageRenderer* Image::getRenderer() const
{
	return aurora::downcast<ImageRenderer*>(m_renderer.get());
}