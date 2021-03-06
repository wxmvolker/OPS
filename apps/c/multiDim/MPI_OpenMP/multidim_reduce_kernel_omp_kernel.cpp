//
// auto-generated by ops.py
//
#define OPS_ACC_MD0(d,x,y) ((x)+(xdim0*(y))+(d)*xdim0*ydim0)
#ifdef _OPENMP
#include <omp.h>
#endif

//user function
inline 
void multidim_reduce_kernel(const double *val, double *redu_dat1) {

  redu_dat1[0] = redu_dat1[0] + val[OPS_ACC_MD0(0,0,0)];
  redu_dat1[1] = redu_dat1[1] + val[OPS_ACC_MD0(1,0,0)];
}



#undef OPS_ACC_MD0


// host stub function
void ops_par_loop_multidim_reduce_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  //Timing
  double t1,t2,c1,c2;

  int  offs[2][2];
  ops_arg args[2] = { arg0, arg1};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,2)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(2,"multidim_reduce_kernel");
    OPS_kernels[2].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block

  int start[2];
  int end[2];

  #ifdef OPS_MPI
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
  #ifdef OPS_DEBUG
  ops_register_args(args, "multidim_reduce_kernel");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 =  (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);

  #ifdef OPS_MPI
  double *arg1h = (double *)(((ops_reduction)args[1].data)->data + ((ops_reduction)args[1].data)->size * block->index);
  #else
  double *arg1h = (double *)(((ops_reduction)args[1].data)->data);
  #endif
  //Halo Exchanges
  ops_H_D_exchanges_host(args, 2);
  ops_halo_exchanges(args,2,range);
  ops_H_D_exchanges_host(args, 2);

  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  //allocate and initialise arrays for global reduction
  //assumes a max of MAX_REDUCT_THREADS threads with a cacche line size of 64 bytes
  double arg_gbl1[MAX(2 , 64) * MAX_REDUCT_THREADS];
  for ( int thr=0; thr<nthreads; thr++ ){
    for ( int d=0; d<2; d++ ){
      arg_gbl1[d+64*thr] = ZERO_double;
    }
  }
  xdim0 = args[0].dat->size[0];
  ydim0 = args[0].dat->size[1];


  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[2].mpi_time += t2-t1;
  }


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int y_size = end[1]-start[1];
    char *p_a[2];

    int start_i = start[1] + ((y_size-1)/nthreads+1)*thr;
    int finish_i = start[1] + MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //get address per thread
    int start0 = start[0];
    int start1 = start_i;

    //set up initial pointers
    int d_m[OPS_MAX_DIM];
    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
    #else
    for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
    #endif
    int base0 = dat0 * 1 *
    (start0 * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
    base0 = base0+ dat0 *
      args[0].dat->size[0] *
      (start1 * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
    p_a[0] = (char *)args[0].data + base0;

    p_a[1] = (char *)arg1h;


    for ( int n_y=start_i; n_y<finish_i; n_y++ ){
      for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
        //call kernel function, passing in pointers to data -vectorised
        for ( int i=0; i<SIMD_VEC; i++ ){
          multidim_reduce_kernel(  (const double * )p_a[0]+ i*1, &arg_gbl1[64*thr] );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
      }

      for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        multidim_reduce_kernel(  (const double * )p_a[0], &arg_gbl1[64*thr] );


        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0);
      }

      //shift pointers to data y direction
      p_a[0]= p_a[0] + (dat0 * off0_1);
    }
  }

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[2].time += t1-t2;
  }


  // combine reduction data
  for ( int thr=0; thr<nthreads; thr++ ){
    for ( int d=0; d<2; d++ ){
      arg1h[d] += arg_gbl1[64*thr+d];
    }
  }
  ops_set_dirtybit_host(args, 2);


  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[2].mpi_time += t2-t1;
    OPS_kernels[2].transfer += ops_compute_transfer(dim, start, end, &arg0);
  }
}
