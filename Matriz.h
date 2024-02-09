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
            cout << "b" << i+1 << ":";
            cin >> *(bs+i);
            cout << endl;
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
    double calculaPivo(double a, double b){
        if(b==0){
            throw runtime_error("Sistema indeterminado");
        }
        return a / b;
    }
    void escalonamento(){
        int j;
        double pivo;
        for(int i = 1; i<linhas; i++){
            int k = i;
            while(k!=linhas){
                j = i - 1;
                try{

                    pivo = calculaPivo(coeficientes[k*colunas + j],coeficientes[(i-1)*colunas + j]);
                } catch(runtime_error& e){
                    cout << e.what() << endl;
                }
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
            try{
                bs[i] = calculaPivo((bs[i] - soma), coeficientes[i * colunas + i]);
            } catch(runtime_error& e){
                cout << e.what() << endl;
            }
        }
        cout << "Solucao do sistema:" << endl;
        for(int i = 0; i<colunas; i++){
            cout << "x" << i+1 << ": " << bs[i] << endl;
        }
        cout << endl;
    }
    void run(){
        int op;
        while(op!=7){
            cout << "1 - Ler o sistema" << endl;
            cout << "2 - Apresentar matriz dos coeficientes" << endl;
            cout << "3 - Apresentar sistema completo" << endl;
            cout << "4 - Resolver sistema por Eliminacao de Gauss" << endl;
            cout << "5 - Resolver sistema por Cholesky" << endl;
            cout << "6 - Resolver sistema por Gauss-Seidel" << endl;
            cout << "7 - Sair" << endl;
            cout << endl;
            cin >> op;
            cout << endl;
            switch(op){
                case 1:
                    lerMatriz();
                    break;
                case 2:
                    apresentaMatriz();
                    break;
                case 3:
                    apresentaSistema();
                    break;
                case 4:
                    escalonamento();
                    break;
            }
            cout << endl;
        }
    }
};