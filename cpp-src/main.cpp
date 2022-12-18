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

constexpr int SIDES = 4;
constexpr int CUBE_POINTS = 108;
constexpr int CUBE_UV_POINTS = 72;
constexpr int CUBE_SSE_POINTS = 9;


void compute_pyramid_uvs()
{

}

void compute_pyramid_normals() 
{

}


void move_the_cube(float* pyr_ver, MovPoints& p, float * current_points) 
{
  float * points = p.get_points();

  __m128 cp1, cp2, cp3, p1, p2, p3, res1, res2, res3;

  for(int i {}, offset {}; i < CUBE_SSE_POINTS; i++, offset += 12 ) 
  {
    p1 = _mm_load_ps(((float *) current_points) + offset + 0);
    p2 = _mm_load_ps(((float *) current_points) + offset + 4);
    p3 = _mm_load_ps(((float *) current_points) + offset + 8);

    cp1 = _mm_load_ps(((float *) points) + 0);
    cp2 = _mm_load_ps(((float *) points) + 4);
    cp3 = _mm_load_ps(((float *) points) + 8);

    res1 = _mm_add_ps( cp1, p1 );
    res2 = _mm_add_ps( cp2, p2 );
    res3 = _mm_add_ps( cp3, p3 );

    _mm_store_ps(((float *) current_points) + offset + 0, res1);
    _mm_store_ps(((float *) current_points) + offset + 4, res2);
    _mm_store_ps(((float *) current_points) + offset + 8, res3); 


    _mm_store_ps(((float *) pyr_ver) + p.index + 0, res1);
    _mm_store_ps(((float *) pyr_ver) + p.index + 4, res2);
    _mm_store_ps(((float *) pyr_ver) + p.index + 8, res3);

    p.increment_index();
  }
}

void compute_pyramid_vertices(float * pyr_vertices, float * initial_point_vertices, int base)
{
  MovPoints p {};
  int side = base;
    
    while(!(base <= 1)) 
    {
      for(int i {}; i < SIDES; i++) 
      {
        for(int j {}; j < side; j++) 
        {
          move_the_cube(pyr_vertices, p, initial_point_vertices);
        }
        
        p.change_direction();

        side = p.calc_side(side);
      }

      p.change_up_direction();      

      move_the_cube(pyr_vertices, p, initial_point_vertices);

      p.change_init_direction();

      p.reset_counter();
      
      base -= 2;
      side = base - 1;
    }
}

int main() {

  int base = 5;

  float * pyr_uvs      = nullptr;        
  float * pyr_normals  = nullptr;    
  float * pyr_vertices = nullptr;


try {
    int num_of_cubes = base * base;
    
    float * pyr_uvs      = static_cast<float*>(std::aligned_alloc(16, num_of_cubes * CUBE_UV_POINTS * sizeof(float)));
    float * pyr_normals  = static_cast<float*>(std::aligned_alloc(16, num_of_cubes * CUBE_POINTS    * sizeof(float)));
    float * pyr_vertices = static_cast<float*>(std::aligned_alloc(16, num_of_cubes * CUBE_POINTS    * sizeof(float)));

    std::thread cpv_t { compute_pyramid_vertices, pyr_vertices, initial_point_vertices, base };
    std::thread cpn_t { compute_pyramid_normals };
    std::thread cpu_t { compute_pyramid_uvs };

    cpv_t.join();
    cpn_t.join();
    cpu_t.join();

    remove("/home/mz/Matan/ThreeJs/PracticeSmall/src/new.js");
    std::ofstream file("/home/mz/Matan/ThreeJs/PracticeSmall/src/new.js");
    file << "export const pyr = [";
    for(int i = 0; i < num_of_cubes * CUBE_POINTS; i++) {
      file << pyr_vertices[i] << ",";
    }
    file << "]";
    file.close();

    std::free(pyr_vertices);
    std::free(pyr_normals);
    std::free(pyr_uvs);
    return 0;
  } catch(std::exception& e) {
    std::free(pyr_vertices);
    std::free(pyr_normals);
    std::free(pyr_uvs);
    return 1;
  } catch(...) {
    std::free(pyr_vertices);
    std::free(pyr_normals);
    std::free(pyr_uvs);
    return 1;
  }

}
