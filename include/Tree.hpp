#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdexcept>

#include "Node.hpp"

using namespace std;

template <typename T>
class Tree
{
  public:
    Tree(unsigned int n)
    {
      this->n = n;
      this->root = nullptr;
    };

    void add(T info)
    {
      if (this->root == nullptr) {
        this->root = new Node<T>(this->n);
      }

      this->root->addInfo(info);
      return;
    };

    void remove(T info)
    {
      if (this->root == nullptr) {
        throw invalid_argument("Info not on tree");
      }

      this->root->removeInfo(info);

      if (this->root->isEmpty()) {
        delete this->root;
        this->root = nullptr;
      }
    };

    virtual ~Tree()
    {
      delete this->root;
    };

    template <typename U> friend ostream& operator<<(ostream& os, const Tree<U>& tree);
  private:
    Node<T>* root;
    int n;
};

template <typename T>
ostream& operator<<(ostream& os, const Tree<T>& tree)
{
  os << *(tree.root);
  return os;
};
#endif
