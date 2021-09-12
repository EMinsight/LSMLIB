/*
 * Test program 1D homogeneous Neumann BCs using ENO1 discretization
 *
 * ---------------------------------------------------------------------
 * COPYRIGHT/LICENSE. This file is part of the LSMLIB package. It is
 * subject to the license terms in the LICENSE file found in the
 * top-level directory of this distribution. No part of the LSMLIB
 * package, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the
 * LICENSE file.
 * ---------------------------------------------------------------------
 */

#include "gtest/gtest.h"

#include "lsmlib_config.h"
#include "lsm_boundary_conditions1d.h"
#include "lsm_spatial_derivatives1d.h"


/************************************************************************
 * Helper function declarations
 ************************************************************************/
#define DIM (1)

/*
 * Test fixtures
 */
class LSMBoundaryConditions1DTest : public ::testing::Test {
  protected:
    // Data members

    LSMLIB_REAL *phi;
    LSMLIB_REAL *phi_x_plus;
    LSMLIB_REAL *phi_x_minus;
    LSMLIB_REAL *D1;
    int ghostcell_width = 3;
    int box_lower[DIM];
    int box_upper[DIM];
    int box_dims[DIM];
    int ghostbox_lower[DIM];
    int ghostbox_upper[DIM];
    int ghostbox_dims[DIM];
    LSMLIB_REAL dx;

    // Constructor
    LSMBoundaryConditions1DTest(){
        // set index space extents
        box_dims[0] = 25;
        box_lower[0] = 0;
        box_upper[0] = box_dims[0]-1;
        ghostbox_lower[0] = box_lower[0] - ghostcell_width;
        ghostbox_upper[0] = box_upper[0] + ghostcell_width;
        ghostbox_dims[0] = ghostbox_upper[0] - ghostbox_lower[0] + 1;

        // set grid spacing
        dx = 1.0/box_dims[0];

        // allocate memory for data
        phi         = new LSMLIB_REAL[ghostbox_dims[0]];
        phi_x_plus  = new LSMLIB_REAL[ghostbox_dims[0]];
        phi_x_minus = new LSMLIB_REAL[ghostbox_dims[0]];
        D1          = new LSMLIB_REAL[ghostbox_dims[0]];

        // set phi data in interior
        for (int i = 0; i < box_dims[0]; i++) {
            int idx = i+ghostcell_width;
            LSMLIB_REAL x = (i+0.5)*dx;
            phi[idx] = (x-0.25)*(x-0.25);
        }
    }

    // Destructor
    ~LSMBoundaryConditions1DTest(){
        // free heap memory
        delete[] phi;
        delete[] phi_x_plus;
        delete[] phi_x_minus;
        delete[] D1;
    }
};

/*
 * Tests
 */
TEST_F(LSMBoundaryConditions1DTest, ENO1) {
    // impose homogeneous Neumann boundary conditions
    int bdry_location_idx = 0;
    LSM1D_HOMOGENEOUS_NEUMANN_ENO1(
        phi,
        &ghostbox_lower[0],
        &ghostbox_upper[0],
        &box_lower[0],
        &box_upper[0],
        &bdry_location_idx);

    bdry_location_idx = 1;
    LSM1D_HOMOGENEOUS_NEUMANN_ENO1(
        phi,
        &ghostbox_lower[0],
        &ghostbox_upper[0],
        &box_lower[0],
        &box_upper[0],
        &bdry_location_idx);

    // compute spatial derivatives using ENO1
    LSM1D_HJ_ENO1(
        phi_x_plus,
        &ghostbox_lower[0],
        &ghostbox_upper[0],
        phi_x_minus,
        &ghostbox_lower[0],
        &ghostbox_upper[0],
        phi,
        &ghostbox_lower[0],
        &ghostbox_upper[0],
        D1,
        &ghostbox_lower[0],
        &ghostbox_upper[0],
        &box_lower[0],
        &box_upper[0],
        &dx);

    /*
     * check that derivatives normal to faces of computational domain are 0.
     */

    // x-lower
    LSMLIB_REAL err_x_lower = fabs(phi_x_minus[box_lower[0]+ghostcell_width]);
    EXPECT_NEAR(err_x_lower, 0, 1e-6);

    // x-upper
    LSMLIB_REAL err_x_upper = fabs(phi_x_plus[box_upper[0]+ghostcell_width]);
    EXPECT_NEAR(err_x_upper, 0, 1e-6);
}
