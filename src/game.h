#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ctime>
#include <iostream>
#include <string>
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

  // Text
  sf::Font font;
  sf::Text textHP;
  sf::Text textScore;

  // Player
  int playerHP;

  // Window
  sf::RenderWindow *window;
  sf::Event ev;
  sf::VideoMode videoMode;

  // Game logic
  int points;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;

  // Game objects
  std::vector<sf::RectangleShape> enemies;
  sf::RectangleShape enemy;
  sf::RectangleShape player;

  // private functions
  void initVariables();
  void initWindow();
  void initEnemies();
  void initPlayer();
  void initText();

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
  void updatePlayer();
  void updateText();
  void update();

  void renderEnemies();
  void renderPlayer();
  void renderText();
  void render();
};
