#include <iostream>
#include "Matriz.h"
using namespace std;

int main(){
    int n;
    cout << "Digite n:";
    cin >> n;
    Matriz matriz(n, n);
    matriz.run();
}