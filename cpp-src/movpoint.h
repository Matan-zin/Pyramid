#ifndef __movpoint__h
#define __movpoint__h

// --------------------------------------------------------------------------------------------------------------

static const int MP_ARR_SIZE = 12;

// --------------------------------------------------------------------------------------------------------------

enum class Direction 
{
    Right, Forward, Left , Backward
};

// --------------------------------------------------------------------------------------------------------------

struct Points 
{
    alignas(16) float points[MP_ARR_SIZE] 
    {
        4.0f, 0.0f, 0.0f,
        4.0f, 0.0f, 0.0f,
        4.0f, 0.0f, 0.0f,
        4.0f, 0.0f, 0.0f,
    };
};

// --------------------------------------------------------------------------------------------------------------

class MovPoints {

public:

    MovPoints() : index(0), dir(Direction::Right), counter(1), isBase(true) {};


    int calc_side(int size) noexcept;

    void print_points() noexcept;

    float * get_points() noexcept;

    void change_direction() noexcept;

    void change_up_direction() noexcept;

    void change_init_direction() noexcept;

    inline void increment_index() noexcept { index += 12; }

    inline void reset_counter() noexcept { counter = 1; }

    int get_counter() noexcept { return counter ; }

    int index;

private:
    Points p;
    Direction dir;
   
    int counter;
    bool isBase;
};

#endif