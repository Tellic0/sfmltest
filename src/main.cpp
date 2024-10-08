#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 480), "My first game");
  sf::Event ev;

  while (window.isOpen()) {

    while (window.pollEvent(ev)) {
      switch (ev.type) {

      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        if (ev.key.code == sf::Keyboard::Escape)
          window.close();
        break;
      }
    }

    window.clear(sf::Color::White);
    window.display();
  }

  return 0;
}
