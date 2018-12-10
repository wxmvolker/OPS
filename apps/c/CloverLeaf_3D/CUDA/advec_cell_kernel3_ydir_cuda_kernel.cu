//
// auto-generated by ops.py
//
__constant__ int xdim0_advec_cell_kernel3_ydir;
int xdim0_advec_cell_kernel3_ydir_h = -1;
__constant__ int ydim0_advec_cell_kernel3_ydir;
int ydim0_advec_cell_kernel3_ydir_h = -1;
__constant__ int xdim1_advec_cell_kernel3_ydir;
int xdim1_advec_cell_kernel3_ydir_h = -1;
__constant__ int ydim1_advec_cell_kernel3_ydir;
int ydim1_advec_cell_kernel3_ydir_h = -1;
__constant__ int xdim2_advec_cell_kernel3_ydir;
int xdim2_advec_cell_kernel3_ydir_h = -1;
__constant__ int ydim2_advec_cell_kernel3_ydir;
int ydim2_advec_cell_kernel3_ydir_h = -1;
__constant__ int xdim3_advec_cell_kernel3_ydir;
int xdim3_advec_cell_kernel3_ydir_h = -1;
__constant__ int ydim3_advec_cell_kernel3_ydir;
int ydim3_advec_cell_kernel3_ydir_h = -1;
__constant__ int xdim4_advec_cell_kernel3_ydir;
int xdim4_advec_cell_kernel3_ydir_h = -1;
__constant__ int ydim4_advec_cell_kernel3_ydir;
int ydim4_advec_cell_kernel3_ydir_h = -1;
__constant__ int xdim5_advec_cell_kernel3_ydir;
int xdim5_advec_cell_kernel3_ydir_h = -1;
__constant__ int ydim5_advec_cell_kernel3_ydir;
int ydim5_advec_cell_kernel3_ydir_h = -1;
__constant__ int xdim6_advec_cell_kernel3_ydir;
int xdim6_advec_cell_kernel3_ydir_h = -1;
__constant__ int ydim6_advec_cell_kernel3_ydir;
int ydim6_advec_cell_kernel3_ydir_h = -1;
__constant__ int xdim7_advec_cell_kernel3_ydir;
int xdim7_advec_cell_kernel3_ydir_h = -1;
__constant__ int ydim7_advec_cell_kernel3_ydir;
int ydim7_advec_cell_kernel3_ydir_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7


#define OPS_ACC0(x,y,z) (x+xdim0_advec_cell_kernel3_ydir*(y)+xdim0_advec_cell_kernel3_ydir*ydim0_advec_cell_kernel3_ydir*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_advec_cell_kernel3_ydir*(y)+xdim1_advec_cell_kernel3_ydir*ydim1_advec_cell_kernel3_ydir*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_advec_cell_kernel3_ydir*(y)+xdim2_advec_cell_kernel3_ydir*ydim2_advec_cell_kernel3_ydir*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_advec_cell_kernel3_ydir*(y)+xdim3_advec_cell_kernel3_ydir*ydim3_advec_cell_kernel3_ydir*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_advec_cell_kernel3_ydir*(y)+xdim4_advec_cell_kernel3_ydir*ydim4_advec_cell_kernel3_ydir*(z))
#define OPS_ACC5(x,y,z) (x+xdim5_advec_cell_kernel3_ydir*(y)+xdim5_advec_cell_kernel3_ydir*ydim5_advec_cell_kernel3_ydir*(z))
#define OPS_ACC6(x,y,z) (x+xdim6_advec_cell_kernel3_ydir*(y)+xdim6_advec_cell_kernel3_ydir*ydim6_advec_cell_kernel3_ydir*(z))
#define OPS_ACC7(x,y,z) (x+xdim7_advec_cell_kernel3_ydir*(y)+xdim7_advec_cell_kernel3_ydir*ydim7_advec_cell_kernel3_ydir*(z))

//user function
__device__

