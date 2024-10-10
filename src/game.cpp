#include "game.h"

void Game::initVariables() {
  this->window = nullptr;

  // Game logic
  this->points = 0;
  this->enemySpawnTimerMax = 10.f;
  this->enemySpawnTimer = this->enemySpawnTimerMax;
  this->maxEnemies = 5;

  this->playerHP = 100;
}

void Game::initWindow() {
  this->videoMode.height = 600;
  this->videoMode.width = 800;
  this->window =
      new sf::RenderWindow(this->videoMode, "My first game", sf::Style::None);
  this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
  this->enemy.setPosition(0.f, 0.f);
  this->enemy.setSize(sf::Vector2f(50.0f, 50.0f));
  this->enemy.setScale(sf::Vector2f(1.f, 1.f));
}

// Constructors / Destructors
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initEnemies();
}

Game::~Game() { delete this->window; }

// Accessors
const bool Game::running() const {
  if (playerHP > 0) {
    return this->window->isOpen();
  } else {
    return false;
  }
}

// Functions
void Game::spawnEnemy() {
  /*
   * @return void
   * Spawns enemies and sets their colour and positions.
   * -Sets a random position and checks until id does not collide with any
   *  other enemy
   * -Sets a random colour
   * -Adds enemy to the
   *  vector
   */
  bool shouldPush = false;
  float posX = 0.f;
  float posY = 0.f;
  float paddingX = 20.f;
  float paddingY = 20.f;

  while (!shouldPush) {
    shouldPush = true;
    posX =
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x -
                                                     this->enemy.getSize().x));
    for (auto &e : this->enemies) {
      if (posX < e.getPosition().x + e.getSize().x + paddingX &&
          posX + this->enemy.getSize().x + paddingX > e.getPosition().x &&
          posY < e.getPosition().y + e.getSize().y + paddingY &&
          posY + this->enemy.getSize().y + paddingY > e.getPosition().y) {
        shouldPush = false;
        break;
      }
    }
  }
  if (shouldPush) {
    this->enemy.setPosition(posX, posY);
    this->enemy.setFillColor(
        sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
    this->enemy.setOutlineColor(sf::Color::Red);
    this->enemy.setOutlineThickness(5.f);
    this->enemies.push_back(this->enemy);
  }
}

void Game::pollEvents() {

  // Event polling
  while (this->window->pollEvent(this->ev)) {
    switch (this->ev.type) {

    case sf::Event::Closed:
      this->window->close();
      break;

    case sf::Event::KeyPressed:
      if (this->ev.key.code == sf::Keyboard::Escape)
        this->window->close();
      break;
    }
  }
}

void Game::updateMousePositions() {
  /*
  @ return void

  Updates the mouse positions:
  - Mouse postition relative to window (Vector2i)
  */

  this->mousePosWindow = sf::Mouse::getPosition(*this->window);
  this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
  /*
    @return void

    Updates the enemy spawn timer and spawns enemies
    when the total amount is smaller than the max.
    Moves the enemies downwards.
    Removes the enemies at the edge of the screen. //TODO
  */

  // Updating the timer for enemy spawning
  if (this->enemies.size() < this->maxEnemies) {
    if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
      // Spawn the enemy and reset the timer
      this->spawnEnemy();
      this->enemySpawnTimer = 0.f;
    } else {
      this->enemySpawnTimer += 1.f;
    }
  }

  // Move and update the enemies
  for (int i = 0; i < this->enemies.size(); i++) {
    this->enemies[i].move(0.f, 5.f);
    bool deleted = false;

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
        deleted = true;

        // Gain points
        this->points += 10.f;
      }
    }

    // If the enemy is below window delete him and lower player hp
    if (this->enemies[i].getPosition().y > this->window->getSize().y) {
      deleted = true;
      this->playerHP -= 10;
    }

    if (deleted) {
      this->enemies.erase(this->enemies.begin() + i);
      i--;
    }
  }
}

void Game::update() {
  this->pollEvents();
  this->updateMousePositions();
  this->updateEnemies();

  std::cout << this->mousePosWindow.x << " " << this->mousePosWindow.y
            << std::endl;
}

void Game::renderEnemies() {
  for (auto &e : this->enemies) {
    this->window->draw(e);
  }
}

void Game::render() {
  /*
    - clear old
    - render objects
    - display frame in window
    Renders the game objects.
  */
  this->window->clear(sf::Color::Black);

  // Draw game objectss
  this->renderEnemies();

  this->window->display();
}
