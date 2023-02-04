#include <iostream>
#include <xmmintrin.h>

#include "movpoint.h"



void inline _fill_array_with_zero(float * arr)
// Array size is known in advance (12)
{
    __m128 zero = _mm_setzero_ps();

    _mm_store_ps(arr + 0, zero);
    _mm_store_ps(arr + 4, zero);
    _mm_store_ps(arr + 8, zero);
}



void change_xy_point(float * arr, float val) 
{
    _fill_array_with_zero(arr);

    arr[0] = arr[3] = arr[6] = arr[9] = val;
    arr[1] = arr[4] = arr[7] = arr[10] = val;
}



void change_x_point(float * arr, float val) 
{
    _fill_array_with_zero(arr);
    
    arr[0] = arr[3] = arr[6] = arr[9] = val;
}



void change_y_point(float * arr, float val) 
{
    _fill_array_with_zero(arr);
    
    arr[1] = arr[4] = arr[7] = arr[10] = val;
}



void change_z_point(float * arr, float val) 
{
    _fill_array_with_zero(arr);
    
    arr[2] = arr[5] = arr[8] = arr[11] = val;
}



void MovPoints::change_direction() noexcept 
{
        
    if(dir == Direction::Backward) 
    {
        dir = Direction::Right;
    } 
    else 
    {
        dir = (Direction)((int) dir + 1);
    }

    switch(dir)
    {
        case Direction::Right: 
        {
            change_x_point(p.points, 4.0f);
            break;
        };
        case Direction::Forward: 
        {
            change_z_point(p.points, 4.0f);
            break;
        };
        case Direction::Left: 
        {
            change_x_point(p.points, -4.0f);
            break;
        };
        case Direction::Backward: 
        {
            change_z_point(p.points, -4.0f);
            break;
        };
    }
}



void MovPoints::change_up_direction() noexcept 
{
    change_xy_point(p.points, 4.0f);
}



void MovPoints::change_init_direction() noexcept 
{
    change_x_point(p.points, 4.0f);
}



float * MovPoints::get_points() noexcept 
{
    return p.points;
}



void MovPoints::print_points() noexcept 
{
    for(int i {} ; i < MP_ARR_SIZE; i++) 
    {
        std::cout << p.points[i] << " ";
        if((i + 1) % 3 == 0) std::cout << "\n";
    }
}



int MovPoints::calc_side(int size) noexcept
{
    if(counter == 1 && isBase  ) size -= 1;
    if(counter == 3) { 
        size -= 1;
        isBase = false;
    }
    
    counter++;
    return size;
}