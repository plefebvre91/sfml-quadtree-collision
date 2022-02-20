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
  _window->setFramerateLimit(60);

  for(auto& entity: _entities) {
    entity.init(4, sf::Color(0x33CC00), sf::Color::Green, 1);
    entity.setPlayableArea(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    entity.move(Random::velocity());
  }

  _quadtree = new Node(sf::Rect<int>(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}

App::~App() {
  delete _quadtree;
  delete _window;
}

void draw(Node* tree, sf::RenderWindow* w) {
  if (tree == nullptr) return;

  sf::RectangleShape rect;
  const auto area = tree->getArea();

  rect.setPosition(sf::Vector2f(area.left, area.top));
  rect.setSize(sf::Vector2f(area.width, area.height));
  rect.setOutlineColor(sf::Color::Blue);
  rect.setOutlineThickness(1.0);

  if (tree->countElements() > 0)
    rect.setFillColor(sf::Color(0x00,0x33,0xCC,0x33));
  else
    rect.setFillColor(sf::Color::Transparent);

  w->draw(rect);

  for (int i=0; i<4; i++) {
    draw(tree->_nodes[i], w);
  }

}

void App::render() {
    _window->clear();

    for(auto& entity: _entities)
      _window->draw(entity.getShape());

    draw(_quadtree, _window);

    _window->display();
}

void App::handleEvents()
{
    sf::Event event;
    while (_window->pollEvent(event))
    {
      if(event.type == sf::Event::KeyPressed)
        if (event.key.code == sf::Keyboard::Escape)
          _window->close();

      if (event.type == sf::Event::Closed)
        _window->close();
    }
}


void App::run()
{
  sf::Clock clock;

  while(_window->isOpen()) {
    auto dt = clock.restart().asSeconds();
    _quadtree->clear();

    for(int i=0; i<NB_ENTITY; i++) {
      _entities[i].update(dt);
      _quadtree->add<Entity>(_entities, i);
    }
    render();

    handleEvents();
  }
}
