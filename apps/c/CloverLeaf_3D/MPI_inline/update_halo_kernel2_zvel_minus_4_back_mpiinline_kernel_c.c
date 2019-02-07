//
// auto-generated by ops.py
//

int xdim0_update_halo_kernel2_zvel_minus_4_back;
int ydim0_update_halo_kernel2_zvel_minus_4_back;
int xdim1_update_halo_kernel2_zvel_minus_4_back;
int ydim1_update_halo_kernel2_zvel_minus_4_back;

#define OPS_ACC0(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim0_update_halo_kernel2_zvel_minus_4_back * 1 +           \
   n_z * xdim0_update_halo_kernel2_zvel_minus_4_back *                         \
       ydim0_update_halo_kernel2_zvel_minus_4_back * 1 +                       \
   x + xdim0_update_halo_kernel2_zvel_minus_4_back * (y) +                     \
   xdim0_update_halo_kernel2_zvel_minus_4_back *                               \
       ydim0_update_halo_kernel2_zvel_minus_4_back * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim1_update_halo_kernel2_zvel_minus_4_back * 1 +           \
   n_z * xdim1_update_halo_kernel2_zvel_minus_4_back *                         \
       ydim1_update_halo_kernel2_zvel_minus_4_back * 1 +                       \
   x + xdim1_update_halo_kernel2_zvel_minus_4_back * (y) +                     \
   xdim1_update_halo_kernel2_zvel_minus_4_back *                               \
       ydim1_update_halo_kernel2_zvel_minus_4_back * (z))

// user function

void update_halo_kernel2_zvel_minus_4_back_c_wrapper(double *restrict zvel0,
                                                     double *restrict zvel1,
                                                     const int *restrict fields,
                                                     int x_size, int y_size,
                                                     int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {

        if (fields[FIELD_ZVEL0] == 1)
          zvel0[OPS_ACC0(0, 0, 0)] = -zvel0[OPS_ACC0(0, 0, 4)];
        if (fields[FIELD_ZVEL1] == 1)
          zvel1[OPS_ACC1(0, 0, 0)] = -zvel1[OPS_ACC1(0, 0, 4)];
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
