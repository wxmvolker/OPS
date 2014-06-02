//
// auto-generated by ops.py on 2014-06-02 14:07
//

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

#pragma OPENCL EXTENSION cl_khr_fp64:enable

#define OPS_ACC0(x,y) (x+xdim0_PdV_kernel_nopredict*(y))
#define OPS_ACC1(x,y) (x+xdim1_PdV_kernel_nopredict*(y))
#define OPS_ACC2(x,y) (x+xdim2_PdV_kernel_nopredict*(y))
#define OPS_ACC3(x,y) (x+xdim3_PdV_kernel_nopredict*(y))
#define OPS_ACC4(x,y) (x+xdim4_PdV_kernel_nopredict*(y))
#define OPS_ACC5(x,y) (x+xdim5_PdV_kernel_nopredict*(y))
#define OPS_ACC6(x,y) (x+xdim6_PdV_kernel_nopredict*(y))
#define OPS_ACC7(x,y) (x+xdim7_PdV_kernel_nopredict*(y))
#define OPS_ACC8(x,y) (x+xdim8_PdV_kernel_nopredict*(y))
#define OPS_ACC9(x,y) (x+xdim9_PdV_kernel_nopredict*(y))
#define OPS_ACC10(x,y) (x+xdim10_PdV_kernel_nopredict*(y))
#define OPS_ACC11(x,y) (x+xdim11_PdV_kernel_nopredict*(y))
#define OPS_ACC12(x,y) (x+xdim12_PdV_kernel_nopredict*(y))
#define OPS_ACC13(x,y) (x+xdim13_PdV_kernel_nopredict*(y))


