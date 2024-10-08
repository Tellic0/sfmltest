#pragma once

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
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

  // Game objects
  sf::RectangleShape enemy;

  // private functions
  void initVariables();
  void initWindow();
  void initEnemies();

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
