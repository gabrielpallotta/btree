#include <iostream>
#include <stdexcept>

#include "Tree.hpp"

using namespace std;

#ifdef _WIN32
  #define CLEAR_CMD "cls"
#elif __linux__
  #define CLEAR_CMD "clear"
#endif

int main()
{
  cout << "Digite o n da arvore: ";

  int n;

  cin >> n;

  Tree<int> tree = Tree<int>(n);

  while (true) {
    system(CLEAR_CMD);
    cout << "Arvore Naria:" << endl;
    cout << tree << endl;
    cout << "Comandos disponiveis: " << endl << endl;
    cout << "1 - Inserir" << endl;
    cout << "2 - Remover" << endl << endl;
    cout << "Digite uma opcao: ";

    int option;
    cin >> option;

    int value;
    switch (option) {
      case 1:
        cout << "Digite o valor que deseja inserir: ";
        cin >> value;
        try {
          tree.add(value);
          cout << "Valor inserido com sucesso" ;
        } catch(exception &err) {
          cout << "Valor ja existe na arvore";
        }
        break;
      case 2:
        cout << "Digite o valor que deseja remover: ";
        cin >> value;
        try {
          tree.remove(value);
          cout << "Valor removido com sucesso";
        } catch(exception &err) {
          cout << "Valor nao existe na arvore";
        }  
        break;  
    }
    cout << endl << endl;
    cout << "Pressione qualquer tecla para continuar...";
    cin.sync();
    cin.ignore();
  }
}
