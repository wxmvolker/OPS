//
// auto-generated by ops.py
//

//user function

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_viscosity_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6) {
#else
void ops_par_loop_viscosity_kernel_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];
  #endif

  //Timing
  double __t1,__t2,__c1,__c2;

  ops_arg args[7] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6};



  #if defined(CHECKPOINTING) && !defined(OPS_LAZY)
  if (!ops_checkpointing_before(args,7,range,34)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(34,"viscosity_kernel");
    OPS_kernels[34].count++;
    ops_timers_core(&__c2,&__t2);
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "viscosity_kernel");
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
  if (compute_ranges(args, 7,block, range, start, end, arg_idx) < 0) return;
  #endif


  //initialize global variable with the dimension of dats
  int xdim0_viscosity_kernel = args[0].dat->size[0];
  int xdim1_viscosity_kernel = args[1].dat->size[0];
  int xdim2_viscosity_kernel = args[2].dat->size[0];
  int xdim3_viscosity_kernel = args[3].dat->size[0];
  int xdim4_viscosity_kernel = args[4].dat->size[0];
  int xdim5_viscosity_kernel = args[5].dat->size[0];
  int xdim6_viscosity_kernel = args[6].dat->size[0];

  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ xvel0_p = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  double * __restrict__ yvel0_p = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  double * __restrict__ celldx_p = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  double * __restrict__ celldy_p = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  double * __restrict__ pressure_p = (double *)(args[4].data + base4);

  int base5 = args[5].dat->base_offset;
  double * __restrict__ density0_p = (double *)(args[5].data + base5);

  int base6 = args[6].dat->base_offset;
  double * __restrict__ viscosity_p = (double *)(args[6].data + base6);



  #ifndef OPS_LAZY
  //Halo Exchanges
  ops_H_D_exchanges_host(args, 7);
  ops_halo_exchanges(args,7,range);
  ops_H_D_exchanges_host(args, 7);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&__c1,&__t1);
    OPS_kernels[34].mpi_time += __t1-__t2;
  }

  #pragma omp parallel for
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #ifdef __INTEL_COMPILER
    #pragma loop_count(10000)
    #pragma omp simd aligned(xvel0_p,yvel0_p,celldx_p,celldy_p,pressure_p,density0_p,viscosity_p)
    #elif defined(__clang__)
    #pragma clang loop vectorize(assume_safety)
    #elif defined(__GNUC__)
    #pragma simd
    #pragma GCC ivdep
    #else
    #pragma simd
    #endif
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      const ACC<double> xvel0(xdim0_viscosity_kernel, xvel0_p + n_x*1 + n_y * xdim0_viscosity_kernel*1);
      const ACC<double> yvel0(xdim1_viscosity_kernel, yvel0_p + n_x*1 + n_y * xdim1_viscosity_kernel*1);
      const ACC<double> celldx(xdim2_viscosity_kernel, celldx_p + n_x*1 + n_y * xdim2_viscosity_kernel*0);
      const ACC<double> celldy(xdim3_viscosity_kernel, celldy_p + n_x*0 + n_y * xdim3_viscosity_kernel*1);
      const ACC<double> pressure(xdim4_viscosity_kernel, pressure_p + n_x*1 + n_y * xdim4_viscosity_kernel*1);
      const ACC<double> density0(xdim5_viscosity_kernel, density0_p + n_x*1 + n_y * xdim5_viscosity_kernel*1);
      ACC<double> viscosity(xdim6_viscosity_kernel, viscosity_p + n_x*1 + n_y * xdim6_viscosity_kernel*1);
      

  double ugrad, vgrad,
         grad2,
         pgradx,pgrady,
         pgradx2,pgrady2,
         grad,
         ygrad, xgrad,
         div,
         strain2,
         limiter,
         pgrad;


  ugrad = (xvel0(1,0) + xvel0(1,1)) - (xvel0(0,0) + xvel0(0,1));
  vgrad = (yvel0(0,1) + yvel0(1,1)) - (yvel0(0,0) + yvel0(1,0));

  div = (celldx(0,0))*(ugrad) + (celldy(0,0))*(vgrad);

  strain2 = 0.5*(xvel0(0,1) + xvel0(1,1) - xvel0(0,0) - xvel0(1,0))/(celldy(0,0)) +
            0.5*(yvel0(1,0) + yvel0(1,1) - yvel0(0,0) - yvel0(0,1))/(celldx(0,0));


  pgradx  = (pressure(1,0) - pressure(-1,0))/(celldx(0,0)+ celldx(1,0));
  pgrady = (pressure(0,1) - pressure(0,-1))/(celldy(0,0)+ celldy(0,1));

  pgradx2 = pgradx * pgradx;
  pgrady2 = pgrady * pgrady;

  limiter = ((0.5*(ugrad)/celldx(0,0)) * pgradx2 +
             (0.5*(vgrad)/celldy(0,0)) * pgrady2 +
              strain2 * pgradx * pgrady)/ MAX(pgradx2 + pgrady2 , 1.0e-16);

  if( (limiter > 0.0) || (div >= 0.0)) {
        viscosity(0,0) = 0.0;
  }
  else {
    pgradx = SIGN( MAX(1.0e-16, fabs(pgradx)), pgradx);
    pgrady = SIGN( MAX(1.0e-16, fabs(pgrady)), pgrady);
    pgrad = sqrt(pgradx*pgradx + pgrady*pgrady);
    xgrad = fabs(celldx(0,0) * pgrad/pgradx);
    ygrad = fabs(celldy(0,0) * pgrad/pgrady);
    grad  = MIN(xgrad,ygrad);
    grad2 = grad*grad;

    viscosity(0,0) = 2.0 * (density0(0,0)) * grad2 * limiter * limiter;
  }

    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&__c2,&__t2);
    OPS_kernels[34].time += __t2-__t1;
  }
  #ifndef OPS_LAZY
  ops_set_dirtybit_host(args, 7);
  ops_set_halo_dirtybit3(&args[6],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&__c1,&__t1);
    OPS_kernels[34].mpi_time += __t1-__t2;
    OPS_kernels[34].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[34].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[34].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[34].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[34].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[34].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[34].transfer += ops_compute_transfer(dim, start, end, &arg6);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6


#ifdef OPS_LAZY
void ops_par_loop_viscosity_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 34;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 34;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 7;
  desc->args = (ops_arg*)malloc(7*sizeof(ops_arg));
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
  desc->function = ops_par_loop_viscosity_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(34,"viscosity_kernel");
  }
  ops_enqueue_kernel(desc);
}
#endif
