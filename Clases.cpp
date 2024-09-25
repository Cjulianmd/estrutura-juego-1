#include <stack>
#include <iostream>
#include <vector>
using namespace std;

class carta{
    public:
        char tipo;
        char pinta;
        carta(char tipo='n', char pinta = 'a'){
            this->tipo = tipo;
            this->pinta = pinta;
        }
        void Mostrar(){
            cout << "(" << tipo << "," << pinta << ") ";     
        };
};

class baraja{
    public:
    stack<int> recibir;
    int darcarta(){
        if(!recibir.empty()){
            int c = recibir.top();
            recibir.pop();
            return c;
        }
        int c = -1;
        return c;
    };
};

class jugador{
    public:
        int mano[9];
        void obtenerCarta(baraja* mazo){
            int c = mazo->darcarta();
            mano[c]++;
            
        };  
};


int main() {
    baraja B;
    jugador J;
    for(int i =0; i<10;i++){
    J.mano[i] = 0;
    }

    vector<int> columna = {};
    for (auto i : columna) {
    J.mano[i]++;
    }
    cout<< " " << endl;
    for(int i=0;i<10;i++){
    cout<< J.mano[i] << " ";
    }

    return 0;
}