#include "widget.h"
#include "Game.h"
#include "iostream"



widget::widget(Game* parent, sf::Vector2f position, sf::Vector2f size):
	_parent{ parent }, _wState{ _default }
{
	this->setPosition(position);
	this->setSize(size);
	_parent->registerWidget(this);
}

widget::~widget()
{
	//delete this;
}
bool widget::isHovered(sf::Vector2i mousePosition){
	return mousePosition.x > getPosition().x && mousePosition.x < (getPosition().x + getSize().x)
		&& mousePosition.y>getPosition().y && mousePosition.y < (getPosition().y + getSize().y);

 }
void widget::drawTo(sf::RenderWindow& window) {
	updateAppearance();
	window.draw(*this);
}

/// STATE / TYPE / HOVER

void widget::setState(widgetState widgetState) {
	_wState = widgetState;
}
widgetState widget::getState() const {
	return _wState;
}

//widgetType widget::getType() const
//{
//	return _wType;
//}

bool widget::isFocusable() const {
	return true;
}
bool widget::canHoverChangeAppearance() const {
	return true;
}

