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

#define OPS_ACC_MD0(d,x,y) ((x)*2+(d)+(xdim0_multidim_reduce_kernel*(y)*2))

//user function
void multidim_reduce_kernel(const __global double * restrict val, double * restrict redu_dat1)

 {

  redu_dat1[0] = redu_dat1[0] + val[OPS_ACC_MD0(0,0,0)];
  redu_dat1[1] = redu_dat1[1] + val[OPS_ACC_MD0(1,0,0)];
}




#undef OPS_ACC_MD0


__kernel void ops_multidim_reduce_kernel(
__global const double* restrict arg0,
__global double* restrict arg1,
__local double* scratch1,
int r_bytes1,
const int base0,
const int size0,
const int size1 ){

  arg1 += r_bytes1;
  double arg1_l[2];
  for (int d=0; d<2; d++) arg1_l[d] = ZERO_double;

  int idx_y = get_global_id(1);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1) {
    multidim_reduce_kernel(&arg0[base0 + idx_x * 1*2 + idx_y * 1*2 * xdim0_multidim_reduce_kernel],
                           arg1_l);
  }
  for (int d=0; d<2; d++)
    reduce_double(arg1_l[0], scratch1, &arg1[d], OPS_INC);

}
