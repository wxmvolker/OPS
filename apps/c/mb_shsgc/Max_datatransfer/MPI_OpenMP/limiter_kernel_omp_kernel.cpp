//
// auto-generated by ops.py
//
#define OPS_ACC_MD0(d, x) ((x)*3 + (d))
#define OPS_ACC_MD1(d, x) ((x)*3 + (d))
#define OPS_ACC_MD2(d, x) ((x)*3 + (d))
#ifdef _OPENMP
#include <omp.h>
#endif

// user function
inline void limiter_kernel(const double *al, double *tht, double *gt) {

  double aalm, aal, all, ar, gtt;
  for (int m = 0; m < 3; m++) {
    aalm = fabs(al[OPS_ACC_MD0(m, -1)]);
    aal = fabs(al[OPS_ACC_MD0(m, 0)]);
    tht[OPS_ACC_MD1(m, 0)] = fabs(aal - aalm) / (aal + aalm + del2);
    all = al[OPS_ACC_MD0(m, -1)];
    ar = al[OPS_ACC_MD0(m, 0)];
    gtt = all * (ar * ar + del2) + ar * (all * all + del2);
    gt[OPS_ACC_MD2(m, 0)] = gtt / (ar * ar + all * all + 2.00 * del2);
  }
}

#undef OPS_ACC_MD0
#undef OPS_ACC_MD1
#undef OPS_ACC_MD2

// host stub function
void ops_par_loop_limiter_kernel(char const *name, ops_block block, int dim,
                                 int *range, ops_arg arg0, ops_arg arg1,
                                 ops_arg arg2) {

  // Timing
  double t1, t2, c1, c2;

  int offs[3][1];
  ops_arg args[3] = {arg0, arg1, arg2};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 3, range, 8))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(8, "limiter_kernel");
    OPS_kernels[8].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute locally allocated range for the sub-block

  int start[1];
  int end[1];

#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 1; n++) {
    start[n] = sb->decomp_disp[n];
    end[n] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (start[n] >= range[2 * n]) {
      start[n] = 0;
    } else {
      start[n] = range[2 * n] - start[n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      start[n] = range[2 * n];
    if (end[n] >= range[2 * n + 1]) {
      end[n] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      end[n] += (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else
  for (int n = 0; n < 1; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif
#ifdef OPS_DEBUG
  ops_register_args(args, "limiter_kernel");
#endif

  offs[0][0] = args[0].stencil->stride[0] * 1; // unit step in x dimension

  offs[1][0] = args[1].stencil->stride[0] * 1; // unit step in x dimension

  offs[2][0] = args[2].stencil->stride[0] * 1; // unit step in x dimension

  int off0_0 = offs[0][0];
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int off1_0 = offs[1][0];
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int off2_0 = offs[2][0];
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);

  // Halo Exchanges
  ops_H_D_exchanges_host(args, 3);
  ops_halo_exchanges(args, 3, range);
  ops_H_D_exchanges_host(args, 3);

#ifdef _OPENMP
  int nthreads = omp_get_max_threads();
#else
  int nthreads = 1;
#endif
  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];
  xdim2 = args[2].dat->size[0];

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[8].mpi_time += t2 - t1;
  }

#pragma omp parallel for
  for (int thr = 0; thr < nthreads; thr++) {

    int x_size = end[0] - start[0];
    char *p_a[3];

    int start_i = start[0] + ((x_size - 1) / nthreads + 1) * thr;
    int finish_i =
        start[0] + MIN(((x_size - 1) / nthreads + 1) * (thr + 1), x_size);

    // get address per thread
    int start0 = start_i;

    // set up initial pointers
    int d_m[OPS_MAX_DIM];
#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[0].dat->d_m[d];
#endif
    int base0 = dat0 * 1 * (start0 * args[0].stencil->stride[0] -
                            args[0].dat->base[0] - d_m[0]);
    p_a[0] = (char *)args[0].data + base0;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[1].dat->d_m[d];
#endif
    int base1 = dat1 * 1 * (start0 * args[1].stencil->stride[0] -
                            args[1].dat->base[0] - d_m[0]);
    p_a[1] = (char *)args[1].data + base1;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[2].dat->d_m[d];
#endif
    int base2 = dat2 * 1 * (start0 * args[2].stencil->stride[0] -
                            args[2].dat->base[0] - d_m[0]);
    p_a[2] = (char *)args[2].data + base2;

    for (int n_x = start_i; n_x < start_i + (finish_i - start_i) / SIMD_VEC;
         n_x++) {
// call kernel function, passing in pointers to data -vectorised
#pragma simd
      for (int i = 0; i < SIMD_VEC; i++) {
        limiter_kernel((const double *)p_a[0] + i * 1 * 3,
                       (double *)p_a[1] + i * 1 * 3,
                       (double *)p_a[2] + i * 1 * 3);
      }

      // shift pointers to data x direction
      p_a[0] = p_a[0] + (dat0 * off0_0) * SIMD_VEC;
      p_a[1] = p_a[1] + (dat1 * off1_0) * SIMD_VEC;
      p_a[2] = p_a[2] + (dat2 * off2_0) * SIMD_VEC;
    }

    for (int n_x = start_i + ((finish_i - start_i) / SIMD_VEC) * SIMD_VEC;
         n_x < finish_i; n_x++) {
      // call kernel function, passing in pointers to data - remainder
      limiter_kernel((const double *)p_a[0], (double *)p_a[1],
                     (double *)p_a[2]);

      // shift pointers to data x direction
      p_a[0] = p_a[0] + (dat0 * off0_0);
      p_a[1] = p_a[1] + (dat1 * off1_0);
      p_a[2] = p_a[2] + (dat2 * off2_0);
    }
  }

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[8].time += t1 - t2;
  }

  ops_set_dirtybit_host(args, 3);

  ops_set_halo_dirtybit3(&args[1], range);
  ops_set_halo_dirtybit3(&args[2], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[8].mpi_time += t2 - t1;
    OPS_kernels[8].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[8].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[8].transfer += ops_compute_transfer(dim, start, end, &arg2);
  }
}
