#ifndef __COMPETENCIA__
#define __COMPETENCIA__

#include "tipos.h"
#include "atleta.h"


class Competencia {

private:
    Categoria _categoria;
    vector<Atleta> _participantes;
    bool _finalizada;
    vector<Atleta> _ranking;
    vector<pair<Atleta, bool> > _lesTocoControlAntiDoping;

    //auxiliares
    Atleta participanteConNumber(int c, const vector<Atleta> &as);
    pair<Atleta,bool> atletaConSuControl(const Atleta &x, const vector<pair<int,bool>> &as);
    bool estaEnControl(const Atleta &x, const vector<pair<int,bool>> &as);
    vector<Atleta> primerosDeAntiDoping(const vector<pair<Atleta,bool>> &ad);
    bool capacidadesOrdenadas(const vector<int> &vs) const;
    bool pertenece(const Atleta &a, const vector<pair<Atleta,bool>> &vs);
    bool mismosParticipantes(const vector<Atleta> &xs, const vector<Atleta> &ys) const;
    int cuentaParticipante(const Atleta &a, const vector<Atleta> &as) const;
    bool mismosAntiDoping(const vector<pair<Atleta,bool>> &xs, const vector<Atleta> &ys) const;
    vector<Atleta> primeros(const vector<pair<Atleta,bool>> &ps) const;
    int cuentaDopado(const Atleta &a, const vector<Atleta> &as) const;

public:
    Competencia(const Deporte &d, const Genero &g, const vector<Atleta> &as);

    Categoria categoria() const;

    vector<Atleta> participantes() const;

    bool finalizada() const;

    vector<Atleta> ranking() const;

    vector<Atleta> lesTocoControlAntiDoping() const;

    bool leDioPositivo(const Atleta &a) const;

    void finalizar(const vector<int> &posiciones, const vector<pair<int, bool> > &control);

    void linfordChristie(const int &n);

    bool gananLosMasCapaces() const;

    void sancionarTramposos();

    bool operator==(const Competencia &c) const;

    Competencia operator=(const Competencia &c);

    //Entrada y salida
    void mostrar(std::ostream &os) const;

    void guardar(std::ostream &os) const;

    void cargar(std::istream &is);
};

std::ostream &operator<<(std::ostream &os, const Competencia &c);

std::istream &operator>>(std::istream &is, Competencia &c);

#endif /*__COMPETENCIA__*/
