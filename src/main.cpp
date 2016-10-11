#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"

int main() {
    Atleta a("jose",Masculino,1994,"Grecia",10);
    Atleta b("hb",Femenino,1800,"holanda",20);
    b.entrenarNuevoDeporte("paleta",60);
    b.mostrar(cout);
    a.mostrar(cout);
    a.cargar(cin);
    a.mostrar(cout);
    cin.get();
return 0;
}