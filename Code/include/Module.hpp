#pragma once
#ifndef _MODULE_HPP_INCLUDED_
#define _MODULE_HPP_INCLUDED_

class Module
{
    public:
        virtual void update(double deltaTime) = 0;

        //enum describing if a module is damaged
        enum damage 
        {
            USABLE,
            DAMAGED,
            BROKEN
        };
        damage getDamageState()
        {
            return damageState;
        }
        double getHP()
        {
            return HP;
        }
        double getMaxHP()
        {
            return maxHP;
        }
        void hit(double pen, double dmg)
        {
            if (pen >= penDurability)
            {
                HP -= dmg;
            }
            if (HP < 0) {
                HP = 0;
                damageState = BROKEN;
            }
            else if (HP < maxHP / 2)
            {
                damageState = DAMAGED;
            }
        }
    private:
        damage damageState;
        double HP;
        double maxHP;
        //penetration needed to damage the module
        double penDurability;
};

#endif