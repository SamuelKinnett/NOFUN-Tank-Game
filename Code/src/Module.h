#ifndef NTG_MODULE_H
#define NTG_MODULE_H

class Module {
public:
    virtual void update(double deltaTime) = 0;
    //virtual void readStream(Stream) = 0;
    //virtual void writeStream(Stream) = 0;

    //enum describing if a module is damaged
    enum damage {
        USABLE,
        DAMAGED,
        BROKEN
    };

    damage getDamageState() {
        return _damageState;
    }

    double getHP() {
        return _HP;
    }

    double getMaxHP() {
        return _maxHP;
    }

    void hit(double pen, double dmg) {
        if (pen >= penDurability) {
            _HP -= dmg;
        }
        if (_HP < 0) {
            _HP = 0;
            _damageState = BROKEN;
        }
        else if (_HP < _maxHP / 2) {
            _damageState = DAMAGED;
        }
    }

private:
    damage _damageState;
    double _HP;
    double _maxHP;
    //penetration needed to damage the module
    double _penDurability;
};

#endif
