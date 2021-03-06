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


#undef OPS_ACC_MD0
#undef OPS_ACC_MD1


#define OPS_ACC_MD0(d,x) ((x)*3+(d))
#define OPS_ACC_MD1(d,x) ((x)*3+(d))

//user function
void tvd_kernel(const __global double * restrict tht,__global double* restrict  ep2,
  const double akap2)

 {
  double maxim;
  for (int m=0; m < 3 ;m++) {
    if (tht[OPS_ACC_MD0(m,0)] > tht[OPS_ACC_MD0(m,1)])
      maxim = tht[OPS_ACC_MD0(m,0)];
    else
      maxim = tht[OPS_ACC_MD0(m,1)];
    ep2[OPS_ACC_MD1(m,0)] = akap2 * maxim;
  }
}



__kernel void ops_tvd_kernel(
__global const double* restrict arg0,
__global double* restrict arg1,
const double akap2,
const int base0,
const int base1,
const int size0 ){


  int idx_x = get_global_id(0);

  if (idx_x < size0) {
    tvd_kernel(&arg0[base0 + idx_x * 1*3],
               &arg1[base1 + idx_x * 1*3],
               akap2);
  }

}
