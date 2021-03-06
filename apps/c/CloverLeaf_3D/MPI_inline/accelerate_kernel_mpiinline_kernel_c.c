//
// auto-generated by ops.py
//

int xdim0_accelerate_kernel;
int ydim0_accelerate_kernel;
int xdim1_accelerate_kernel;
int ydim1_accelerate_kernel;
int xdim2_accelerate_kernel;
int ydim2_accelerate_kernel;
int xdim3_accelerate_kernel;
int ydim3_accelerate_kernel;
int xdim4_accelerate_kernel;
int ydim4_accelerate_kernel;
int xdim5_accelerate_kernel;
int ydim5_accelerate_kernel;
int xdim6_accelerate_kernel;
int ydim6_accelerate_kernel;
int xdim7_accelerate_kernel;
int ydim7_accelerate_kernel;
int xdim8_accelerate_kernel;
int ydim8_accelerate_kernel;
int xdim9_accelerate_kernel;
int ydim9_accelerate_kernel;
int xdim10_accelerate_kernel;
int ydim10_accelerate_kernel;
int xdim11_accelerate_kernel;
int ydim11_accelerate_kernel;
int xdim12_accelerate_kernel;
int ydim12_accelerate_kernel;
int xdim13_accelerate_kernel;
int ydim13_accelerate_kernel;


#define OPS_ACC0(x,y,z) (n_x*1+n_y*xdim0_accelerate_kernel*1+n_z*xdim0_accelerate_kernel*ydim0_accelerate_kernel*1+x+xdim0_accelerate_kernel*(y)+xdim0_accelerate_kernel*ydim0_accelerate_kernel*(z))
#define OPS_ACC1(x,y,z) (n_x*1+n_y*xdim1_accelerate_kernel*1+n_z*xdim1_accelerate_kernel*ydim1_accelerate_kernel*1+x+xdim1_accelerate_kernel*(y)+xdim1_accelerate_kernel*ydim1_accelerate_kernel*(z))
#define OPS_ACC2(x,y,z) (n_x*1+n_y*xdim2_accelerate_kernel*1+n_z*xdim2_accelerate_kernel*ydim2_accelerate_kernel*1+x+xdim2_accelerate_kernel*(y)+xdim2_accelerate_kernel*ydim2_accelerate_kernel*(z))
#define OPS_ACC3(x,y,z) (n_x*1+n_y*xdim3_accelerate_kernel*1+n_z*xdim3_accelerate_kernel*ydim3_accelerate_kernel*1+x+xdim3_accelerate_kernel*(y)+xdim3_accelerate_kernel*ydim3_accelerate_kernel*(z))
#define OPS_ACC4(x,y,z) (n_x*1+n_y*xdim4_accelerate_kernel*1+n_z*xdim4_accelerate_kernel*ydim4_accelerate_kernel*1+x+xdim4_accelerate_kernel*(y)+xdim4_accelerate_kernel*ydim4_accelerate_kernel*(z))
#define OPS_ACC5(x,y,z) (n_x*1+n_y*xdim5_accelerate_kernel*1+n_z*xdim5_accelerate_kernel*ydim5_accelerate_kernel*1+x+xdim5_accelerate_kernel*(y)+xdim5_accelerate_kernel*ydim5_accelerate_kernel*(z))
#define OPS_ACC6(x,y,z) (n_x*1+n_y*xdim6_accelerate_kernel*1+n_z*xdim6_accelerate_kernel*ydim6_accelerate_kernel*1+x+xdim6_accelerate_kernel*(y)+xdim6_accelerate_kernel*ydim6_accelerate_kernel*(z))
#define OPS_ACC7(x,y,z) (n_x*1+n_y*xdim7_accelerate_kernel*1+n_z*xdim7_accelerate_kernel*ydim7_accelerate_kernel*1+x+xdim7_accelerate_kernel*(y)+xdim7_accelerate_kernel*ydim7_accelerate_kernel*(z))
#define OPS_ACC8(x,y,z) (n_x*1+n_y*xdim8_accelerate_kernel*1+n_z*xdim8_accelerate_kernel*ydim8_accelerate_kernel*1+x+xdim8_accelerate_kernel*(y)+xdim8_accelerate_kernel*ydim8_accelerate_kernel*(z))
#define OPS_ACC9(x,y,z) (n_x*1+n_y*xdim9_accelerate_kernel*1+n_z*xdim9_accelerate_kernel*ydim9_accelerate_kernel*1+x+xdim9_accelerate_kernel*(y)+xdim9_accelerate_kernel*ydim9_accelerate_kernel*(z))
#define OPS_ACC10(x,y,z) (n_x*1+n_y*xdim10_accelerate_kernel*1+n_z*xdim10_accelerate_kernel*ydim10_accelerate_kernel*1+x+xdim10_accelerate_kernel*(y)+xdim10_accelerate_kernel*ydim10_accelerate_kernel*(z))
#define OPS_ACC11(x,y,z) (n_x*1+n_y*xdim11_accelerate_kernel*1+n_z*xdim11_accelerate_kernel*ydim11_accelerate_kernel*1+x+xdim11_accelerate_kernel*(y)+xdim11_accelerate_kernel*ydim11_accelerate_kernel*(z))
#define OPS_ACC12(x,y,z) (n_x*1+n_y*xdim12_accelerate_kernel*1+n_z*xdim12_accelerate_kernel*ydim12_accelerate_kernel*1+x+xdim12_accelerate_kernel*(y)+xdim12_accelerate_kernel*ydim12_accelerate_kernel*(z))
#define OPS_ACC13(x,y,z) (n_x*1+n_y*xdim13_accelerate_kernel*1+n_z*xdim13_accelerate_kernel*ydim13_accelerate_kernel*1+x+xdim13_accelerate_kernel*(y)+xdim13_accelerate_kernel*ydim13_accelerate_kernel*(z))

