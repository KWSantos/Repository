#include <iostream>
#include "Matriz.h"
using namespace std;

int main(){
    int n;
    cout << "Digite n:";
    cin >> n;
    Matriz matriz(n, n);
    matriz.lerMatriz();
    matriz.apresentaMatriz();
    matriz.apresentaSistema();
    matriz.escalonamento();
    matriz.apresentaSistema();
}