inline void advec_cell_kernel3_ydir_gpu( const double *vol_flux_y, const double *pre_vol, const int *yy,
                              const double *vertexdy,
                              const double *density1, const double *energy1 ,
                              double *mass_flux_y, double *ener_flux) {

  double sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0/6.0;

  int y_max=field.y_max;

  int upwind,donor,downwind,dif;





  if(vol_flux_y[OPS_ACC0(0,0,0)] > 0.0) {
    upwind   = -2;
    donor    = -1;
    downwind = 0;
    dif      = donor;
  }
  else if (yy[OPS_ACC2(0,1,0)] < y_max+2-2) {
    upwind   = 1;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  } else {
    upwind   = 0;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  }


  sigmat = fabs(vol_flux_y[OPS_ACC0(0,0,0)])/pre_vol[OPS_ACC1(0,donor,0)];
  sigma3 = (1.0 + sigmat)*(vertexdy[OPS_ACC3(0,0,0)]/vertexdy[OPS_ACC3(0,dif,0)]);
  sigma4 = 2.0 - sigmat;

  sigmav = sigmat;

  diffuw = density1[OPS_ACC4(0,donor,0)] - density1[OPS_ACC4(0,upwind,0)];
  diffdw = density1[OPS_ACC4(0,downwind,0)] - density1[OPS_ACC4(0,donor,0)];

  if( (diffuw*diffdw) > 0.0)
    limiter=(1.0 - sigmav) * SIGN(1.0 , diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3*fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  mass_flux_y[OPS_ACC6(0,0,0)] = (vol_flux_y[OPS_ACC0(0,0,0)]) * ( density1[OPS_ACC4(0,donor,0)] + limiter );

  sigmam = fabs(mass_flux_y[OPS_ACC6(0,0,0)])/( density1[OPS_ACC4(0,donor,0)] * pre_vol[OPS_ACC1(0,donor,0)]);
  diffuw = energy1[OPS_ACC5(0,donor,0)] - energy1[OPS_ACC5(0,upwind,0)];
  diffdw = energy1[OPS_ACC5(0,downwind,0)] - energy1[OPS_ACC5(0,donor,0)];

  if( (diffuw*diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0,diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  ener_flux[OPS_ACC7(0,0,0)] = mass_flux_y[OPS_ACC6(0,0,0)] * ( energy1[OPS_ACC5(0,donor,0)] + limiter );
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7


__global__ void ops_advec_cell_kernel3_ydir(
const double* __restrict arg0,
const double* __restrict arg1,
const int* __restrict arg2,
const double* __restrict arg3,
const double* __restrict arg4,
const double* __restrict arg5,
double* __restrict arg6,
double* __restrict arg7,
int size0,
int size1,
int size2 ){


  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_advec_cell_kernel3_ydir + idx_z * 1*1 * xdim0_advec_cell_kernel3_ydir * ydim0_advec_cell_kernel3_ydir;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_advec_cell_kernel3_ydir + idx_z * 1*1 * xdim1_advec_cell_kernel3_ydir * ydim1_advec_cell_kernel3_ydir;
  arg2 += idx_x * 0*1 + idx_y * 1*1 * xdim2_advec_cell_kernel3_ydir + idx_z * 0*1 * xdim2_advec_cell_kernel3_ydir * ydim2_advec_cell_kernel3_ydir;
  arg3 += idx_x * 0*1 + idx_y * 1*1 * xdim3_advec_cell_kernel3_ydir + idx_z * 0*1 * xdim3_advec_cell_kernel3_ydir * ydim3_advec_cell_kernel3_ydir;
  arg4 += idx_x * 1*1 + idx_y * 1*1 * xdim4_advec_cell_kernel3_ydir + idx_z * 1*1 * xdim4_advec_cell_kernel3_ydir * ydim4_advec_cell_kernel3_ydir;
  arg5 += idx_x * 1*1 + idx_y * 1*1 * xdim5_advec_cell_kernel3_ydir + idx_z * 1*1 * xdim5_advec_cell_kernel3_ydir * ydim5_advec_cell_kernel3_ydir;
  arg6 += idx_x * 1*1 + idx_y * 1*1 * xdim6_advec_cell_kernel3_ydir + idx_z * 1*1 * xdim6_advec_cell_kernel3_ydir * ydim6_advec_cell_kernel3_ydir;
  arg7 += idx_x * 1*1 + idx_y * 1*1 * xdim7_advec_cell_kernel3_ydir + idx_z * 1*1 * xdim7_advec_cell_kernel3_ydir * ydim7_advec_cell_kernel3_ydir;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    advec_cell_kernel3_ydir_gpu(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6, arg7);
  }

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_advec_cell_kernel3_ydir(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {
#else
void ops_par_loop_advec_cell_kernel3_ydir_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];
  ops_arg arg7 = desc->args[7];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,8,range,115)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(115,"advec_cell_kernel3_ydir");
    OPS_kernels[115].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];
  #if OPS_MPI && !OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<3; n++ ){
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
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);
  int z_size = MAX(0,end[2]-start[2]);

  int xdim0 = args[0].dat->size[0];
  int ydim0 = args[0].dat->size[1];
  int xdim1 = args[1].dat->size[0];
  int ydim1 = args[1].dat->size[1];
  int xdim2 = args[2].dat->size[0];
  int ydim2 = args[2].dat->size[1];
  int xdim3 = args[3].dat->size[0];
  int ydim3 = args[3].dat->size[1];
  int xdim4 = args[4].dat->size[0];
  int ydim4 = args[4].dat->size[1];
  int xdim5 = args[5].dat->size[0];
  int ydim5 = args[5].dat->size[1];
  int xdim6 = args[6].dat->size[0];
  int ydim6 = args[6].dat->size[1];
  int xdim7 = args[7].dat->size[0];
  int ydim7 = args[7].dat->size[1];

  if (xdim0 != xdim0_advec_cell_kernel3_ydir_h || ydim0 != ydim0_advec_cell_kernel3_ydir_h || xdim1 != xdim1_advec_cell_kernel3_ydir_h || ydim1 != ydim1_advec_cell_kernel3_ydir_h || xdim2 != xdim2_advec_cell_kernel3_ydir_h || ydim2 != ydim2_advec_cell_kernel3_ydir_h || xdim3 != xdim3_advec_cell_kernel3_ydir_h || ydim3 != ydim3_advec_cell_kernel3_ydir_h || xdim4 != xdim4_advec_cell_kernel3_ydir_h || ydim4 != ydim4_advec_cell_kernel3_ydir_h || xdim5 != xdim5_advec_cell_kernel3_ydir_h || ydim5 != ydim5_advec_cell_kernel3_ydir_h || xdim6 != xdim6_advec_cell_kernel3_ydir_h || ydim6 != ydim6_advec_cell_kernel3_ydir_h || xdim7 != xdim7_advec_cell_kernel3_ydir_h || ydim7 != ydim7_advec_cell_kernel3_ydir_h) {
    cudaMemcpyToSymbol( xdim0_advec_cell_kernel3_ydir, &xdim0, sizeof(int) );
    xdim0_advec_cell_kernel3_ydir_h = xdim0;
    cudaMemcpyToSymbol( ydim0_advec_cell_kernel3_ydir, &ydim0, sizeof(int) );
    ydim0_advec_cell_kernel3_ydir_h = ydim0;
    cudaMemcpyToSymbol( xdim1_advec_cell_kernel3_ydir, &xdim1, sizeof(int) );
    xdim1_advec_cell_kernel3_ydir_h = xdim1;
    cudaMemcpyToSymbol( ydim1_advec_cell_kernel3_ydir, &ydim1, sizeof(int) );
    ydim1_advec_cell_kernel3_ydir_h = ydim1;
    cudaMemcpyToSymbol( xdim2_advec_cell_kernel3_ydir, &xdim2, sizeof(int) );
    xdim2_advec_cell_kernel3_ydir_h = xdim2;
    cudaMemcpyToSymbol( ydim2_advec_cell_kernel3_ydir, &ydim2, sizeof(int) );
    ydim2_advec_cell_kernel3_ydir_h = ydim2;
    cudaMemcpyToSymbol( xdim3_advec_cell_kernel3_ydir, &xdim3, sizeof(int) );
    xdim3_advec_cell_kernel3_ydir_h = xdim3;
    cudaMemcpyToSymbol( ydim3_advec_cell_kernel3_ydir, &ydim3, sizeof(int) );
    ydim3_advec_cell_kernel3_ydir_h = ydim3;
    cudaMemcpyToSymbol( xdim4_advec_cell_kernel3_ydir, &xdim4, sizeof(int) );
    xdim4_advec_cell_kernel3_ydir_h = xdim4;
    cudaMemcpyToSymbol( ydim4_advec_cell_kernel3_ydir, &ydim4, sizeof(int) );
    ydim4_advec_cell_kernel3_ydir_h = ydim4;
    cudaMemcpyToSymbol( xdim5_advec_cell_kernel3_ydir, &xdim5, sizeof(int) );
    xdim5_advec_cell_kernel3_ydir_h = xdim5;
    cudaMemcpyToSymbol( ydim5_advec_cell_kernel3_ydir, &ydim5, sizeof(int) );
    ydim5_advec_cell_kernel3_ydir_h = ydim5;
    cudaMemcpyToSymbol( xdim6_advec_cell_kernel3_ydir, &xdim6, sizeof(int) );
    xdim6_advec_cell_kernel3_ydir_h = xdim6;
    cudaMemcpyToSymbol( ydim6_advec_cell_kernel3_ydir, &ydim6, sizeof(int) );
    ydim6_advec_cell_kernel3_ydir_h = ydim6;
    cudaMemcpyToSymbol( xdim7_advec_cell_kernel3_ydir, &xdim7, sizeof(int) );
    xdim7_advec_cell_kernel3_ydir_h = xdim7;
    cudaMemcpyToSymbol( ydim7_advec_cell_kernel3_ydir, &ydim7, sizeof(int) );
    ydim7_advec_cell_kernel3_ydir_h = ydim7;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, (z_size-1)/OPS_block_size_z +1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,OPS_block_size_z);



  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int dat5 = (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int dat6 = (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);
  int dat7 = (OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size);

  char *p_a[8];

  //set up initial pointers
  int base0 = args[0].dat->base_offset + 
           dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    args[0].dat->size[1] *
    (start[2] * args[0].stencil->stride[2]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = args[1].dat->base_offset + 
           dat1 * 1 * (start[0] * args[1].stencil->stride[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    args[1].dat->size[1] *
    (start[2] * args[1].stencil->stride[2]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = args[2].dat->base_offset + 
           dat2 * 1 * (start[0] * args[2].stencil->stride[0]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    args[2].dat->size[1] *
    (start[2] * args[2].stencil->stride[2]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = args[3].dat->base_offset + 
           dat3 * 1 * (start[0] * args[3].stencil->stride[0]);
  base3 = base3+ dat3 *
    args[3].dat->size[0] *
    (start[1] * args[3].stencil->stride[1]);
  base3 = base3+ dat3 *
    args[3].dat->size[0] *
    args[3].dat->size[1] *
    (start[2] * args[3].stencil->stride[2]);
  p_a[3] = (char *)args[3].data_d + base3;

  int base4 = args[4].dat->base_offset + 
           dat4 * 1 * (start[0] * args[4].stencil->stride[0]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    (start[1] * args[4].stencil->stride[1]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    args[4].dat->size[1] *
    (start[2] * args[4].stencil->stride[2]);
  p_a[4] = (char *)args[4].data_d + base4;

  int base5 = args[5].dat->base_offset + 
           dat5 * 1 * (start[0] * args[5].stencil->stride[0]);
  base5 = base5+ dat5 *
    args[5].dat->size[0] *
    (start[1] * args[5].stencil->stride[1]);
  base5 = base5+ dat5 *
    args[5].dat->size[0] *
    args[5].dat->size[1] *
    (start[2] * args[5].stencil->stride[2]);
  p_a[5] = (char *)args[5].data_d + base5;

  int base6 = args[6].dat->base_offset + 
           dat6 * 1 * (start[0] * args[6].stencil->stride[0]);
  base6 = base6+ dat6 *
    args[6].dat->size[0] *
    (start[1] * args[6].stencil->stride[1]);
  base6 = base6+ dat6 *
    args[6].dat->size[0] *
    args[6].dat->size[1] *
    (start[2] * args[6].stencil->stride[2]);
  p_a[6] = (char *)args[6].data_d + base6;

  int base7 = args[7].dat->base_offset + 
           dat7 * 1 * (start[0] * args[7].stencil->stride[0]);
  base7 = base7+ dat7 *
    args[7].dat->size[0] *
    (start[1] * args[7].stencil->stride[1]);
  base7 = base7+ dat7 *
    args[7].dat->size[0] *
    args[7].dat->size[1] *
    (start[2] * args[7].stencil->stride[2]);
  p_a[7] = (char *)args[7].data_d + base7;


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 8);
  ops_halo_exchanges(args,8,range);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[115].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0 && z_size > 0)
    ops_advec_cell_kernel3_ydir<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
           (int *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6], (double *)p_a[7],x_size, y_size, z_size);

  cutilSafeCall(cudaGetLastError());

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[115].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 8);
  ops_set_halo_dirtybit3(&args[6],range);
  ops_set_halo_dirtybit3(&args[7],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[115].mpi_time += t2-t1;
    OPS_kernels[115].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[115].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[115].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[115].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[115].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[115].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[115].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_kernels[115].transfer += ops_compute_transfer(dim, start, end, &arg7);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_advec_cell_kernel3_ydir(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 115;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 115;
  for ( int i=0; i<6; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 8;
  desc->args = (ops_arg*)malloc(8*sizeof(ops_arg));
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
  desc->function = ops_par_loop_advec_cell_kernel3_ydir_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(115,"advec_cell_kernel3_ydir");
  }
  ops_enqueue_kernel(desc);
}
#endif
