//
// auto-generated by ops.py
//
#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_update_halo_kernel5_minus_2_back;
int ydim0_update_halo_kernel5_minus_2_back;
int xdim1_update_halo_kernel5_minus_2_back;
int ydim1_update_halo_kernel5_minus_2_back;


#undef OPS_ACC0
#undef OPS_ACC1


#define OPS_ACC0(x,y,z) (x+xdim0_update_halo_kernel5_minus_2_back*(y)+xdim0_update_halo_kernel5_minus_2_back*ydim0_update_halo_kernel5_minus_2_back*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_update_halo_kernel5_minus_2_back*(y)+xdim1_update_halo_kernel5_minus_2_back*ydim1_update_halo_kernel5_minus_2_back*(z))

//user function

inline void update_halo_kernel5_minus_2_back(double *vol_flux_z, double *mass_flux_z, const int* fields) {
  if(fields[FIELD_VOL_FLUX_Z] == 1)  vol_flux_z[OPS_ACC0(0,0,0)]  = -vol_flux_z[OPS_ACC0(0,0,2)];
  if(fields[FIELD_MASS_FLUX_Z] == 1) mass_flux_z[OPS_ACC1(0,0,0)] = -mass_flux_z[OPS_ACC1(0,0,2)];
}


#undef OPS_ACC0
#undef OPS_ACC1



void update_halo_kernel5_minus_2_back_c_wrapper(
  double *p_a0,
  double *p_a1,
  int *p_a2,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2)
  #pragma acc loop
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        update_halo_kernel5_minus_2_back(  p_a0 + n_x*1*1 + n_y*xdim0_update_halo_kernel5_minus_2_back*1*1 + n_z*xdim0_update_halo_kernel5_minus_2_back*ydim0_update_halo_kernel5_minus_2_back*1,
           p_a1 + n_x*1*1 + n_y*xdim1_update_halo_kernel5_minus_2_back*1*1 + n_z*xdim1_update_halo_kernel5_minus_2_back*ydim1_update_halo_kernel5_minus_2_back*1,
           p_a2 );

      }
    }
  }
}
