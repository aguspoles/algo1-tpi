#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"

Atleta atletaProdigio(JJOO j){
    int i = 0;
    int max = 0;
    Atleta res("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);
    while(i < j.competenciasFinalizadasConOroEnPodio().size()){
        if(j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0].anioNacimiento() > max) {
            res = j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0];
            max = j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0].anioNacimiento();
        }
        i++;
    }
    return res;
}