//user function



void accelerate_kernel_c_wrapper(
  const double * restrict density0,
  const double * restrict volume,
  double * restrict stepbymass,
  const double * restrict xvel0,
  double * restrict xvel1,
  const double * restrict xarea,
  const double * restrict pressure,
  const double * restrict yvel0,
  double * restrict yvel1,
  const double * restrict yarea,
  const double * restrict viscosity,
  const double * restrict zvel0,
  double * restrict zvel1,
  const double * restrict zarea,
  int x_size, int y_size, int z_size) {
  #pragma omp parallel for
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        

  double nodal_mass = 0.0;
  nodal_mass =(density0[OPS_ACC0(-1,-1, 0)] * volume[OPS_ACC1(-1,-1, 0)] +
               density0[OPS_ACC0( 0,-1, 0)] * volume[OPS_ACC1( 0,-1, 0)] +
               density0[OPS_ACC0( 0, 0, 0)] * volume[OPS_ACC1( 0, 0, 0)] +
               density0[OPS_ACC0(-1, 0, 0)] * volume[OPS_ACC1(-1, 0, 0)] +
               density0[OPS_ACC0(-1,-1,-1)] * volume[OPS_ACC1(-1,-1,-1)] +
               density0[OPS_ACC0( 0,-1,-1)] * volume[OPS_ACC1( 0,-1,-1)] +
               density0[OPS_ACC0( 0, 0,-1)] * volume[OPS_ACC1( 0, 0,-1)] +
               density0[OPS_ACC0(-1, 0,-1)] * volume[OPS_ACC1(-1, 0,-1)]) * 0.125;

  stepbymass[OPS_ACC2(0,0,0)] = 0.25*dt / nodal_mass;

  xvel1[OPS_ACC4(0,0,0)] = xvel0[OPS_ACC3(0,0,0)] - stepbymass[OPS_ACC2(0,0,0)] *
            ( xarea[OPS_ACC5(0,0,0)]  * ( pressure[OPS_ACC6(0,0,0)] - pressure[OPS_ACC6(-1,0,0)] ) +
              xarea[OPS_ACC5(0,-1,0)] * ( pressure[OPS_ACC6(0,-1,0)] - pressure[OPS_ACC6(-1,-1,0)] ) +
              xarea[OPS_ACC5(0,0,-1)] * ( pressure[OPS_ACC6(0,0,-1)] - pressure[OPS_ACC6(-1,0,-1)] ) +
              xarea[OPS_ACC5(0,-1,-1)] * ( pressure[OPS_ACC6(0,-1,-1)] - pressure[OPS_ACC6(-1,-1,-1)] ) );

  yvel1[OPS_ACC8(0,0,0)] = yvel0[OPS_ACC7(0,0,0)] - stepbymass[OPS_ACC2(0,0,0)] *
            ( yarea[OPS_ACC9(0,0,0)]  * ( pressure[OPS_ACC6(0,0,0)] - pressure[OPS_ACC6(0,-1,0)] ) +
              yarea[OPS_ACC9(-1,0,0)] * ( pressure[OPS_ACC6(-1,0,0)] - pressure[OPS_ACC6(-1,-1,0)] ) +
              yarea[OPS_ACC9(0,0,-1)] * ( pressure[OPS_ACC6(0,0,-1)] - pressure[OPS_ACC6(0,-1,-1)] ) +
              yarea[OPS_ACC9(-1,0,-1)]* ( pressure[OPS_ACC6(-1,0,-1)] - pressure[OPS_ACC6(-1,-1,-1)] ) );

  zvel1[OPS_ACC12(0,0,0)] = zvel0[OPS_ACC11(0,0,0)] - stepbymass[OPS_ACC2(0,0,0)] *
            ( zarea[OPS_ACC13(0,0,0)]  * ( pressure[OPS_ACC6(0,0,0)] - pressure[OPS_ACC6(0,0,-1)] ) +
              zarea[OPS_ACC13(0,-1,0)] * ( pressure[OPS_ACC6(0,-1,0)] - pressure[OPS_ACC6(0,-1,-1)] ) +
              zarea[OPS_ACC13(-1,0,0)] * ( pressure[OPS_ACC6(-1,0,0)] - pressure[OPS_ACC6(-1,0,-1)] ) +
              zarea[OPS_ACC13(-1,-1,0)]* ( pressure[OPS_ACC6(-1,-1,0)] - pressure[OPS_ACC6(-1,-1,-1)] ) );

  xvel1[OPS_ACC4(0,0,0)] = xvel1[OPS_ACC4(0,0,0)] - stepbymass[OPS_ACC2(0,0,0)] *
            ( xarea[OPS_ACC5(0,0,0)]  * ( viscosity[OPS_ACC10(0,0,0)] - viscosity[OPS_ACC10(-1,0,0)] ) +
              xarea[OPS_ACC5(0,-1,0)] * ( viscosity[OPS_ACC10(0,-1,0)] - viscosity[OPS_ACC10(-1,-1,0)] ) +
              xarea[OPS_ACC5(0,0,-1)] * ( viscosity[OPS_ACC10(0,0,-1)] - viscosity[OPS_ACC10(-1,0,-1)] ) +
              xarea[OPS_ACC5(0,-1,-1)]* ( viscosity[OPS_ACC10(0,-1,-1)] - viscosity[OPS_ACC10(-1,-1,-1)] ) );

  yvel1[OPS_ACC8(0,0,0)] = yvel1[OPS_ACC8(0,0,0)] - stepbymass[OPS_ACC2(0,0,0)] *
            ( yarea[OPS_ACC9(0,0,0)]  * ( viscosity[OPS_ACC10(0,0,0)]  - viscosity[OPS_ACC10(0,-1,0)] ) +
              yarea[OPS_ACC9(-1,0,0)] * ( viscosity[OPS_ACC10(-1,0,0)] - viscosity[OPS_ACC10(-1,-1,0)] ) +
              yarea[OPS_ACC9(0,0,-1)] * ( viscosity[OPS_ACC10(0,0,-1)] - viscosity[OPS_ACC10(0,-1,-1)] ) +
              yarea[OPS_ACC9(-1,0,-1)]* ( viscosity[OPS_ACC10(-1,0,-1)]- viscosity[OPS_ACC10(-1,-1,-1)] ) );

  zvel1[OPS_ACC12(0,0,0)] = zvel1[OPS_ACC12(0,0,0)] - stepbymass[OPS_ACC2(0,0,0)] *
            ( zarea[OPS_ACC13(0,0,0)]  * ( viscosity[OPS_ACC10(0,0,0)]  - viscosity[OPS_ACC10(0,0,-1)] ) +
              zarea[OPS_ACC13(0,-1,0)] * ( viscosity[OPS_ACC10(0,-1,0)] - viscosity[OPS_ACC10(0,-1,-1)] ) +
              zarea[OPS_ACC13(-1,0,0)] * ( viscosity[OPS_ACC10(-1,0,0)] - viscosity[OPS_ACC10(-1,0,-1)] ) +
              zarea[OPS_ACC13(-1,-1,0)]* ( viscosity[OPS_ACC10(-1,-1,0)]- viscosity[OPS_ACC10(-1,-1,-1)] ) );


      }
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
#undef OPS_ACC11
#undef OPS_ACC12
#undef OPS_ACC13

