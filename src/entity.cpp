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

#include "entity.hpp"


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000


sf::Vector2f randomPosition() {
  int x = rand() % WINDOW_WIDTH;
  int y = rand() % WINDOW_HEIGHT;

  return sf::Vector2f(x,y);
}


Entity::Entity(): _position(), _velocity(), _acceleration() {
  _shape.setRadius(2);
  _shape.setFillColor(sf::Color(0x33, 0xCC, 0x00));
  _shape.setOutlineColor(sf::Color::Green);
  _shape.setOutlineThickness(2);
  _position = randomPosition();
  _shape.setPosition(_position);
}

void Entity::update(double dt) {
  _velocity.x += _acceleration.x;
  _velocity.y += _acceleration.y;

  _position.x += _velocity.x;
  _position.y += _velocity.y;

  if (_position.x > _area.width || _position.x < 1)
    _velocity.x *= -1;

  if (_position.y > _area.height || _position.y < 1)
    _velocity.y *= -1;

  _acceleration.y = 0.0f;
  _acceleration.x = 0.0f;

  _shape.setPosition(_position);
}
