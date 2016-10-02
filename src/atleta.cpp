#include "../include/atleta.h"


Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {
    Deporte d = "Tenis";
    _anioNacimiento = a;
    _ciaNumber = c;
    _nacionalidad = p;
    _nombre = n;
    _genero = g;
    _deportes.push_back(pair(d,0));
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
    }
    return ret;
}

int Atleta::capacidad(const Deporte &d) const {
    int i = 0;
    while(i < _deportes.size()) {
        if (_deportes[i].first == d)
            return _deportes[i].second;
    }
}

Deporte Atleta::especialidad() const {
    int i = 1;
    Deporte max = _deportes[0].first;
    while(i < _deportes.size()){
        if(_deportes[i].second >= _deportes[i].second)
            max = _deportes[i].first;
    }
    return max;
}

void Atleta::entrenarNuevoDeporte(const Deporte &d, const int &c) {
    int i = 0;
    bool estaElDeporte = false;
    while(i < _deportes.size() && !estaElDeporte){
        if(_deportes[i].first == d) {
            estaElDeporte = true;
            _deportes[i].second = c;
        }
    }
    if(!estaElDeporte)
        _deportes.push_back(pair(d,c));

    //y aca lo ordeno
}

void Atleta::mostrar(std::ostream &os) const {
}

void Atleta::guardar(std::ostream &os) const {
}

void Atleta::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const Atleta &a) {
    return os;
}

std::ostream &operator>>(std::ostream &os, const Atleta &a) {
    return os;
}

bool Atleta::operator==(const Atleta &a) const {
    bool res = false;
    int i = 0;
    if(this->_nombre != a.nombre())
        return false;
    if(this->_anioNacimiento != a.anioNacimiento())
        return false;
    if(this->_ciaNumber != a.ciaNumber())
        return false;
    if(this->genero() != a.genero())
        return false;
    if(this->_nacionalidad != a.nacionalidad())
        return false;
    while(i < _deportes.size()){
        if(_deportes[i].first != (a.deportes())[i] || _deportes[i].second != a.capacidad(a.deportes()[i]))
            return false;
    }
    return true;
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
