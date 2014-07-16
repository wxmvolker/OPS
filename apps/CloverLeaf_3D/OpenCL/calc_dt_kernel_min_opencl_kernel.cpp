//
// auto-generated by ops.py on 2014-07-16 13:13
//


static bool isbuilt_calc_dt_kernel_min = false;

void buildOpenCLKernels_calc_dt_kernel_min(int xdim0, int ydim0) {
  
  if(!isbuilt_calc_dt_kernel_min) {
    buildOpenCLKernels();
    //clSafeCall( clUnloadCompiler() );       
    cl_int ret;
    char* source_filename[1] = {"./OpenCL/calc_dt_kernel_min.cl"};

    // Load the kernel source code into the array source_str
    FILE *fid;
    char *source_str[1];
    size_t source_size[1];

    for(int i=0; i<1; i++) {
      fid = fopen(source_filename[i], "r");
      if (!fid) {
        fprintf(stderr, "Can't open the kernel source file!\n");
        exit(1);
      }
      
      source_str[i] = (char*)malloc(4*0x1000000);
      source_size[i] = fread(source_str[i], 1, 4*0x1000000, fid);
      if(source_size[i] != 4*0x1000000) {
        if (ferror(fid)) {
          printf ("Error while reading kernel source file %s\n", source_filename[i]);
          exit(-1);
        }
        if (feof(fid))
          printf ("Kernel source file %s succesfuly read.\n", source_filename[i]);
          //printf("%s\n",source_str[i]);
      }
      fclose(fid);
    }
    
    printf("Compiling calc_dt_kernel_min source -- start \n");

      // Create a program from the source
      OPS_opencl_core.program = clCreateProgramWithSource(OPS_opencl_core.context, 1, (const char **) &source_str, (const size_t *) &source_size, &ret);
      clSafeCall( ret );

      // Build the program
      char buildOpts[255*2];
      char* pPath = NULL;
      pPath = getenv ("OPS_INSTALL_PATH");
      if (pPath!=NULL)
        sprintf(buildOpts,"-cl-mad-enable -I%s/include -DOPS_WARPSIZE=%d  -Dxdim0_calc_dt_kernel_min=%d -Dydim0_calc_dt_kernel_min=%d", pPath, 32,xdim0, ydim0);
      else {
        sprintf("Incorrect OPS_INSTALL_PATH %s\n",pPath);
        exit(EXIT_FAILURE);
      }
      
      ret = clBuildProgram(OPS_opencl_core.program, 1, &OPS_opencl_core.device_id, buildOpts, NULL, NULL);

      if(ret != CL_SUCCESS) {
        char* build_log;
        size_t log_size;
        clSafeCall( clGetProgramBuildInfo(OPS_opencl_core.program, OPS_opencl_core.device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size) );
        build_log = (char*) malloc(log_size+1);
        clSafeCall( clGetProgramBuildInfo(OPS_opencl_core.program, OPS_opencl_core.device_id, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL) );
        build_log[log_size] = '\0';
        fprintf(stderr, "=============== OpenCL Program Build Info ================\n\n%s", build_log);
        fprintf(stderr, "\n========================================================= \n");
        free(build_log);
        exit(EXIT_FAILURE);
      }
      printf("compiling calc_dt_kernel_min -- done\n");

    // Create the OpenCL kernel
    OPS_opencl_core.kernel[127] = clCreateKernel(OPS_opencl_core.program, "ops_calc_dt_kernel_min", &ret);
    clSafeCall( ret );
      
    isbuilt_calc_dt_kernel_min = true;
  }
  
}  


// host stub function
void ops_par_loop_calc_dt_kernel_min(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {
  ops_arg args[2] = { arg0, arg1};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start_add[3];
  int end_add[3];
  for ( int n=0; n<3; n++ ){
    start_add[n] = sb->istart[n];end_add[n] = sb->iend[n]+1;
    if (start_add[n] >= range[2*n]) {
      start_add[n] = 0;
    }
    else {
      start_add[n] = range[2*n] - start_add[n];
    }
    if (end_add[n] >= range[2*n+1]) {
      end_add[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end_add[n] = sb->sizes[n];
    }
  }


  int x_size = MAX(0,end_add[0]-start_add[0]);
  int y_size = MAX(0,end_add[1]-start_add[1]);
  int z_size = MAX(0,end_add[2]-start_add[2]);

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  int ydim0 = args[0].dat->block_size[1];

  //build opencl kernel if not already built

  buildOpenCLKernels_calc_dt_kernel_min(
  xdim0, ydim0);

  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(127,"calc_dt_kernel_min");
  ops_timers_core(&c2,&t2);

  //set up OpenCL thread blocks
  size_t globalWorkSize[3] = {((x_size-1)/OPS_block_size_x+ 1)*OPS_block_size_x, ((y_size-1)/OPS_block_size_y + 1)*OPS_block_size_y, z_size};
  size_t localWorkSize[3] =  {OPS_block_size_x,OPS_block_size_y,1};


  double *arg1h = (double *)arg1.data;
  int nblocks = ((x_size-1)/OPS_block_size_x+ 1)*((y_size-1)/OPS_block_size_y + 1)*z_size;
  int maxblocks = nblocks;
  int reduct_bytes = 0;

  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  int r_bytes1 = reduct_bytes/sizeof(double);
  arg1.data = OPS_reduct_h + reduct_bytes;
  arg1.data_d = OPS_reduct_d;// + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg1.data)[d+b*1] = INFINITY_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);
  int dat0 = args[0].dat->size;

  //set up initial pointers
  int base0 = 1 * 
  (start_add[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0 + args[0].dat->block_size[0] *
  (start_add[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0 + args[0].dat->block_size[1] *  args[0].dat->block_size[1] *
  (start_add[2] * args[0].stencil->stride[2] - args[0].dat->offset[2]);


  ops_H_D_exchanges_cuda(args, 2);

  ops_timers_core(&c1,&t1);
  OPS_kernels[127].mpi_time += t1-t2;

  int nthread = OPS_block_size_x*OPS_block_size_y;


  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[127], 0, sizeof(cl_mem), (void*) &arg0.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[127], 1, sizeof(cl_mem), (void*) &arg1.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[127], 2, nthread*sizeof(double), NULL));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[127], 3, sizeof(cl_int), (void*) &r_bytes1 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[127], 4, sizeof(cl_int), (void*) &base0 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[127], 5, sizeof(cl_int), (void*) &x_size ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[127], 6, sizeof(cl_int), (void*) &y_size ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[127], 7, sizeof(cl_int), (void*) &z_size ));

  //call/enque opencl kernel wrapper function
  clSafeCall( clEnqueueNDRangeKernel(OPS_opencl_core.command_queue, OPS_opencl_core.kernel[127], 3, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL) );
  if (OPS_diags>1) {
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg1h[d] = MIN(arg1h[d],((double *)arg1.data)[d+b*1]);
    }
  }
  arg1.data = (char *)arg1h;

  ops_set_dirtybit_opencl(args, 2);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[127].count++;
  OPS_kernels[127].time += t2-t1;
  OPS_kernels[127].transfer += ops_compute_transfer(dim, range, &arg0);
}
