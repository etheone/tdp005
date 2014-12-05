/*
 *  Wall class declaration
 */
#ifndef WALL_H
#define WALL_H

#include "Sprite.h"

class Wall : public Sprite
{

public:
	Wall(int x, int y, double angle, const char*& img_file);
	~Wall();

    // Functions
    int get_x();
    int get_y();
    void draw(); // Troligtvis inte här
    bool bounding_box();
    //int predict(Shot *shot);
    //void SHOTCALCULATORFUNCTION(Shot *shot);

private:
};

#endif
