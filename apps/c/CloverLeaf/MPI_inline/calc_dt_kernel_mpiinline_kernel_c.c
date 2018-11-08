//
// auto-generated by ops.py
//

int xdim0_calc_dt_kernel;
int xdim1_calc_dt_kernel;
int xdim2_calc_dt_kernel;
int xdim3_calc_dt_kernel;
int xdim4_calc_dt_kernel;
int xdim5_calc_dt_kernel;
int xdim6_calc_dt_kernel;
int xdim7_calc_dt_kernel;
int xdim8_calc_dt_kernel;
int xdim9_calc_dt_kernel;
int xdim10_calc_dt_kernel;


#define OPS_ACC0(x,y) (n_x*1 + x + (n_y*0+(y))*xdim0_calc_dt_kernel)
#define OPS_ACC1(x,y) (n_x*0 + x + (n_y*1+(y))*xdim1_calc_dt_kernel)
#define OPS_ACC2(x,y) (n_x*1 + x + (n_y*1+(y))*xdim2_calc_dt_kernel)
#define OPS_ACC3(x,y) (n_x*1 + x + (n_y*1+(y))*xdim3_calc_dt_kernel)
#define OPS_ACC4(x,y) (n_x*1 + x + (n_y*1+(y))*xdim4_calc_dt_kernel)
#define OPS_ACC5(x,y) (n_x*1 + x + (n_y*1+(y))*xdim5_calc_dt_kernel)
#define OPS_ACC6(x,y) (n_x*1 + x + (n_y*1+(y))*xdim6_calc_dt_kernel)
#define OPS_ACC7(x,y) (n_x*1 + x + (n_y*1+(y))*xdim7_calc_dt_kernel)
#define OPS_ACC8(x,y) (n_x*1 + x + (n_y*1+(y))*xdim8_calc_dt_kernel)
#define OPS_ACC9(x,y) (n_x*1 + x + (n_y*1+(y))*xdim9_calc_dt_kernel)
#define OPS_ACC10(x,y) (n_x*1 + x + (n_y*1+(y))*xdim10_calc_dt_kernel)
//user function



void calc_dt_kernel_c_wrapper(
  const double * restrict celldx,
  const double * restrict celldy,
  const double * restrict soundspeed,
  const double * restrict viscosity,
  const double * restrict density0,
  const double * restrict xvel0,
  const double * restrict xarea,
  const double * restrict volume,
  const double * restrict yvel0,
  const double * restrict yarea,
  double * restrict dt_min,
  int x_size, int y_size) {
  #pragma omp parallel for
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      

  double div, dsx, dsy, dtut, dtvt, dtct, dtdivt, cc, dv1, dv2;

  dsx = celldx(0,0);
  dsy = celldy(0,0);

  cc = soundspeed(0,0) * soundspeed(0,0);
  cc = cc + 2.0 * viscosity(0,0)/density0(0,0);
  cc = MAX(sqrt(cc),g_small);

  dtct = dtc_safe * MIN(dsx,dsy)/cc;

  div=0.0;


  dv1 = (xvel0(0,0) + xvel0(0,1)) * xarea(0,0);
  dv2 = (xvel0(1,0) + xvel0(1,1)) * xarea(1,0);

  div = div + dv2 - dv1;

  dtut = dtu_safe * 2.0 * volume(0,0)/MAX(MAX(fabs(dv1), fabs(dv2)), g_small * volume(0,0));

  dv1 = (yvel0(0,0) + yvel0(1,0)) * yarea(0,0);
  dv2 = (yvel0(0,1) + yvel0(1,1)) * yarea(0,1);

  div = div + dv2 - dv1;

  dtvt = dtv_safe * 2.0 * volume(0,0)/MAX(MAX(fabs(dv1),fabs(dv2)), g_small * volume(0,0));

  div = div/(2.0 * volume(0,0));

  if(div < -g_small)
    dtdivt = dtdiv_safe * (-1.0/div);
  else
    dtdivt = g_big;

  dt_min(0,0) = MIN(MIN(dtct, dtut), MIN(dtvt, dtdivt));



    }
  }
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

