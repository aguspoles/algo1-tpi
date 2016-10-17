#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"

int main() {
    ifstream entrada("entrada.txt");
    ofstream salida("salida.txt");

    Atleta a("jose",Masculino,1994,"Grecia",10);
    Atleta b("hb",Femenino,1800,"holanda",20);
    Competencia c("Foot", Masculino, {a,b});
    c.finalizar({10,20},{{10,true},{20, false}});
    b.entrenarNuevoDeporte("paleta",60);

    b.guardar(cout);
    cout << endl;
    a.mostrar(cout);
    cout << endl;
    c.mostrar(cout);

    entrada.close();
    salida.close();
    return 0;
}