//
// auto-generated by ops.py on 2014-07-16 13:13
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

void ops_par_loop_PdV_kernel_predict(char const *, ops_block, int , int*,
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
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_PdV_kernel_nopredict(char const *, ops_block, int , int*,
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
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "PdV_kernel.h"

void ideal_gas(int predict);
void update_halo(int* fields, int depth);
void revert();

void PdV(int predict)
{
  error_condition = 0;

  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int z_min = field.z_min;
  int z_max = field.z_max;

  int rangexyz_inner[] = {x_min,x_max,y_min,y_max,z_min,z_max};

  if(predict == TRUE) {
  ops_par_loop_PdV_kernel_predict("PdV_kernel_predict", clover_grid, 3, rangexyz_inner,
               ops_arg_dat(xarea, S3D_000_P100, "double", OPS_READ),
               ops_arg_dat(xvel0, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(yarea, S3D_000_0P10, "double", OPS_READ),
               ops_arg_dat(yvel0, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(volume, S3D_000, "double", OPS_READ),
               ops_arg_dat(pressure, S3D_000, "double", OPS_READ),
               ops_arg_dat(density0, S3D_000, "double", OPS_READ),
               ops_arg_dat(density1, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(viscosity, S3D_000, "double", OPS_READ),
               ops_arg_dat(energy0, S3D_000, "double", OPS_READ),
               ops_arg_dat(energy1, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(zarea, S3D_000_00P1, "double", OPS_READ),
               ops_arg_dat(zvel0, S3D_000_fP1P1P1, "double", OPS_READ));
  }
  else {
  ops_par_loop_PdV_kernel_nopredict("PdV_kernel_nopredict", clover_grid, 3, rangexyz_inner,
               ops_arg_dat(xarea, S3D_000_P100, "double", OPS_READ),
               ops_arg_dat(xvel0, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(xvel1, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(yarea, S3D_000_0P10, "double", OPS_READ),
               ops_arg_dat(yvel0, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(yvel1, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(volume, S3D_000, "double", OPS_READ),
               ops_arg_dat(pressure, S3D_000, "double", OPS_READ),
               ops_arg_dat(density0, S3D_000, "double", OPS_READ),
               ops_arg_dat(density1, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(viscosity, S3D_000, "double", OPS_READ),
               ops_arg_dat(energy0, S3D_000, "double", OPS_READ),
               ops_arg_dat(energy1, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(zarea, S3D_000_00P1, "double", OPS_READ),
               ops_arg_dat(zvel0, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(zvel1, S3D_000_fP1P1P1, "double", OPS_READ));
  }

  if(error_condition == 1) {
    ops_printf("PdV: error in PdV\n");
    exit(-2);
  }

  if(predict == TRUE) {
    ideal_gas(TRUE);

    fields[FIELD_DENSITY0]  = 0;
    fields[FIELD_ENERGY0]   = 0;
    fields[FIELD_PRESSURE]  = 1;
    fields[FIELD_VISCOSITY] = 0;
    fields[FIELD_DENSITY1]  = 0;
    fields[FIELD_ENERGY1]   = 0;
    fields[FIELD_XVEL0]     = 0;
    fields[FIELD_YVEL0]     = 0;
    fields[FIELD_XVEL1]     = 0;
    fields[FIELD_YVEL1]     = 0;
    fields[FIELD_VOL_FLUX_X] = 0;
    fields[FIELD_VOL_FLUX_Y] = 0;
    fields[FIELD_MASS_FLUX_X] = 0;
    fields[FIELD_MASS_FLUX_Y] = 0;
    update_halo(fields,1);

  }

  if(predict == TRUE) {
    revert();
  }

}
