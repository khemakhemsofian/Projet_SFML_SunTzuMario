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
	void updateVolumes();
	void handleEvents(Event& event, RenderWindow& _window);
	void draw(RenderWindow& _window);
	bool checkReturnToMenu(Vector2f mousePosition);
	

private:
	Texture _backgroundTexture;
	SoundBuffer _clickSoundBuffer;
	Sound _clickSound;
	Music _backgroundMusic;
	Font _font;
	Text _returnToMenu;
	RectangleShape _fullscreenCheckbox;
	bool _FullScreen;
	float _masterVolume;  
	float _musicVolume;  
	float _sfxVolume;    

	RectangleShape _masterSlider, 
				   _musicSlider, 
				   _sfxSlider;
	CircleShape _masterHandle, 
				_musicHandle,
				_sfxHandle;
};




#endif // !OPTIONSCENE_H

