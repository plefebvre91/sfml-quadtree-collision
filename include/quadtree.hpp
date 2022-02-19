#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <iostream>


// A node in the quadtree.
#define NB_SUBNODES 4
#define NORTH_WEST 0
#define NORTH_EAST 1
#define SOUTH_EAST 2
#define SOUTH_WEST 3

#define BETWEEN(X, A, B) ((X>A) && (X<B))

#define MAX_ELEMENTS 4


struct Node {
  using Position = sf::Vector2f;
  using Rectangle = sf::Rect<int>;
  using EntityId = unsigned int;

  Node(const Rectangle& r) {
    _leaf = true;

    x = r.left;
    y = r.top;
    width = r.width;
    height = r.height;

    for (auto& node: _nodes)
      node = nullptr;
  }

  void split() {
    // Create children nodes
    _nodes[NORTH_WEST] = new Node(Rectangle(x, y, width/2, height/2));
    _nodes[NORTH_EAST] = new Node(Rectangle(x + width/2, y, width/2, height/2));
    _nodes[SOUTH_WEST] = new Node(Rectangle(x, y + height/2, width/2, height/2));
    _nodes[SOUTH_EAST] = new Node(Rectangle(x + width/2, y + height/2, width/2, height/2));

    // This node is no more a leaf
    _leaf = false;
  }

  void clear() {
    for (auto& node: _nodes) {
      if (node != nullptr) {
        node->clear();
        delete node;
      }
    }
    _leaf = true;
  }

  inline bool contains(const Position& p) {
    return BETWEEN(p.x, x, x + width) && BETWEEN(p.y, y, y + height);
  }


  template<typename T>
  void insertInSubnodes(const T* entities, EntityId id) {
    const Position& position = entities[id].getPosition();
    for (auto& node: _nodes) {
      if (node->contains(position))
        node->add(entities, id);
    }
  }

  template<typename T>
  void add(const T* entities, EntityId id) {
    if (_leaf == true) {
      _elements.push_back(id);

      if (_elements.size() >= MAX_ELEMENTS) {
        split();

        for (auto id: _elements) {
          insertInSubnodes<T>(entities, id);
        }
        _elements.clear();
      }
    } else {
      insertInSubnodes<T>(entities, id);
    }
  }

  Node* _nodes[NB_SUBNODES]; // mettre un pointeur à la place
  std::vector<EntityId> _elements;
  int x, y, width, height;
  bool _leaf;
};

#endif
