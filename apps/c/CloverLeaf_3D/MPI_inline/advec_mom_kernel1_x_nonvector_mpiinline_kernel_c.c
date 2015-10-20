//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_advec_mom_kernel1_x_nonvector;
int ydim0_advec_mom_kernel1_x_nonvector;
int xdim1_advec_mom_kernel1_x_nonvector;
int ydim1_advec_mom_kernel1_x_nonvector;
int xdim2_advec_mom_kernel1_x_nonvector;
int ydim2_advec_mom_kernel1_x_nonvector;
int xdim3_advec_mom_kernel1_x_nonvector;
int ydim3_advec_mom_kernel1_x_nonvector;
int xdim4_advec_mom_kernel1_x_nonvector;
int ydim4_advec_mom_kernel1_x_nonvector;

#define OPS_ACC0(x,y,z) (n_x*1+n_y*xdim0_advec_mom_kernel1_x_nonvector*1+n_z*xdim0_advec_mom_kernel1_x_nonvector*ydim0_advec_mom_kernel1_x_nonvector*1+x+xdim0_advec_mom_kernel1_x_nonvector*(y)+xdim0_advec_mom_kernel1_x_nonvector*ydim0_advec_mom_kernel1_x_nonvector*(z))
#define OPS_ACC1(x,y,z) (n_x*1+n_y*xdim1_advec_mom_kernel1_x_nonvector*1+n_z*xdim1_advec_mom_kernel1_x_nonvector*ydim1_advec_mom_kernel1_x_nonvector*1+x+xdim1_advec_mom_kernel1_x_nonvector*(y)+xdim1_advec_mom_kernel1_x_nonvector*ydim1_advec_mom_kernel1_x_nonvector*(z))
#define OPS_ACC2(x,y,z) (n_x*1+n_y*xdim2_advec_mom_kernel1_x_nonvector*1+n_z*xdim2_advec_mom_kernel1_x_nonvector*ydim2_advec_mom_kernel1_x_nonvector*1+x+xdim2_advec_mom_kernel1_x_nonvector*(y)+xdim2_advec_mom_kernel1_x_nonvector*ydim2_advec_mom_kernel1_x_nonvector*(z))
#define OPS_ACC3(x,y,z) (n_x*1+n_y*xdim3_advec_mom_kernel1_x_nonvector*0+n_z*xdim3_advec_mom_kernel1_x_nonvector*ydim3_advec_mom_kernel1_x_nonvector*0+x+xdim3_advec_mom_kernel1_x_nonvector*(y)+xdim3_advec_mom_kernel1_x_nonvector*ydim3_advec_mom_kernel1_x_nonvector*(z))
#define OPS_ACC4(x,y,z) (n_x*1+n_y*xdim4_advec_mom_kernel1_x_nonvector*1+n_z*xdim4_advec_mom_kernel1_x_nonvector*ydim4_advec_mom_kernel1_x_nonvector*1+x+xdim4_advec_mom_kernel1_x_nonvector*(y)+xdim4_advec_mom_kernel1_x_nonvector*ydim4_advec_mom_kernel1_x_nonvector*(z))

//user function



void advec_mom_kernel1_x_nonvector_c_wrapper(
  const double * restrict node_flux,
  const double * restrict node_mass_pre,
  double * restrict mom_flux,
  const double * restrict celldx,
  const double * restrict vel1,
  int x_size, int y_size, int z_size) {
  #pragma omp parallel for
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        

  double sigma, wind, width;
  double vdiffuw, vdiffdw, auw, adw, limiter;
  int upwind, donor, downwind, dif;

  double advec_vel_temp;

  if( (node_flux[OPS_ACC0(0,0,0)]) < 0.0) {
    upwind = 2;
    donor = 1;
    downwind = 0;
    dif = donor;
  }
  else {
    upwind = -1;
    donor = 0;
    downwind = 1;
    dif = upwind;
  }

  sigma = fabs(node_flux[OPS_ACC0(0,0,0)])/node_mass_pre[OPS_ACC1(donor,0,0)];

  width = celldx[OPS_ACC3(0,0,0)];
  vdiffuw = vel1[OPS_ACC4(donor,0,0)] - vel1[OPS_ACC4(upwind,0,0)];
  vdiffdw = vel1[OPS_ACC4(downwind,0,0)] - vel1[OPS_ACC4(donor,0,0)];
  limiter=0.0;

  if(vdiffuw*vdiffdw > 0.0) {
    auw = fabs(vdiffuw);
    adw = fabs(vdiffdw);
    wind = 1.0;
    if(vdiffdw <= 0.0) wind = -1.0;
    limiter=wind*MIN(width*((2.0-sigma)*adw/width+(1.0+sigma)*auw/celldx[OPS_ACC3(dif,0,0)])/6.0, MIN(auw, adw));
  }

  advec_vel_temp = vel1[OPS_ACC4(donor,0,0)] + (1.0 - sigma) * limiter;
  mom_flux[OPS_ACC2(0,0,0)] = advec_vel_temp * node_flux[OPS_ACC0(0,0,0)];


      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4