//user function
void PdV_kernel_nopredict( __global double *xarea, __global double *xvel0, __global double *xvel1, __global double *yarea, __global double *yvel0, __global double *yvel1, __global double *volume_change, __global double *volume, __global double *pressure, __global double *density0, __global double *density1, __global double *viscosity, __global double *energy0, __global double *energy1, 
  double dt,
  int xdim0_PdV_kernel_nopredict,
int xdim1_PdV_kernel_nopredict,
int xdim2_PdV_kernel_nopredict,
int xdim3_PdV_kernel_nopredict,
int xdim4_PdV_kernel_nopredict,
int xdim5_PdV_kernel_nopredict,
int xdim6_PdV_kernel_nopredict,
int xdim7_PdV_kernel_nopredict,
int xdim8_PdV_kernel_nopredict,
int xdim9_PdV_kernel_nopredict,
int xdim10_PdV_kernel_nopredict,
int xdim11_PdV_kernel_nopredict,
int xdim12_PdV_kernel_nopredict,
int xdim13_PdV_kernel_nopredict)

  {


  double recip_volume, energy_change, min_cell_volume;
  double right_flux, left_flux, top_flux, bottom_flux, total_flux;

  left_flux = ( xarea[OPS_ACC0(0,0)] * ( xvel0[OPS_ACC1(0,0)] + xvel0[OPS_ACC1(0,1)] +
                                xvel1[OPS_ACC2(0,0)] + xvel1[OPS_ACC2(0,1)] ) ) * 0.25 * dt;
  right_flux = ( xarea[OPS_ACC0(1,0)] * ( xvel0[OPS_ACC1(1,0)] + xvel0[OPS_ACC1(1,1)] +
                                 xvel1[OPS_ACC2(1,0)] + xvel1[OPS_ACC2(1,1)] ) ) * 0.25 * dt;

  bottom_flux = ( yarea[OPS_ACC3(0,0)] * ( yvel0[OPS_ACC4(0,0)] + yvel0[OPS_ACC4(1,0)] +
                                  yvel1[OPS_ACC5(0,0)] + yvel1[OPS_ACC5(1,0)] ) ) * 0.25* dt;
  top_flux = ( yarea[OPS_ACC3(0,1)] * ( yvel0[OPS_ACC4(0,1)] + yvel0[OPS_ACC4(1,1)] +
                               yvel1[OPS_ACC5(0,1)] + yvel1[OPS_ACC5(1,1)] ) ) * 0.25 * dt;

  total_flux = right_flux - left_flux + top_flux - bottom_flux;

  volume_change[OPS_ACC6(0,0)] = (volume[OPS_ACC7(0,0)])/(volume[OPS_ACC7(0,0)] + total_flux);

  min_cell_volume = MIN( volume[OPS_ACC7(0,0)] + right_flux - left_flux + top_flux - bottom_flux ,
                           MIN(volume[OPS_ACC7(0,0)] + right_flux - left_flux,
                           volume[OPS_ACC7(0,0)] + top_flux - bottom_flux) );

  recip_volume = 1.0/volume[OPS_ACC7(0,0)];

  energy_change = ( pressure[OPS_ACC8(0,0)]/density0[OPS_ACC9(0,0)] +
                    viscosity[OPS_ACC11(0,0)]/density0[OPS_ACC9(0,0)] ) * total_flux * recip_volume;
  energy1[OPS_ACC13(0,0)] = energy0[OPS_ACC12(0,0)] - energy_change;
  density1[OPS_ACC10(0,0)] = density0[OPS_ACC9(0,0)] * volume_change[OPS_ACC6(0,0)];

}



 #undef OPS_ACC0
 #undef OPS_ACC1
 #undef OPS_ACC2
 #undef OPS_ACC3
 #undef OPS_ACC4
 #undef OPS_ACC5
 #undef OPS_ACC6
 #undef OPS_ACC7
 #undef OPS_ACC8
 #undef OPS_ACC9
 #undef OPS_ACC10
 #undef OPS_ACC11
 #undef OPS_ACC12
 #undef OPS_ACC13


 __kernel void ops_PdV_kernel_nopredict(
 __global double* arg0,
 __global double* arg1,
 __global double* arg2,
 __global double* arg3,
 __global double* arg4,
 __global double* arg5,
 __global double* arg6,
 __global double* arg7,
 __global double* arg8,
 __global double* arg9,
 __global double* arg10,
 __global double* arg11,
 __global double* arg12,
 __global double* arg13,
 double *dt,
 int xdim0_PdV_kernel_nopredict,
 int xdim1_PdV_kernel_nopredict,
 int xdim2_PdV_kernel_nopredict,
 int xdim3_PdV_kernel_nopredict,
 int xdim4_PdV_kernel_nopredict,
 int xdim5_PdV_kernel_nopredict,
 int xdim6_PdV_kernel_nopredict,
 int xdim7_PdV_kernel_nopredict,
 int xdim8_PdV_kernel_nopredict,
 int xdim9_PdV_kernel_nopredict,
 int xdim10_PdV_kernel_nopredict,
 int xdim11_PdV_kernel_nopredict,
 int xdim12_PdV_kernel_nopredict,
 int xdim13_PdV_kernel_nopredict,
 const int base0,
 const int base1,
 const int base2,
 const int base3,
 const int base4,
 const int base5,
 const int base6,
 const int base7,
 const int base8,
 const int base9,
 const int base10,
 const int base11,
 const int base12,
 const int base13,
 int size0,
 int size1 ){


   int idx_y = get_global_id(1);
   int idx_x = get_global_id(0);

   if (idx_x < size0 && idx_y < size1) {
     PdV_kernel_nopredict(&arg0[base0 + idx_x * 1 + idx_y * 1 * xdim0_PdV_kernel_nopredict],
                &arg1[base1 + idx_x * 1 + idx_y * 1 * xdim1_PdV_kernel_nopredict],
                &arg2[base2 + idx_x * 1 + idx_y * 1 * xdim2_PdV_kernel_nopredict],
                &arg3[base3 + idx_x * 1 + idx_y * 1 * xdim3_PdV_kernel_nopredict],
                &arg4[base4 + idx_x * 1 + idx_y * 1 * xdim4_PdV_kernel_nopredict],
                &arg5[base5 + idx_x * 1 + idx_y * 1 * xdim5_PdV_kernel_nopredict],
                &arg6[base6 + idx_x * 1 + idx_y * 1 * xdim6_PdV_kernel_nopredict],
                &arg7[base7 + idx_x * 1 + idx_y * 1 * xdim7_PdV_kernel_nopredict],
                &arg8[base8 + idx_x * 1 + idx_y * 1 * xdim8_PdV_kernel_nopredict],
                &arg9[base9 + idx_x * 1 + idx_y * 1 * xdim9_PdV_kernel_nopredict],
                &arg10[base10 + idx_x * 1 + idx_y * 1 * xdim10_PdV_kernel_nopredict],
                &arg11[base11 + idx_x * 1 + idx_y * 1 * xdim11_PdV_kernel_nopredict],
                &arg12[base12 + idx_x * 1 + idx_y * 1 * xdim12_PdV_kernel_nopredict],
                &arg13[base13 + idx_x * 1 + idx_y * 1 * xdim13_PdV_kernel_nopredict],
                *dt,
                xdim0_PdV_kernel_nopredict,
                xdim1_PdV_kernel_nopredict,
                xdim2_PdV_kernel_nopredict,
                xdim3_PdV_kernel_nopredict,
                xdim4_PdV_kernel_nopredict,
                xdim5_PdV_kernel_nopredict,
                xdim6_PdV_kernel_nopredict,
                xdim7_PdV_kernel_nopredict,
                xdim8_PdV_kernel_nopredict,
                xdim9_PdV_kernel_nopredict,
                xdim10_PdV_kernel_nopredict,
                xdim11_PdV_kernel_nopredict,
                xdim12_PdV_kernel_nopredict,
                xdim13_PdV_kernel_nopredict);
   }

 }
