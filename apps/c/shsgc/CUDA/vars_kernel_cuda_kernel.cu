//
// auto-generated by ops.py
//
__constant__ int xdim0_vars_kernel;
int xdim0_vars_kernel_h = -1;
int ydim0_vars_kernel_h = -1;
__constant__ int xdim1_vars_kernel;
int xdim1_vars_kernel_h = -1;
int ydim1_vars_kernel_h = -1;
__constant__ int xdim2_vars_kernel;
int xdim2_vars_kernel_h = -1;
int ydim2_vars_kernel_h = -1;
__constant__ int xdim3_vars_kernel;
int xdim3_vars_kernel_h = -1;
int ydim3_vars_kernel_h = -1;
__constant__ int xdim4_vars_kernel;
int xdim4_vars_kernel_h = -1;
int ydim4_vars_kernel_h = -1;


#undef OPS_ACC_MD0
#undef OPS_ACC_MD1
#undef OPS_ACC_MD2
#undef OPS_ACC_MD3
#undef OPS_ACC_MD4


#define OPS_ACC_MD0(d,x) ((x)*3+(d))
#define OPS_ACC_MD1(d,x) ((x)*3+(d))
#define OPS_ACC_MD2(d,x) ((x)*3+(d))
#define OPS_ACC_MD3(d,x) ((x)*3+(d))
#define OPS_ACC_MD4(d,x) ((x)*3+(d))
//user function
__device__

void vars_kernel(const double* alam, const double* al, const double *gt, double* cmp,  double* cf) {

  double  anu, aaa, ga, qf, ww;
  for (int m=0; m < 3 ;m++) {
			anu = alam[OPS_ACC_MD0(m,0)];
			aaa = al[OPS_ACC_MD1(m,0)];
			ga = aaa * ( gt[OPS_ACC_MD2(m,1)] - gt[OPS_ACC_MD2(m,0)]) / (pow(aaa,2.0) + del2);
			qf = sqrt ( con + pow(anu,2.0));
			cmp[OPS_ACC_MD3(m,0)] = 0.50 * qf;
			ww = anu + cmp[OPS_ACC_MD3(m,0)] * ga;
			qf = sqrt(con + pow(ww,2.0));
			cf[OPS_ACC_MD4(m,0)] = qf;
		}
}




#undef OPS_ACC_MD0
#undef OPS_ACC_MD1
#undef OPS_ACC_MD2
#undef OPS_ACC_MD3
#undef OPS_ACC_MD4

__global__ void ops_vars_kernel(
const double* __restrict arg0,
const double* __restrict arg1,
const double* __restrict arg2,
double* __restrict arg3,
double* __restrict arg4,
int size0 ){


  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*3;
  arg1 += idx_x * 1*3;
  arg2 += idx_x * 1*3;
  arg3 += idx_x * 1*3;
  arg4 += idx_x * 1*3;

  if (idx_x < size0) {
    vars_kernel(arg0, arg1, arg2, arg3,
                   arg4);
  }

}

// host stub function
void ops_par_loop_vars_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4) {

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[5] = { arg0, arg1, arg2, arg3, arg4};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,5,range,10)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(10,"vars_kernel");
    OPS_kernels[10].count++;
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

  if (xdim0 != xdim0_vars_kernel_h || xdim1 != xdim1_vars_kernel_h || xdim2 != xdim2_vars_kernel_h || xdim3 != xdim3_vars_kernel_h || xdim4 != xdim4_vars_kernel_h) {
    cudaMemcpyToSymbol( xdim0_vars_kernel, &xdim0, sizeof(int) );
    xdim0_vars_kernel_h = xdim0;
    cudaMemcpyToSymbol( xdim1_vars_kernel, &xdim1, sizeof(int) );
    xdim1_vars_kernel_h = xdim1;
    cudaMemcpyToSymbol( xdim2_vars_kernel, &xdim2, sizeof(int) );
    xdim2_vars_kernel_h = xdim2;
    cudaMemcpyToSymbol( xdim3_vars_kernel, &xdim3, sizeof(int) );
    xdim3_vars_kernel_h = xdim3;
    cudaMemcpyToSymbol( xdim4_vars_kernel, &xdim4, sizeof(int) );
    xdim4_vars_kernel_h = xdim4;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, 1, 1);
  dim3 tblock(OPS_block_size_x,1,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat2 = args[2].dat->elem_size;
  int dat3 = args[3].dat->elem_size;
  int dat4 = args[4].dat->elem_size;

  char *p_a[5];

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


  ops_H_D_exchanges_device(args, 5);
  ops_halo_exchanges(args,5,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[10].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_vars_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4],x_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[10].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 5);
  ops_set_halo_dirtybit3(&args[3],range);
  ops_set_halo_dirtybit3(&args[4],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[10].mpi_time += t2-t1;
    OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg0);
    OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg1);
    OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg2);
    OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg3);
    OPS_kernels[10].transfer += ops_compute_transfer(dim, range, &arg4);
  }
}
