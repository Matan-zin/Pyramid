#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

#include "movpoint.h"
#include "data_points.h"
#include "shared_data.h"

constexpr int SIDES = 4;
constexpr int CUBE_POINTS = 108;
constexpr int CUBE_UV_POINTS = 72;
constexpr int CUBE_SSE_POINTS = 9;

// TODO: need to implement
void compute_pyramid_uvs()
{

}

// TODO: need to implement
void compute_pyramid_normals(float * pyramid_normals, SharedData * share) 
{
  int x = 0, temp = -1;

  while (x != -1)
  {
    x = share -> get_index();
    if(temp != -1 && x != temp) {
      std::cout << "[INDEX]: " << x << std::endl;
    }
    temp = x;
  }
  
}


void move_the_cube(float* pyr_ver, MovPoints& p, float * current_points) 
{
  float * points = p.get_points();

  __m128 cp1, cp2, cp3, p1, p2, p3, res1, res2, res3;

  for(int i {}, offset {}; i < CUBE_SSE_POINTS; i++, offset += 12 ) 
  {
    p1 = _mm_load_ps(current_points + offset + 0);
    p2 = _mm_load_ps(current_points + offset + 4);
    p3 = _mm_load_ps(current_points + offset + 8);

    cp1 = _mm_load_ps(points + 0);
    cp2 = _mm_load_ps(points + 4);
    cp3 = _mm_load_ps(points + 8);

    res1 = _mm_add_ps( cp1, p1 );
    res2 = _mm_add_ps( cp2, p2 );
    res3 = _mm_add_ps( cp3, p3 );

    _mm_store_ps(current_points + offset + 0, res1);
    _mm_store_ps(current_points + offset + 4, res2);
    _mm_store_ps(current_points + offset + 8, res3); 


    _mm_store_ps(pyr_ver + p.index + 0, res1);
    _mm_store_ps(pyr_ver + p.index + 4, res2);
    _mm_store_ps(pyr_ver + p.index + 8, res3);

    p.increment_index();
  }
}

void compute_pyramid_vertices(float * pyramid_vertices, float * initial_cube_vertices, SharedData * share, int base)
{
  MovPoints mov_points {};
  int side = base;
    
    while(!(base <= 1)) 
    {
      for(int i {}; i < SIDES; i++) 
      {
        for(int j {}; j < side; j++) 
        {
          move_the_cube(pyramid_vertices, mov_points, initial_cube_vertices);
          
          share -> set_index(mov_points.index);
        }
        
        mov_points.change_direction();

        side = mov_points.calc_side(side);
      }

      mov_points.change_up_direction();      

      move_the_cube(pyramid_vertices, mov_points, initial_cube_vertices);

      mov_points.change_init_direction();

      mov_points.reset_counter();
      
      base -= 2;
      side = base - 1;
    }

    share -> set_index(-1);
}

int main() {

  int base = 49;
  int num_of_cubes = base * base;
  int pyr_vn_size = num_of_cubes * CUBE_POINTS * sizeof(float);
  int pyr_uv_size = num_of_cubes * CUBE_UV_POINTS * sizeof(float);

  SharedData shared { pyr_vn_size };

  float * pyramid_uvs      = nullptr;        
  float * pyramid_normals  = nullptr;    
  float * pyramid_vertices = nullptr;


try {
    
    pyramid_uvs      = static_cast<float*>(std::aligned_alloc(16, pyr_uv_size));
    pyramid_normals  = static_cast<float*>(std::aligned_alloc(16, pyr_vn_size));
    pyramid_vertices = static_cast<float*>(std::aligned_alloc(16, pyr_vn_size));

    std::thread cpu_t { compute_pyramid_uvs };
    std::thread cpn_t { compute_pyramid_normals, pyramid_normals, &shared };
    std::thread cpv_t { compute_pyramid_vertices, pyramid_vertices, initial_cube_points_vertices, &shared, base };

    cpv_t.join();
    cpn_t.join();
    cpu_t.join();

    remove("/home/mz/Matan/ThreeJs/PracticeSmall/src/new.js");
    std::ofstream file("/home/mz/Matan/ThreeJs/PracticeSmall/src/new.js");
    file << "export const pyr = [";
    for(int i = 0; i < num_of_cubes * CUBE_POINTS; i++) {
      file << pyramid_vertices[i] << ",";
    }
    file << "]";
    file.close();

    std::free(pyramid_vertices);
    std::free(pyramid_normals);
    std::free(pyramid_uvs);
    return 0;

  } catch(std::exception& e) {

    std::free(pyramid_vertices);
    std::free(pyramid_normals);
    std::free(pyramid_uvs);
    return 1;

  } catch(...) {
    
    std::free(pyramid_vertices);
    std::free(pyramid_normals);
    std::free(pyramid_uvs);
    return 1;
  }

}
