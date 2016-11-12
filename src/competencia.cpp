#include "../include/competencia.h"


Competencia::Competencia(const Deporte &d, const Genero &g, const vector<Atleta> &as) {
    _categoria.first = d;
    _categoria.second = g;
    _participantes = as;
    _finalizada = false;
}

Categoria Competencia::categoria() const {
    return _categoria;
}

vector<Atleta> Competencia::participantes() const{
    return _participantes;
}

bool Competencia::finalizada() const {
    return _finalizada;
}

vector<Atleta> Competencia::ranking() const {
    return _ranking;
}

vector<Atleta> Competencia::lesTocoControlAntiDoping() const {
    vector<Atleta> ret;
    int i = 0;
    while(i < _lesTocoControlAntiDoping.size()){
        ret.push_back(_lesTocoControlAntiDoping[i].first);
        i++;
    }
    return ret;
}

bool Competencia::leDioPositivo(const Atleta &a) const {
    int i = 0;
    while(i < _lesTocoControlAntiDoping.size()) {
        if (_lesTocoControlAntiDoping[i].first == a)
            return _lesTocoControlAntiDoping[i].second;
        i++;
    }
}

void Competencia::finalizar(const vector<int> &posiciones, const vector<pair<int, bool> > &control) {
    vector <Atleta> ranking;
    vector <pair<Atleta,bool>> controlAntiDoping;
    int i = 0;
    int j = 0;
    _finalizada = true;
    while(i < posiciones.size()) {
            ranking.push_back(participanteConNumber(posiciones[i], _participantes));
        i++;
    }
    _ranking = ranking;
    while(j < _participantes.size()) {
        if(estaEnControl(_participantes[j],control))
           controlAntiDoping.push_back(atletaConSuControl(_participantes[j],control));
        j++;
    }
    _lesTocoControlAntiDoping = controlAntiDoping;
}

void Competencia::linfordChristie(const int &n) {
    vector<Atleta> res;
    int i = 0;
    while(i < _participantes.size()){
        if(_participantes[i].ciaNumber() != n)
            res.push_back(_participantes[i]);
        i++;
    }
    _participantes = res;
}

bool Competencia::gananLosMasCapaces() const {
    vector<int> capacidades;
    int i = _ranking.size()-1;
    while(i >= 0) {
        capacidades.push_back(_ranking[i].capacidad(_categoria.first));
        i--;
    }
    return capacidadesOrdenadas(capacidades);
}

void Competencia::sancionarTramposos() {
    int i = 0;
    vector<Atleta> atletasResponsables;
    while(i < _ranking.size()){
        if(!pertenece(_ranking[i],_lesTocoControlAntiDoping) || !leDioPositivo(_ranking[i]))
            atletasResponsables.push_back(_ranking[i]);
        i++;
    }
    _ranking = atletasResponsables;
}

/*C (|Rugby|, |Masculino|) |True|
 * [(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]),
 * (A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)]),
 * (A |Jackson| |Masculino| 1935 |Escocia| 6 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)])]
 * [1, 6] [(1, |True|), (6, |True|)]
*/
void Competencia::mostrar(std::ostream &os) const {
    int i = 0;
    /*C (|Rugby|, |Masculino|) |True| */
    os << "C" << "(|" << categoria().first << "|, " << "|" << categoria().second << "|) ";
    os << "|" << boolToString(finalizada()) << "| ";
    os << "[";
    /*[(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]), (A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)]), (A |Jackson| |Masculino| 1935 |Escocia| 6 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)])]*/
    while (i < participantes().size()){
        os << "(";
        os << participantes()[i];
        if(i < participantes().size()-1)
            os << "), ";
        else os << ")] ";
        i++;
    }
    i = 0;
    /*[1, 6]*/
    os << "[";
    while(i < ranking().size()) {
        os << ranking()[i].ciaNumber();
        if(i < ranking().size()-1)
            os << ", ";
        else os << "] ";
        i++;
    }
    if(!_finalizada) os << "] ";
    i = 0;
    /*[(1, |True|), (6, |True|)]*/
    os << "[";
    while(i < lesTocoControlAntiDoping().size()){
        os << "(" << lesTocoControlAntiDoping()[i].ciaNumber();
        os << ", |" << boolToString(leDioPositivo(lesTocoControlAntiDoping()[i])) << "|)";
        if(i < lesTocoControlAntiDoping().size()-1)
            os << ", ";
        else os << "]";
        i++;
    }
    if(!_finalizada) os << "] ";
}

