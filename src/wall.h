/*
 *  Wall class declaration
 */
// hej

class shot;

#ifndef WALL_H
#define WALL_H_


class Wall {
private:
    // Wall position
    int x;
    int y;

public:
    Wall(int x, int y);

public:
    // Wall dimensions
    static const int HEIGHT;
    static const int WIDTH;

    // Functions
    int get_x();
    int get_y();
    //int predict(Shot *shot);
    //void SHOTCALCULATORFUNCTION(Shot *shot);
};

#endif
