#include "OptionsScene.h"


OptionsScene::OptionsScene(float _width, float _height) {
    // Chargement de la police
    if (!_font.loadFromFile("Assets/Font/Super_Mario_64_font.ttf")) {
        cerr << "Erreur de chargement de la police" << endl;
    }

    if (!_backgroundTexture.loadFromFile("Assets/Image/Young_Sun_Tzu_cosplay_Mario.jpg")) {
        cerr << "Erreur de chargement de la police" << endl;
    }

    if (!_clickSoundBuffer.loadFromFile("Assets/Audio/UI-Click_Sound.wav")) {
        cerr << "Erreur de chargement de la police" << endl;
    }

    if (!_backgroundMusic.openFromFile("Assets/Audio/572__aarondbaron__ambienceforyou.wav")) {
        cerr << "Erreur de chargement de la police" << endl;
    }

    _returnToMenu.setFont(_font);
    _returnToMenu.setString("Retour au Menu");
    _returnToMenu.setCharacterSize(24);
    _returnToMenu.setFillColor(Color::White);
    _returnToMenu.setPosition(10, 10);

    _FullScreen = false;
    _fullscreenCheckbox.setSize(Vector2f(20, 20));
    _fullscreenCheckbox.setFillColor(Color::White);
    _fullscreenCheckbox.setPosition(300, 300);

    _masterSlider.setSize(Vector2f(300, 10));
    _masterSlider.setPosition(100, 100);
    _masterSlider.setFillColor(Color::White);

    _musicSlider.setSize(Vector2f(300, 10));
    _musicSlider.setPosition(100, 150);
    _musicSlider.setFillColor(Color::White);

    _sfxSlider.setSize(Vector2f(300, 10));
    _sfxSlider.setPosition(100, 200);
    _sfxSlider.setFillColor(Color::White);

    
    _masterHandle.setRadius(10);
    _masterHandle.setFillColor(Color::Green);
    _masterHandle.setPosition(100 + (_masterVolume * 2), 95);

    _musicHandle.setRadius(10);
    _musicHandle.setFillColor(Color::Blue);
    _musicHandle.setPosition(100 + (_musicVolume * 2), 145);

    _sfxHandle.setRadius(10);
    _sfxHandle.setFillColor(Color::Red);
    _sfxHandle.setPosition(100 + (_sfxVolume * 2), 195);
  
   
}


void OptionsScene::updateVolumes() {
    
    float effectiveMusicVolume = _musicVolume * (_masterVolume / 100.0f);
    float effectiveSfxVolume = _sfxVolume * (_masterVolume / 100.0f);

    // Assurez-vous d'appliquer ces valeurs aux objets SFML Music et Sound
    // Exemple avec un objet SFML Music
    // music.setVolume(effectiveMusicVolume);
    _backgroundMusic.setVolume(effectiveMusicVolume);

    // Exemple avec un objet SFML Sound
    // sound.setVolume(effectiveSfxVolume);
    _clickSound.setVolume(effectiveSfxVolume);
}
    
    void OptionsScene::handleEvents(Event & event, RenderWindow & _window) 
    {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePosition = _window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

            // Vérifier si le bouton de retour est cliqué
            if (checkReturnToMenu(mousePosition)) {
                cout << "Retour au menu sélectionné." << endl;

            }

            if (_fullscreenCheckbox.getGlobalBounds().contains(mousePosition)) {
                _FullScreen = !_FullScreen; 
                if (_FullScreen) {
                    _fullscreenCheckbox.setFillColor(Color::Green);
                    _window.create(VideoMode::getDesktopMode(), "Jeu en plein écran", Style::Fullscreen);
                    
                }
                else {
                    _fullscreenCheckbox.setFillColor(Color::White); // Indiquer que le plein écran est désactivé
                    _window.create(VideoMode(800, 600), "Jeu Fenêtré", Style::Default);
                  
                }
            }
            if (_masterSlider.getGlobalBounds().contains(Vector2f(mousePosition))) {
                // Modifier la position du curseur master
                _masterHandle.setPosition(mousePosition.x - _masterHandle.getRadius(), 95);
                _masterVolume = (mousePosition.x - 100) / 3.0f; // Convertir en pourcentage
                OptionsScene::updateVolumes();
            }

            if (_musicSlider.getGlobalBounds().contains(Vector2f(mousePosition))) {
                // Modifier la position du curseur musique
                _musicHandle.setPosition(mousePosition.x - _musicHandle.getRadius(), 145);
                _musicVolume = (mousePosition.x - 100) / 3.0f;
                updateVolumes();
            }

            if (_sfxSlider.getGlobalBounds().contains(Vector2f(mousePosition))) {
                // Modifier la position du curseur SFX
                _sfxHandle.setPosition(mousePosition.x - _sfxHandle.getRadius(), 195);
                _sfxVolume = (mousePosition.x - 100) / 3.0f;
                updateVolumes();
            }

        }

        
    }
 
   
 bool OptionsScene::checkReturnToMenu(Vector2f mousePosition) {
        return _returnToMenu.getGlobalBounds().contains(mousePosition);
    }
void OptionsScene::draw(RenderWindow& _window)
{
    
    _window.draw(_returnToMenu);
    _window.draw(_fullscreenCheckbox);
   
    _window.draw(_masterSlider);
    _window.draw(_musicSlider);
    _window.draw(_sfxSlider);

    _window.draw(_masterHandle);
    _window.draw(_musicHandle);
    _window.draw(_sfxHandle);
}
