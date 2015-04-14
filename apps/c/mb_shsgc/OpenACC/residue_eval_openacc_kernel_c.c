//
// auto-generated by ops.py
//
#include "./OpenACC/shsgc_common.h"

#define OPS_GPU

int xdim0_residue_eval;
int xdim1_residue_eval;
int xdim2_residue_eval;
int xdim3_residue_eval;
int xdim4_residue_eval;
int xdim5_residue_eval;

#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)
#define OPS_ACC2(x) (x)
#define OPS_ACC3(x) (x)
#define OPS_ACC4(x) (x)
#define OPS_ACC5(x) (x)

//user function
inline
void residue_eval(const double *der1, const double *der2, const double *der3,
                  double *rho_res, double *rhou_res, double *rhoE_res) {
  rho_res[OPS_ACC3(0)] = der1[OPS_ACC0(0)];
  rhou_res[OPS_ACC4(0)] = der2[OPS_ACC1(0)];
  rhoE_res[OPS_ACC5(0)] = der3[OPS_ACC2(0)];
  }


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5



void residue_eval_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  int x_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5)
  #pragma acc loop
  #endif
  for ( int n_x=0; n_x<x_size; n_x++ ){
    residue_eval(  p_a0 + n_x*1*1,
           p_a1 + n_x*1*1, p_a2 + n_x*1*1,
           p_a3 + n_x*1*1, p_a4 + n_x*1*1,
           p_a5 + n_x*1*1 );

  }
}
