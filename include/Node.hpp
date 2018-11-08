#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
class Node
{
  public:
    Node(unsigned int n)
    {
      this->n = n;
      this->nodes = vector<Node*>(n, nullptr);
    };

    bool isEmpty()
    {
      return (this->infos.size() == 0);
    }

    bool isFull()
    {
      return (this->infos.size() >= this->n - 1);
    };

    bool isLeaf()
    {
      for (int i = 0; i < this->n; i++) {
        if (this->nodes[i] != nullptr) {
          return false;
        }
      }
      return true;
    }

    void addInfo(T info) throw (char*)
    {
      if (!this->isFull()) {
          this->infos.push_back(info);
          sort(this->infos.begin(), this->infos.end());
          return;
      } else {
        for (int i = 0; i < this->n - 1; i++) {
          if (info == this->infos[i]) {
            throw "Duplicated info on tree";
          }
          if (info < this->infos[i]) {
            if (this->nodes[i] == nullptr) {
              this->nodes[i] = new Node<T>(this->n);
            }
            this->nodes[i]->addInfo(info);
            return;
          }
        }
        if (this->nodes[this->n - 1] == nullptr) {
          this->nodes[this->n - 1] = new Node<T>(this->n);
        }
        this->nodes[this->n - 1]->addInfo(info);
        return;
      }
    };

    void removeInfo(T info) throw (char*)
    {
      if (this->isLeaf()) {
        typename vector<T>::iterator it = find(this->infos.begin(), this->infos.end(), info);
        if (it == this->infos.end()) {
          throw "Info not on tree";
        } else {
          this->infos.erase(it);
        }
        return;
      }

      for (int i = 0; i < this->n; i++) {
        if (i == this->n - 1 || this->infos[i] > info) {
          if (this->nodes[i] == nullptr) {
            throw "Info not on tree";
          } else {
            this->nodes[i]->removeInfo(info);
            if (this->nodes[i]->isEmpty()) {
              delete this->nodes[i];
              this->nodes[i] = nullptr;
            }
          }
          return;
        } else if (this->infos[i] == info) {
            if (this->nodes[i] != nullptr) {
              this->infos.erase(this->infos.begin() + i);
              this->addInfo(this->nodes[i]->popBiggestInfo());
            } else if (this->nodes[i + 1] != nullptr) {
              this->infos.erase(this->infos.begin() + i);
              this->addInfo(this->nodes[i + 1]->popSmallestInfo());
            } else {
              if (this->getNotNullChildDirection(i) == 1) {
                T aux = this->infos[i + 1];
                this->removeInfo(this->infos[i + 1]);
                this->infos[i] = aux;
              } else {
                T aux = this->infos[i - 1];
                this->removeInfo(this->infos[i - 1]);
                this->infos[i] = aux;
              }
            }
          return;
        }
//        if (this->nodes[j]->isEmpty()) {
//          delete this->nodes[j];
//          this->nodes[j] = nullptr;
//        }
      }
    }

    T popBiggestInfo()
    {
      Node<T>* node = this->nodes[this->infos.size()];
      if (node != nullptr) {
        T biggest = node->popBiggestInfo();
        if (node->isEmpty()) {
          delete node;
          node = nullptr;
        }
        return biggest;
      } else {
        T biggest = this->infos[this->infos.size() - 1];
        this->removeInfo(biggest);
        return biggest;
      }
    }

    T popSmallestInfo()
    {
      Node<T>* node = this->nodes[0];
      if (node != nullptr) {
        T smallest = node->popSmallestInfo();
        if (node->isEmpty()) {
          delete node;
          node = nullptr;
        }
        return smallest;
      } else {
        T smallest = this->infos[0];
        this->removeInfo(smallest);
        return smallest;
      }
    }

    // -1 -> left
    //  0 -> none
    //  1 -> right
    int getNotNullChildDirection(int index)
    {
      if (this->isLeaf()) {
        return 0;
      }

      for (int i = index + 1; i < this->n; i++) {
        if (this->nodes[i] != nullptr) {
          return 1;
        }
      }

      return -1;
    }

    virtual ~Node()
    {
      for (int i = 0; i < this->n; i++) {
        delete this->nodes[i];
        this->nodes[i] = nullptr;
      }
    };

    template <typename U> friend ostream& operator<<(ostream& os, const Node<U>& node);
  private:
    int n;
    vector<T> infos;
    vector<Node*> nodes;
};

template <typename T>
ostream& operator<<(ostream& os, const Node<T>& node)
{
  if (&node != nullptr) {
    os << "(";
    for (int i = 0; i < node.n; i++) {
      os << *(node.nodes[i]);
      if (node.infos.size() > i) {
        os << " " << node.infos[i] << " ";
      }
    }
    os << ")";
  }
  return os;
};

#endif
