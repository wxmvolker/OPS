//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_fact_kernel;
int xdim1_fact_kernel;



#undef OPS_ACC_MD0
#undef OPS_ACC_MD1


#define OPS_ACC_MD0(d,x) ((x)*3+(d))
#define OPS_ACC_MD1(d,x) ((x)*3+(d))
//user function
inline 
void fact_kernel(const double* eff, double *s) {
  double fact;
  for (int m=0; m < 3 ;m++) {
    fact  = 0.50 * dt / dx ;
    s[OPS_ACC_MD1(m,0)] = -fact * (eff[OPS_ACC_MD0(m,0)] - eff[OPS_ACC_MD0(m,-1)]);
  }
}



#undef OPS_ACC_MD0
#undef OPS_ACC_MD1


void fact_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  int x_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1)
  #pragma acc loop
  #endif
  for ( int n_x=0; n_x<x_size; n_x++ ){
    fact_kernel(  p_a0 + n_x*1*3,
           p_a1 + n_x*1*3 );

  }
}
