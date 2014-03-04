//
// auto-generated by ops.py on 2014-03-04 15:29
//



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_viscosity_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "viscosity_kernel.h"

void viscosity_func()
{

  int x_cells = grid->x_cells;
  int y_cells = grid->y_cells;
  int x_min = field->x_min;
  int x_max = field->x_max;
  int y_min = field->y_min;
  int y_max = field->y_max;

  int rangexy_inner[] = {x_min,x_max,y_min,y_max};

  ops_par_loop_viscosity_kernel("viscosity_kernel", clover_grid, 2, rangexy_inner,
               ops_arg_dat(xvel0, S2D_00_P10_0P1_P1P1, "double", OPS_READ),
               ops_arg_dat(yvel0, S2D_00_P10_0P1_P1P1, "double", OPS_READ),
               ops_arg_dat(celldx, S2D_00_P10_STRID2D_X, "double", OPS_READ),
               ops_arg_dat(celldy, S2D_00_0P1_STRID2D_Y, "double", OPS_READ),
               ops_arg_dat(pressure, S2D_10_M10_01_0M1, "double", OPS_READ),
               ops_arg_dat(density0, S2D_00, "double", OPS_READ),
               ops_arg_dat(viscosity, S2D_00, "double", OPS_WRITE));
}
