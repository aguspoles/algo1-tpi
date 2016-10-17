#include "../include/jjoo.h"

#include <utility>
#include <algorithm>


JJOO::JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs) {
    _anio = a;
    _atletas = as;
    _cronograma = cs;
    _jornadaActual = 1;
}

int JJOO::anio() const {
    return _anio;
}

vector<Atleta> JJOO::atletas() const {
    return _atletas;
}

int JJOO::cantDias() const {
    return _cronograma.size();
}

int JJOO::jornadaActual() const {
    return _jornadaActual;
}

vector<Competencia> JJOO::cronograma(const int &d) const {
    int i = 0;
    while(i < _cronograma.size()){
        if(i == d-1)
            return _cronograma[i];
        i++;
    }
    return {{}};
}

vector<Competencia> JJOO::competencias() const {
    vector<Competencia> ret;
    int i = 0;
    int j;
    while(i < _cronograma.size()){
        j = 0;
        while(j < _cronograma[i].size()){
            ret.push_back(_cronograma[i][j]);
            j++;
        }
        i++;
    }
    return ret;
}

vector<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const {
    vector<Competencia> ret;
    int i = 0;
    int j;
    while(i < _cronograma.size()){
        j = 0;
        while(j < _cronograma[i].size()){
            if(_cronograma[i][j].ranking().size() > 0)
                ret.push_back(_cronograma[i][j]);
            j++;
        }
        i++;
    }
    return ret;
}

vector<Atleta> JJOO::dePaseo() const {
    vector<Atleta> ret;
    int i = 0;
    int j = 0;
    while(i < _atletas.size()){
        j = 0;
        while(j < competencias().size()) {
            if (perteneceACompetencia(_atletas[i], competencias()[j])) {
                break;
            }
            j++;
        }
        if(j == competencias().size())
            ret.push_back(_atletas[i]);
        i++;
    }
    return ret;
}

vector<pair<Pais, vector<int> > > JJOO::medallero() const {
    vector<pair<Pais, vector<int> > > ret;
    /*int i = 0;
    int j = 0;
    int cuentaOro = 0;
    int cuentaPlata = 0;
    int cuentaBronce = 0;
    pair<Pais, vector<int> > cantidadMedallas;
    while(i < _atletas.size()){
        j = 0;
        cuentaBronce = cuentaOro = cuentaPlata = 0;
        while(j < competencias().size()){
            if(_atletas[i] == competencias()[j].ranking()[0])
                cuentaOro++;
            if(_atletas[i] == competencias()[j].ranking()[1])
                cuentaPlata++;
            if(_atletas[i] == competencias()[j].ranking()[2])
                cuentaBronce++;
            j++;
        }
        cantidadMedallas = make_pair(_atletas[i].nacionalidad(), {cuentaOro,cuentaPlata,cuentaBronce});
        ret.push_back(cantidadMedallas);
        i++;
    }*/
    return ret;
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    int i = 0;
    int j = 0;
    int h = 0;
    int cuenta = 0;
    Deporte d;
    Genero  g;
    vector<vector<Competencia>> res;
    vector<Atleta> as;
    vector<int> is;
    vector<pair<int,bool>> xs;

    while(i < _cronograma.size()){
        j = 0;
        while(j < _cronograma[i].size()){
            h = 0;
            if(_cronograma[i][j].categoria() == c){
                while(h < _cronograma[i][j].participantes().size()){
                    if(_cronograma[i][j].participantes()[h].nacionalidad() != p)
                        as.push_back(_cronograma[i][j].participantes()[h]);
                    else cuenta++;
                    h++;
                }
                d = _cronograma[i][j].categoria().first;
                g = _cronograma[i][j].categoria().second;
                is = sacoLosDeRanking(_cronograma[i][j], p);
                xs = sacoLosDeDoping(_cronograma[i][j], p);
            }
            Competencia c(d,g,as);
            _cronograma[i][j] = c;
            if(_cronograma[i][j].finalizada()) _cronograma[i][j].finalizar(is,xs);
            j++;
        }
        i++;
    }
    return cuenta;
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    vector<Atleta> ret;
    int i = 0;
    int j = 0;
    while(i < _cronograma.size()){
        j = 0;
        while (j < _cronograma[i].size()) {
            ret.push_back(losMasParticipantes(losAtletasDelPais(_cronograma[i][j], p), _cronograma[i]));
            j++;
        }
        i++;
    }
    return ret;
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
    return;
}

Atleta JJOO::stevenBradbury() const {
    Atleta ret("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);
    /*int i = 0;
    int min = cronograma(1)[0].ranking()[0].capacidad(cronograma(1)[0].categoria().first);
    while(i < ganadoresPorCategoria(_cronograma,jornadaActual()).size()){
        vector<pair<Atleta,Categoria>> x = ganadoresPorCategoria(_cronograma,jornadaActual());
        if(x[i].first.capacidad(x[i].second.first) < min) {
            min = x[i].first.capacidad(x[i].second.first);
            ret = x[i].first;
        }
    }*/
    return ret;
}

bool JJOO::uyOrdenadoAsiHayUnPatron() const {
    return true;
}

vector<Pais> JJOO::sequiaOlimpica() const {
    vector<Pais> ret;
    return ret;
}

void JJOO::transcurrirDia() {
        int i = 0;
        vector<int> is;
        vector<pair<int, bool>> ds;
        pair<int, bool> l = make_pair(2, false);

        while (i < _cronograma[_jornadaActual - 1].size()) {
            if (!(_cronograma[_jornadaActual - 1][i].finalizada())) {
                is = ciaNumbers(atletasDeLaCompetencia(_cronograma[_jornadaActual - 1][i].participantes(), _cronograma[_jornadaActual - 1][i]));
                ds.push_back(l);
                _cronograma[_jornadaActual - 1][i].finalizar(is, ds);
            }
            i++;
        }
        _jornadaActual += 1;
}

void JJOO::mostrar(std::ostream &os) const {
}

void JJOO::guardar(std::ostream &os) const {
}

void JJOO::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const JJOO &j) {
    return os;
}

