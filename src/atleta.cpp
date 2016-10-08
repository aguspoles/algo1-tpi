#include "../include/atleta.h"


Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {
    Deporte d = "Tenis";
    pair<Deporte,int> dep = make_pair(d,50);
    _anioNacimiento = a;
    _ciaNumber = c;
    _nacionalidad = p;
    _nombre = n;
    _genero = g;
    _deportes.push_back(dep);
}

string Atleta::nombre() const {
    return _nombre;
}

Genero Atleta::genero() const {
    return _genero;
}

int Atleta::anioNacimiento() const {
    return _anioNacimiento;
}

Pais Atleta::nacionalidad() const {
    return _nacionalidad;
}

int Atleta::ciaNumber() const {
    return _ciaNumber;
}

vector<Deporte> Atleta::deportes() const {
    vector<Deporte> ret;
    int i = 0;
    while(i < _deportes.size()){
        ret.push_back(_deportes[i].first);
        i++;
    }
    return ret;
}

int Atleta::capacidad(const Deporte &d) const {
    int i = 0;
    while(i < _deportes.size()) {
        if (_deportes[i].first == d)
            return _deportes[i].second;
        i++;
    }
}

Deporte Atleta::especialidad() const {
    int i = 1;
    Deporte max = _deportes[0].first;
    while(i < _deportes.size()-1){
        if(_deportes[i].second >= _deportes[i+1].second)
            max = _deportes[i].first;
        i++;
    }
    return max;
}

void Atleta::entrenarNuevoDeporte(const Deporte &d, const int &c) {
    int i = 0;
    bool estaElDeporte = false;
    pair<Deporte,int> dep = make_pair(d,c);
    while(i < _deportes.size() && !estaElDeporte){
        if(_deportes[i].first == d) {
            estaElDeporte = true;
            _deportes[i].second = c;
        }
        i++;
    }
    if(!estaElDeporte) {
        _deportes.push_back(dep);
        ordenar(_deportes);
    }
}

void Atleta::mostrar(std::ostream &os) const {
    os << *this;
}

void Atleta::guardar(std::ostream &os) const {
    os << *this;
}

void Atleta::cargar(std::istream &is) {
    //is >> *this;
}

//A |Liu Song| |Masculino| 1972 |China| 123 [(|Tenis de Mesa|, 90)]
std::ostream &operator<<(std::ostream &os, const Atleta &a) {
    os << "A " << "|" << a.nombre() << "| " << "|" << a.genero() << "| ";
    os << a.anioNacimiento() << " " << "|" << a.nacionalidad() << "| ";
    os << "[";
    int i = 0;
    while(i < a.deportes().size()){
        os << "(|" << a.deportes()[i] << "|," << a.capacidad(a.deportes()[i]) << ")";
        if(i < a.deportes().size()-1)
            os << ",";
    }
    os << "]";
    return os;
}

//A |Liu Song| | Masculino 4 1972 |China| 123 [(|Tenis de Mesa|, 90)]
std::istream &operator>>(std::istream &is, const Atleta &a) {
    /*string s;
    is.ignore(3);//A >> ' ' >> '|'
    getline(is,s,'|');
    a.nombre() = s;
    is.ignore(2);//' ' >> '|'
    is >> a.genero();
    is.ignore(2);//'|' >> ' '
    is >> a.anioNacimiento();
    is.ignore(2);
    is >> a.nacionalidad();*/
    return is;
}

bool Atleta::operator==(const Atleta &a) const {
    bool res = false;
    int i = 0;
    if(_nombre != a.nombre())
        return false;
    if(_anioNacimiento != a.anioNacimiento())
        return false;
    if(_ciaNumber != a.ciaNumber())
        return false;
    if(_genero != a.genero())
        return false;
    if(_nacionalidad != a.nacionalidad())
        return res;
    if(_deportes.size() != a.deportes().size())
        return res;
    while(i < _deportes.size()){
        if(_deportes[i].first != (a.deportes())[i])
            return res;
        else if(_deportes[i].second != a.capacidad(a.deportes()[i]))
            return res;
        i++;
    }
    res = true;
    return res;
}

Atleta Atleta::operator=(const Atleta &a) {
    _anioNacimiento = a._anioNacimiento;
    _ciaNumber = a._ciaNumber;
    _nacionalidad = a._nacionalidad;
    _nombre = a._nombre;
    _genero = a._genero;
    _deportes = a._deportes;
    return (*this);
}

//auxiliar
void Atleta::ordenar(vector<pair<Deporte,int>> &vs){
    int i = 0;
    int pasada = 1;
    pair<Deporte,int> swap;
    while(pasada < vs.size()) {
        while (i < vs.size() - 1) {
            if (vs[i].first > vs[i + 1].first) {
                swap = vs[i];
                vs[i] = vs[i + 1];
                vs[i + 1] = swap;
            }
            i++;
        }
        pasada++;
    }
}