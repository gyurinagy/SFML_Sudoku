#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include "widget.h"

class Field : public widget
{
	int _value;
	sf::Text* _valueText;
	
	/// PRIVATE FUNCTIONS
	void updateAppearance();
	void initText(sf::Font& font);
	void updateText();
	//void setType();
	

public:
	/// CONSTRUCTOR / DESTRUCTOR
	Field(sf::Font& font, Game* parent, sf::Vector2f position = { 50,50 }, sf::Vector2f size = { 40,40 });
	~Field();
	/// GETTER / SETTER
	void setValue(int value);
	int getValue() const;
	/// HANDLE
	virtual void handle( sf::Event& ev ,widgetState state);
	/// DRAW
	void drawTo(sf::RenderWindow& window);
};




//#pragma once
//
//#include <SFML/Graphics.hpp>
//
//class Field
//{
//	float _r,_posX, _posY;
//	sf::Color color;
//	sf::RectangleShape* _field;
//public:
//	/// CONSTRUCTOR / DESTRUCTOR
//	Field(float r = 40  );
//	Field();
//	~Field();
//
//	/// FUNCTIONS 
//	void drawTo(sf::RenderWindow& window);
//	
//	
//	void setColor(int r, int g, int b, int a = 255);
//	void setFieldPosition(sf::Vector2f pos);
//	float getSize() const {		return _r; 	}
//	
//
//};

