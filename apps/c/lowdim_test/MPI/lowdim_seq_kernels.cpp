//
// auto-generated by ops.py//

//header
#define OPS_3D
#define OPS_ACC_MD_MACROS
#include "ops_lib_cpp.h"
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif

// global constants

void ops_init_backend() {}

//user kernel files
#include "set_val_seq_kernel.cpp"
#include "calc_seq_kernel.cpp"
