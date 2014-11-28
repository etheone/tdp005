/*
 *  Wall class declaration
 */
// hejjj

class shot;

#ifndef WALL_H
#define WALL_H


class Wall {

public:

    Wall(int x1, int x2, int y1, int y2);
    // Wall dimensions

    static const int HEIGHT{25};
    static const int WIDTH{25};

    // Functions
    int get_x();
    int get_y();
    void draw(); // Troligtvis inte här
    bool bounding_box();
    //int predict(Shot *shot);
    //void SHOTCALCULATORFUNCTION(Shot *shot);

private:
    // Wall position
    int x1;
    int x2;
    int y1;
    int y2;
};

#endif
