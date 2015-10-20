//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_update_halo_kernel2_yvel_plus_2_right;
int ydim0_update_halo_kernel2_yvel_plus_2_right;
int xdim1_update_halo_kernel2_yvel_plus_2_right;
int ydim1_update_halo_kernel2_yvel_plus_2_right;

#define OPS_ACC0(x,y,z) (n_x*1+n_y*xdim0_update_halo_kernel2_yvel_plus_2_right*1+n_z*xdim0_update_halo_kernel2_yvel_plus_2_right*ydim0_update_halo_kernel2_yvel_plus_2_right*1+x+xdim0_update_halo_kernel2_yvel_plus_2_right*(y)+xdim0_update_halo_kernel2_yvel_plus_2_right*ydim0_update_halo_kernel2_yvel_plus_2_right*(z))
#define OPS_ACC1(x,y,z) (n_x*1+n_y*xdim1_update_halo_kernel2_yvel_plus_2_right*1+n_z*xdim1_update_halo_kernel2_yvel_plus_2_right*ydim1_update_halo_kernel2_yvel_plus_2_right*1+x+xdim1_update_halo_kernel2_yvel_plus_2_right*(y)+xdim1_update_halo_kernel2_yvel_plus_2_right*ydim1_update_halo_kernel2_yvel_plus_2_right*(z))

//user function



void update_halo_kernel2_yvel_plus_2_right_c_wrapper(
  double * restrict yvel0,
  double * restrict yvel1,
  const int * restrict fields,
  int x_size, int y_size, int z_size) {
  #pragma omp parallel for
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        
  if(fields[FIELD_YVEL0] == 1) yvel0[OPS_ACC0(0,0,0)] = yvel0[OPS_ACC0(-2,0,0)];
  if(fields[FIELD_YVEL1] == 1) yvel1[OPS_ACC1(0,0,0)] = yvel1[OPS_ACC1(-2,0,0)];

      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1

