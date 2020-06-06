#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include "widget.h"
enum fieldState {active=0, inactive=1};
class Field : public widget
{
	int _value;
	sf::Text* _valueText;
	fieldState _fState;
	
	/// PRIVATE FUNCTIONS
	void updateAppearance();
	void initText(sf::Font& font);
	void updateText();
	
public:
	/// CONSTRUCTOR / DESTRUCTOR
	Field(sf::Font& font, Game* parent, sf::Vector2f position = { 50,50 }, sf::Vector2f size = { 40,40 });
	~Field();

	/// GETTER / SETTER
	void setValue(int value);
	int getValue() const;
	void setFieldState(fieldState state);
	bool isFocusable() const;

	/// HANDLE
	virtual void handle( sf::Event& ev ,widgetState state);

	/// DRAW
	void drawTo(sf::RenderWindow& window);
};
