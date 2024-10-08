#include "game.h"
#include <SFML/System/Vector2.hpp>

void Game::initVariables() { this->window = nullptr; }

void Game::initWindow() {
  this->videoMode.height = 600;
  this->videoMode.width = 800;
  this->window =
      new sf::RenderWindow(this->videoMode, "My first game", sf::Style::None);
  this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
  this->enemy.setPosition(0.f, 0.f);
  this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
  this->enemy.setScale(sf::Vector2f(1.0f, 1.0f));
  this->enemy.setFillColor(sf::Color::Cyan);
  this->enemy.setOutlineColor(sf::Color::Green);
  this->enemy.setOutlineThickness(1.f);
}

// Constructors / Destructors
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initEnemies();
}

Game::~Game() { delete this->window; }

// Accessors
const bool Game::running() const { return this->window->isOpen(); }

// Functions
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

void Game::update() {
  this->pollEvents();

  // Update Mouse position
  std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " "
            << sf::Mouse::getPosition(*this->window).y << std::endl;
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
  this->window->draw(this->enemy);
  this->window->display();
}
