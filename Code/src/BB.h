#ifndef NTG_BB_H
#define NTG_BB_H

//Implements a Bounding Box with a rotation
class BB
{
public:
    BB();

private:
    double _x[2], _y[2], rotation;
};

#endif // BB_H_INCLUDED
