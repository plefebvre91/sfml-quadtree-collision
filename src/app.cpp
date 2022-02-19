/* MIT License

Copyright (c) 2022 Pierre Lefebvre

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "app.hpp"
#include <X11/Xlib.h>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <time.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

sf::Vector2f randomVelocity() {
  int e = rand()%2 == 0 ? 1:-1;
  int f = rand()%2 == 0 ? 1:-1;
  int x = 3 + rand() % 3;
  int y = 3 + rand() % 3;

  return sf::Vector2f(e*x,f*y);
}

App::App() {
  XInitThreads();

  // Create SFML window
  srand(time(0));
  _window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "app");
  _window->setActive(false);
  _window->setFramerateLimit(60);

  for(auto& entity: _entities) {
    entity.setPlayableArea(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    entity.move(randomVelocity());

  }
}

void App::render() {
    _window->clear();

    for(auto& entity: _entities)
      _window->draw(entity.getShape());

    _window->display();
}

void App::update() {
  sf::Clock clock;
  while(_window->isOpen()){
    auto dt = clock.restart().asSeconds();


//      std::this_thread::sleep_for(std::chrono::milliseconds(VL_UPDATE_THREAD_MS));
  }
}

void App::handleEvents()
{
  // Start the game loop
    // Process events
    sf::Event event;
    while (_window->pollEvent(event))
    {
      if(event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
        case sf::Keyboard::Escape: _window->close(); break;
        default: break;
        }
      }

      if (event.type == sf::Event::Closed)
        _window->close();
    }
}

void App::run()
{

  //std::thread render_thread(&_render, this);  while(_window->isOpen()){
  //std::thread update_thread(&_update, this);
  sf::Clock clock;

  while(_window->isOpen()) {
    auto dt = clock.restart().asSeconds();

    for(auto& entity: _entities) {
      entity.update(dt);
    }

    render();
    handleEvents();
  }
  //update_thread.join();
  //render_thread.join();
}
