//
// auto-generated by ops.py
//
__constant__ int dims_advec_cell_kernel4_xdir [11][1];
static int dims_advec_cell_kernel4_xdir_h [11][1] = {0};

//user function
__device__

inline void advec_cell_kernel4_xdir_gpu( ACC<double> &density1, ACC<double> &energy1,
                         const ACC<double> &mass_flux_x, const ACC<double> &vol_flux_x,
                         const ACC<double> &pre_vol, const ACC<double> &post_vol,
                         ACC<double> &pre_mass, ACC<double> &post_mass,
                         ACC<double> &advec_vol, ACC<double> &post_ener,
                         const ACC<double> &ener_flux) {

  pre_mass(0,0) = density1(0,0) * pre_vol(0,0);
  post_mass(0,0) = pre_mass(0,0) + mass_flux_x(0,0) - mass_flux_x(1,0);
  post_ener(0,0) = ( energy1(0,0) * pre_mass(0,0) + ener_flux(0,0) - ener_flux(1,0))/post_mass(0,0);
  advec_vol(0,0) = pre_vol(0,0) + vol_flux_x(0,0) - vol_flux_x(1,0);
  density1(0,0) = post_mass(0,0)/advec_vol(0,0);
  energy1(0,0) = post_ener(0,0);

}



