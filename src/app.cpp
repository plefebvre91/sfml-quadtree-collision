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
#include "quadtree.hpp"
#include "constants.hpp"
#include "utils.hpp"

App::App() {
  // Create SFML window
  Random::init();
  _window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "app");
  _window->setActive(false);
  _window->setFramerateLimit(30);

  for(auto& entity: _entities) {
    entity.init(1, sf::Color(0x33CC00), sf::Color::Green, 1);
    entity.setPlayableArea(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    entity.move(Random::velocity());
  }

  _quadtree = new Node(sf::Rect<int>(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}

App::~App() {
  delete _quadtree;
  delete _window;
}

void App::render() {
    _window->clear();

    for(auto& entity: _entities)
      _window->draw(entity.getShape());

    _quadtree->draw(_window);

    _window->display();
}

void App::resolveCollisions() {

  // Retrieve all leaves from the quadtree
  std::vector<Node*> leaves;
  _quadtree->getLeaves(&leaves);

  // For each leaf...
  for (auto leaf: leaves) {

    // ... get the associated objects
    unsigned int* elements;
    unsigned int nbEntities = leaf->getElements(&elements);

    // Test collision between all objects in the leaf
    for (unsigned int i=0; i<nbEntities; i++) {
      Entity& e = _entities[elements[i]];

      for (unsigned int j=i+1; j<nbEntities; j++) {
        Entity& f = _entities[elements[j]];

        if (e.isColliding(f)) {
          e.bounce(f);
          f.bounce(e);
        }
      }
    }
  }
}

void App::handleEvents() {
    sf::Event event;
  
    while (_window->pollEvent(event)) {
      if(event.type == sf::Event::KeyPressed)
        if (event.key.code == sf::Keyboard::Escape)
          _window->close();

      if (event.type == sf::Event::Closed)
        _window->close();
    }
}

void App::run() {
  sf::Clock clock;

  while(_window->isOpen()) {
    auto dt = clock.restart().asSeconds();
    _quadtree->clear();

    for(int i=0; i<NB_ENTITY; i++) {
      _entities[i].update(dt);
      _quadtree->add<Entity>(_entities, i);
    }
    resolveCollisions();
    render();
    handleEvents();
  }
}