void Competencia::guardar(std::ostream &os) const {
    int i = 0;
    /*C (|Rugby|, |Masculino|) |True| */
    os << "C" << "(|" << _categoria.first << "|, " << "|" << _categoria.second << "|) ";
    os << "|" << boolToString(_finalizada) << "| ";
    os << "[";
    /*[(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]), (A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)]), (A |Jackson| |Masculino| 1935 |Escocia| 6 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)])]*/
    while (i < _participantes.size()){
        os << "(";
        os << _participantes[i];
        if(i < _participantes.size()-1)
            os << "), ";
        else os << ")] ";
        i++;
    }
    i = 0;
    /*[1, 6]*/
    os << "[";
    while(i < _ranking.size()) {
        os << _ranking[i].ciaNumber();
        if(i < _ranking.size()-1)
            os << ", ";
        else os << "] ";
        i++;
    }
    if(!_finalizada) os << "] ";
    i = 0;
    /*[(1, |True|), (6, |True|)]*/
    os << "[";
    while(i < _lesTocoControlAntiDoping.size()){
        os << "(" << _lesTocoControlAntiDoping[i].first.ciaNumber();
        os << ", |" << boolToString(_lesTocoControlAntiDoping[i].second) << "|)";
        if(i < _lesTocoControlAntiDoping.size()-1)
            os << ", ";
        else os << "]";
    }
    if(!_finalizada) os << "] ";
}

