//
// auto-generated by ops.py
//
#ifdef _OPENMP
#include <omp.h>
#endif

//user function
inline
void poisson_kernel_populate(const int *dispx, const int *dispy, const int *idx, double *u, double *f, double *ref) {
  double x = dx * (double)(idx[0]+dispx[0]);
  double y = dy * (double)(idx[1]+dispy[0]);

  u[OPS_ACC3(0,0)] = sin(M_PI*x)*cos(2.0*M_PI*y);
  f[OPS_ACC4(0,0)] = -5.0*M_PI*M_PI*sin(M_PI*x)*cos(2.0*M_PI*y);
  ref[OPS_ACC5(0,0)] = sin(M_PI*x)*cos(2.0*M_PI*y);

}





// host stub function
void ops_par_loop_poisson_kernel_populate(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5) {

  //Timing
  double t1,t2,c1,c2;

  int  offs[6][2];
  ops_arg args[6] = { arg0, arg1, arg2, arg3, arg4, arg5};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,6,range,0)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(0,"poisson_kernel_populate");
    OPS_kernels[0].count++;
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
  ops_register_args(args, "poisson_kernel_populate");
  #endif

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off2D(1, &start[0],
      &end[0],args[3].dat->size, args[3].stencil->stride) - offs[3][0];

  offs[4][0] = args[4].stencil->stride[0]*1;  //unit step in x dimension
  offs[4][1] = off2D(1, &start[0],
      &end[0],args[4].dat->size, args[4].stencil->stride) - offs[4][0];

  offs[5][0] = args[5].stencil->stride[0]*1;  //unit step in x dimension
  offs[5][1] = off2D(1, &start[0],
      &end[0],args[5].dat->size, args[5].stencil->stride) - offs[5][0];



  int off3_0 = offs[3][0];
  int off3_1 = offs[3][1];
  int dat3 =  (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int off4_0 = offs[4][0];
  int off4_1 = offs[4][1];
  int dat4 =  (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int off5_0 = offs[5][0];
  int off5_1 = offs[5][1];
  int dat5 =  (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);

  //Halo Exchanges
  ops_H_D_exchanges_host(args, 6);
  ops_halo_exchanges(args,6,range);
  ops_H_D_exchanges_host(args, 6);

  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  xdim3 = args[3].dat->size[0];
  xdim4 = args[4].dat->size[0];
  xdim5 = args[5].dat->size[0];


  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[0].mpi_time += t2-t1;
  }


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int y_size = end[1]-start[1];
    char *p_a[6];

    int start_i = start[1] + ((y_size-1)/nthreads+1)*thr;
    int finish_i = start[1] + MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //get address per thread
    int start0 = start[0];
    int start1 = start_i;

    int arg_idx[2];
    #ifdef OPS_MPI
    arg_idx[0] = sb->decomp_disp[0]+start0;
    arg_idx[1] = sb->decomp_disp[1]+start1;
    #else
    arg_idx[0] = start0;
    arg_idx[1] = start1;
    #endif
    //set up initial pointers
    int d_m[OPS_MAX_DIM];
    p_a[0] = (char *)args[0].data;

    p_a[1] = (char *)args[1].data;

    p_a[2] = (char *)arg_idx;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
    #else
    for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d];
    #endif
    int base3 = dat3 * 1 *
    (start0 * args[3].stencil->stride[0] - args[3].dat->base[0] - d_m[0]);
    base3 = base3+ dat3 *
      args[3].dat->size[0] *
      (start1 * args[3].stencil->stride[1] - args[3].dat->base[1] - d_m[1]);
    p_a[3] = (char *)args[3].data + base3;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
    #else
    for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d];
    #endif
    int base4 = dat4 * 1 *
    (start0 * args[4].stencil->stride[0] - args[4].dat->base[0] - d_m[0]);
    base4 = base4+ dat4 *
      args[4].dat->size[0] *
      (start1 * args[4].stencil->stride[1] - args[4].dat->base[1] - d_m[1]);
    p_a[4] = (char *)args[4].data + base4;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d] + OPS_sub_dat_list[args[5].dat->index]->d_im[d];
    #else
    for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d];
    #endif
    int base5 = dat5 * 1 *
    (start0 * args[5].stencil->stride[0] - args[5].dat->base[0] - d_m[0]);
    base5 = base5+ dat5 *
      args[5].dat->size[0] *
      (start1 * args[5].stencil->stride[1] - args[5].dat->base[1] - d_m[1]);
    p_a[5] = (char *)args[5].data + base5;


    for ( int n_y=start_i; n_y<finish_i; n_y++ ){
      for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
        //call kernel function, passing in pointers to data -vectorised
        for ( int i=0; i<SIMD_VEC; i++ ){
          poisson_kernel_populate(  (int * )p_a[0], (int * )p_a[1], arg_idx,
           (double * )p_a[3]+ i*1*1, (double * )p_a[4]+ i*1*1, (double * )p_a[5]+ i*1*1 );

          arg_idx[0]++;
        }

        //shift pointers to data x direction
        p_a[3]= p_a[3] + (dat3 * off3_0)*SIMD_VEC;
        p_a[4]= p_a[4] + (dat4 * off4_0)*SIMD_VEC;
        p_a[5]= p_a[5] + (dat5 * off5_0)*SIMD_VEC;
      }

      for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        poisson_kernel_populate(  (int * )p_a[0], (int * )p_a[1], arg_idx,
           (double * )p_a[3], (double * )p_a[4], (double * )p_a[5] );


        //shift pointers to data x direction
        p_a[3]= p_a[3] + (dat3 * off3_0);
        p_a[4]= p_a[4] + (dat4 * off4_0);
        p_a[5]= p_a[5] + (dat5 * off5_0);
        arg_idx[0]++;
      }

      //shift pointers to data y direction
      p_a[3]= p_a[3] + (dat3 * off3_1);
      p_a[4]= p_a[4] + (dat4 * off4_1);
      p_a[5]= p_a[5] + (dat5 * off5_1);
      #ifdef OPS_MPI
      arg_idx[0] = sb->decomp_disp[0]+start0;
      #else
      arg_idx[0] = start0;
      #endif
      arg_idx[1]++;
    }
  }

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[0].time += t1-t2;
  }

  ops_set_dirtybit_host(args, 6);

  ops_set_halo_dirtybit3(&args[3],range);
  ops_set_halo_dirtybit3(&args[4],range);
  ops_set_halo_dirtybit3(&args[5],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[0].mpi_time += t2-t1;
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg5);
  }
}
