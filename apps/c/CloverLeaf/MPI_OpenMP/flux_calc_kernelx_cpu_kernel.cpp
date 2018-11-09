//
// auto-generated by ops.py
//

//user function

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_flux_calc_kernelx(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
#else
void ops_par_loop_flux_calc_kernelx_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  #endif

  //Timing
  double __t1,__t2,__c1,__c2;

  ops_arg args[4] = { arg0, arg1, arg2, arg3};



  #if defined(CHECKPOINTING) && !defined(OPS_LAZY)
  if (!ops_checkpointing_before(args,4,range,59)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(59,"flux_calc_kernelx");
    OPS_kernels[59].count++;
    ops_timers_core(&__c2,&__t2);
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "flux_calc_kernelx");
  #endif


  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #ifdef OPS_MPI
  int arg_idx[2];
  #endif
  #if defined(OPS_LAZY) || !defined(OPS_MPI)
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #else
  if (compute_ranges(args, 4,block, range, start, end, arg_idx) < 0) return;
  #endif


  //initialize global variable with the dimension of dats
  int xdim0_flux_calc_kernelx = args[0].dat->size[0];
  int xdim1_flux_calc_kernelx = args[1].dat->size[0];
  int xdim2_flux_calc_kernelx = args[2].dat->size[0];
  int xdim3_flux_calc_kernelx = args[3].dat->size[0];

  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ vol_flux_x_p = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  double * __restrict__ xarea_p = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  double * __restrict__ xvel0_p = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  double * __restrict__ xvel1_p = (double *)(args[3].data + base3);



  #ifndef OPS_LAZY
  //Halo Exchanges
  ops_H_D_exchanges_host(args, 4);
  ops_halo_exchanges(args,4,range);
  ops_H_D_exchanges_host(args, 4);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&__c1,&__t1);
    OPS_kernels[59].mpi_time += __t1-__t2;
  }

  #pragma omp parallel for
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #ifdef __INTEL_COMPILER
    #pragma loop_count(10000)
    #pragma omp simd
    #elif defined(__clang__)
    #pragma clang loop vectorize(assume_safety)
    #elif defined(__GNUC__)
    #pragma simd
    #pragma GCC ivdep
    #else
    #pragma simd
    #endif
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      ACC<double> vol_flux_x(xdim0_flux_calc_kernelx, vol_flux_x_p + n_x*1 + n_y * xdim0_flux_calc_kernelx*1);
      const ACC<double> xarea(xdim1_flux_calc_kernelx, xarea_p + n_x*1 + n_y * xdim1_flux_calc_kernelx*1);
      const ACC<double> xvel0(xdim2_flux_calc_kernelx, xvel0_p + n_x*1 + n_y * xdim2_flux_calc_kernelx*1);
      const ACC<double> xvel1(xdim3_flux_calc_kernelx, xvel1_p + n_x*1 + n_y * xdim3_flux_calc_kernelx*1);
      

  vol_flux_x(0,0) = 0.25 * dt * (xarea(0,0)) *
  ( (xvel0(0,0)) + (xvel0(0,1)) + (xvel1(0,0)) + (xvel1(0,1)) );


    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&__c2,&__t2);
    OPS_kernels[59].time += __t2-__t1;
  }
  #ifndef OPS_LAZY
  ops_set_dirtybit_host(args, 4);
  ops_set_halo_dirtybit3(&args[0],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&__c1,&__t1);
    OPS_kernels[59].mpi_time += __t1-__t2;
    OPS_kernels[59].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[59].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[59].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[59].transfer += ops_compute_transfer(dim, start, end, &arg3);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


#ifdef OPS_LAZY
void ops_par_loop_flux_calc_kernelx(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 59;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 59;
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
  desc->function = ops_par_loop_flux_calc_kernelx_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(59,"flux_calc_kernelx");
  }
  ops_enqueue_kernel(desc);
}
#endif
