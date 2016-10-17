#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"

int main() {
    ifstream entrada("entrada.txt");
    ofstream salida("salida.txt");

    Atleta a("jose",Masculino,1994,"Grecia",10);
    Atleta b("hb",Femenino,1800,"holanda",20);
    b.entrenarNuevoDeporte("paleta",60);
    b.guardar(salida);
    b.mostrar(cout);
    a.cargar(entrada);
    cout << endl;
    a.mostrar(cout);

    entrada.close();
    salida.close();
    return 0;
}