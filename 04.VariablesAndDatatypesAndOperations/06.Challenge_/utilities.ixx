module;
#include <string_view>
#include <SFML/Graphics.hpp>

//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview

export void app(){

  //Store the data in predefined variables.
  int width = 200;
  int height = 200;
  float circleRadius = 100.f;
  std::string title = "SFML works!";
  sf::Color backgroundColor = sf::Color::Red;
  sf::Color shapeColor = sf::Color::Green;

  //Change the code to use the predefined variables.
  sf::RenderWindow window(sf::VideoMode(width,height), title);
  sf::CircleShape shape(circleRadius);
  shape.setFillColor(shapeColor);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear(backgroundColor);
    window.draw(shape);
    window.display();
  }

}