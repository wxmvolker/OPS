//
// auto-generated by ops.py
//
#define OPS_ACC0(x,y) (n_x*1+n_y*xdim0_generate_chunk_kernel*0+x+xdim0_generate_chunk_kernel*(y))
#define OPS_ACC1(x,y) (n_x*0+n_y*xdim1_generate_chunk_kernel*1+x+xdim1_generate_chunk_kernel*(y))
#define OPS_ACC2(x,y) (n_x*1+n_y*xdim2_generate_chunk_kernel*1+x+xdim2_generate_chunk_kernel*(y))
#define OPS_ACC3(x,y) (n_x*1+n_y*xdim3_generate_chunk_kernel*1+x+xdim3_generate_chunk_kernel*(y))
#define OPS_ACC4(x,y) (n_x*1+n_y*xdim4_generate_chunk_kernel*1+x+xdim4_generate_chunk_kernel*(y))
#define OPS_ACC5(x,y) (n_x*1+n_y*xdim5_generate_chunk_kernel*1+x+xdim5_generate_chunk_kernel*(y))
#define OPS_ACC6(x,y) (n_x*1+n_y*xdim6_generate_chunk_kernel*0+x+xdim6_generate_chunk_kernel*(y))
#define OPS_ACC7(x,y) (n_x*0+n_y*xdim7_generate_chunk_kernel*1+x+xdim7_generate_chunk_kernel*(y))


//user function

// host stub function
void ops_par_loop_generate_chunk_kernel_execute(ops_kernel_descriptor *desc) {
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
  ops_arg arg7 = desc->args[7];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,8,range,42)) return;
  #endif

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "generate_chunk_kernel");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  const double * __restrict__ vertexx = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  const double * __restrict__ vertexy = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  double * __restrict__ energy0 = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  double * __restrict__ density0 = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  double * __restrict__ xvel0 = (double *)(args[4].data + base4);

  int base5 = args[5].dat->base_offset;
  double * __restrict__ yvel0 = (double *)(args[5].data + base5);

  int base6 = args[6].dat->base_offset;
  const double * __restrict__ cellx = (double *)(args[6].data + base6);

  int base7 = args[7].dat->base_offset;
  const double * __restrict__ celly = (double *)(args[7].data + base7);


  //initialize global variable with the dimension of dats
  int xdim0_generate_chunk_kernel = args[0].dat->size[0];
  int xdim1_generate_chunk_kernel = args[1].dat->size[0];
  int xdim2_generate_chunk_kernel = args[2].dat->size[0];
  int xdim3_generate_chunk_kernel = args[3].dat->size[0];
  int xdim4_generate_chunk_kernel = args[4].dat->size[0];
  int xdim5_generate_chunk_kernel = args[5].dat->size[0];
  int xdim6_generate_chunk_kernel = args[6].dat->size[0];
  int xdim7_generate_chunk_kernel = args[7].dat->size[0];

  #pragma omp parallel for
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #pragma omp simd
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      

  double radius, x_cent, y_cent;
  int is_in = 0;
  int is_in2 = 0;


  energy0[OPS_ACC2(0,0)]= states[0].energy;
  density0[OPS_ACC3(0,0)]= states[0].density;
  xvel0[OPS_ACC4(0,0)]=states[0].xvel;
  yvel0[OPS_ACC5(0,0)]=states[0].yvel;

  for(int i = 1; i<number_of_states; i++) {

    x_cent=states[i].xmin;
    y_cent=states[i].ymin;
    is_in = 0;
    is_in2 = 0;

    if (states[i].geometry == g_rect) {
      for (int i1 = -1; i1 <= 0; i1++) {
        for (int j1 = -1; j1 <= 0; j1++) {
          if(vertexx[OPS_ACC0(1+i1,0)] >= states[i].xmin  && vertexx[OPS_ACC0(0+i1,0)] < states[i].xmax) {
            if(vertexy[OPS_ACC1(0,1+j1)] >= states[i].ymin && vertexy[OPS_ACC1(0,0+j1)] < states[i].ymax) {
              is_in = 1;
            }
          }
        }
      }
      if(vertexx[OPS_ACC0(1,0)] >= states[i].xmin  && vertexx[OPS_ACC0(0,0)] < states[i].xmax) {
        if(vertexy[OPS_ACC1(0,1)] >= states[i].ymin && vertexy[OPS_ACC1(0,0)] < states[i].ymax) {
          is_in2 = 1;
        }
      }
      if (is_in2) {
        energy0[OPS_ACC2(0,0)] = states[i].energy;
        density0[OPS_ACC3(0,0)] = states[i].density;
      }
      if (is_in) {
        xvel0[OPS_ACC4(0,0)] = states[i].xvel;
        yvel0[OPS_ACC5(0,0)] = states[i].yvel;
      }
    }
    else if(states[i].geometry == g_circ) {
      for (int i1 = -1; i1 <= 0; i1++) {
        for (int j1 = -1; j1 <= 0; j1++) {
          radius = sqrt ((cellx[OPS_ACC6(i1,0)] - x_cent) * (cellx[OPS_ACC6(i1,0)] - x_cent) +
                     (celly[OPS_ACC7(0,j1)] - y_cent) * (celly[OPS_ACC7(0,j1)] - y_cent));
          if (radius <= states[i].radius) {
            is_in = 1;
          }
        }
      }
      if (radius <= states[i].radius) is_in2 = 1;

      if (is_in2) {
        energy0[OPS_ACC2(0,0)] = states[i].energy;
        density0[OPS_ACC3(0,0)] = states[i].density;
      }

      if (is_in) {
        xvel0[OPS_ACC4(0,0)] = states[i].xvel;
        yvel0[OPS_ACC5(0,0)] = states[i].yvel;
      }
    }
    else if(states[i].geometry == g_point) {
      for (int i1 = -1; i1 <= 0; i1++) {
        for (int j1 = -1; j1 <= 0; j1++) {
          if(vertexx[OPS_ACC0(i1,0)] == x_cent && vertexy[OPS_ACC1(0,j1)] == y_cent) {
            is_in = 1;
          }
        }
      }
      if(vertexx[OPS_ACC0(0,0)] == x_cent && vertexy[OPS_ACC1(0,0)] == y_cent)
        is_in2 = 1;

      if (is_in2) {
        energy0[OPS_ACC2(0,0)] = states[i].energy;
        density0[OPS_ACC3(0,0)] = states[i].density;
      }

      if (is_in) {
        xvel0[OPS_ACC4(0,0)] = states[i].xvel;
        yvel0[OPS_ACC5(0,0)] = states[i].yvel;
      }
    }
  }

    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7


void ops_par_loop_generate_chunk_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 42;
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
    desc->range[2*n] = sb->decomp_disp[n];desc->range[2*n+1] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (desc->range[2*n] >= range[2*n]) {
      desc->range[2*n] = 0;
    }
    else {
      desc->range[2*n] = range[2*n] - desc->range[2*n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) desc->range[2*n] = range[2*n];
    if (desc->range[2*n+1] >= range[2*n+1]) {
      desc->range[2*n+1] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      desc->range[2*n+1] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      desc->range[2*n+1] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
  }
  #endif //OPS_MPI
  desc->nargs = 8;
  desc->args = (ops_arg*)malloc(8*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->args[1] = arg1;
  desc->args[2] = arg2;
  desc->args[3] = arg3;
  desc->args[4] = arg4;
  desc->args[5] = arg5;
  desc->args[6] = arg6;
  desc->args[7] = arg7;
  desc->function = ops_par_loop_generate_chunk_kernel_execute;
  ops_enqueue_kernel(desc);
  }
