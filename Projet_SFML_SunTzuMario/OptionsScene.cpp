#include "OptionsScene.h"

 OptionsScene::OptionsScene(float _width, float _height)
{
          // Chargement de la police
         if (!_font.loadFromFile("Assets/Font/Super_Mario_64_font.ttf")) 
         {
             cerr << "Erreur de chargement de la police" << endl;
         }


         void handleEvents(Event & event, RenderWindow & _window);
         void draw(RenderWindow & _window);
}