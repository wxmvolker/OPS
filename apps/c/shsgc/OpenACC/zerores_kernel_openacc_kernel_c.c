//
// auto-generated by ops.py
//
#include "./OpenACC/shsgc_common.h"

#define OPS_GPU

int xdim0_zerores_kernel;
int xdim1_zerores_kernel;
int xdim2_zerores_kernel;


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2


#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)
#define OPS_ACC2(x) (x)

//user function
inline
void zerores_kernel(double *rho_res, double *rhou_res, double *rhoE_res) {
      rho_res[OPS_ACC0(0)] = 0.0;
      rhou_res[OPS_ACC1(0)] = 0.0;
      rhoE_res[OPS_ACC2(0)] = 0.0;
}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2



void zerores_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  int x_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2)
  #pragma acc loop
  #endif
  for ( int n_x=0; n_x<x_size; n_x++ ){
    zerores_kernel(  p_a0 + n_x*1*1,
           p_a1 + n_x*1*1, p_a2 + n_x*1*1 );

  }
}
