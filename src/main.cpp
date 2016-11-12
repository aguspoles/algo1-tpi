#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"

int main() {

    ofstream salida("C:\\Users\\rocio\\Documents\\GitHub\\algo1-tpi\\salida.txt");
    Atleta a("jose",Masculino,1994,"Grecia",10);
    Atleta b("Nole", Genero::Masculino, 1983, "Serbia", 5);

    a.guardar(salida);
    salida.close();

    ifstream entrada("C:\\Users\\rocio\\Documents\\GitHub\\algo1-tpi\\salida.txt");
    b.cargar(entrada);
    entrada.close();


    if(a == b) cout << "bien";

    /*
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
     */
    return 0;
}