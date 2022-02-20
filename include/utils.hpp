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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "constants.hpp"
#include <cmath>

struct Utils {
  /**
   * Compute square distance between 2 points
   */
  static float sd(const sf::Vector2f& a, const sf::Vector2f& b) {
    auto x = a.x - b.x;
    auto y = a.y - b.y;
    return x*x + y*y;
  }

  /**
   * Compute vector coords from 2 points
   */
  static sf::Vector2f v(const sf::Vector2f& a, const sf::Vector2f& b) {
    return b - a;
  }

  /**
   * Compute normalized vector coords from 2 points
   */
  static sf::Vector2f nv(const sf::Vector2f& a, const sf::Vector2f& b) {
    auto u = v(b,a);
    auto n = std::hypotf(u.x, u.y);

    return u/n;
  }
};


struct Random {
  /**
   * Init randomizer
   */
  static void init() {
    srand(time(0));
  }

  /**
   * Creates a random position in [0,xMax] x [0,yMax]
   * @param maximum X coordinate
   * @param maximum Y coordinate
   */
  static sf::Vector2f position(int xMax, int yMax) {
    int x = rand() % xMax;
    int y = rand() % yMax;

    return sf::Vector2f(x,y);
  }

  /**
   * Creates a random velocity
   */
  static sf::Vector2f velocity() {
    int e = rand()%2 == 0 ? 1:-1;
    int f = rand()%2 == 0 ? 1:-1;
    int x = 3 + rand() % 3;
    int y = 3 + rand() % 3;

    return sf::Vector2f(e*x,f*y);
  }
};

#endif
