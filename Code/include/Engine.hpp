#pragma once
#ifndef _ENGINE_HPP_INCLUDED_
#define _ENGINE_HPP_INCLUDED_

#include "Module.hpp"

class Engine : public Module
{
    public:
        Engine();
        virtual void update(double deltaTime)
        {
            
        }

        virtual void copyState(const Engine& e)
        {

        }
    private:

};

#endif