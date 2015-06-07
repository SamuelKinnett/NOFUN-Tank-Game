#pragma once
#ifndef BB_HPP_INCLUDED
#define BB_HPP_INCLUDED

//Implements a Bounding Box with a rotation
class BB
{
    public:
        BB();
    private:
        double _x[2], _y[2], rotation;
};

#endif // BB_H_INCLUDED
