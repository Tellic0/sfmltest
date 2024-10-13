#include "game.h"

void Game::initVariables() {
  this->window = nullptr;
  this->isFail = false;

  // Game logic
  this->points = 0;
  this->enemySpawnTimerMax = 40.f;
  this->enemySpawnTimer = this->enemySpawnTimerMax;
  this->maxEnemies = 5;

  this->playerHP = 100;
}

void Game::initWindow() {
  this->videoMode.height = 720;
  this->videoMode.width = 1080;
  this->window =
      new sf::RenderWindow(this->videoMode, "My first game", sf::Style::None);
  this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
  this->enemies.clear();
  this->enemy.setPosition(0.f, 0.f);
  this->enemy.setSize(sf::Vector2f(50.0f, 50.0f));
  this->enemy.setScale(sf::Vector2f(1.f, 1.f));
}

void Game::initPlayer() {
  this->player.setSize(sf::Vector2f(200.f, 20.f));
  this->player.setOutlineColor(sf::Color::Red);
  this->player.setOutlineThickness(5.f);
  this->player.setScale(sf::Vector2f(1.f, 1.f));
  this->player.setFillColor(sf::Color::White);
  this->player.setPosition((static_cast<float>(this->videoMode.width) / 2) -
                               (this->player.getSize().x / 2),
                           static_cast<float>(this->videoMode.height) -
                               this->player.getSize().y - 5);
}

void Game::initText() {
  this->font.loadFromFile("../assets/fonts/Roboto-Medium.ttf");
  this->textHP.setFont(font);
  this->textHP.setFillColor(sf::Color::White);
  this->textHP.setCharacterSize(30);
  this->textHP.setString("HP : ");
  this->textHP.setPosition(0.f, 30.f);

  this->textScore.setFont(font);
  this->textScore.setFillColor(sf::Color::White);
  this->textScore.setCharacterSize(30);
  this->textScore.setString("Score : ");
  this->textScore.setPosition(0.f, 0.f);
}

// Constructors / Destructors
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initEnemies();
  this->initPlayer();
  this->initText();
}

Game::~Game() { delete this->window; }

// Accessors
const bool Game::running() const { return this->window->isOpen(); }

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
    // generate healing enemies
    if ((rand() % 10) + 1 == 1) {
      this->enemy.setOutlineColor(sf::Color::Green);
    } else {
      this->enemy.setOutlineColor(sf::Color::Red);
    }
    this->enemy.setPosition(posX, posY);
    this->enemy.setFillColor(
        sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
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
    float speed = this->points / 100.f;
    this->enemies[i].move(0.f, 2.f + speed);
    bool deleted = false;

    // Cheack if it collides with the player
    if (this->enemies[i].getGlobalBounds().intersects(
            this->player.getGlobalBounds())) {
      if (this->enemies[i].getOutlineColor() == sf::Color::Green) {
        this->playerHP += 10;
      }
      deleted = true;
      this->points += 10.f;
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

void Game::updatePlayer() {
  bool isBoostActive = false;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
    isBoostActive = true;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    if (isBoostActive) {
      this->player.move(-40.f, 0.f);
    } else {
      this->player.move(-15.f, 0.f);
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    if (isBoostActive) {
      this->player.move(40.f, 0.f);
    } else {
      this->player.move(15.f, 0.f);
    }
  }
}

void Game::updateText() {
  std::string HP = "HP : " + std::to_string(this->playerHP);
  this->textHP.setString(HP);

  std::string SCORE = "Score : " + std::to_string(this->points);
  this->textScore.setString(SCORE);
}

void Game::update() {
  // Fail and restart system
  if (playerHP <= 0) {
    isFail = true;
  }
  if (!isFail) {
    this->pollEvents();
    this->updatePlayer();
    this->updateEnemies();
    this->updateText();
  } else {
    this->points = 0;
    this->playerHP = 100;
    this->initPlayer();
    this->initEnemies();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      isFail = false;
    }
  }
}

void Game::renderEnemies() {
  for (auto &e : this->enemies) {
    this->window->draw(e);
  }
}

void Game::renderPlayer() { this->window->draw(this->player); }

void Game::renderText() {
  this->window->draw(this->textScore);
  this->window->draw(this->textHP);
}

void Game::render() {
  /*
    - clear old
    - render enemies
    - render player
    - display frame in window
    Renders the game objects.
  */
  this->window->clear(sf::Color::Black);

  // Draw game objects
  this->renderEnemies();
  this->renderPlayer();
  this->renderText();

  this->window->display();
}
