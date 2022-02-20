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
#include "constants.hpp"
#include "utils.hpp"


Entity::Entity():
    _velocity(), _acceleration() {
  _position = Random::position(WINDOW_WIDTH, WINDOW_HEIGHT) + STARTING_OFFSET;
}

void Entity::init(int radius, const sf::Color& color, const sf::Color& outline, int thickness) {
  _shape.setRadius(radius);
  _shape.setFillColor(color);
  _shape.setOutlineColor(outline);
  _shape.setOutlineThickness(thickness);
  _shape.setOrigin(sf::Vector2f(radius, radius));
  _shape.setPosition(_position);
  _squaredRadius = radius*radius;
}

bool Entity::isColliding(const Entity& e) const {
  sf::Vector2f p = e.getPosition();
  sf::Vector2f v = p - _position;
  return (v.x*v.x + v.y*v.y) < 4*_squaredRadius;
}

void Entity::bounce(Entity& e) {
  const sf::Vector2f& v = Utils::nv(_position, e.getPosition()) ;
  _velocity.x = 10*v.x;
  _velocity.y = 10*v.y;

  _shape.setFillColor(sf::Color::Blue);
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
