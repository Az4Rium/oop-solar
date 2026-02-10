#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <queue>
#include "Desktop.h"
#include "Circle.h"
#include "Event.h"
#include "Rectangle.h"


std::queue<Event> EventQueue;


void pushSFMLEvent(const sf::Event &e){
  if (e.is<sf::Event::MouseButtonPressed>()){
    const auto &m = e.getIf<sf::Event::MouseButtonPressed>();
    EventQueue.push(MouseEvent{
      m->position.x,
      m->position.y
    });
  }
  else if(e.is<sf::Event::KeyPressed>()){
    const auto &k = e.getIf<sf::Event::KeyPressed>();
    EventQueue.push(KeyEvent{
      k->code
    });
  }
}

int main(){
  sf::RenderWindow window(sf::VideoMode({800,600}),"Test 2", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);

  Desktop desktop;

  desktop.pos = {400.0f, 300.0f};

  CircleFigure circle(50.f);
  circle.orbitRadius = 120.f;
  circle.color = sf::Color::Green;
  circle.angle = 0.0f;
  desktop.insert(&circle);

  RectangleFigure rect(100.f);
  rect.orbitRadius = 120.f;
  circle.angle = 180.0f;
  rect.color = sf::Color::Red;
  desktop.insert(&rect);

  sf::Clock clock;

  while(window.isOpen()){
    while(std::optional<sf::Event> e = window.pollEvent()){
      if(e->is<sf::Event::Closed>()){
        window.close();
      }
      pushSFMLEvent(*e);
    }

    float dt = clock.restart().asSeconds();
    desktop.setAngle(dt * desktop.speed);
    desktop.update(dt);

    while(!EventQueue.empty()){
      Event e = EventQueue.front();
      EventQueue.pop();
      desktop.handleEvent(e);
    }
    if (desktop.quit) window.close(); 
    window.clear(sf::Color::Black);
    desktop.draw(window);
    window.display();
  }
  
  return 0;
}
