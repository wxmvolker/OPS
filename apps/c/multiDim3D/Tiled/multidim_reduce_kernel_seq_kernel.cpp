//
// auto-generated by ops.py
//

#define OPS_ACC_MD0(d,x,y,z) (n_x*1 + n_y*xdim0_multidim_reduce_kernel*1 + n_z*xdim0_multidim_reduce_kernel*ydim0_multidim_reduce_kernel*1 + (x)+(d)*xdim0_multidim_reduce_kernel*ydim0_multidim_reduce_kernel*zdim0_multidim_reduce_kernel+(xdim0_multidim_reduce_kernel*(y))+(xdim0_multidim_reduce_kernel*ydim0_multidim_reduce_kernel*(z)))

//user function

// host stub function
void ops_par_loop_multidim_reduce_kernel_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[2] = { arg0, arg1};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,2)) return;
  #endif

  if (OPS_diags > 1) {
    OPS_kernels[2].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];

  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "multidim_reduce_kernel");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  const double * __restrict__ val = (double *)(args[0].data + base0);

  #ifdef OPS_MPI
  double * __restrict__ p_a1 = (double *)(((ops_reduction)args[1].data)->data + ((ops_reduction)args[1].data)->size * block->index);
  #else //OPS_MPI
  double * __restrict__ p_a1 = (double *)((ops_reduction)args[1].data)->data;
  #endif //OPS_MPI



  //initialize global variable with the dimension of dats
  int xdim0_multidim_reduce_kernel = args[0].dat->size[0];
  int ydim0_multidim_reduce_kernel = args[0].dat->size[1];
  int zdim0_multidim_reduce_kernel = args[0].dat->size[2];

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[2].mpi_time += t1-t2;
  }

  double p_a1_0 = p_a1[0];
  double p_a1_1 = p_a1[1];
  double p_a1_2 = p_a1[2];
  #pragma omp parallel for reduction(+:p_a1_0) reduction(+:p_a1_1) reduction(+:p_a1_2)
  for ( int n_z=start[2]; n_z<end[2]; n_z++ ){
    for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
      #ifdef intel
      #pragma loop_count(10000)
      #pragma omp simd reduction(+:p_a1_0) reduction(+:p_a1_1) reduction(+:p_a1_2) aligned(val)
      #else
      #pragma simd reduction(+:p_a1_0) reduction(+:p_a1_1) reduction(+:p_a1_2)
      #endif
      for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
        double redu_dat1[3];
        redu_dat1[0] = ZERO_double;
        redu_dat1[1] = ZERO_double;
        redu_dat1[2] = ZERO_double;
        

  redu_dat1[0] = redu_dat1[0] + val[OPS_ACC_MD0(0,0,0,0)];
  redu_dat1[1] = redu_dat1[1] + val[OPS_ACC_MD0(1,0,0,0)];
  redu_dat1[2] = redu_dat1[2] + val[OPS_ACC_MD0(2,0,0,0)];

        p_a1_0 +=redu_dat1[0];
        p_a1_1 +=redu_dat1[1];
        p_a1_2 +=redu_dat1[2];
      }
    }
  }
  p_a1[0] = p_a1_0;
  p_a1[1] = p_a1_1;
  p_a1[2] = p_a1_2;
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[2].time += t2-t1;
  }

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[2].mpi_time += t1-t2;
    OPS_kernels[2].transfer += ops_compute_transfer(dim, start, end, &arg0);
  }
}
#undef OPS_ACC_MD0


void ops_par_loop_multidim_reduce_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 2;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 2;
  for ( int i=0; i<6; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 2;
  desc->args = (ops_arg*)malloc(2*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->function = ops_par_loop_multidim_reduce_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(2,"multidim_reduce_kernel");
  }
  ops_enqueue_kernel(desc);
  }
