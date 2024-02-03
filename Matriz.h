#include <iostream>
using namespace std;

class Matriz {
private:
    int linhas;
    int colunas;
    long double *coeficientes;
    long double *bs;
public:
    Matriz(int l, int c){
        linhas = l;
        colunas = c;
        coeficientes = new long double[linhas * colunas];
        bs = new long double[linhas];
    }
    void lerMatriz(){
        for(int i = 0; i<linhas; i++){
            cout << "Funcao " << i+1 << endl;
            for(int j = 0; j<colunas; j++){
                cout << "x" << j+1 << ":";
                cin >> coeficientes[i * colunas + j];
            }
            cout << endl;
        }
        cout << "Vetor b:" << endl;
        for(int i = 0; i<linhas; i++){
            cout << "b" << i+1 << ": ";
            cin >> *(bs+i);
        }
    }
    void apresentaMatriz(){
        cout << "Matriz dos coeficientes: " << endl;
        for(int i = 0; i<linhas; i++){
            for(int j = 0; j<colunas; j++){
                cout << coeficientes[i * colunas + j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    void apresentaSistema(){
        cout << "Sistema Linear:" << endl;
        for(int i = 0; i<linhas; i++){
            for(int j = 0; j<colunas; j++){
                if(coeficientes[i * colunas + j] >= 0 && j!=0){
                    cout << "+" << coeficientes[i * colunas + j] << "x" << j+1<< " ";
                }
                else {
                    cout << coeficientes[i * colunas + j] << "x" << j+1<< " ";
                }
            }
            cout << "= " << *(bs+i) << endl;
        }
        cout << endl;
    }
    void escalonamento(){
        int j;
        long double pivo;
        for(int i = 1; i<linhas; i++){
            int k = i;
            while(k!=linhas){
                j = i - 1;
                pivo = (coeficientes[k*colunas + j])/(coeficientes[(i-1)*colunas + j]);
                for(j = i-1; j<colunas; j++){
                    coeficientes[k*colunas + j] -= pivo*(coeficientes[(i-1)*colunas + j]);
                }
                *(bs + k) -= pivo*(*(bs + k - 1));
                k++;
            }
        }
        for (int i = linhas - 1; i >= 0; i--) {
            long double soma = 0;
            for (int j = i + 1; j < colunas; j++) {
                soma += coeficientes[i * colunas + j] * bs[j];
            }
            bs[i] = (bs[i] - soma) / coeficientes[i * colunas + i];
        }
    }
};