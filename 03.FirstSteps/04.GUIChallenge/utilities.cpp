#include "utilities.h"

//#include <fmt/format.h>
#include <iostream>
#include <SFML/Graphics.hpp>

//Module purview
void print_msg(std::string_view msg)
{
  //fmt::println("{}",msg);
  std::cout << msg << std::endl;
}


void app()
{

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) { if (event.type == sf::Event::Closed) window.close(); }

    window.clear(sf::Color::Red);
    window.draw(shape);
    window.display();
  }

}