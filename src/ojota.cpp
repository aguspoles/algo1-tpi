#include "../include/tipos.h"
#include "../include/atleta.h"
#include "../include/competencia.h"
#include "../include/jjoo.h"

Atleta atletaProdigio(JJOO j){
    int i = 0;
    int max = 0;
    vector<Competencia> cs = j.competenciasFinalizadasConOroEnPodio();
    int r;
    Atleta res("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);

    while(i < cs.size()){
        r = cs[i].ranking()[0].anioNacimiento();
        if(r > max) {
            res = cs[i].ranking()[0];
            max = r;
        }
        i++;
    }
    return res;
}
