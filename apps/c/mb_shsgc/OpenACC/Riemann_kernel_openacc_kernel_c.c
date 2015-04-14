//
// auto-generated by ops.py
//
#include "./OpenACC/shsgc_common.h"

#define OPS_GPU

int xdim0_Riemann_kernel;
int xdim1_Riemann_kernel;
int xdim2_Riemann_kernel;
int xdim3_Riemann_kernel;
int xdim4_Riemann_kernel;
int xdim5_Riemann_kernel;

#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)
#define OPS_ACC2(x) (x)

#define OPS_ACC_MD3(d,x) ((x)*3+(d))
#define OPS_ACC_MD4(d,x) ((x)*9+(d))
#define OPS_ACC_MD5(d,x) ((x)*3+(d))
//user function
inline
void Riemann_kernel(const double* rho_new, const double *rhou_new, const double* rhoE_new,
                    double* alam, double* r, double* al) {
  double rl, rr, rho, leftu, rightu, u, hl, hr, h, Vsq, csq, c, g;
  double dw1, dw2, dw3, delpc2, rdeluc;
  double ri[3][3];

  rl = sqrt(rho_new[OPS_ACC0(0)]);
  rr = sqrt(rho_new[OPS_ACC0(1)]);
  rho = rl + rr;
  u = ((rhou_new[OPS_ACC1(0)] / rl) + (rhou_new[OPS_ACC1(1)] / rr)) / rho ;
  double fni = rhou_new[OPS_ACC1(0)] * rhou_new[OPS_ACC1(0)] / rho_new[OPS_ACC0(0)] ;
  double p = gam1 * (rhoE_new[OPS_ACC2(0)] - 0.5 * fni);
  hl = (rhoE_new[OPS_ACC2(0)] + p)  / rl ;
  fni = rhou_new[OPS_ACC1(1)] * rhou_new[OPS_ACC1(1)] / rho_new[OPS_ACC0(1)] ;
  p = gam1 * (rhoE_new[OPS_ACC2(1)] - 0.5 * fni);
  hr = (rhoE_new[OPS_ACC2(1)] + p)  / rr ;
  h = (hl + hr)/rho;
  Vsq = u*u;
  csq = gam1 * (h - 0.5 * Vsq);
  g = gam1 / csq;
  c = sqrt(csq);

  alam[OPS_ACC_MD3(0,0)] = u - c;
  alam[OPS_ACC_MD3(1,0)] = u;
  alam[OPS_ACC_MD3(2,0)] = u + c;

  r[OPS_ACC_MD4(0,0)] = 1.0;
  r[OPS_ACC_MD4(1,0)] = 1.0;
  r[OPS_ACC_MD4(2,0)] = 1.0;

  r[OPS_ACC_MD4(3,0)] = u - c;
  r[OPS_ACC_MD4(4,0)] = u;
  r[OPS_ACC_MD4(5,0)] = u + c;

  r[OPS_ACC_MD4(6,0)] = h - u * c;
  r[OPS_ACC_MD4(7,0)] = 0.5 * Vsq;
  r[OPS_ACC_MD4(8,0)] = h + u * c;

  for (int m=0; m<9; m++)
    r[OPS_ACC_MD4(m,0)] = r[OPS_ACC_MD4(m,0)] / csq;

  dw1 = rho_new[OPS_ACC0(1)] - rho_new[OPS_ACC0(0)];
  dw2 = rhou_new[OPS_ACC1(1)] - rhou_new[OPS_ACC1(0)];
  dw3 = rhoE_new[OPS_ACC2(1)] - rhoE_new[OPS_ACC2(0)];

  delpc2 = gam1 * ( dw3 + 0.50 * Vsq * dw1  - u * dw2) / csq;
  rdeluc = ( dw2 - u * dw1) / c ;

  al[OPS_ACC_MD5(0,0)] = 0.5 * (delpc2 - rdeluc);
  al[OPS_ACC_MD5(1,0)] = dw1 - delpc2 ;
  al[OPS_ACC_MD5(2,0)] = 0.5 * ( delpc2 + rdeluc );

  for (int m=0; m<3; m++)
    al[OPS_ACC_MD5(m,0)] = al[OPS_ACC_MD5(m,0)] * csq;
}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

#undef OPS_ACC_MD3
#undef OPS_ACC_MD4
#undef OPS_ACC_MD5


void Riemann_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  int x_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5)
  #pragma acc loop
  #endif
  for ( int n_x=0; n_x<x_size; n_x++ ){
    Riemann_kernel(  p_a0 + n_x*1*1,
           p_a1 + n_x*1*1, p_a2 + n_x*1*1,
           p_a3 + n_x*1*3, p_a4 + n_x*1*9,
           p_a5 + n_x*1*3 );

  }
}