__global__ void ops_advec_cell_kernel4_xdir(
double* __restrict arg0,
double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
double* __restrict arg4,
double* __restrict arg5,
double* __restrict arg6,
double* __restrict arg7,
double* __restrict arg8,
double* __restrict arg9,
double* __restrict arg10,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[0][0];
  arg1 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[1][0];
  arg2 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[2][0];
  arg3 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[3][0];
  arg4 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[4][0];
  arg5 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[5][0];
  arg6 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[6][0];
  arg7 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[7][0];
  arg8 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[8][0];
  arg9 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[9][0];
  arg10 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel4_xdir[10][0];

  if (idx_x < size0 && idx_y < size1) {
    ACC<double> argp0(dims_advec_cell_kernel4_xdir[0][0], arg0);
    ACC<double> argp1(dims_advec_cell_kernel4_xdir[1][0], arg1);
    const ACC<double> argp2(dims_advec_cell_kernel4_xdir[2][0], arg2);
    const ACC<double> argp3(dims_advec_cell_kernel4_xdir[3][0], arg3);
    const ACC<double> argp4(dims_advec_cell_kernel4_xdir[4][0], arg4);
    const ACC<double> argp5(dims_advec_cell_kernel4_xdir[5][0], arg5);
    ACC<double> argp6(dims_advec_cell_kernel4_xdir[6][0], arg6);
    ACC<double> argp7(dims_advec_cell_kernel4_xdir[7][0], arg7);
    ACC<double> argp8(dims_advec_cell_kernel4_xdir[8][0], arg8);
    ACC<double> argp9(dims_advec_cell_kernel4_xdir[9][0], arg9);
    const ACC<double> argp10(dims_advec_cell_kernel4_xdir[10][0], arg10);
    advec_cell_kernel4_xdir_gpu(argp0,
                   argp1,
                   argp2,
                   argp3,
                   argp4,
                   argp5,
                   argp6,
                   argp7,
                   argp8,
                   argp9,
                   argp10);
  }

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_advec_cell_kernel4_xdir(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7, ops_arg arg8,
 ops_arg arg9, ops_arg arg10) {
#else
void ops_par_loop_advec_cell_kernel4_xdir_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  #ifdef OPS_MPI
  ops_block block = desc->block;
  #endif
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];
  ops_arg arg7 = desc->args[7];
  ops_arg arg8 = desc->args[8];
  ops_arg arg9 = desc->args[9];
  ops_arg arg10 = desc->args[10];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[11] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,11,range,64)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(64,"advec_cell_kernel4_xdir");
    OPS_kernels[64].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  #ifdef OPS_MPI
  int arg_idx[2];
  #endif
  #ifdef OPS_MPI
  #ifdef OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
    arg_idx[n] = sb->decomp_disp[n]+start[n];
  }
  #else
  if (compute_ranges(args, 11,block, range, start, end, arg_idx) < 0) return;
  #endif
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif
  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];
  int xdim6 = args[6].dat->size[0];
  int xdim7 = args[7].dat->size[0];
  int xdim8 = args[8].dat->size[0];
  int xdim9 = args[9].dat->size[0];
  int xdim10 = args[10].dat->size[0];

  if (xdim0 != dims_advec_cell_kernel4_xdir_h[0][0] || xdim1 != dims_advec_cell_kernel4_xdir_h[1][0] || xdim2 != dims_advec_cell_kernel4_xdir_h[2][0] || xdim3 != dims_advec_cell_kernel4_xdir_h[3][0] || xdim4 != dims_advec_cell_kernel4_xdir_h[4][0] || xdim5 != dims_advec_cell_kernel4_xdir_h[5][0] || xdim6 != dims_advec_cell_kernel4_xdir_h[6][0] || xdim7 != dims_advec_cell_kernel4_xdir_h[7][0] || xdim8 != dims_advec_cell_kernel4_xdir_h[8][0] || xdim9 != dims_advec_cell_kernel4_xdir_h[9][0] || xdim10 != dims_advec_cell_kernel4_xdir_h[10][0]) {
    dims_advec_cell_kernel4_xdir_h[0][0] = xdim0;
    dims_advec_cell_kernel4_xdir_h[1][0] = xdim1;
    dims_advec_cell_kernel4_xdir_h[2][0] = xdim2;
    dims_advec_cell_kernel4_xdir_h[3][0] = xdim3;
    dims_advec_cell_kernel4_xdir_h[4][0] = xdim4;
    dims_advec_cell_kernel4_xdir_h[5][0] = xdim5;
    dims_advec_cell_kernel4_xdir_h[6][0] = xdim6;
    dims_advec_cell_kernel4_xdir_h[7][0] = xdim7;
    dims_advec_cell_kernel4_xdir_h[8][0] = xdim8;
    dims_advec_cell_kernel4_xdir_h[9][0] = xdim9;
    dims_advec_cell_kernel4_xdir_h[10][0] = xdim10;
    cutilSafeCall(cudaMemcpyToSymbol( dims_advec_cell_kernel4_xdir, dims_advec_cell_kernel4_xdir_h, sizeof(dims_advec_cell_kernel4_xdir)));
  }



  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,OPS_block_size_z);



  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int dat5 = (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int dat6 = (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);
  int dat7 = (OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size);
  int dat8 = (OPS_soa ? args[8].dat->type_size : args[8].dat->elem_size);
  int dat9 = (OPS_soa ? args[9].dat->type_size : args[9].dat->elem_size);
  int dat10 = (OPS_soa ? args[10].dat->type_size : args[10].dat->elem_size);

  char *p_a[11];

  //set up initial pointers
  int base0 = args[0].dat->base_offset + 
           dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = args[1].dat->base_offset + 
           dat1 * 1 * (start[0] * args[1].stencil->stride[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = args[2].dat->base_offset + 
           dat2 * 1 * (start[0] * args[2].stencil->stride[0]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = args[3].dat->base_offset + 
           dat3 * 1 * (start[0] * args[3].stencil->stride[0]);
  base3 = base3+ dat3 *
    args[3].dat->size[0] *
    (start[1] * args[3].stencil->stride[1]);
  p_a[3] = (char *)args[3].data_d + base3;

  int base4 = args[4].dat->base_offset + 
           dat4 * 1 * (start[0] * args[4].stencil->stride[0]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    (start[1] * args[4].stencil->stride[1]);
  p_a[4] = (char *)args[4].data_d + base4;

  int base5 = args[5].dat->base_offset + 
           dat5 * 1 * (start[0] * args[5].stencil->stride[0]);
  base5 = base5+ dat5 *
    args[5].dat->size[0] *
    (start[1] * args[5].stencil->stride[1]);
  p_a[5] = (char *)args[5].data_d + base5;

  int base6 = args[6].dat->base_offset + 
           dat6 * 1 * (start[0] * args[6].stencil->stride[0]);
  base6 = base6+ dat6 *
    args[6].dat->size[0] *
    (start[1] * args[6].stencil->stride[1]);
  p_a[6] = (char *)args[6].data_d + base6;

  int base7 = args[7].dat->base_offset + 
           dat7 * 1 * (start[0] * args[7].stencil->stride[0]);
  base7 = base7+ dat7 *
    args[7].dat->size[0] *
    (start[1] * args[7].stencil->stride[1]);
  p_a[7] = (char *)args[7].data_d + base7;

  int base8 = args[8].dat->base_offset + 
           dat8 * 1 * (start[0] * args[8].stencil->stride[0]);
  base8 = base8+ dat8 *
    args[8].dat->size[0] *
    (start[1] * args[8].stencil->stride[1]);
  p_a[8] = (char *)args[8].data_d + base8;

  int base9 = args[9].dat->base_offset + 
           dat9 * 1 * (start[0] * args[9].stencil->stride[0]);
  base9 = base9+ dat9 *
    args[9].dat->size[0] *
    (start[1] * args[9].stencil->stride[1]);
  p_a[9] = (char *)args[9].data_d + base9;

  int base10 = args[10].dat->base_offset + 
           dat10 * 1 * (start[0] * args[10].stencil->stride[0]);
  base10 = base10+ dat10 *
    args[10].dat->size[0] *
    (start[1] * args[10].stencil->stride[1]);
  p_a[10] = (char *)args[10].data_d + base10;


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 11);
  ops_halo_exchanges(args,11,range);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[64].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0)
    ops_advec_cell_kernel4_xdir<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
         (double *)p_a[2], (double *)p_a[3],
         (double *)p_a[4], (double *)p_a[5],
         (double *)p_a[6], (double *)p_a[7],
         (double *)p_a[8], (double *)p_a[9],
         (double *)p_a[10],x_size, y_size);

  cutilSafeCall(cudaGetLastError());

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[64].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 11);
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[6],range);
  ops_set_halo_dirtybit3(&args[7],range);
  ops_set_halo_dirtybit3(&args[8],range);
  ops_set_halo_dirtybit3(&args[9],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[64].mpi_time += t2-t1;
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg7);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg8);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg9);
    OPS_kernels[64].transfer += ops_compute_transfer(dim, start, end, &arg10);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_advec_cell_kernel4_xdir(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7, ops_arg arg8, ops_arg arg9, ops_arg arg10) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 64;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 64;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 11;
  desc->args = (ops_arg*)malloc(11*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->args[4] = arg4;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg4.dat->index;
  desc->args[5] = arg5;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg5.dat->index;
  desc->args[6] = arg6;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg6.dat->index;
  desc->args[7] = arg7;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg7.dat->index;
  desc->args[8] = arg8;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg8.dat->index;
  desc->args[9] = arg9;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg9.dat->index;
  desc->args[10] = arg10;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg10.dat->index;
  desc->function = ops_par_loop_advec_cell_kernel4_xdir_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(64,"advec_cell_kernel4_xdir");
  }
  ops_enqueue_kernel(desc);
}
#endif
