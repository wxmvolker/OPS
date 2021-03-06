//
// auto-generated by ops.py
//

int xdim0_tea_leaf_dot_kernel;
int xdim1_tea_leaf_dot_kernel;


#define OPS_ACC0(x,y) (n_x*1+n_y*xdim0_tea_leaf_dot_kernel*1+x+xdim0_tea_leaf_dot_kernel*(y))
#define OPS_ACC1(x,y) (n_x*1+n_y*xdim1_tea_leaf_dot_kernel*1+x+xdim1_tea_leaf_dot_kernel*(y))

//user function



void tea_leaf_dot_kernel_c_wrapper(
  const double * restrict r,
  const double * restrict p,
  double * restrict rro_g,
  int x_size, int y_size) {
  double rro_v = *rro_g;
  #pragma omp parallel for reduction(+:rro_v)
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      double * restrict rro = &rro_v;
      
  *rro = *rro + r[OPS_ACC0(0,0)] * p[OPS_ACC1(0,0)];

    }
  }
  *rro_g = rro_v;
}
#undef OPS_ACC0
#undef OPS_ACC1

