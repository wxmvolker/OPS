//
// auto-generated by ops.py
//
__constant__ int xdim0_xder1_kernel;
int xdim0_xder1_kernel_h = -1;
int ydim0_xder1_kernel_h = -1;
__constant__ int xdim1_xder1_kernel;
int xdim1_xder1_kernel_h = -1;
int ydim1_xder1_kernel_h = -1;

#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)

//user function
__device__

void xder1_kernel(const double *inp, double *out) {
  double dlx = 1/(12.00*dx);
  out[OPS_ACC1(0)] = (inp[OPS_ACC0(-2)] - inp[OPS_ACC0(2)]  + 8.0 *(
  inp[OPS_ACC0(1)] - inp[OPS_ACC0(-1)] )) * dlx;
}



#undef OPS_ACC0
#undef OPS_ACC1


__global__ void ops_xder1_kernel(
const double* __restrict arg0,
double* __restrict arg1,
int size0 ){


  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1;
  arg1 += idx_x * 1*1;

  if (idx_x < size0) {
    xder1_kernel(arg0, arg1);
  }

}

// host stub function
void ops_par_loop_xder1_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  ops_arg args[2] = { arg0, arg1};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,4)) return;
  #endif

  ops_timing_realloc(4,"xder1_kernel");
  OPS_kernels[4].count++;

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


  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c2,&t2);

  if (xdim0 != xdim0_xder1_kernel_h || xdim1 != xdim1_xder1_kernel_h) {
    cudaMemcpyToSymbol( xdim0_xder1_kernel, &xdim0, sizeof(int) );
    xdim0_xder1_kernel_h = xdim0;
    cudaMemcpyToSymbol( xdim1_xder1_kernel, &xdim1, sizeof(int) );
    xdim1_xder1_kernel_h = xdim1;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, 1, 1);
  dim3 tblock(OPS_block_size_x,1,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;

  char *p_a[2];

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


  ops_H_D_exchanges_device(args, 2);
  ops_halo_exchanges(args,2,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[4].mpi_time += t1-t2;


  //call kernel wrapper function, passing in pointers to data
  ops_xder1_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],x_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[4].time += t2-t1;
  ops_set_dirtybit_device(args, 2);
  ops_set_halo_dirtybit3(&args[1],range);

  //Update kernel record
  OPS_kernels[4].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[4].transfer += ops_compute_transfer(dim, range, &arg1);
}
