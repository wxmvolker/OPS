//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64:enable

#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a,b) ((a<b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a>b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a,b) ((b<0.0) ? (a*(-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8


#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)
#define OPS_ACC2(x) (x)
#define OPS_ACC3(x) (x)
#define OPS_ACC4(x) (x)
#define OPS_ACC5(x) (x)
#define OPS_ACC6(x) (x)
#define OPS_ACC7(x) (x)
#define OPS_ACC8(x) (x)


//user function
void updateRK3_kernel(__global double * restrict rho_new,__global double* restrict  rhou_new,__global double* restrict  rhoE_new,
__global double * restrict rho_old,__global double* restrict  rhou_old,__global double* restrict  rhoE_old,const __global double * restrict rho_res,
const __global double * restrict rhou_res,const __global double * restrict rhoE_res,const  double* restrict  a1,const  double* restrict  a2,

  const double dt)

 {

			rho_new[OPS_ACC0(0)] = rho_old[OPS_ACC3(0)] + dt * a1[0] * (-rho_res[OPS_ACC6(0)]);
			rhou_new[OPS_ACC1(0)] = rhou_old[OPS_ACC4(0)] + dt * a1[0] * (-rhou_res[OPS_ACC7(0)]);
			rhoE_new[OPS_ACC2(0)] = rhoE_old[OPS_ACC5(0)] + dt * a1[0] * (-rhoE_res[OPS_ACC8(0)]);

			rho_old[OPS_ACC3(0)] = rho_old[OPS_ACC3(0)] + dt * a2[0] * (-rho_res[OPS_ACC6(0)]);
			rhou_old[OPS_ACC4(0)] = rhou_old[OPS_ACC4(0)] + dt * a2[0] * (-rhou_res[OPS_ACC7(0)]);
			rhoE_old[OPS_ACC5(0)] = rhoE_old[OPS_ACC5(0)] + dt * a2[0] * (-rhoE_res[OPS_ACC8(0)]);
}



__kernel void ops_updateRK3_kernel(
__global double* restrict arg0,
__global double* restrict arg1,
__global double* restrict arg2,
__global double* restrict arg3,
__global double* restrict arg4,
__global double* restrict arg5,
__global const double* restrict arg6,
__global const double* restrict arg7,
__global const double* restrict arg8,
const double arg9,
const double arg10,
const double dt,
const int base0,
const int base1,
const int base2,
const int base3,
const int base4,
const int base5,
const int base6,
const int base7,
const int base8,
const int size0 ){


  int idx_x = get_global_id(0);

  if (idx_x < size0) {
    updateRK3_kernel(&arg0[base0 + idx_x * 1*1],
                     &arg1[base1 + idx_x * 1*1],
                     &arg2[base2 + idx_x * 1*1],
                     &arg3[base3 + idx_x * 1*1],
                     &arg4[base4 + idx_x * 1*1],
                     &arg5[base5 + idx_x * 1*1],
                     &arg6[base6 + idx_x * 1*1],
                     &arg7[base7 + idx_x * 1*1],
                     &arg8[base8 + idx_x * 1*1],
                     &arg9,
                     &arg10,
                     dt);
  }

}
