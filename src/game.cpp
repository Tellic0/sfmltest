#include "game.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

void Game::initVariables() { this->window = nullptr; }

void Game::initWindow() {
  this->videoMode.height = 600;
  this->videoMode.width = 800;
  this->window =
      new sf::RenderWindow(this->videoMode, "My first game", sf::Style::None);
}

// Constructors / Destructors
Game::Game() {
  this->initVariables();
  this->initWindow();
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

void Game::update() { this->pollEvents(); }

void Game::render() {
  /*
    - clear old
    - render objects
    - display frame in window
    Renders the game objects.
  */
  this->window->clear(sf::Color(225, 0, 0, 255));

  // Draw game objectss

  this->window->display();
}
