#ifndef OPTIONSCENE_H
#define OPTIONSCENE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;


class OptionsScene
{
public:
	OptionsScene(float _width, float _height);
	void handleEvents(Event& event, RenderWindow& _window);
	void draw(RenderWindow& _window);
	

private:
	Font _font;
};




#endif // !OPTIONSCENE_H

