//
// auto-generated by ops.py
//
__constant__ int xdim0_tea_leaf_common_init_u_u0_kernel;
int xdim0_tea_leaf_common_init_u_u0_kernel_h = -1;
__constant__ int xdim1_tea_leaf_common_init_u_u0_kernel;
int xdim1_tea_leaf_common_init_u_u0_kernel_h = -1;
__constant__ int xdim2_tea_leaf_common_init_u_u0_kernel;
int xdim2_tea_leaf_common_init_u_u0_kernel_h = -1;
__constant__ int xdim3_tea_leaf_common_init_u_u0_kernel;
int xdim3_tea_leaf_common_init_u_u0_kernel_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


#define OPS_ACC0(x,y) (x+xdim0_tea_leaf_common_init_u_u0_kernel*(y))
#define OPS_ACC1(x,y) (x+xdim1_tea_leaf_common_init_u_u0_kernel*(y))
#define OPS_ACC2(x,y) (x+xdim2_tea_leaf_common_init_u_u0_kernel*(y))
#define OPS_ACC3(x,y) (x+xdim3_tea_leaf_common_init_u_u0_kernel*(y))

//user function
__device__

void tea_leaf_common_init_u_u0_kernel_gpu(double *u, double *u0, const double *energy, const double *density) {
	u [OPS_ACC0(0,0)]=energy[OPS_ACC2(0,0)]*density[OPS_ACC3(0,0)];
	u0[OPS_ACC1(0,0)]=energy[OPS_ACC2(0,0)]*density[OPS_ACC3(0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


__global__ void ops_tea_leaf_common_init_u_u0_kernel(
double* __restrict arg0,
double* __restrict arg1,
const double* __restrict arg2,
const double* __restrict arg3,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_tea_leaf_common_init_u_u0_kernel;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_tea_leaf_common_init_u_u0_kernel;
  arg2 += idx_x * 1*1 + idx_y * 1*1 * xdim2_tea_leaf_common_init_u_u0_kernel;
  arg3 += idx_x * 1*1 + idx_y * 1*1 * xdim3_tea_leaf_common_init_u_u0_kernel;

  if (idx_x < size0 && idx_y < size1) {
    tea_leaf_common_init_u_u0_kernel_gpu(arg0, arg1, arg2, arg3);
  }

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_tea_leaf_common_init_u_u0_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
#else
void ops_par_loop_tea_leaf_common_init_u_u0_kernel_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,4,range,28)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(28,"tea_leaf_common_init_u_u0_kernel");
    OPS_kernels[28].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #if OPS_MPI && !OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
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
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];

  if (xdim0 != xdim0_tea_leaf_common_init_u_u0_kernel_h || xdim1 != xdim1_tea_leaf_common_init_u_u0_kernel_h || xdim2 != xdim2_tea_leaf_common_init_u_u0_kernel_h || xdim3 != xdim3_tea_leaf_common_init_u_u0_kernel_h) {
    cudaMemcpyToSymbol( xdim0_tea_leaf_common_init_u_u0_kernel, &xdim0, sizeof(int) );
    xdim0_tea_leaf_common_init_u_u0_kernel_h = xdim0;
    cudaMemcpyToSymbol( xdim1_tea_leaf_common_init_u_u0_kernel, &xdim1, sizeof(int) );
    xdim1_tea_leaf_common_init_u_u0_kernel_h = xdim1;
    cudaMemcpyToSymbol( xdim2_tea_leaf_common_init_u_u0_kernel, &xdim2, sizeof(int) );
    xdim2_tea_leaf_common_init_u_u0_kernel_h = xdim2;
    cudaMemcpyToSymbol( xdim3_tea_leaf_common_init_u_u0_kernel, &xdim3, sizeof(int) );
    xdim3_tea_leaf_common_init_u_u0_kernel_h = xdim3;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,OPS_block_size_z);



  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);

  char *p_a[4];

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


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 4);
  ops_halo_exchanges(args,4,range);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[28].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0)
    ops_tea_leaf_common_init_u_u0_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],x_size, y_size);

  cutilSafeCall(cudaGetLastError());

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[28].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 4);
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[28].mpi_time += t2-t1;
    OPS_kernels[28].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[28].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[28].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[28].transfer += ops_compute_transfer(dim, start, end, &arg3);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_tea_leaf_common_init_u_u0_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 28;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 28;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 4;
  desc->args = (ops_arg*)malloc(4*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->function = ops_par_loop_tea_leaf_common_init_u_u0_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(28,"tea_leaf_common_init_u_u0_kernel");
  }
  ops_enqueue_kernel(desc);
}
#endif