std::istream &operator>>(std::istream &is, JJOO &j) {
    return is;
}

bool JJOO::operator==(const JJOO &j) const {
    return true;
}

JJOO JJOO::operator=(const JJOO &j) {
    _anio = j._anio;
    _atletas = j._atletas;
    _cronograma = j._cronograma;
    _jornadaActual = j._jornadaActual;
    return (*this);
}


//AUXILIARES

bool JJOO::perteneceACompetencia(const Atleta &a, const Competencia &c)const{
    int i = 0;
    while(i < c.participantes().size()){
        if(a == c.participantes()[i])
            return true;
        i++;
    }
    return  false;
}

vector<int> JJOO::ciaNumbers(vector<Atleta> as){
    int i = 0;
    vector<int> res;
    while(i < as.size()){
        res.push_back(as[i].ciaNumber());
        i++;
    }
    return res;
}

void JJOO::ordenarPorCapacidad(vector<Atleta> &vs, Deporte d){
    int i = 0;
    int pasada = 1;
    Atleta swap("Argentina", Masculino, 1994, "Argentina", 2);
    while (pasada < vs.size()) {
        i = 0;
        while (i < vs.size() - 1) {
            if (vs[i].capacidad(d) < vs[i + 1].capacidad(d)) {
                swap = vs[i];
                vs[i] = vs[i + 1];
                vs[i + 1] = swap;
            }
            i++;
        }
        pasada++;
    }
}

vector<Atleta> JJOO::atletasDeLaCompetencia(vector<Atleta> as, Competencia c){
    int j = 0;
    vector<Atleta> res;
        while(j < as.size()) {
            if (perteneceACompetencia(as[j], c))
                res.push_back(as[j]);
            j++;
        }
    ordenarPorCapacidad(res, c.categoria().first);
    return res;
}

/*vector<pair<Atleta,Categoria>> JJOO::ganadoresPorCategoria(const vector<vector<Competencia>> &cs, const int &dia) const{
    int i = 0;
    int j = 1;
    vector<pair<Atleta,Categoria>> res;
    pair<Atleta,Categoria> ganador;
    while(j <= dia) {
        i = 0;
        while (i < cs.size()) {
            if (cronograma(j)[i].finalizada()) {
                ganador = make_pair(cronograma(j)[i].ranking()[0], cronograma(j)[i].categoria());
                res.push_back(ganador);
            }
            i++;
        }
        j++;
    }
    return  res;
}*/

vector<int> JJOO::sacoLosDeRanking(Competencia c, Pais p){
    int i = 0;
    vector<int> cia;
    while(i < c.ranking().size()){
        if(c.ranking()[i].nacionalidad() != p)
            cia.push_back(c.ranking()[i].ciaNumber());
        i++;
    }
    return cia;
}

vector<pair<int,bool>> JJOO::sacoLosDeDoping(Competencia c, Pais p){
    int i = 0;
    vector<pair<int,bool>> xs;
    pair<int,bool> x;
    while(i < c.lesTocoControlAntiDoping().size()){
        if(c.lesTocoControlAntiDoping()[i].nacionalidad() != p){
            x = make_pair(c.lesTocoControlAntiDoping()[i].ciaNumber(),c.leDioPositivo(c.lesTocoControlAntiDoping()[i]));
            xs.push_back(x);
        }
        i++;
    }
    return  xs;
}

vector<Atleta> JJOO::losAtletasDelPais(Competencia c, Pais p)const{
    int i = 0;
    vector<Atleta> res;
    while(i < c.participantes().size()){
        if(c.participantes()[i].nacionalidad() == p)
            res.push_back(c.participantes()[i]);
        i++;
    }
    return res;
}

Atleta JJOO::losMasParticipantes(vector<Atleta> as, vector<Competencia> cs)const{
    int i = 0;
    int j = 0;
    int max = 0;
    Atleta a("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);
    while(i < cs.size()){
        j = 0;
        while (j < as.size()){
            if(cuentaParticipaciones(as[j],cs) > max){
                max = cuentaParticipaciones(as[j],cs);
                a = as[j];
            }
            j++;
        }
        i++;
    }
    return a;
}

int JJOO::cuentaParticipaciones(Atleta a, vector<Competencia> cs)const{
    int cuenta = 0;
    int i = 0;
    while(i < cs.size()){
        if(pertenece(a,cs[i]) && noGanoMedallas(a,cs[i])) cuenta++;
        i++;
    }
    return  cuenta;
}

bool JJOO::pertenece(Atleta a, Competencia c)const{
    int i = 0;
    while(i < c.participantes().size()){
        if(c.participantes()[i] == a) return true;
    }
    return false;
}

bool JJOO::noGanoMedallas(Atleta a, Competencia c)const{
    int i = 0;
    while(i < c.ranking().size()){
        if(c.ranking()[0] == a || c.ranking()[1] == a || c.ranking()[2] == a)
            return false;
        i++;
    }
    return true;
}