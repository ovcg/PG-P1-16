#ifndef PONTO_H
#define PONTO_H

class Ponto
{
public:
    float x, y;
    Ponto(float x, float y) : x(x), y(y) {};

 Ponto operator-(Ponto p);
};
    
Ponto Ponto::operator-(Ponto pt){
    int a, b;
    a = x - pt.x;
    b = y - pt.y;
    
    return Ponto(a, b);
}

#endif
