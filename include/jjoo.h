#ifndef __JJOO__
#define __JJOO__

#include "tipos.h"
#include "atleta.h"
#include "competencia.h"


class JJOO {

private:
    int _anio;
    vector<Atleta> _atletas;
    vector<vector<Competencia> > _cronograma;
    int _jornadaActual;

    friend class jjoo_tests_competencias_al_transcurrir_un_dia_Test;

    friend class jjoo_tests_competencias_al_transcurrir_dos_dias_Test;

    friend class jjoo_tests_sequias_olimpicas_y_los_mas_fracasados_Test;

    friend class jjoo_tests_hay_un_patron_Test;

    friend class jjoo_tests_liu_song_Test;

    //auxiliares
    bool perteneceACompetencia(const Atleta &a, const Competencia &c)const;
    vector<int> ciaNumbers(vector<Atleta> as);
    void ordenarPorCapacidad(vector<Atleta> &vs, Deporte d);
    vector<Atleta> atletasDeLaCompetencia(vector<Atleta> as, Competencia c);
    vector<pair<Atleta,Categoria>> ganadoresPorCategoria(const vector<vector<Competencia>> &cs, const int &dia) const;
    vector<pair<int,bool>> sacoLosDeDoping(Competencia c, Pais p);
    vector<int> sacoLosDeRanking(Competencia c, Pais p);
    Atleta losMasParticipantes(vector<Atleta> as, vector<Competencia> cs) const;
    vector<Atleta> losAtletasDelPais(Competencia c, Pais p) const;
    int cuentaParticipaciones(Atleta a, vector<Competencia> cs)const;
    bool pertenece(Atleta a, Competencia c)const;
    bool noGanoMedallas(Atleta a, Competencia c)const;

public:
    JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs);

    int anio() const;

    vector<Atleta> atletas() const;

    int cantDias() const;

    int jornadaActual() const;

    vector<Competencia> cronograma(const int &d) const;

    vector<Competencia> competencias() const;

    vector<Competencia> competenciasFinalizadasConOroEnPodio() const;

    vector<Atleta> dePaseo() const;

    vector<pair<Pais, vector<int> > > medallero() const;

    int boicotPorDisciplina(const Categoria &c, const Pais &p);

    vector<Atleta> losMasFracasados(const Pais &p) const;

    void liuSong(const Atleta &a, const Pais &p);

    Atleta stevenBradbury() const;

    bool uyOrdenadoAsiHayUnPatron() const;

    vector<Pais> sequiaOlimpica() const;

    void transcurrirDia();

    bool operator==(const JJOO &j) const;

    JJOO operator=(const JJOO &j);

    //Entrada y salida
    void mostrar(std::ostream &os) const;

    void guardar(std::ostream &os) const;

    void cargar(std::istream &is);
};

std::ostream &operator<<(std::ostream &os, const JJOO &j);

std::istream &operator>>(std::istream &is, JJOO &j);

#endif /*__JJOO__*/