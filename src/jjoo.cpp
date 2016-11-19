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
    return _cronograma[d-1];
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
    int i = 0;
    int j = 0;
    int cuentaOro = 0;
    int cuentaPlata = 0;
    int cuentaBronce = 0;
    pair<Pais, vector<int> > cantidadMedallas;

    while(i < paises().size()){
        j = 0;
        cuentaBronce = cuentaOro = cuentaPlata = 0;
        while(j < competencias().size()) {
            if (competencias()[j].finalizada()) {
                if (competencias()[j].ranking().size() > 0 &&
                    paises()[i] == competencias()[j].ranking()[0].nacionalidad())
                    cuentaOro++;
                if (competencias()[j].ranking().size() > 1 &&
                         paises()[i] == competencias()[j].ranking()[1].nacionalidad())
                    cuentaPlata++;
                if (competencias()[j].ranking().size() > 2 &&
                         paises()[i] == competencias()[j].ranking()[2].nacionalidad())
                    cuentaBronce++;
            }
            j++;
        }
        cantidadMedallas = make_pair(paises()[i], (std::vector<int>) {cuentaOro, cuentaPlata, cuentaBronce});
        ret.push_back(cantidadMedallas);
        i++;
    }
    ordenarMedallero(ret);
    return ret;
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    int i = 0, j = 0, h = 0, cuenta = 0;
    Deporte d;
    Genero  g;
    vector<Atleta> participantes;
    vector<int> rank;
    vector<pair<int,bool>> anti;

    while(i < _cronograma.size()) {
        j = 0;
        while (j < _cronograma[i].size()) {
            h = 0;

            if (_cronograma[i][j].categoria() == c) {
                while (h < _cronograma[i][j].participantes().size()) {
                    if (_cronograma[i][j].participantes()[h].nacionalidad() != p)
                        participantes.push_back(_cronograma[i][j].participantes()[h]);
                    else cuenta++;
                    h++;
                }
                d = _cronograma[i][j].categoria().first;
                g = _cronograma[i][j].categoria().second;
                rank = sacoLosDeRanking(_cronograma[i][j], p);
                anti = sacoLosDeDoping(_cronograma[i][j], p);

                Competencia c(d, g, participantes);
                if (_cronograma[i][j].finalizada()) {
                    _cronograma[i][j] = c;
                    _cronograma[i][j].finalizar(rank, anti);
                } else _cronograma[i][j] = c;
            }
            j++;
        }

        i++;
    }
    return cuenta;
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    return losMasParticipantes(losAtletasDelPais(_atletas, p), competencias());
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
    int i = 0, j = 0, h = 0;
    while(i < _atletas.size()){
        if(_atletas[i] == a) {
            Atleta liu(a.nombre(),a.genero(),a.anioNacimiento(),p,a.ciaNumber());
            _atletas[i] = liu;
            break;
        }
        i++;
    }
    i = 0;
    while(i < _cronograma.size()){
        j = 0;
        while(j < _cronograma[i].size()){
            h = 0;
            while(h < _cronograma[i][j].participantes().size()) {
                if (_cronograma[i][j].participantes()[h] == a) {
                    Atleta liu(a.nombre(), a.genero(), a.anioNacimiento(), p, a.ciaNumber());
                    _cronograma[i][j].participantes()[h] = liu;
                }
                h++;
            }
            j++;
        }
        i++;
    }
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
    return siguenUnOrden(losMejoresPaises());
}

vector<Pais> JJOO::sequiaOlimpica() const {
    vector<Pais> ret;
    int i = 0;
    while(i < paises().size()){
        if(masDiasSinMedallas(paises()[i]) == maxDiasSinMedallas())
            ret.push_back(paises()[i]);
        i++;
    }
    return ret;
}

