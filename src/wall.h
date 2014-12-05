/*
 *  Wall class declaration
 */
#ifndef WALL_H
#define WALL_H

#include "Sprite.h"

class Wall : public Sprite
{

public:
	Wall(int x, int y, double angle, const char*& img_file,
			SDL_Renderer*& renderer);
	~Wall();

    // Returns the exact position of original "top left corner"
	// after rotation.
    double get_x1();
    double get_y1();
    void draw(); // Troligtvis inte här
    bool bounding_box();
    //int predict(Shot *shot);
    //void SHOTCALCULATORFUNCTION(Shot *shot);

private:

};

#endif
