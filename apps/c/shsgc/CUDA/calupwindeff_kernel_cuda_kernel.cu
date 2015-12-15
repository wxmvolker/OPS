//
// auto-generated by ops.py
//
__constant__ int xdim0_calupwindeff_kernel;
int xdim0_calupwindeff_kernel_h = -1;
int ydim0_calupwindeff_kernel_h = -1;
__constant__ int xdim1_calupwindeff_kernel;
int xdim1_calupwindeff_kernel_h = -1;
int ydim1_calupwindeff_kernel_h = -1;
__constant__ int xdim2_calupwindeff_kernel;
int xdim2_calupwindeff_kernel_h = -1;
int ydim2_calupwindeff_kernel_h = -1;
__constant__ int xdim3_calupwindeff_kernel;
int xdim3_calupwindeff_kernel_h = -1;
int ydim3_calupwindeff_kernel_h = -1;
__constant__ int xdim4_calupwindeff_kernel;
int xdim4_calupwindeff_kernel_h = -1;
int ydim4_calupwindeff_kernel_h = -1;
__constant__ int xdim5_calupwindeff_kernel;
int xdim5_calupwindeff_kernel_h = -1;
int ydim5_calupwindeff_kernel_h = -1;
__constant__ int xdim6_calupwindeff_kernel;
int xdim6_calupwindeff_kernel_h = -1;
int ydim6_calupwindeff_kernel_h = -1;


#undef OPS_ACC_MD0
#undef OPS_ACC_MD1
#undef OPS_ACC_MD2
#undef OPS_ACC_MD3
#undef OPS_ACC_MD4
#undef OPS_ACC_MD5
#undef OPS_ACC_MD6


#define OPS_ACC_MD0(d,x) ((x)*3+(d))
#define OPS_ACC_MD1(d,x) ((x)*3+(d))
#define OPS_ACC_MD2(d,x) ((x)*3+(d))
#define OPS_ACC_MD3(d,x) ((x)*3+(d))
#define OPS_ACC_MD4(d,x) ((x)*3+(d))
#define OPS_ACC_MD5(d,x) ((x)*9+(d))
#define OPS_ACC_MD6(d,x) ((x)*3+(d))
//user function
__device__

void calupwindeff_kernel(const double* cmp, const double *gt, const double* cf,
                         const double* al, const double* ep2, const double* r, double* eff) {

		double e1 = (cmp[OPS_ACC_MD0(0,0)] * (gt[OPS_ACC_MD1(0,0)] + gt[OPS_ACC_MD1(0,1)]) - cf[OPS_ACC_MD2(0,0)] * al[OPS_ACC_MD3(0,0)]) * ep2[OPS_ACC_MD4(0,0)];
		double e2 = (cmp[OPS_ACC_MD0(1,0)] * (gt[OPS_ACC_MD1(1,0)] + gt[OPS_ACC_MD1(1,1)]) - cf[OPS_ACC_MD2(1,0)] * al[OPS_ACC_MD3(1,0)]) * ep2[OPS_ACC_MD4(1,0)];
		double e3 = (cmp[OPS_ACC_MD0(2,0)] * (gt[OPS_ACC_MD1(2,0)] + gt[OPS_ACC_MD1(2,1)]) - cf[OPS_ACC_MD2(2,0)] * al[OPS_ACC_MD3(2,0)]) * ep2[OPS_ACC_MD4(2,0)];

		eff[OPS_ACC_MD6(0,0)]=e1 * r[OPS_ACC_MD5(0,0)] + e2 * r[OPS_ACC_MD5(1,0)] + e3 * r[OPS_ACC_MD5(2,0)];
		eff[OPS_ACC_MD6(1,0)]=e1 * r[OPS_ACC_MD5(3,0)] + e2 * r[OPS_ACC_MD5(4,0)] + e3 * r[OPS_ACC_MD5(5,0)];
		eff[OPS_ACC_MD6(2,0)]=e1 * r[OPS_ACC_MD5(6,0)] + e2 * r[OPS_ACC_MD5(7,0)] + e3 * r[OPS_ACC_MD5(8,0)];
}




#undef OPS_ACC_MD0
#undef OPS_ACC_MD1
#undef OPS_ACC_MD2
#undef OPS_ACC_MD3
#undef OPS_ACC_MD4
#undef OPS_ACC_MD5
#undef OPS_ACC_MD6

