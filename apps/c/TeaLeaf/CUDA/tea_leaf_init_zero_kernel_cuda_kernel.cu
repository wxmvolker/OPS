//
// auto-generated by ops.py
//
__constant__ int dims_tea_leaf_init_zero_kernel [1][1];
static int dims_tea_leaf_init_zero_kernel_h [1][1] = {0};

#undef OPS_ACC0


#define OPS_ACC0(x,y) (x+dims_tea_leaf_init_zero_kernel[0][0]*(y))

//user function
__device__

void tea_leaf_init_zero_kernel_gpu (double * p) {
  p[OPS_ACC0(0,0)] = 0.0;
}



#undef OPS_ACC0


__global__ void ops_tea_leaf_init_zero_kernel(
double* __restrict arg0,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * dims_tea_leaf_init_zero_kernel[0][0];

  if (idx_x < size0 && idx_y < size1) {
    tea_leaf_init_zero_kernel_gpu(arg0);
  }

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_tea_leaf_init_zero_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0) {
#else
void ops_par_loop_tea_leaf_init_zero_kernel_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  #ifdef OPS_MPI
  ops_block block = desc->block;
  #endif
  ops_arg arg0 = desc->args[0];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[1] = { arg0};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,1,range,45)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(45,"tea_leaf_init_zero_kernel");
    OPS_kernels[45].count++;
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
  if (compute_ranges(args, 1,block, range, start, end, arg_idx) < 0) return;
  #endif
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif
  int xdim0 = args[0].dat->size[0];

  if (xdim0 != dims_tea_leaf_init_zero_kernel_h[0][0]) {
    dims_tea_leaf_init_zero_kernel_h[0][0] = xdim0;
    cutilSafeCall(cudaMemcpyToSymbol( dims_tea_leaf_init_zero_kernel, dims_tea_leaf_init_zero_kernel_h, sizeof(dims_tea_leaf_init_zero_kernel)));
  }



  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,OPS_block_size_z);



  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);

  char *p_a[1];

  //set up initial pointers
  int base0 = args[0].dat->base_offset + 
           dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1]);
  p_a[0] = (char *)args[0].data_d + base0;


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 1);
  ops_halo_exchanges(args,1,range);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[45].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0)
    ops_tea_leaf_init_zero_kernel<<<grid, tblock >>> (  (double *)p_a[0],x_size, y_size);

  cutilSafeCall(cudaGetLastError());

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[45].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 1);
  ops_set_halo_dirtybit3(&args[0],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[45].mpi_time += t2-t1;
    OPS_kernels[45].transfer += ops_compute_transfer(dim, start, end, &arg0);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_tea_leaf_init_zero_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 45;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 45;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 1;
  desc->args = (ops_arg*)malloc(1*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->function = ops_par_loop_tea_leaf_init_zero_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(45,"tea_leaf_init_zero_kernel");
  }
  ops_enqueue_kernel(desc);
}
#endif
