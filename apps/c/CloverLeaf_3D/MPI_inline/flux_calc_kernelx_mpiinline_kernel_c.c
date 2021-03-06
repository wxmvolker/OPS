//
// auto-generated by ops.py
//

int xdim0_flux_calc_kernelx;
int ydim0_flux_calc_kernelx;
int xdim1_flux_calc_kernelx;
int ydim1_flux_calc_kernelx;
int xdim2_flux_calc_kernelx;
int ydim2_flux_calc_kernelx;
int xdim3_flux_calc_kernelx;
int ydim3_flux_calc_kernelx;


#define OPS_ACC0(x,y,z) (n_x*1+n_y*xdim0_flux_calc_kernelx*1+n_z*xdim0_flux_calc_kernelx*ydim0_flux_calc_kernelx*1+x+xdim0_flux_calc_kernelx*(y)+xdim0_flux_calc_kernelx*ydim0_flux_calc_kernelx*(z))
#define OPS_ACC1(x,y,z) (n_x*1+n_y*xdim1_flux_calc_kernelx*1+n_z*xdim1_flux_calc_kernelx*ydim1_flux_calc_kernelx*1+x+xdim1_flux_calc_kernelx*(y)+xdim1_flux_calc_kernelx*ydim1_flux_calc_kernelx*(z))
#define OPS_ACC2(x,y,z) (n_x*1+n_y*xdim2_flux_calc_kernelx*1+n_z*xdim2_flux_calc_kernelx*ydim2_flux_calc_kernelx*1+x+xdim2_flux_calc_kernelx*(y)+xdim2_flux_calc_kernelx*ydim2_flux_calc_kernelx*(z))
#define OPS_ACC3(x,y,z) (n_x*1+n_y*xdim3_flux_calc_kernelx*1+n_z*xdim3_flux_calc_kernelx*ydim3_flux_calc_kernelx*1+x+xdim3_flux_calc_kernelx*(y)+xdim3_flux_calc_kernelx*ydim3_flux_calc_kernelx*(z))

//user function



void flux_calc_kernelx_c_wrapper(
  double * restrict vol_flux_x,
  const double * restrict xarea,
  const double * restrict xvel0,
  const double * restrict xvel1,
  int x_size, int y_size, int z_size) {
  #pragma omp parallel for
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        

  vol_flux_x[OPS_ACC0(0,0,0)] = 0.125 * dt * (xarea[OPS_ACC1(0,0,0)]) *
  ( xvel0[OPS_ACC2(0,0,0)] + xvel0[OPS_ACC2(0,1,0)] + xvel0[OPS_ACC2(0,0,1)] + xvel0[OPS_ACC2(0,1,1)] +
    xvel1[OPS_ACC3(0,0,0)] + xvel1[OPS_ACC3(0,1,0)] + xvel1[OPS_ACC3(0,0,1)] + xvel1[OPS_ACC3(0,1,1)]);

      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

