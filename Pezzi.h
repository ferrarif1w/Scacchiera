#ifndef PEZZI_H
#define PEZZI_H

class Pieces
{

private:
    int Pos(pair<int, int> pos);
    bool PrimaMossa = false;

public:
    R();
    R(int Posicion, int PM);

    D();
    D(int Posicion);

    A();
    A(int Posicion);

    C();
    C(int Posicion);

    T();
    T(int Posicion);

    P();
    P(int Posicion, int PM);
};
#endif