void JJOO::transcurrirDia() {
    int i = 0;
    vector<int> is;
    vector<pair<int, bool>> ds;
    pair<int, bool> l;

    while (i < _cronograma[_jornadaActual - 1].size()) {
        if (!(_cronograma[_jornadaActual - 1][i].finalizada())) {
            is = ciaNumbers(_cronograma[_jornadaActual - 1][i].participantes());
            l = make_pair(is[0], true);
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

//LOS MAS FRACASADOS
vector<Atleta> JJOO::losAtletasDelPais(vector<Atleta> as, Pais p)const{
    int i = 0;
    vector<Atleta> res;
    while(i < as.size()){
        if(as[i].nacionalidad() == p)
            res.push_back(as[i]);
        i++;
    }
    return res;
}

vector<Atleta> JJOO::losMasParticipantes(vector<Atleta> as, vector<Competencia> cs)const{
    int j = 0;
    int max = 0;
    vector<Atleta> res;
        while (j < as.size()){
            if(cuentaParticipaciones(as[j],cs) == maxParticipaciones()){
                res.push_back(as[j]);
            }
            j++;
        }
    return as;
}

int JJOO::cuentaParticipaciones(Atleta a, vector<Competencia> cs)const{
    int cuenta = 0;
    int i = 0;
    while(i < cs.size()){
        if(perteneceACompetencia(a,cs[i]) && noGanoMedallas(a,cs[i])) cuenta++;
        i++;
    }
    return  cuenta;
}

int JJOO::maxParticipaciones() const{
    int j = 0, max = 0;
    vector<Competencia> cs = competencias();
    while(j < _atletas.size()) {
        if(cuentaParticipaciones(_atletas[j],cs) > max)
            max = cuentaParticipaciones(_atletas[j],cs);
        j++;
    }
    return max;
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
//FIN LOS MAS FRACASADOS

//SEQUIA
vector<Pais> JJOO::paises() const{
    int i = 0;
    vector<Pais> ret;
    while(i < _atletas.size()) {
        ret.push_back(_atletas[i].nacionalidad());
        i++;
    }
    return sacarRepetidos(ret);
}

vector<Pais> JJOO::sacarRepetidos(vector<Pais> &ps) const{
    int i = 0;
    vector<Pais> res;
    while(i < ps.size()){
        if(cuentaPais(ps[i],res) == 0)
            res.push_back(ps[i]);
        i++;
    }
    return res;
}

int JJOO::cuentaPais(Pais p, vector<Pais> ps) const {
    int cuenta = 0, i = 0;
    while(i < ps.size()){
        if(ps[i] == p)
            cuenta++;
        i++;
    }
    return cuenta;
}

int JJOO::masDiasSinMedallas(Pais p)const{
    int i = 0, j = 0;
    vector<int> is;
    while(i < _jornadaActual-1){
        j = 0;
        while (j < _cronograma[i].size()){
            if(ganoMedallaEseDia(p,i,j)) {
                is.push_back(i + 1);
                break;
            }
            j++;
        }
        i++;
    }
    is.push_back(_jornadaActual);//jornadaActual
    return maxDif(is);
}

bool JJOO::ganoMedallaEseDia(Pais p, int i, int j)const{
    if(_cronograma[i][j].ranking().size() > 0 && _cronograma[i][j].ranking()[0].nacionalidad() == p)
        return true;
    else if(_cronograma[i][j].ranking().size() > 1 && _cronograma[i][j].ranking()[1].nacionalidad() == p)
        return true;
    else if(_cronograma[i][j].ranking().size() > 2 && _cronograma[i][j].ranking()[2].nacionalidad() == p)
        return  true;
    return false;
}

int JJOO::maxDif(vector<int> is) const{
    int i = 0, max = is[0];
    while(i < is.size()-1){
        if((is[i+1]-is[i]) > max)
            max = is[i+1]-is[i];
        i++;
    }
    return max;
}

int JJOO::maxDiasSinMedallas()const{
    int i = 0, max = 0;
    while(i < paises().size()){
        if(masDiasSinMedallas(paises()[i]) > max)
            max = masDiasSinMedallas(paises()[i]);
        i++;
    }
    return max;
}
//FIN SEQUIA

//PATRON
vector<Pais> JJOO::losMejoresPaises() const{
    int d = 0;
    vector<Pais> res;
    while(d < _jornadaActual){
        if(alguienGanoOro(d))
            res.push_back(elMejorDelDia(d));
        d++;
    }
    return res;
}

Pais JJOO::elMejorDelDia(int d)const{
    int j = 0;
    Pais mejor;
    int max = 0, actual = 0;
    while(j < paises().size()){
            actual = cuentaOro(paises()[j],d);
            if (actual > max ||(actual == max && paises()[j] < mejor)) {
                mejor = paises()[j];
                max = actual;
            }
        j++;
    }
    return mejor;
}

int JJOO::cuentaOro(Pais p, int d)const{
    int i = 0;
    int cuenta = 0;
    while(i < _cronograma[d].size()){
        if(_cronograma[d][i].ranking()[0].nacionalidad() == p)
            cuenta++;
        i++;
    }
    return cuenta;
}

bool JJOO::alguienGanoOro(int d)const{
    int i = 0;
    while(i < _cronograma[d].size()){
        if(_cronograma[d][i].finalizada() && _cronograma[d][i].ranking().size() > 0)
            return true;
        i++;
    }
    return false;
}

bool JJOO::siguenUnOrden(vector<Pais> ps)const{
    return paraAdelante(ps) && paraAtras(ps);
}

bool JJOO::paraAdelante(vector<Pais> ps)const{
    int i = 0, j;
    while(i < ps.size()-1){
        j = 0;
        while(j < ps.size()-1) {
            if (i < j && ps[i] == ps[j]) {
                if (ps[i + 1] != ps[j + 1])
                    return false;
            }
            j++;
        }
        i++;
    }
    return true;
}

bool JJOO::paraAtras(vector<Pais> ps)const{
    int i = 1, j;
    while(i < ps.size()){
        j = 1;
        while(j < ps.size()) {
            if (i < j && ps[i] == ps[j]) {
                if (ps[i - 1] != ps[j - 1])
                    return false;
            }
            j++;
        }
        i++;
    }
    return true;
}
//FIN PATRON

void JJOO::ordenarMedallero(vector<pair<Pais, vector<int> >> &vs) const{
    int i = 0;
    int pasada = 1;
    pair<Pais, vector<int> > swap;
    while (pasada < vs.size()) {
        i = 0;
        while (i < vs.size() - 1) {
            if ( (vs[i].second[0] < vs[i + 1].second[0])
                || (vs[i].second[0] == vs[i + 1].second[0] && vs[i].second[1] < vs[i + 1].second[1])
                || (vs[i].second[0] == vs[i + 1].second[0] && vs[i].second[1] == vs[i + 1].second[1]
                    && vs[i].second[2] < vs[i + 1].second[2])) {
                swap = vs[i];
                vs[i] = vs[i + 1];
                vs[i + 1] = swap;
            }
            i++;
        }
        pasada++;
    }
}