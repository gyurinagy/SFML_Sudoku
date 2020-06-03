#pragma once

#include <SFML/Graphics.hpp>

class Game; 

enum  widgetState{ _default = 0, _hovered =1, _focused=2 };
//enum  widgetType{ _field=0, _button=1, _statictext=2 };


class widget : public sf::RectangleShape
{
	Game* _parent;
	widgetState _wState;
	
protected:
	//widgetType _wType;
	//virtual void setType()=0;
	virtual void updateAppearance()=0;

public:
	/// CONSTRUCTOR / DESTRUCTOR
	widget(Game* game, sf::Vector2f position = { 50,50 }, sf::Vector2f size = { 40,40 });
	~widget();

	/// FUNCTIONS
	virtual bool isHovered(sf::Vector2i mousePosition);
	virtual void drawTo(sf::RenderWindow& window);
	virtual void handle(sf::Event& ev,widgetState state) = 0;
	

	/// STATE / TYPE / HOVER 
	void setState(widgetState widgetState);
	widgetState getState() const;
	
	//widgetType getType() const;


	virtual bool isFocusable() const;
	virtual bool canHoverChangeAppearance() const;


};

