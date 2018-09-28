#include <iostream>

#include "Tree.hpp"

using namespace std;

int main()
{
  Tree<int> tree = Tree<int>(3);

  tree.add(1);
  cout << tree << endl;
  tree.add(7);
  cout << tree << endl;
  tree.add(4);
  cout << tree << endl;
  tree.add(2);
  cout << tree << endl;
  tree.add(5);
  cout << tree << endl;
  tree.add(9);
  cout << tree << endl;
  tree.remove(4);
  cout << tree << endl;
  tree.remove(5);
  cout << tree << endl;
  tree.remove(9);
  cout << tree << endl;

  return 0;
}
