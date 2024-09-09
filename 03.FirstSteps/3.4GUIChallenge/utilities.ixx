module;
#include <string_view>
//#include <fmt/format.h>
#include <iostream>
#include <SFML/Graphics.hpp>

//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	//fmt::println("{}",msg);
  std::cout << msg << std::endl;
}


export void app(){

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color::Red);
    window.draw(shape);
    window.display();
  }

}