/*C (|Rugby|, |Masculino|) |True|
 * [(A |Juan| |Masculino| 1920 |Argentina| 1 [(|Football|, 35), (|Rugby|, 10)]),
 * (A |Jorge| |Masculino| 1930 |Argentina| 2 [(|Football|, 32), (|Rugby|, 20)]),
 * (A |Jackson| |Masculino| 1935 |Escocia| 6 [(|Basket|, 25), (|Football|, 40), (|Rugby|, 5)])]
 * [1, 6] [(1, |True|), (6, |True|)]
*/
void Competencia::cargar(std::istream &is) {
    string gen,finalizada,auxiliar;
    Atleta a("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);
    vector<Atleta> as;
    vector<int> posiciones;
    vector<pair<int,bool>> ys;
    pair<int,bool> y;
    bool anti;
    int i = 0;

    is.ignore(4);
    getline(is,_categoria.first,'|');
    is.ignore(3);
    getline(is,gen,'|');
    _categoria.second = stringToGenero(gen);
    is.ignore(3);
    getline(is,finalizada,'|');
    is.ignore(3);
    //cargamos los participantes
    while(is.peek() == 'A') {
        is >> a;
        _participantes.push_back(a);
        is.ignore();
        if(is.peek() == ',') is.ignore(3);
        else is.ignore(2);
    }

    /*[1, 6]*/
    is.ignore();
    while(is.peek() != ']'){
        getline(is,auxiliar,',');
        is.putback(',');
        i = atoi(auxiliar.c_str());
        posiciones.push_back(i);
        if(is.peek() == ',') is.ignore(2);
    }

    is.ignore(3);
    /*[(1, |True|), (6, |True|)]*/
    while (is.peek() != ']'){
        is.ignore();
        getline(is,auxiliar,',');
        i = atoi(auxiliar.c_str());
        is.ignore(2);
        getline(is,auxiliar,'|');
        anti = stringToBool(auxiliar);
        y = make_pair(i,anti);
        ys.push_back(y);
        is.ignore();
        if(is.peek() == ',') is.ignore(2);
    }
    is.ignore();
    if(finalizada == "True") finalizar(posiciones,ys);
}

std::ostream &operator<<(std::ostream &os, const Competencia &c) {
    c.mostrar(os);
    return os;
}

std::istream &operator>>(std::istream &is, Competencia &c) {
    c.cargar(is);
    return is;
}

bool Competencia::operator==(const Competencia &c) const {
    if(_categoria != c._categoria)
        return false;
    if(!mismosParticipantes(_participantes,c._participantes))
        return false;
    if(_finalizada != c._finalizada)
        return false;
    if(_ranking != c._ranking)
        return false;
    if(!mismosAntiDoping(_lesTocoControlAntiDoping,c._lesTocoControlAntiDoping))
        return false;
    return true;
}

Competencia Competencia::operator=(const Competencia &c) {
    _categoria = c._categoria;
    _participantes = c._participantes;
    _finalizada = c._finalizada;
    _ranking = c._ranking;
    _lesTocoControlAntiDoping = c._lesTocoControlAntiDoping;
    return (*this);
}

//AUXILIARES
Atleta Competencia::participanteConNumber(int c, const vector<Atleta> &as){
    int i = 0;
    while(i < as.size()) {
        if (as[i].ciaNumber() == c)
            return as[i];
        i++;
    }
}

pair<Atleta,bool> Competencia::atletaConSuControl(const Atleta &x, const vector<pair<int,bool>> &as){
    int i = 0;
    while(i < as.size()) {
        if (as[i].first == x.ciaNumber()) {
            pair<Atleta, bool> res = make_pair(x, as[i].second);
            return res;
        }
        i++;
    }
}

bool Competencia::estaEnControl(const Atleta &x, const vector<pair<int,bool>> &as){
    int i = 0;
    while(i < as.size()) {
        if (as[i].first == x.ciaNumber()) {
            return true;
        }
        i++;
    }
    return false;
}

vector<Atleta> Competencia::primerosDeAntiDoping(const vector<pair<Atleta,bool>> &ad){
    int i = 0;
    vector<Atleta> ps;
    while(i < ad.size()) {
        ps.push_back(ad[i].first);
        i++;
    }
    return ps;
}

bool Competencia::capacidadesOrdenadas(const vector<int> &vs) const{
    int i = 0;
    while(i < vs.size()-1) {
        if (vs[i] > vs[i + 1])
            return false;
        i++;
    }
    return true;
}

bool Competencia::pertenece(const Atleta &a, const vector<pair<Atleta,bool>> &vs){
    int i = 0;
    while(i < vs.size()){
        if(vs[i].first == a)
            return true;
        i++;
    }
    return false;
}

bool Competencia::mismosParticipantes(const vector<Atleta> &xs, const vector<Atleta> &ys) const{
    int i = 0;
    if(xs.size() != ys.size()) return false;
    while(i < xs.size()){
        if(cuentaParticipante(xs[i],xs) != cuentaParticipante(xs[i],ys))
            return false;
        i++;
    }
    return true;
}

int Competencia::cuentaParticipante(const Atleta &a, const vector<Atleta> &as) const{
    int i = 0;
    int cuenta = 0;
    while(i < as.size()){
        if(a == as[i])
            cuenta++;
        i++;
    }
    return  cuenta;
}

bool Competencia::mismosAntiDoping(const vector<pair<Atleta,bool>> &xs, const vector<pair<Atleta,bool>> &ys) const{
    int i = 0;
    bool res = true;
    while(i < xs.size() && res){
        if(cuentaDopado(xs[i].first,primeros(xs)) == cuentaDopado(xs[i].first,primeros(ys)))
                res = true;
        else res = false;
        i++;
    }
    return res;
}

vector<Atleta> Competencia::primeros(const vector<pair<Atleta,bool>> &ps) const{
    vector<Atleta> as;
    int i = 0;
    while(i < ps.size()){
        as.push_back(ps[i].first);
        i++;
    }
    return as;
}

int Competencia::cuentaDopado(const Atleta &a, const vector<Atleta> &as) const{
    int i = 0;
    int cuenta = 0;
    while(i < as.size() && leDioPositivo(as[i]) == leDioPositivo(a)) {
        if (as[i] == a)
            cuenta++;
        i++;
    }
    return cuenta;
}

bool stringToBool(string s){
    if(s == "True") return true;
    else return false;
}

string boolToString(bool b){
    if(b == true) return "True";
    else return "False";
}

//FIN AUXILIARES
