//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_update_halo_kernel2_xvel_minus_2_b;
int xdim1_update_halo_kernel2_xvel_minus_2_b;


#undef OPS_ACC0
#undef OPS_ACC1


#define OPS_ACC0(x,y) (x+xdim0_update_halo_kernel2_xvel_minus_2_b*(y))
#define OPS_ACC1(x,y) (x+xdim1_update_halo_kernel2_xvel_minus_2_b*(y))

//user function

inline void update_halo_kernel2_xvel_minus_2_b(ACC<double> &xvel0, ACC<double> &xvel1, const int* fields)
{
  if(fields[FIELD_XVEL0] == 1) xvel0(0,0) = -xvel0(-2,0);
  if(fields[FIELD_XVEL1] == 1) xvel1(0,0) = -xvel1(-2,0);
}


#undef OPS_ACC0
#undef OPS_ACC1



void update_halo_kernel2_xvel_minus_2_b_c_wrapper(
  double *p_a0,
  double *p_a1,
  int *p_a2,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      update_halo_kernel2_xvel_minus_2_b(  p_a0 + n_x*1*1 + n_y*xdim0_update_halo_kernel2_xvel_minus_2_b*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_update_halo_kernel2_xvel_minus_2_b*1*1, p_a2 );

    }
  }
}
