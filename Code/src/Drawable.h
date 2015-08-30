#ifndef DRAWABLE_HPP_INCLUDED_
#define DRAWABLE_HPP_INCLUDED_

class Drawable {
public:
    virtual void draw() = 0;

    virtual ~Drawable();
};

#endif
