#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Menu.h"
#include "GameScene.h"
#include "OptionsScene.h" // Inclure le fichier d'en-t�te pour OptionsScene

using namespace sf;
using namespace std;

int main() {
    RenderWindow _window(VideoMode(800, 600), "Mario Tzu Party");
    _window.setFramerateLimit(60);

    GameScene* _gameScene;
    OptionsScene* _optionsScene; // D�claration de la sc�ne des options
    bool _inMenu = true;
    bool _inOptions = false; // Indicateur pour savoir si nous sommes dans les options

    Texture _backgroundTexture;
    SoundBuffer _clickSoundBuffer;
    Sound _clickSound;
    Music _backgroundMusic;


    if (!_backgroundTexture.loadFromFile("Assets/Image/Young_Sun_Tzu_cosplay_Mario.jpg")) {
        return -1;
    }

    if (!_clickSoundBuffer.loadFromFile("Assets/Audio/UI-Click_Sound.wav")) {
        return -1;
    }

    if (!_backgroundMusic.openFromFile("Assets/Audio/572__aarondbaron__ambienceforyou.wav")) {
        return -1;
    }

    _backgroundMusic.setLoop(true);
    _backgroundMusic.play();
    _clickSound.setBuffer(_clickSoundBuffer);

    Sprite _backgroundSprite(_backgroundTexture);
    Menu _menu(_window.getSize().x, _window.getSize().y);
    _gameScene = new GameScene(_window.getSize().x, _window.getSize().y);
    _optionsScene = new OptionsScene(_window.getSize().x, _window.getSize().y); // Initialiser la sc�ne des options

    while (_window.isOpen()) {
        Event event;
        while (_window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                _window.close();
            }
            if (event.type == Event::MouseMoved) {
                Vector2f _mouseposition = _window.mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y));
                _menu.UpdateEffetSurvol(_mouseposition);
            }
            if (_inMenu) {
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f _mousePosition = _window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                    _menu.selectOption(_mousePosition);
                    _clickSound.play();

                    int _selected = _menu.getSelectedIndex();
                    switch (_selected) {
                    case 0:
                        cout << "Nouvelle Partie s�lectionn�e" << endl;
                        _inMenu = false;
                        break;
                    case 1:
                        cout << "Charger une Partie s�lectionn�e." << endl;
                        break;
                    case 2:
                        cout << "Options s�lectionn�es" << endl;
                        _inMenu = false; // Quitter le menu
                        _inOptions = true; // Entrer dans les options
                        break;
                    case 3:
                        cout << "Quitter le jeu" << endl;
                        _window.close();
                        break;
                    }
                }
            }
            else if (_inOptions) {
                _optionsScene->handleEvents(event, _window);

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f _mousePosition = _window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                    // V�rifier si le bouton de retour est cliqu�
                    if (_optionsScene->checkReturnToMenu(_mousePosition)) {
                        cout << "Retour au menu s�lectionn�." << endl;
                        _inOptions = false; // Retourner aux options
                        _inMenu = true; // Retourner au menu principal
                    }
                }
            }
            else {
                _gameScene->handleEvents(event, _window);
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f _mousePosition = _window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                    // V�rifier si le bouton de retour est cliqu�
                    if (_gameScene->checkReturnToMenu(_mousePosition)) {
                        cout << "Retour au menu s�lectionn�." << endl;
                        _inMenu = true; // Retourner au menu
                    }
                    _clickSound.play();
                }
            }
        }

        _window.clear();
        if (_inMenu) {
            _window.draw(_backgroundSprite);
            _menu.draw(_window);
        }
        else if (_inOptions) {
            _optionsScene->draw(_window);
           // _optionsScene->updateSlider(_window);
        }
        else {
            // _gameScene->Update(0);
            _gameScene->draw(_window);
        }

        _window.display();
    }

    delete _gameScene;
    delete _optionsScene; // Lib�rer la m�moire de la sc�ne des options
    return 0;
}
