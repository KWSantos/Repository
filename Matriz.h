#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;

class Matriz {
private:
    int linhas;
    int colunas;
    long double *coeficientes;
    long double *bs;
    long double *xs;
public:
    Matriz(int l, int c){
        linhas = l;
        colunas = c;
        coeficientes = new long double[linhas * colunas];
        bs = new long double[linhas];
        xs = new long double[linhas];
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
    void limparSistema(){
        for(int i = 0; i<linhas; i++){
            for(int j = 0; j<colunas; j++){
                coeficientes[i * colunas + j] = 0;
            }
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
    long double calculaPivo(long double a,long double b){
        if(b<=0.00001 && b>=-0.00001){
            throw runtime_error("Sistema indeterminado");
        }
        return a / b;
    }
    void escalonamento() {
        for (int i = 0; i < linhas - 1; i++) {
            for (int k = i + 1; k < linhas; k++) {
                if (coeficientes[i * colunas + i] == 0) {
                    for (int j = i + 1; j < linhas; j++) {
                        if (coeficientes[j * colunas + i] != 0) {
                            for (int l = 0; l < colunas; l++) {
                                swap(coeficientes[i * colunas + l], coeficientes[j * colunas + l]);
                            }
                            swap(bs[i], bs[j]);
                            break;
                        }
                    }
                }
                if (coeficientes[i * colunas + i] == 0) {
                    cout << "Sistema singular. Não é possível prosseguir com o escalonamento." << endl;
                    return;
                }

                long double pivo;
                try {
                    pivo = calculaPivo(coeficientes[k * colunas + i], coeficientes[i * colunas + i]);
                } catch (runtime_error &e) {
                    cout << e.what() << endl;
                    return;
                }

                for (int j = i; j < colunas; j++) {
                    coeficientes[k * colunas + j] -= pivo * coeficientes[i * colunas + j];
                }
                bs[k] -= pivo * bs[i];
            }
        }

        for (int i = linhas - 1; i >= 0; i--) {
            long double soma = 0;
            for (int j = i + 1; j < colunas; j++) {
                soma += coeficientes[i * colunas + j] * xs[j];
            }

            try {
                xs[i] = calculaPivo(bs[i] - soma, coeficientes[i * colunas + i]);
            } catch (runtime_error &e) {
                cout << e.what() << endl;
                return;
            }
        }

        cout << "Solucao do sistema:" << endl;
        for (int i = 0; i < colunas; i++) {
            cout << "x" << i + 1 << ": " << xs[i] << endl;
        }
        cout << endl;
    }
    void Jacobi(int maxIterations) {
        double *xs = new double[colunas]; // Vetor de soluções
        double *xAnterior = new double[colunas];
        double TOLERANCE;
        cout << "Insira as aproximacoes iniciais:";
        cin >> TOLERANCE;

        // Inicializa as soluções
        for (int i = 0; i < colunas; i++) {
            xs[i] = 0.0;
        }

        for (int iteration = 0; iteration < maxIterations; iteration++) {
            // Copia as soluções da iteração anterior
            for (int i = 0; i < colunas; i++) {
                xAnterior[i] = xs[i];
            }

            // Pivoteamento de linhas
            for (int i = 0; i < linhas; i++) {
                int max_index = i;
                double max_value = abs(coeficientes[i * colunas + i]);
                for (int j = i + 1; j < colunas; j++) {
                    double value = abs(coeficientes[j * colunas + i]);
                    if (value > max_value) {
                        max_index = j;
                        max_value = value;
                    }
                }
                if (max_index != i) {
                    // Trocar as linhas
                    for (int k = 0; k < colunas; k++) {
                        swap(coeficientes[i * colunas + k], coeficientes[max_index * colunas + k]);
                    }
                    swap(bs[i], bs[max_index]);
                }
            }

            for (int i = 0; i < linhas; i++) {
                double soma = 0.0;
                for (int j = 0; j < colunas; j++) {
                    if (j != i) {
                        soma += coeficientes[i * colunas + j] * xAnterior[j];
                    }
                }

                try {
                    xs[i] = calculaPivo(bs[i] - soma, coeficientes[i * colunas + i]);
                } catch (runtime_error &e) {
                    cout << e.what() << endl;
                    return;
                }
            }

            // Verifica a convergência
            bool convergiu = true;
            for (int i = 0; i < colunas; i++) {
                if (abs(xs[i] - xAnterior[i]) > TOLERANCE) {
                    convergiu = false;
                    break;
                }
            }

            if (convergiu) {
                cout << "Convergencia alcancada apos " << iteration + 1 << " iteracoes." << endl;
                break;
            }
        }

        cout << "Solucao do sistema:" << endl;
        for (int i = 0; i < colunas; i++) {
            cout << "x" << i + 1 << ": " << xs[i] << endl;
        }
    }


    int gaussSeidel(){
        float a[linhas][colunas+1],x[linhas],aerr,maxerr=0,t,s,err;
        int i,j,itr,maxitr;

        for(i=0;i<linhas;i++){
            for(j=0;j<colunas+1;j++){
                if(j==colunas){
                    a[i][j]=*(bs+i);
                }
                else{
                    a[i][j]=coeficientes[i*colunas+j];
                }
            }
        }
        
        std::cout<<"\nInsira o erro permitido e o numero maximo de iteracoes"<<endl;
        std::cin>>aerr>>maxitr;
        std::cout<<fixed;
        std::cout<<"\nInsira as aproximacoes iniciais:\n";

        for(i=0;i<linhas;i++){
            std::cout<<"x"<<i<<":";
            std::cin>>x[i];
        }

        std::cout<<"Iteracao"<<setw(6)<<"x[1]";
        std::cout<<setw(11)<<"x[2]";
        std::cout<<setw(11)<<"x[3]"<<endl;

        for(itr=1;itr<=maxitr;itr++){
            maxerr=0;
            for(i=0;i<linhas;i++){
                s=0;
                for(j=0;j<linhas;j++)
                    if(j != i) 
                    s += a[i][j]*x[j];
                    if(a[i][i]!=0){
                        t=(a[i][linhas]-s)/a[i][i];
                    }
                    else{
                        std::cout<<"Erro, divisao por 0"<<endl;
                    }
                    err=fabs(x[i]-t);

                    if(err>maxerr)
                    maxerr=err;

                    x[i]=t;
                }

                std::cout<<setw(5)<<itr;
                for(i=0;i<linhas;i++)
                std::cout<<setw(11)<<setprecision(4)<<x[i];
                std::cout<<endl;

            if(maxerr<aerr){
                std::cout<<"Convergiu em"<<setw(3)<<itr<<"iteracoes"<<endl;
                for(i=0;i<linhas;i++){
                    std::cout<<"x["<<i+1<<"]=";
                    std::cout<<setw(7)<<setprecision(4)<<x[i]<<endl;
                }
                return -1;
            }
        }
        std::cout<<"O numero maximo de iteracoes nao foi suficiente"<<endl;
        return 1;
    }
    void run(){
        int op;
        while(op!=8){
            cout << "1 - Ler o sistema" << endl;
            cout << "2 - Apresentar matriz dos coeficientes" << endl;
            cout << "3 - Apresentar sistema completo" << endl;
            cout << "4 - Resolver sistema por Eliminacao de Gauss" << endl;
            cout << "5 - Resolver sistema por Gauss-Jacobi" << endl;
            cout << "6 - Resolver sistema por Gauss-Seidel" << endl;
            cout << "7 - Limpar sistema" << endl;
            cout << "8 - Sair" << endl;
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
                case 5:
                    Jacobi(100);
                    break;
                case 6:
                    gaussSeidel();
                    break;
                case 7:
                    limparSistema();
                    break;
            }
            cout << endl;
        }
    }
};