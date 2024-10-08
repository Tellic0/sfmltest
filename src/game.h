#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
/*
  Class that acts as the game engine.
*/

class Game {
private:
  // Variables
  // Window
  sf::RenderWindow *window;
  sf::Event ev;
  sf::VideoMode videoMode;

  // private functions
  void initVariables();
  void initWindow();

public:
  // Costructors and Destructors
  Game();
  virtual ~Game();

  // Accessors
  const bool running() const;

  // Functions
  void pollEvents();
  void update();
  void render();
};
