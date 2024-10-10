#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <ctime>
#include <iostream>
#include <vector>

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

  // Mouse positions
  sf::Vector2i mousePosWindow;

  // Game logic
  int points;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;

  // Game objects
  std::vector<sf::RectangleShape> enemies;
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
  void spawnEnemy();

  void pollEvents();

  void updateMousePositions();
  void updateEnemies();
  void update();

  void renderEnemies();
  void render();
};
