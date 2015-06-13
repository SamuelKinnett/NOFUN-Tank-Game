#pragma once
#ifndef _ENGINE_HPP_INCLUDED_
#define _ENGINE_HPP_INCLUDED_

#include "Module.hpp"
#include <stdarg.h>

class Engine : public Module
{
    public:
        Engine(int numGears, double... args)
        {
            _numGears = numGears;
            _gears = new double[numGears];
        }
        virtual void update(double deltaTime)
        {

        }
    private:
        int _rpm;
        int _gear;
        int _numGears;
        double *_gearRatios;
};

#endif