__global__ void ops_calupwindeff_kernel(
const double* __restrict arg0,
const double* __restrict arg1,
const double* __restrict arg2,
const double* __restrict arg3,
const double* __restrict arg4,
const double* __restrict arg5,
double* __restrict arg6,
int size0 ){


  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*3;
  arg1 += idx_x * 1*3;
  arg2 += idx_x * 1*3;
  arg3 += idx_x * 1*3;
  arg4 += idx_x * 1*3;
  arg5 += idx_x * 1*9;
  arg6 += idx_x * 1*3;

  if (idx_x < size0) {
    calupwindeff_kernel(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6);
  }

}

// host stub function
void ops_par_loop_calupwindeff_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6) {

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[7] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,7,range,11)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(11,"calupwindeff_kernel");
    OPS_kernels[11].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[1];
  int end[1];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<1; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int n=0; n<1; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI

  int x_size = MAX(0,end[0]-start[0]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];
  int xdim6 = args[6].dat->size[0];

  if (xdim0 != xdim0_calupwindeff_kernel_h || xdim1 != xdim1_calupwindeff_kernel_h || xdim2 != xdim2_calupwindeff_kernel_h || xdim3 != xdim3_calupwindeff_kernel_h || xdim4 != xdim4_calupwindeff_kernel_h || xdim5 != xdim5_calupwindeff_kernel_h || xdim6 != xdim6_calupwindeff_kernel_h) {
    cudaMemcpyToSymbol( xdim0_calupwindeff_kernel, &xdim0, sizeof(int) );
    xdim0_calupwindeff_kernel_h = xdim0;
    cudaMemcpyToSymbol( xdim1_calupwindeff_kernel, &xdim1, sizeof(int) );
    xdim1_calupwindeff_kernel_h = xdim1;
    cudaMemcpyToSymbol( xdim2_calupwindeff_kernel, &xdim2, sizeof(int) );
    xdim2_calupwindeff_kernel_h = xdim2;
    cudaMemcpyToSymbol( xdim3_calupwindeff_kernel, &xdim3, sizeof(int) );
    xdim3_calupwindeff_kernel_h = xdim3;
    cudaMemcpyToSymbol( xdim4_calupwindeff_kernel, &xdim4, sizeof(int) );
    xdim4_calupwindeff_kernel_h = xdim4;
    cudaMemcpyToSymbol( xdim5_calupwindeff_kernel, &xdim5, sizeof(int) );
    xdim5_calupwindeff_kernel_h = xdim5;
    cudaMemcpyToSymbol( xdim6_calupwindeff_kernel, &xdim6, sizeof(int) );
    xdim6_calupwindeff_kernel_h = xdim6;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, 1, 1);
  dim3 tblock(OPS_block_size_x,1,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat2 = args[2].dat->elem_size;
  int dat3 = args[3].dat->elem_size;
  int dat4 = args[4].dat->elem_size;
  int dat5 = args[5].dat->elem_size;
  int dat6 = args[6].dat->elem_size;

  char *p_a[7];

  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif //OPS_MPI
  int base0 = dat0 * 1 *
  (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  p_a[0] = (char *)args[0].data_d + base0;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
  #endif //OPS_MPI
  int base1 = dat1 * 1 *
  (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
  p_a[1] = (char *)args[1].data_d + base1;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d];
  #endif //OPS_MPI
  int base2 = dat2 * 1 *
  (start[0] * args[2].stencil->stride[0] - args[2].dat->base[0] - d_m[0]);
  p_a[2] = (char *)args[2].data_d + base2;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d];
  #endif //OPS_MPI
  int base3 = dat3 * 1 *
  (start[0] * args[3].stencil->stride[0] - args[3].dat->base[0] - d_m[0]);
  p_a[3] = (char *)args[3].data_d + base3;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d];
  #endif //OPS_MPI
  int base4 = dat4 * 1 *
  (start[0] * args[4].stencil->stride[0] - args[4].dat->base[0] - d_m[0]);
  p_a[4] = (char *)args[4].data_d + base4;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d] + OPS_sub_dat_list[args[5].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d];
  #endif //OPS_MPI
  int base5 = dat5 * 1 *
  (start[0] * args[5].stencil->stride[0] - args[5].dat->base[0] - d_m[0]);
  p_a[5] = (char *)args[5].data_d + base5;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d] + OPS_sub_dat_list[args[6].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d];
  #endif //OPS_MPI
  int base6 = dat6 * 1 *
  (start[0] * args[6].stencil->stride[0] - args[6].dat->base[0] - d_m[0]);
  p_a[6] = (char *)args[6].data_d + base6;


  ops_H_D_exchanges_device(args, 7);
  ops_halo_exchanges(args,7,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[11].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_calupwindeff_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6],x_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[11].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 7);
  ops_set_halo_dirtybit3(&args[6],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[11].mpi_time += t2-t1;
    OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg0);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg1);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg2);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg3);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg4);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg5);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, range, &arg6);
  }
}
