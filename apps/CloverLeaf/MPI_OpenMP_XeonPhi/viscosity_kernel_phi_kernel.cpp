//
// auto-generated by ops.py on 2014-07-09 17:28
//

#include "./MPI_OpenMP_XeonPhi/clover_leaf_common.h"

extern int xdim0_viscosity_kernel;
extern int xdim1_viscosity_kernel;
extern int xdim2_viscosity_kernel;
extern int xdim3_viscosity_kernel;
extern int xdim4_viscosity_kernel;
extern int xdim5_viscosity_kernel;
extern int xdim6_viscosity_kernel;

#ifdef __cplusplus
extern "C" {
#endif
void viscosity_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  int x_size, int y_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_viscosity_kernel(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5, ops_arg arg6) {

  ops_arg args[7] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start_add[2];
  int end_add[2];
  for ( int n=0; n<2; n++ ){
    start_add[n] = sb->istart[n];end_add[n] = sb->iend[n]+1;
    if (start_add[n] >= range[2*n]) {
      start_add[n] = 0;
    }
    else {
      start_add[n] = range[2*n] - start_add[n];
    }
    if (end_add[n] >= range[2*n+1]) {
      end_add[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end_add[n] = sb->sizes[n];
    }
  }


  int x_size = MAX(0,end_add[0]-start_add[0]);
  int y_size = MAX(0,end_add[1]-start_add[1]);


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(0,"viscosity_kernel");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[0].count == 0) {
    xdim0_viscosity_kernel = args[0].dat->block_size[0]*args[0].dat->dim;
    xdim1_viscosity_kernel = args[1].dat->block_size[0]*args[1].dat->dim;
    xdim2_viscosity_kernel = args[2].dat->block_size[0]*args[2].dat->dim;
    xdim3_viscosity_kernel = args[3].dat->block_size[0]*args[3].dat->dim;
    xdim4_viscosity_kernel = args[4].dat->block_size[0]*args[4].dat->dim;
    xdim5_viscosity_kernel = args[5].dat->block_size[0]*args[5].dat->dim;
    xdim6_viscosity_kernel = args[6].dat->block_size[0]*args[6].dat->dim;
  }

  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat2 = args[2].dat->size;
  int dat3 = args[3].dat->size;
  int dat4 = args[4].dat->size;
  int dat5 = args[5].dat->size;
  int dat6 = args[6].dat->size;


  //set up initial pointers
  int base0 = dat0 * 1 * 
    (start_add[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    (start_add[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  double *p_a0 = (double *)((char *)args[0].data + base0);

  int base1 = dat1 * 1 * 
    (start_add[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start_add[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  double *p_a1 = (double *)((char *)args[1].data + base1);

  int base2 = dat2 * 1 * 
    (start_add[0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    (start_add[1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  double *p_a2 = (double *)((char *)args[2].data + base2);

  int base3 = dat3 * 1 * 
    (start_add[0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    (start_add[1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
  double *p_a3 = (double *)((char *)args[3].data + base3);

  int base4 = dat4 * 1 * 
    (start_add[0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    (start_add[1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
  double *p_a4 = (double *)((char *)args[4].data + base4);

  int base5 = dat5 * 1 * 
    (start_add[0] * args[5].stencil->stride[0] - args[5].dat->offset[0]);
  base5 = base5+ dat5 *
    args[5].dat->block_size[0] *
    (start_add[1] * args[5].stencil->stride[1] - args[5].dat->offset[1]);
  double *p_a5 = (double *)((char *)args[5].data + base5);

  int base6 = dat6 * 1 * 
    (start_add[0] * args[6].stencil->stride[0] - args[6].dat->offset[0]);
  base6 = base6+ dat6 *
    args[6].dat->block_size[0] *
    (start_add[1] * args[6].stencil->stride[1] - args[6].dat->offset[1]);
  double *p_a6 = (double *)((char *)args[6].data + base6);


  ops_H_D_exchanges(args, 7);
  ops_halo_exchanges(args,7,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[0].mpi_time += t1-t2;

  viscosity_kernel_c_wrapper(
    p_a0,
    p_a1,
    p_a2,
    p_a3,
    p_a4,
    p_a5,
    p_a6,
    x_size, y_size);

  ops_timers_core(&c2,&t2);
  OPS_kernels[0].time += t2-t1;
  ops_set_dirtybit_host(args, 7);
  ops_set_halo_dirtybit3(&args[6],range);

  //Update kernel record
  OPS_kernels[0].count++;
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg6);
}