#include "Field.h"
#include "iostream"

/// PRIVATE FUNCTIONS
void Field::updateAppearance()
{
	switch (getState()) {
	case 0:
		setFillColor(sf::Color(28,79,89));
		break;
	case 1:
		setFillColor(sf::Color(0, 71, 85));
		break;
	case 2:
		setFillColor(sf::Color(1, 24, 54));
		break;
	}
}
void Field::initText(sf::Font& font) {
	
	_valueText = new sf::Text("", font);
	_valueText->setPosition({ getPosition().x + 10,getPosition().y+2 });
}
void Field::updateText() {
	if (_value == 0) {
		_valueText->setString("");
	}else if (_value > 0 && _value < 10) {
		std::stringstream ss;
		ss << _value;
		std::string s;
		ss >> s;
		_valueText->setString(s);
	}
}
//void Field::setType()
//{
//	_wType = _field;
//}
/// ****** CONSTRUCTOR / DESTRUCTOR ******
Field::Field(sf::Font& font, Game* parent,sf::Vector2f position, sf::Vector2f size) :
	widget(parent,position,size),_value(0), _valueText(nullptr) 
{
	//setType();
	initText(font);
}

Field::~Field() {}

/// GETTER / SETTER
void Field::setValue(int value) {
	_value = value;
	updateText();
}

int Field::getValue() const { return _value; }

/// HANDLE FUNCTIONS
void Field::handle( sf::Event& ev,widgetState state) {
	
	if (getState()==_default  && state == _hovered) {
		setState(_hovered);
		//std::cout << "hovered triggered\n";
	}
	else if (getState() != _focused && state == _focused) {
		setState(_focused);
		//std::cout << getState() << '\n';
	}
	if (getState() == _focused && state == _focused) {

		switch (ev.type) {

		case sf::Event::KeyPressed:
			switch (ev.key.code) {
			case sf::Keyboard::Num1 :
				setValue(1);
				break;
			case sf::Keyboard::Num2:
				setValue(2);
				break;
			case sf::Keyboard::Num3:
				setValue(3);
				break;
			case sf::Keyboard::Num4:
				setValue(4);
				break;
			case sf::Keyboard::Num5:
				setValue(5);
				break;
			case sf::Keyboard::Num6:
				setValue(6);
				break;
			case sf::Keyboard::Num7:
				setValue(7);
				break;
			case sf::Keyboard::Num8:
				setValue(8);
				break;
			case sf::Keyboard::Num9:
				setValue(9);
				break;
				case sf::Keyboard::Num0:
				setValue(0);
				break;
			}


		}
	}
	
	
}

/// DRAW
void Field::drawTo(sf::RenderWindow& window) {
	updateAppearance();
	window.draw(*this);
	window.draw(*_valueText);
}

