//
// auto-generated by ops.py
//
#include "./OpenACC/shsgc_common.h"

#define OPS_GPU

extern int xdim0_gridgen_kernel;
int xdim0_gridgen_kernel_h = -1;

#ifdef __cplusplus
extern "C" {
#endif
void gridgen_kernel_c_wrapper(
  double *p_a0,
  int *p_a1,
  int arg_idx0,
  int x_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_gridgen_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  ops_arg args[2] = { arg0, arg1};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,0)) return;
  #endif

  ops_timing_realloc(0,"gridgen_kernel");
  OPS_kernels[0].count++;

  //compute localy allocated range for the sub-block
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

  int arg_idx[1];
  #ifdef OPS_MPI
  arg_idx[0] = sb->decomp_disp[0]+start[0];
  #else //OPS_MPI
  arg_idx[0] = start[0];
  #endif //OPS_MPI

  xdim0 = args[0].dat->size[0];

  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c2,&t2);

  if (xdim0 != xdim0_gridgen_kernel_h) {
    xdim0_gridgen_kernel = xdim0;
    xdim0_gridgen_kernel_h = xdim0;
  }

  int dat0 = args[0].dat->elem_size;


  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif //OPS_MPI
  int base0 = dat0 * 1 *
    (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  #ifdef OPS_GPU
  double *p_a0 = (double *)((char *)args[0].data_d + base0);
  #else
  double *p_a0 = (double *)((char *)args[0].data + base0);
  #endif

  int *p_a1 = NULL;


  #ifdef OPS_GPU
  ops_H_D_exchanges_device(args, 2);
  #else
  ops_H_D_exchanges_host(args, 2);
  #endif
  ops_halo_exchanges(args,2,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[0].mpi_time += t1-t2;

  gridgen_kernel_c_wrapper(
    p_a0,
    p_a1,
    arg_idx[0],
    x_size);

  ops_timers_core(&c2,&t2);
  OPS_kernels[0].time += t2-t1;
  #ifdef OPS_GPU
  ops_set_dirtybit_device(args, 2);
  #else
  ops_set_dirtybit_host(args, 2);
  #endif
  ops_set_halo_dirtybit3(&args[0],range);

  //Update kernel record
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg0);
}
