/*
    . GUI Challenge: SFML
        . Create a window
        . Show a circle in the window
        . Change the color of the circle
        . Change the color of the background
        . On linux, I had a few issues may be related to missing binaries on the system.
          . Installed these and the issue seemed to go away: 
              . sudo apt-get install libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev
              . splitting the target_link_libraries command into two also seemd to change something: 
                  . target_link_libraries(rooster PRIVATE fmt::fmt) 
                  . target_link_libraries(rooster PRIVATE sfml-graphics)
              . Improvise on these problems.
                   

*/

#include <SFML/Graphics.hpp>

int main()
{
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

  return 0;
}