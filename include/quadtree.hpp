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

#define MAX_ELEMENTS 10

class Node {
  using Position = sf::Vector2f;
  using Rectangle = sf::Rect<int>;
  using EntityId = unsigned int;

public:
  /**
   * Constructor
   * @param screen area associated to the node
   */
  Node(const Rectangle& r):_area(r), _elements(), _isLeaf(true) {
    for (auto& node: _nodes)
      node = nullptr;
  }

  /**
   * Add an element in the tree
   * @template type of elements referenced in the tree
   * @entities the external array storing all objects
   * @param index of object to add in tree
   */
  template<typename T>
  void add(const T* entities, EntityId id) {

    // If this is not a leaf, object should be inserted in the correct child
    if (not _isLeaf)
      insertInSubnodes<T>(entities, id);

    // And if this node is a leaf, object is inserted
    else {
      _elements.push_back(id);

      // If there is too much objects in the same node...
      if (_elements.size() >= MAX_ELEMENTS) {

        // ...the node is split in 4...
        _split();

        // ...and its elements are re-dispatched in its children
        for (auto id: _elements)
          insertInSubnodes<T>(entities, id);

        _elements.clear();
      }
    }
  }

  /**
   * Fill an array with all the tree leaves
   * @param output array
   */
  void getLeaves(std::vector<Node*>* out) {
    // If this node is a leaf, add it to the result...
    if (_isLeaf)
      out->push_back(this);

    // ...else scan its children
    else for (auto& node: _nodes)
      if (node != nullptr)
          node->getLeaves(out);
  }

  /**
   * Getter for node elements
   * @param output array
   * @return the output size
   */
  unsigned int getElements(unsigned int** data) {
    *data = _elements.data();
    return _elements.size();
  }

  /**
   * Drawing function
   */
  void draw(sf::RenderWindow* w) {
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(_area.left, _area.top));
    rect.setSize(sf::Vector2f(_area.width, _area.height));
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(1.0);

    if (_elements.size() > 0) {
      rect.setFillColor(sf::Color(0x00,0x33,0xCC,0x33));
      w->draw(rect);
    }
    else
      rect.setFillColor(sf::Color::Transparent);

    for (auto node: _nodes)
      if (node != nullptr)
        node->draw(w);
  }


  /**
   * Clear the tree
   */
  void clear() {
    for (auto& node: _nodes)
      // Depth-first search for non-null nodes
      if (node != nullptr) {
        node->clear();
        delete node;
      }

    // As this node does not have children anymore, it becomes a leaf
    _isLeaf = true;
  }



private:

  // 4 Children
  Node* _nodes[NB_SUBNODES];

  // Screen are associated to this node
  Rectangle _area;

  // Referenced objects
  std::vector<EntityId> _elements;

  // True if node is a leaf
  bool _isLeaf;

  /**
   * Creates the 4 children of a node
   */
  void _split() {
    // Get the area coordinates
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
    _isLeaf = false;
  }

  /**
   * Add an element in correct children of a node.
   * This is a recursive subroutine of add().
   * @template type of elements referenced in the tree
   * @entities the external array storing all objects
   * @param index of object to add in tree
   */
  template<typename T>
  void insertInSubnodes(const T* entities, EntityId id) {
    // Get the object positions
    const Position& position = entities[id].getPosition();

    // Search for the correct children for the node to be inserted
    for (auto node: _nodes)
      if (node->contains(position))
        node->add(entities, id);
  }

  /**
   * Return true if the position is in the node area
   */
  inline bool contains(const Position& p) const {
    return _area.contains(sf::Vector2i(p));
  }
};

#endif
