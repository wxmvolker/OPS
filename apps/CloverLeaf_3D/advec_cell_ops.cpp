//
// auto-generated by ops.py on 2014-07-16 16:41
//



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define OPS_3D
#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_advec_cell_kernel1_xdir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel2_xdir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel3_xdir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel4_xdir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel1_ydir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel2_ydir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel3_ydir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel4_ydir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel1_zdir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel2_zdir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel3_zdir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_cell_kernel4_zdir(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"
//#include "advec_cell_kernel.h"


void advec_cell(int sweep_number, int dir)
{

  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int z_min = field.z_min;
  int z_max = field.z_max;

  int rangexyz[] = {x_min-2,x_max+2,y_min-2,y_max+2,z_min-2,z_max+2};
  int rangexyz_inner[] = {x_min,x_max,y_min,y_max,z_min,z_max};

  int rangexyz_inner_plus2x[] = {x_min,x_max+2,y_min,y_max,z_min,z_max};
  int rangexyz_inner_plus2yz[] = {x_min,x_max,y_min,y_max+2,z_min,z_max+2};
  int rangexyz_inner_plus2z[] = {x_min,x_max,y_min,y_max,z_min,z_max+2};


  if(dir == g_xdir) {

    if(sweep_number == 1) {
      ops_par_loop_advec_cell_kernel1_xdir("advec_cell_kernel1_xdir", clover_grid, 3, rangexyz,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                   ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ),
                   ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ),
                   ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ));
    }
    else if (sweep_number == 3) {
      ops_par_loop_advec_cell_kernel2_xdir("advec_cell_kernel2_xdir", clover_grid, 3, rangexyz,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                   ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ));
    }

    ops_par_loop_advec_cell_kernel3_xdir("advec_cell_kernel3_xdir", clover_grid, 3, rangexyz_inner_plus2x,
                 ops_arg_dat(vol_flux_x, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array1, S3D_000_M100, "double", OPS_READ),
                 ops_arg_dat(xx, S3D_000_P100_STRID3D_X, "int", OPS_READ),
                 ops_arg_dat(vertexdx, S3D_000_P100_M100_STRID3D_X, "double", OPS_READ),
                 ops_arg_dat(density1, S3D_000_P100_M100_M200, "double", OPS_READ),
                 ops_arg_dat(energy1, S3D_000_P100_M100_M200, "double", OPS_READ),
                 ops_arg_dat(mass_flux_x, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE));

    ops_par_loop_advec_cell_kernel4_xdir("advec_cell_kernel4_xdir", clover_grid, 3, rangexyz_inner,
                 ops_arg_dat(density1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(energy1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(mass_flux_x, S3D_000_P100, "double", OPS_READ),
                 ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ),
                 ops_arg_dat(work_array1, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array2, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array4, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array5, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000_P100, "double", OPS_READ));

  }
  else if(dir == g_ydir) {
    if(sweep_number == 2) {
      if (advect_x) {
      ops_par_loop_advec_cell_kernel1_ydir("advec_cell_kernel1_ydir", clover_grid, 3, rangexyz,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                   ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ),
                   ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ));
    }
    else {
      ops_par_loop_advec_cell_kernel2_ydir("advec_cell_kernel2_ydir", clover_grid, 3, rangexyz,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                   ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ),
                   ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ));
    }
  }

    ops_par_loop_advec_cell_kernel3_ydir("advec_cell_kernel3_ydir", clover_grid, 3, rangexyz_inner_plus2yz,
                 ops_arg_dat(vol_flux_y, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array1, S3D_000_0M10, "double", OPS_READ),
                 ops_arg_dat(yy, S3D_000_0P10_STRID3D_Y, "int", OPS_READ),
                 ops_arg_dat(vertexdy, S3D_000_0P10_0M10_STRID3D_Y, "double", OPS_READ),
                 ops_arg_dat(density1, S3D_000_0P10_0M10_0M20, "double", OPS_READ),
                 ops_arg_dat(energy1, S3D_000_0P10_0M10_0M20, "double", OPS_READ),
                 ops_arg_dat(mass_flux_y, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE));

    ops_par_loop_advec_cell_kernel4_ydir("advec_cell_kernel4_ydir", clover_grid, 3, rangexyz_inner,
                 ops_arg_dat(density1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(energy1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(mass_flux_y, S3D_000_0P10, "double", OPS_READ),
                 ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ),
                 ops_arg_dat(work_array1, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array2, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array4, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array5, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000_0P10, "double", OPS_READ));

  }
  else if(dir == g_zdir) {

    if(sweep_number == 1) {
      ops_par_loop_advec_cell_kernel1_zdir("advec_cell_kernel1_zdir", clover_grid, 3, rangexyz,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                   ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ),
                   ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ),
                   ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ));
    }
    else if (sweep_number == 3) {
      ops_par_loop_advec_cell_kernel2_zdir("advec_cell_kernel2_zdir", clover_grid, 3, rangexyz,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                   ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ));
    }

    ops_par_loop_advec_cell_kernel3_zdir("advec_cell_kernel3_zdir", clover_grid, 3, rangexyz_inner_plus2z,
                 ops_arg_dat(vol_flux_z, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array1, S3D_000_00M1, "double", OPS_READ),
                 ops_arg_dat(zz, S3D_000_00P1_STRID3D_Z, "int", OPS_READ),
                 ops_arg_dat(vertexdz, S3D_000_00P1_00M1_STRID3D_Z, "double", OPS_READ),
                 ops_arg_dat(density1, S3D_000_00P1_00M1_00M2, "double", OPS_READ),
                 ops_arg_dat(energy1, S3D_000_00P1_00M1_00M2, "double", OPS_READ),
                 ops_arg_dat(mass_flux_z, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE));

    ops_par_loop_advec_cell_kernel4_zdir("advec_cell_kernel4_zdir", clover_grid, 3, rangexyz_inner,
                 ops_arg_dat(density1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(energy1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(mass_flux_z, S3D_000_00P1, "double", OPS_READ),
                 ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ),
                 ops_arg_dat(work_array1, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array2, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array4, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array5, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000_00P1, "double", OPS_READ));

  }

}
