//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_advec_mom_kernel_post_pre_advec_x;
int xdim1_advec_mom_kernel_post_pre_advec_x;
int xdim2_advec_mom_kernel_post_pre_advec_x;
int xdim3_advec_mom_kernel_post_pre_advec_x;
int xdim4_advec_mom_kernel_post_pre_advec_x;


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4


#define OPS_ACC0(x,y) (x+xdim0_advec_mom_kernel_post_pre_advec_x*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_mom_kernel_post_pre_advec_x*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_mom_kernel_post_pre_advec_x*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_mom_kernel_post_pre_advec_x*(y))
#define OPS_ACC4(x,y) (x+xdim4_advec_mom_kernel_post_pre_advec_x*(y))

//user function

inline void advec_mom_kernel_post_pre_advec_x( ACC<double> &node_mass_post, const ACC<double> &post_vol,
                                  const ACC<double> &density1, ACC<double> &node_mass_pre, const ACC<double> &node_flux) {



  node_mass_post(0,0) = 0.25 * ( density1(0,-1) * post_vol(0,-1) +
                              density1(0,0)   * post_vol(0,0)   +
                              density1(-1,-1) * post_vol(-1,-1) +
                              density1(-1,0)  * post_vol(-1,0)  );

  node_mass_pre(0,0) = node_mass_post(0,0) - node_flux(-1,0) + node_flux(0,0);

}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4



void advec_mom_kernel_post_pre_advec_x_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      advec_mom_kernel_post_pre_advec_x(  p_a0 + n_x*1*1 + n_y*xdim0_advec_mom_kernel_post_pre_advec_x*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_advec_mom_kernel_post_pre_advec_x*1*1, p_a2 + n_x*1*1 + n_y*xdim2_advec_mom_kernel_post_pre_advec_x*1*1,
           p_a3 + n_x*1*1 + n_y*xdim3_advec_mom_kernel_post_pre_advec_x*1*1, p_a4 + n_x*1*1 + n_y*xdim4_advec_mom_kernel_post_pre_advec_x*1*1 );

    }
  }
}
