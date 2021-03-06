! Open source copyright declaration based on BSD open source template:
! http://www.opensource.org/licenses/bsd-license.php
!
! This file is part of the OPS distribution.
!
! Copyright (c) 2013, Mike Giles and others. Please see the AUTHORS file in
! the main source directory for a full list of copyright holders.
! All rights reserved.
!
! Redistribution and use in source and binary forms, with or without
! modification, are permitted provided that the following conditions are met:
! Redistributions of source code must retain the above copyright
! notice, this list of conditions and the following disclaimer.
! Redistributions in binary form must reproduce the above copyright
! notice, this list of conditions and the following disclaimer in the
! documentation and/or other materials provided with the distribution.
! The name of Mike Giles may not be used to endorse or promote products
! derived from this software without specific prior written permission.
!
! THIS SOFTWARE IS PROVIDED BY Mike Giles ''AS IS'' AND ANY
! EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
! WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
! DISCLAIMED. IN NO EVENT SHALL Mike Giles BE LIABLE FOR ANY
! DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
! (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
! LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
! ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
! (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
! SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
!

! @brief test application for multi-dimensionsl ops_dats functionality
! @author Gihan Mudalige



program MULTIDIM
  use OPS_Fortran_Reference
  use OPS_CONSTANTS
  !use OPS_Fortran_Declarations
  !use OPS_Fortran_RT_Support
  !use MULTIDIM_KERNEL_MODULE
  !use MULTIDIM_PRINT_KERNEL_MODULE
  !use MULTIDIM_COPY_KERNEL_MODULE


  use, intrinsic :: ISO_C_BINDING

  implicit none

  intrinsic :: sqrt, real
  !initialize sizes using global values
  integer x_cells /4/
  integer y_cells /4/

  ! integer references (valid inside the OPS library) for ops_block
  type(ops_block)   :: grid2D

  !ops_dats
  type(ops_dat)     :: dat0, dat1

  ! vars for stencils
  integer s2D_00_arry(2) /0,0/
  type(ops_stencil) :: S2D_00

  !vars for reduction
  real(8) reduct_result
  type(ops_reduction) :: reduct_dat1

  ! vars for halo_depths
  integer d_p(2) /1,1/   !max halo depths for the dat in the possitive direction
  integer d_m(2) /-1,-1/ !max halo depths for the dat in the negative direction

  !size
  integer size(2) /4,4/ !size of the dat -- should be identical to the block on which its define on

  !base
  integer base1(2) /1,1/ ! this is in fortran indexing
  integer base2(2) /1,1/ ! this is in fortran indexing

  !null array
  real(8) temp[allocatable](:)


  ! profiling
  real(kind=c_double) :: startTime = 0
  real(kind=c_double) :: endTime = 0

  !iteration range
  !iterange needs to be fortran indexed here
  ! inclusive indexing for both min and max points in the range
  !.. but internally will convert to c index
  integer iter_range(4) /1,4,1,4/


  !-------------------------- Initialisation --------------------------

  !OPS initialisation
  call ops_init(2)

  !----------------------------OPS Declarations------------------------

  !declare block
  call ops_decl_block(2, grid2D, "grid2D")

  !declare stencils
  call ops_decl_stencil( 2, 1, s2D_00_arry, S2D_00, "00");

  !declare data on blocks
  !declare ops_dat with dim = 2
  call ops_decl_dat(grid2D, 2, size, base1, d_m, d_p, temp,  dat0, "double", "dat0"); ! "double" should be "read(8)"
  call ops_decl_dat(grid2D, 2, size, base2, d_m, d_p, temp,  dat1, "double", "dat1"); ! "double" should be "read(8)"

  !initialize and declare constants
  const1 = 5.44_8
  call ops_decl_const("const1", 1, "double", const1);

  !declare reduction handles
  reduct_result = 0.0_8
  call ops_decl_reduction_handle(8, reduct_dat1, "double", "reduct_dat1");

  !decompose the block
  call ops_partition("2D_BLOCK_DECOMPSE")
  call ops_diagnostic_output()
  ! start timer
  call ops_timers ( startTime )

  call ops_par_loop(multidim_kernel, "multidim_kernel", grid2D, 2, iter_range, &
               & ops_arg_dat(dat0, 2, S2D_00, "real(8)", OPS_WRITE), &
               & ops_arg_idx());

  call ops_par_loop(multidim_copy_kernel, "multidim_copy_kernel", grid2D, 2, iter_range, &
               & ops_arg_dat(dat0, 2, S2D_00, "real(8)", OPS_READ), &
               & ops_arg_dat(dat1, 2, S2D_00, "real(8)", OPS_WRITE));

  !call ops_par_loop(multidim_print_kernel,"multidim_print_kernel", grid2D, 2, iter_range, &
  !             & ops_arg_dat(dat0, 2, S2D_00, "real(8)", OPS_READ));

  call ops_par_loop(multidim_reduce_kernel,"multidim_reduce_kernel", grid2D, 2, iter_range, &
               & ops_arg_dat(dat1, 2, S2D_00, "real(8)", OPS_READ), &
               & ops_arg_reduce(reduct_dat1, 1, "real(8)", OPS_INC));

  !call ops_reduction_result(reduct_dat1, reduct_result)

  !write(*,*) "Reduction result = ", reduct_dat1
  call ops_timers ( endTime )
  call ops_print_dat_to_txtfile(dat1, "multidim.dat");
  call ops_print_dat_to_txtfile(dat0, "multidim.dat");

  !call ops_timing_output (6) ! where is this printing to ? .. problem in what stdout is in fortran
  if (ops_is_root() .eq. 1) then
    write (*,*) 'Max total runtime =', endTime - startTime,'seconds'
  end if

  call ops_exit( )

end program MULTIDIM