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

#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

// A node in the quadtree.
#define NB_SUBNODES 4
#define NORTH_WEST 0
#define NORTH_EAST 1
#define SOUTH_EAST 2
#define SOUTH_WEST 3

#define MAX_ELEMENTS 2


class Node {
  using Position = sf::Vector2f;
  using Rectangle = sf::Rect<int>;
  using EntityId = unsigned int;

public:
  /**
   * Constructor
   */
  Node(const Rectangle& r):_area(r), _elements(), _leaf(true) {
    for (auto& node: _nodes)
      node = nullptr;
  }

  /**
   * Constructor
   */
  template<typename T>
  void add(const T* entities, EntityId id) {
    if (_leaf == true) {
      _elements.push_back(id);

      if (_elements.size() >= MAX_ELEMENTS) {
        _split();

        for (auto id: _elements)
          insertInSubnodes<T>(entities, id);

        _elements.clear();
      }
    }
    else
      insertInSubnodes<T>(entities, id);
  }

  /**
   * Constructor
   */
  void clear() {
    for (auto& node: _nodes)
      // Depth-first search for non-null nodes
      if (node != nullptr) {
        node->clear();
        delete node;
      }

    // As this node does not have children anymore, it becomes a leaf
    _leaf = true;
  }

  /**
   * Constructor
   */
  inline const Rectangle& getArea() const {
    return _area;
  }

  inline unsigned int countElements() const {
    return _elements.size();
  }

  Node* _nodes[NB_SUBNODES]; // mettre un pointeur à la place
private:

  /**
   * Constructor
   */

  void _split() {
    int x = _area.left;
    int y = _area.top;
    int width = _area.width;
    int height = _area.height;

    // Create children nodes
    _nodes[NORTH_WEST] = new Node(Rectangle(x, y, width/2, height/2));
    _nodes[NORTH_EAST] = new Node(Rectangle(x + width/2, y, width/2, height/2));
    _nodes[SOUTH_WEST] = new Node(Rectangle(x, y + height/2, width/2, height/2));
    _nodes[SOUTH_EAST] = new Node(Rectangle(x + width/2, y + height/2, width/2, height/2));

    // This node is no more a leaf
    _leaf = false;
  }

  /**
   * Constructor
   */
  template<typename T>
  void insertInSubnodes(const T* entities, EntityId id) {
    const Position& position = entities[id].getPosition();
    for (auto& node: _nodes)
      if (node->contains(position))
        node->add(entities, id);
  }

  /**
   * Constructor
   */
  inline bool contains(const Position& p) const {
    return _area.contains(sf::Vector2i(p));
  }


  Rectangle _area;
  std::vector<EntityId> _elements;
  bool _leaf;
};

#endif
