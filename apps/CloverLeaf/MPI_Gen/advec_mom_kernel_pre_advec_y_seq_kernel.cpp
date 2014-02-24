//
// auto-generated by ops.py on 2014-02-24 14:07
//

//user function
#include "advec_mom_kernel.h"

// host stub function
void ops_par_loop_advec_mom_kernel_pre_advec_y(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  char *p_a[3];
  int  offs[3][2];
  ops_arg args[3] = { arg0, arg1, arg2};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block
  int ndim = sb->ndim;
  int start[ndim*3];
  int end[ndim*3];

  int s[ndim];
  int e[ndim];

  for ( int n=0; n<ndim; n++ ){
    s[n] = sb->istart[n];e[n] = sb->iend[n]+1;
    if (s[n] >= range[2*n]) {
      s[n] = 0;
    }
    else {
      s[n] = range[2*n] - s[n];
    }
    if (e[n] >= range[2*n+1]) {
      e[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      e[n] = sb->sizes[n];
    }
  }

  for ( int i=0; i<3; i++ ){
    for ( int n=0; n<ndim; n++ ){
      start[i*ndim+n] = s[n];
      end[i*ndim+n]   = e[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "advec_mom_kernel_pre_advec_y");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  for ( int n=1; n<ndim; n++ ){
    offs[0][n] = off2(ndim, n, &start[0*ndim],
    &end[0*ndim],args[0].dat->block_size, args[0].stencil->stride);
  }
  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  for ( int n=1; n<ndim; n++ ){
    offs[1][n] = off2(ndim, n, &start[1*ndim],
    &end[1*ndim],args[1].dat->block_size, args[1].stencil->stride);
  }
  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  for ( int n=1; n<ndim; n++ ){
    offs[2][n] = off2(ndim, n, &start[2*ndim],
    &end[2*ndim],args[2].dat->block_size, args[2].stencil->stride);
  }


  //set up initial pointers
  p_a[0] = (char *)args[0].data
  + address2(ndim, args[0].dat->size, &start[0*ndim],
  args[0].dat->block_size, args[0].stencil->stride, args[0].dat->offset);

  //set up initial pointers
  p_a[1] = (char *)args[1].data
  + address2(ndim, args[1].dat->size, &start[1*ndim],
  args[1].dat->block_size, args[1].stencil->stride, args[1].dat->offset);
  ops_exchange_halo(&args[1],2);

  //set up initial pointers
  p_a[2] = (char *)args[2].data
  + address2(ndim, args[2].dat->size, &start[2*ndim],
  args[2].dat->block_size, args[2].stencil->stride, args[2].dat->offset);
  ops_exchange_halo(&args[2],2);


  int off0_1 = offs[0][0];
  int off0_2 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_1 = offs[1][0];
  int off1_2 = offs[1][1];
  int dat1 = args[1].dat->size;
  int off2_1 = offs[2][0];
  int off2_2 = offs[2][1];
  int dat2 = args[2].dat->size;

  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(71,"advec_mom_kernel_pre_advec_y");
  ops_timers_core(&c1,&t1);

  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];
  xdim2 = args[2].dat->block_size[0];

  int n_x;
  for ( int n_y=s[1]; n_y<e[1]; n_y++ ){
    for ( int n_x=s[0]; n_x<s[0]+(e[0]-s[0])/SIMD_VEC; n_x++ ){
        //call kernel function, passing in pointers to data -vectorised
        #pragma simd
        for ( int i=0; i<SIMD_VEC; i++ ){
          advec_mom_kernel_pre_advec_y(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*1, (double *)p_a[2]+ i*1 );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_1)*SIMD_VEC;
        p_a[1]= p_a[1] + (dat1 * off1_1)*SIMD_VEC;
        p_a[2]= p_a[2] + (dat2 * off2_1)*SIMD_VEC;
      }

      for ( int n_x=s[0]+((e[0]-s[0])/SIMD_VEC)*SIMD_VEC; n_x<e[0]; n_x++ ){
          //call kernel function, passing in pointers to data - remainder
          advec_mom_kernel_pre_advec_y(  (double *)p_a[0], (double *)p_a[1], (double *)p_a[2] );


          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_1);
          p_a[1]= p_a[1] + (dat1 * off1_1);
          p_a[2]= p_a[2] + (dat2 * off2_1);
        }

        //shift pointers to data y direction
        p_a[0]= p_a[0] + (dat0 * off0_2);
        p_a[1]= p_a[1] + (dat1 * off1_2);
        p_a[2]= p_a[2] + (dat2 * off2_2);
      }
      ops_set_halo_dirtybit(args, 3);


      //Update kernel record
      ops_timers_core(&c2,&t2);
      OPS_kernels[71].count++;
      OPS_kernels[71].time += t2-t1;
      OPS_kernels[71].transfer += ops_compute_transfer(dim, range, &arg0);
      OPS_kernels[71].transfer += ops_compute_transfer(dim, range, &arg1);
      OPS_kernels[71].transfer += ops_compute_transfer(dim, range, &arg2);
    }
