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


#ifndef VL_ENTITY_HPP
#define VL_ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
public:
  /**
   * Constructor
   * @param intial position
   */
  Entity();

  /**
   * Upadte object at each frame
   * @param time since last update
   */
  void update(double dt);

  /**
   * IPhysicalObject interface implementation
   * @return object position
   */
  inline const sf::Vector2f& getPosition() const {
    return _position;
  }

  /**
   * IPhysicalObject interface implementation
   * @param new position
   */
  inline void setPosition(const sf::Vector2f& position) {
    _position = position;
  }

  /**
   * IDynamicObject interface implementation
   * @return object velocity
   */
  inline const sf::Vector2f& getVelocity() const {
    return _velocity;
  }

  /**
   * IDynamicObject interface implementation
   * @return object acceleration
   */
  inline const sf::Vector2f& getAcceleration() const {
    return _acceleration;
  }

  /**
   * Get shape
   * @return object acceleration
   */
  inline const sf::Drawable& getShape() const {
    return _shape;
  }

  /**
   * IDynamicObject interface implementation
   * @param velocity
   */
  inline void move(const sf::Vector2f& v) {
    _velocity = v;
  }

  /**
   * Define external bounds for the object
   * @param bounds coords
   */
  void setPlayableArea(const sf::FloatRect& area) {
      _area = area;
  }

protected:
  sf::CircleShape _shape;
  sf::Vector2f _position;
  sf::Vector2f _velocity;
  sf::Vector2f _acceleration;
  sf::FloatRect _area;
};

#endif
