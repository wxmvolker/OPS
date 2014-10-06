//
// auto-generated by ops.py
//
//user function
#include "mgrid_prolong_kernel.h"

// host stub function
void ops_par_loop_mgrid_prolong_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  char *p_a[3];
  int  offs[3][2];
  ops_arg args[3] = { arg0, arg1, arg2};



  ops_timing_realloc(1,"mgrid_prolong_kernel");
  OPS_kernels[1].count++;

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  int arg_idx[2];

  #ifdef OPS_MPI
  if (compute_ranges(args, block, range, start, end, arg_idx) < 0) return;
  #else //OPS_MPI
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI

  #ifdef OPS_DEBUG
  ops_register_args(args, "mgrid_prolong_kernel");
  #endif

  #ifdef OPS_MPI
  int arg_idx_0 = arg_idx[0];
  int arg_idx_1 = arg_idx[1];
  #else //OPS_MPI
  int arg_idx_0 = start[0];
  int arg_idx_1 = start[1];
  #endif //OPS_MPI
  int global_idx[2];
  #ifdef OPS_MPI
  global_idx[0] = arg_idx[0];
  global_idx[1] = arg_idx[1];
  #else //OPS_MPI
  global_idx[0] = start[0];
  global_idx[1] = start[1];
  #endif //OPS_MPI

  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c2,&t2);

  //This arg has a prolong stencil - so create different ranges
  sub_dat *sd0 = OPS_sub_dat_list[args[0].dat->index];
  int start_0[2]; int end_0[2]; int stride_0[2];int d_size_0[2];
  for ( int n=0; n<2; n++ ){
    stride_0[n] = args[0].stencil->mgrid_stride[n];
    d_size_0[n] = args[0].dat->d_m[n] + sd0->decomp_size[n] - args[0].dat->d_p[n];
    start_0[n] = global_idx[n]/stride_0[n] - sd0->decomp_disp[n] + args[0].dat->d_m[n];
    end_0[n] = start_0[n] + d_size_0[n];
  }
  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start_0[0],
      &end_0[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off2D(1, &start[0],
      &end[0],args[1].dat->size, args[1].stencil->stride) - offs[1][0];


  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = args[0].dat->elem_size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int dat1 = args[1].dat->elem_size;

  //set up initial pointers and exchange halos if necessary
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif //OPS_MPI
  int base0 = dat0 * 1 * 
    ((start_0[0]) * args[0].stencil->stride[0] - args[0].dat->base[0]- d_m[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    ((start_0[1]) * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
  p_a[0] = (char *)args[0].data + base0;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
  #endif //OPS_MPI
  int base1 = dat1 * 1 * 
    (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->base[1] - d_m[1]);
  p_a[1] = (char *)args[1].data + base1;

  p_a[2] = (char *)arg_idx;


  ops_H_D_exchanges_host(args, 3);
  ops_halo_exchanges(args,3,range);
  ops_H_D_exchanges_host(args, 3);

  ops_timers_core(&c1,&t1);
  OPS_kernels[1].mpi_time += t1-t2;

  xdim0 = args[0].dat->size[0]*args[0].dat->dim;
  xdim1 = args[1].dat->size[0]*args[1].dat->dim;

  int n_x;
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #pragma novector
    for( n_x=start[0]; n_x<end[0]; n_x++ ) {
      //call kernel function, passing in pointers to data
      mgrid_prolong_kernel(  (double *)p_a[0], (double *)p_a[1], (int *)p_a[2] );

      //shift pointers to data x direction
      p_a[0]= p_a[0] + (dat0 * off0_0) * (((global_idx[0]+1) % stride_0[0] == 0)?1:0);
      p_a[1]= p_a[1] + (dat1 * off1_0);
      arg_idx[0]++;
      global_idx[0]++;
    }

    //shift pointers to data y direction
    if ((global_idx[1]+1) % stride_0[1] == 0) {
      p_a[0]= p_a[0] + (dat0 * off0_1);
    }
    else {
      p_a[0]= p_a[0] - (dat0 * off0_0) * (end_0[0]-start_0[0]);
    }
    p_a[1]= p_a[1] + (dat1 * off1_1);

    #ifdef OPS_MPI
    arg_idx[0] = arg_idx_0;
    #else //OPS_MPI
    arg_idx[0] = start[0];
    #endif //OPS_MPI
    arg_idx[1]++;

    #ifdef OPS_MPI
    global_idx[0] = arg_idx_0;
    #else //OPS_MPI
    global_idx[0] = start[0];
    #endif //OPS_MPI
    global_idx[1]++;
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[1].time += t2-t1;
  ops_set_dirtybit_host(args, 3);
  ops_set_halo_dirtybit3(&args[1],range);

  //Update kernel record
  OPS_kernels[1].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[1].transfer += ops_compute_transfer(dim, range, &arg1);
}
