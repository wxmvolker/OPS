//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64:enable

#include "user_types.h"
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


#define OPS_ACC0(x,y,z) (x+xdim0_advec_mom_kernel1_y_nonvector*(y)+xdim0_advec_mom_kernel1_y_nonvector*ydim0_advec_mom_kernel1_y_nonvector*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_advec_mom_kernel1_y_nonvector*(y)+xdim1_advec_mom_kernel1_y_nonvector*ydim1_advec_mom_kernel1_y_nonvector*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_advec_mom_kernel1_y_nonvector*(y)+xdim2_advec_mom_kernel1_y_nonvector*ydim2_advec_mom_kernel1_y_nonvector*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_advec_mom_kernel1_y_nonvector*(y)+xdim3_advec_mom_kernel1_y_nonvector*ydim3_advec_mom_kernel1_y_nonvector*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_advec_mom_kernel1_y_nonvector*(y)+xdim4_advec_mom_kernel1_y_nonvector*ydim4_advec_mom_kernel1_y_nonvector*(z))


//user function
inline void advec_mom_kernel1_y_nonvector( const __global double * restrict node_flux,const __global double * restrict node_mass_pre,__global double * restrict mom_flux,
const __global double * restrict celldy,const __global double * restrict vel1)

 {

  double sigma, wind, width;
  double vdiffuw, vdiffdw, auw, adw, limiter;
  int upwind, donor, downwind, dif;
  double advec_vel_temp;

  if( (node_flux[OPS_ACC0(0,0,0)]) < 0.0) {
    upwind = 2;
    donor = 1;
    downwind = 0;
    dif = donor;
  } else {
    upwind = -1;
    donor = 0;
    downwind = 1;
    dif = upwind;
  }

  sigma = fabs(node_flux[OPS_ACC0(0,0,0)])/node_mass_pre[OPS_ACC1(0,donor,0)];
  width = celldy[OPS_ACC3(0,0,0)];
  vdiffuw = vel1[OPS_ACC4(0,donor,0)] - vel1[OPS_ACC4(0,upwind,0)];
  vdiffdw = vel1[OPS_ACC4(0,downwind,0)] - vel1[OPS_ACC4(0,donor,0)];
  limiter = 0.0;
  if(vdiffuw*vdiffdw > 0.0) {
    auw = fabs(vdiffuw);
    adw = fabs(vdiffdw);
    wind = 1.0;
    if(vdiffdw <= 0.0) wind = -1.0;
    limiter=wind*MIN(width*((2.0-sigma)*adw/width+(1.0+sigma)*auw/celldy[OPS_ACC3(0,dif,0)])/6.0,MIN(auw,adw));
  }
  advec_vel_temp= vel1[OPS_ACC4(0,donor,0)] + (1.0 - sigma) * limiter;
  mom_flux[OPS_ACC2(0,0,0)] = advec_vel_temp * node_flux[OPS_ACC0(0,0,0)];
}



__kernel void ops_advec_mom_kernel1_y_nonvector(
__global const double* restrict arg0,
__global const double* restrict arg1,
__global double* restrict arg2,
__global const double* restrict arg3,
__global const double* restrict arg4,
const int base0,
const int base1,
const int base2,
const int base3,
const int base4,
const int size0,
const int size1,
const int size2 ){


  int idx_y = get_global_id(1);
  int idx_z = get_global_id(2);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    advec_mom_kernel1_y_nonvector(&arg0[base0 + idx_x * 1*1 + idx_y * 1*1 * xdim0_advec_mom_kernel1_y_nonvector + idx_z * 1*1 * xdim0_advec_mom_kernel1_y_nonvector * ydim0_advec_mom_kernel1_y_nonvector],
                     &arg1[base1 + idx_x * 1*1 + idx_y * 1*1 * xdim1_advec_mom_kernel1_y_nonvector + idx_z * 1*1 * xdim1_advec_mom_kernel1_y_nonvector * ydim1_advec_mom_kernel1_y_nonvector],
                     &arg2[base2 + idx_x * 1*1 + idx_y * 1*1 * xdim2_advec_mom_kernel1_y_nonvector + idx_z * 1*1 * xdim2_advec_mom_kernel1_y_nonvector * ydim2_advec_mom_kernel1_y_nonvector],
                     &arg3[base3 + idx_x * 0*1 + idx_y * 1*1 * xdim3_advec_mom_kernel1_y_nonvector + idx_z * 0*1 * xdim3_advec_mom_kernel1_y_nonvector * ydim3_advec_mom_kernel1_y_nonvector],
                     &arg4[base4 + idx_x * 1*1 + idx_y * 1*1 * xdim4_advec_mom_kernel1_y_nonvector + idx_z * 1*1 * xdim4_advec_mom_kernel1_y_nonvector * ydim4_advec_mom_kernel1_y_nonvector]);
  }

}
