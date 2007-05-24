/*
 * File:        lsm_spatial_derivatives2d.h
 * Copyright:   (c) 2005-2006 Kevin T. Chu
 * Revision:    $Revision: 1.19 $
 * Modified:    $Date: 2006/10/28 01:48:58 $
 * Description: Header file for Fortran 77 2D ENO/WENO routines.
 */

#ifndef INCLUDED_LSM_SPATIAL_DERIVATIVES_2D_H
#define INCLUDED_LSM_SPATIAL_DERIVATIVES_2D_H

#ifdef __cplusplus
extern "C" {
#endif

/*! \file lsm_spatial_derivatives2d.h
 *
 * \brief
 * @ref lsm_spatial_derivatives2d.h provides support for computing spatial
 * derivatives in two space dimensions using high-order ENO and WENO 
 * discretizations.  
 *
 */


/* Link between C/C++ and Fortran function names 
 *
 *      name in                      name in
 *      C/C++ code                   Fortran code
 *      ----------                   ------------
 */
#define LSM2D_HJ_ENO1                lsm2dhjeno1_
#define LSM2D_HJ_ENO2                lsm2dhjeno2_
#define LSM2D_HJ_ENO3                lsm2dhjeno3_
#define LSM2D_HJ_WENO5               lsm2dhjweno5_
#define LSM2D_UPWIND_HJ_ENO1         lsm2dupwindhjeno1_
#define LSM2D_UPWIND_HJ_ENO2         lsm2dupwindhjeno2_
#define LSM2D_UPWIND_HJ_ENO3         lsm2dupwindhjeno3_
#define LSM2D_UPWIND_HJ_WENO5        lsm2dupwindhjweno5_
#define LSM2D_CENTRAL_GRAD_ORDER2    lsm2dcentralgradorder2_
#define LSM2D_CENTRAL_GRAD_ORDER4    lsm2dcentralgradorder4_
#define LSM2D_LAPLACIAN_ORDER2       lsm2dlaplacianorder2_
#define LSM2D_PHI_UPWIND_GRAD_F      lsm2dphiupwindgradf_
#define LSM2D_AVERAGE_GRAD_PHI       lsm2daveragegradphi_


/*!
 * LSM2D_HJ_ENO1() computes the forward (plus) and backward (minus)
 * first-order Hamilton-Jacobi ENO approximations to the gradient of
 * \f$ \phi \f$.
 *           
 * Arguments:
 *  - phi_*_plus (out):   components of \f$ \nabla \phi \f$ in plus direction
 *  - phi_*_minus (out):  components of \f$ \nabla \phi \f$ in minus direction
 *  - phi (in):           \f$ \phi \f$
 *  - D1 (in):            scratch space for holding undivided first-differences
 *  - dx, dy (in):        grid spacing
 *  - *_gb (in):          index range for ghostbox
 *  - *_fb (in):          index range for fillbox
 *      
 * Return value:          none
 *
 * NOTES:
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 *  - phi_x_plus and phi_x_minus are face-centered data (i.e. their
 *    indices are of the form (i+1/2) and (i-1/2)).  For phi_x_plus,
 *    the data array position corresponding to the (i+1/2) is i (i.e. 
 *    the index shifted down to the nearest integer index).  For 
 *    phi_x_minus, the data array position corresponding to the (i-1/2) 
 *    is i (i.e.  the index shifted up to the nearest integer index).  
 *    Analogous conventions hold for phi_y_plus and phi_y_minus.
 *  - it is assumed that BOTH the plus AND minus derivatives have
 *    the same fillbox
 *
 */
void LSM2D_HJ_ENO1(
  double *phi_x_plus,
  double *phi_y_plus,
  const int *ilo_grad_phi_plus_gb,
  const int *ihi_grad_phi_plus_gb,
  const int *jlo_grad_phi_plus_gb,
  const int *jhi_grad_phi_plus_gb,
  double *phi_x_minus,
  double *phi_y_minus,
  const int *ilo_grad_phi_minus_gb,
  const int *ihi_grad_phi_minus_gb,
  const int *jlo_grad_phi_minus_gb,
  const int *jhi_grad_phi_minus_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  double *D1,
  const int *ilo_D1_gb,
  const int *ihi_D1_gb,
  const int *jlo_D1_gb,
  const int *jhi_D1_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*!
 * LSM2D_HJ_ENO2() computes the forward (plus) and backward (minus)
 * second-order Hamilton-Jacobi ENO approximations to the gradient of
 * \f$ \phi \f$.
 *           
 * Arguments:
 *  - phi_*_plus (out):   components of \f$ \nabla \phi \f$ in plus direction
 *  - phi_*_minus (out):  components of \f$ \nabla \phi \f$ in minus direction
 *  - phi (in):           \f$ \phi \f$
 *  - D1 (in):            scratch space for holding undivided first-differences
 *  - D2 (in):            scratch space for holding undivided 
 *                        second-differences
 *  - dx, dy (in):        grid spacing
 *  - *_gb (in):          index range for ghostbox
 *  - *_fb (in):          index range for fillbox
 *      
 * Return value:          none
 *
 * NOTES:
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 *  - phi_x_plus and phi_x_minus are face-centered data (i.e. their
 *    indices are of the form (i+1/2) and (i-1/2)).  For phi_x_plus,
 *    the data array position corresponding to the (i+1/2) is i (i.e. 
 *    the index shifted down to the nearest integer index).  For 
 *    phi_x_minus, the data array position corresponding to the (i-1/2) 
 *    is i (i.e.  the index shifted up to the nearest integer index).  
 *    Analogous conventions hold for phi_y_plus and phi_y_minus.
 *  - it is assumed that BOTH the plus AND minus derivatives have
 *    the same fillbox
 *
 */
void LSM2D_HJ_ENO2(
  double *phi_x_plus,
  double *phi_y_plus,
  const int *ilo_grad_phi_plus_gb,
  const int *ihi_grad_phi_plus_gb,
  const int *jlo_grad_phi_plus_gb,
  const int *jhi_grad_phi_plus_gb,
  double *phi_x_minus,
  double *phi_y_minus,
  const int *ilo_grad_phi_minus_gb,
  const int *ihi_grad_phi_minus_gb,
  const int *jlo_grad_phi_minus_gb,
  const int *jhi_grad_phi_minus_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  double *D1,
  const int *ilo_D1_gb,
  const int *ihi_D1_gb,
  const int *jlo_D1_gb,
  const int *jhi_D1_gb,
  double *D2,
  const int *ilo_D2_gb,
  const int *ihi_D2_gb,
  const int *jlo_D2_gb,
  const int *jhi_D2_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*!
 * LSM2D_HJ_ENO3() computes the forward (plus) and backward (minus)
 * third-order Hamilton-Jacobi ENO approximations to the gradient of
 * \f$ \phi \f$.
 *           
 * Arguments:
 *  - phi_*_plus (out):   components of \f$ \nabla \phi \f$ in plus direction
 *  - phi_*_minus (out):  components of \f$ \nabla \phi \f$ in minus direction
 *  - phi (in):           \f$ \phi \f$
 *  - D1 (in):            scratch space for holding undivided first-differences
 *  - D2 (in):            scratch space for holding undivided 
 *                        second-differences
 *  - D3 (in):            scratch space for holding undivided third-differences
 *  - dx, dy (in):        grid spacing
 *  - *_gb (in):          index range for ghostbox
 *  - *_fb (in):          index range for fillbox
 *      
 * Return value:          none
 *
 * NOTES:
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 *  - phi_x_plus and phi_x_minus are face-centered data (i.e. their
 *    indices are of the form (i+1/2) and (i-1/2)).  For phi_x_plus,
 *    the data array position corresponding to the (i+1/2) is i (i.e. 
 *    the index shifted down to the nearest integer index).  For 
 *    phi_x_minus, the data array position corresponding to the (i-1/2) 
 *    is i (i.e.  the index shifted up to the nearest integer index).  
 *    Analogous conventions hold for phi_y_plus and phi_y_minus.
 *  - it is assumed that BOTH the plus AND minus derivatives have
 *    the same fillbox
 *
 */
void LSM2D_HJ_ENO3(
  double *phi_x_plus,
  double *phi_y_plus,
  const int *ilo_grad_phi_plus_gb,
  const int *ihi_grad_phi_plus_gb,
  const int *jlo_grad_phi_plus_gb,
  const int *jhi_grad_phi_plus_gb,
  double *phi_x_minus,
  double *phi_y_minus,
  const int *ilo_grad_phi_minus_gb,
  const int *ihi_grad_phi_minus_gb,
  const int *jlo_grad_phi_minus_gb,
  const int *jhi_grad_phi_minus_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  double *D1,
  const int *ilo_D1_gb,
  const int *ihi_D1_gb,
  const int *jlo_D1_gb,
  const int *jhi_D1_gb,
  double *D2,
  const int *ilo_D2_gb,
  const int *ihi_D2_gb,
  const int *jlo_D2_gb,
  const int *jhi_D2_gb,
  double *D3,
  const int *ilo_D3_gb,
  const int *ihi_D3_gb,
  const int *jlo_D3_gb,
  const int *jhi_D3_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*!
 * LSM2D_HJ_WENO5() computes the forward (plus) and backward (minus)
 * fifth-order Hamilton-Jacobi WENO approximations to the gradient of
 * \f$ \phi \f$.
 *           
 * Arguments:
 *  - phi_*_plus (out):   components of \f$ \nabla \phi \f$ in plus direction
 *  - phi_*_minus (out):  components of \f$ \nabla \phi \f$ in minus direction
 *  - phi (in):           \f$ \phi \f$
 *  - D1 (in):            scratch space for holding undivided first-differences
 *  - dx, dy (in):        grid spacing
 *  - *_gb (in):          index range for ghostbox
 *  - *_fb (in):          index range for fillbox
 *      
 * Return value:          none
 *
 * NOTES:
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 *  - phi_x_plus and phi_x_minus are face-centered data (i.e. their
 *    indices are of the form (i+1/2) and (i-1/2)).  For phi_x_plus,
 *    the data array position corresponding to the (i+1/2) is i (i.e. 
 *    the index shifted down to the nearest integer index).  For 
 *    phi_x_minus, the data array position corresponding to the (i-1/2) 
 *    is i (i.e.  the index shifted up to the nearest integer index).  
 *    Analogous conventions hold for phi_y_plus and phi_y_minus.
 *  - it is assumed that BOTH the plus AND minus derivatives have
 *    the same fillbox
 *
 */
void LSM2D_HJ_WENO5(
  double *phi_x_plus,
  double *phi_y_plus,
  const int *ilo_grad_phi_plus_gb,
  const int *ihi_grad_phi_plus_gb,
  const int *jlo_grad_phi_plus_gb,
  const int *jhi_grad_phi_plus_gb,
  double *phi_x_minus,
  double *phi_y_minus,
  const int *ilo_grad_phi_minus_gb,
  const int *ihi_grad_phi_minus_gb,
  const int *jlo_grad_phi_minus_gb,
  const int *jhi_grad_phi_minus_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  double *D1,
  const int *ilo_D1_gb,
  const int *ihi_D1_gb,
  const int *jlo_D1_gb,
  const int *jhi_D1_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*! 
 * LSM2D_UPWIND_HJ_ENO1() computes the first-order Hamilton-Jacobi ENO
 * upwind approximation to the gradient of \f$ \phi \f$.
 * 
 * Arguments:
 *  - phi_* (out):  components of \f$ \nabla \phi \f$
 *  - phi (in):     \f$ \phi \f$
 *  - vel_* (in):   components of the velocity 
 *  - D1 (in):      scratch space for holding undivided first-differences
 *  - dx, dy (in):  grid cell size
 *  - *_gb (in):    index range for ghostbox
 *  - *_fb (in):    index range for fillbox
 *
 * Return value:    none
 *
 * NOTES:
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 */
void LSM2D_UPWIND_HJ_ENO1(
  double *phi_x,
  double *phi_y,
  const int *ilo_grad_phi_gb,
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb,
  const int *jhi_grad_phi_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  const double *vel_x,
  const double *vel_y,
  const int *ilo_vel_gb,
  const int *ihi_vel_gb,
  const int *jlo_vel_gb,
  const int *jhi_vel_gb,
  double *D1,
  const int *ilo_D1_gb,
  const int *ihi_D1_gb,
  const int *jlo_D1_gb,
  const int *jhi_D1_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*! 
 * LSM2D_UPWIND_HJ_ENO2() computes the second-order Hamilton-Jacobi ENO
 * upwind approximation to the gradient of \f$ \phi \f$.
 * 
 * Arguments:
 *  - phi_* (out):  components of \f$ \nabla \phi \f$
 *  - phi (in):     \f$ \phi \f$
 *  - vel_* (in):   components of the velocity 
 *  - D1 (in):      scratch space for holding undivided first-differences
 *  - D2 (in):      scratch space for holding undivided second-differences
 *  - dx, dy (in):  grid cell size
 *  - *_gb (in):    index range for ghostbox
 *  - *_fb (in):    index range for fillbox
 *
 * Return value:    none
 *
 * NOTES:
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 */
void LSM2D_UPWIND_HJ_ENO2(
  double *phi_x,
  double *phi_y,
  const int *ilo_grad_phi_gb,
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb,
  const int *jhi_grad_phi_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  const double *vel_x,
  const double *vel_y,
  const int *ilo_vel_gb,
  const int *ihi_vel_gb,
  const int *jlo_vel_gb,
  const int *jhi_vel_gb,
  double *D1,
  const int *ilo_D1_gb,
  const int *ihi_D1_gb,
  const int *jlo_D1_gb,
  const int *jhi_D1_gb,
  double *D2,
  const int *ilo_D2_gb,
  const int *ihi_D2_gb,
  const int *jlo_D2_gb,
  const int *jhi_D2_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*! 
 * LSM2D_UPWIND_HJ_ENO3() computes the third-order Hamilton-Jacobi ENO
 * upwind approximation to the gradient of \f$ \phi \f$.
 * 
 * Arguments:
 *  - phi_* (out):  components of \f$ \nabla \phi \f$
 *  - phi (in):     \f$ \phi \f$
 *  - vel_* (in):   components of the velocity 
 *  - D1 (in):      scratch space for holding undivided first-differences
 *  - D2 (in):      scratch space for holding undivided second-differences
 *  - D3 (in):      scratch space for holding undivided third-differences
 *  - dx, dy (in):  grid cell size
 *  - *_gb (in):    index range for ghostbox
 *  - *_fb (in):    index range for fillbox
 *
 * Return value:    none
 *
 * NOTES:
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 */
void LSM2D_UPWIND_HJ_ENO3(
  double *phi_x,
  double *phi_y,
  const int *ilo_grad_phi_gb,
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb,
  const int *jhi_grad_phi_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  const double *vel_x,
  const double *vel_y,
  const int *ilo_vel_gb,
  const int *ihi_vel_gb,
  const int *jlo_vel_gb,
  const int *jhi_vel_gb,
  double *D1,
  const int *ilo_D1_gb,
  const int *ihi_D1_gb,
  const int *jlo_D1_gb,
  const int *jhi_D1_gb,
  double *D2,
  const int *ilo_D2_gb,
  const int *ihi_D2_gb,
  const int *jlo_D2_gb,
  const int *jhi_D2_gb,
  double *D3,
  const int *ilo_D3_gb,
  const int *ihi_D3_gb,
  const int *jlo_D3_gb,
  const int *jhi_D3_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*! 
 * LSM2D_UPWIND_HJ_WENO5() computes the fifth-order Hamilton-Jacobi WENO
 * upwind approximation to the gradient of \f$ \phi \f$.
 * 
 * Arguments:
 *  - phi_* (out):  components of \f$ \nabla \phi \f$
 *  - phi (in):     \f$ \phi \f$
 *  - vel_* (in):   components of the velocity 
 *  - D1 (in):      scratch space for holding undivided first-differences
 *  - dx, dy (in):  grid cell size
 *  - *_gb (in):    index range for ghostbox
 *  - *_fb (in):    index range for fillbox
 *
 * Return value:    none
 *
 * NOTES:
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 */
void LSM2D_UPWIND_HJ_WENO5(
  double *phi_x,
  double *phi_y,
  const int *ilo_grad_phi_gb,
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb,
  const int *jhi_grad_phi_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  const double *vel_x,
  const double *vel_y,
  const int *ilo_vel_gb,
  const int *ihi_vel_gb,
  const int *jlo_vel_gb,
  const int *jhi_vel_gb,
  double *D1,
  const int *ilo_D1_gb,
  const int *ihi_D1_gb,
  const int *jlo_D1_gb,
  const int *jhi_D1_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*! 
 * LSM2D_CENTRAL_GRAD_ORDER2() computes the second-order, central,
 * finite difference approximation to the gradient of \f$ \phi \f$ 
 * using the formula:
 *
 *    \f[
 *
 *      \left( \frac{\partial \phi}{\partial x} \right)_i \approx
 *        \frac{ \phi_{i+1} - \phi_{i-1} }{ 2 dx }
 *
 *    \f]
 * 
 * Arguments:
 *  - phi_* (out):  components of \f$ \nabla \phi \f$
 *  - phi (in):     \f$ \phi \f$
 *  - dx, dy (in):  grid cell size
 *  - *_gb (in):    index range for ghostbox
 *  - *_fb (in):    index range for fillbox
 *
 * Return value:        none
 */
void LSM2D_CENTRAL_GRAD_ORDER2( 
  double *phi_x,
  double *phi_y,
  const int *ilo_grad_phi_gb,
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb,
  const int *jhi_grad_phi_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*! 
 * LSM2D_CENTRAL_GRAD_ORDER4() computes the fourth-order, central, 
 * finite difference approximation to the gradient of \f$ \phi \f$ 
 * using the formula:
 *
 *    \f[
 *
 *      \left( \frac{\partial \phi}{\partial x} \right)_i \approx
 *         \frac{ -\phi_{i+2} + 8 \phi_{i+1} - 8 \phi_{i-1} + \phi_{i-2} }
 *              { 12 dx }
 *
 *    \f]
 *
 * Arguments:
 *  - phi_* (out):  components of \f$ \nabla \phi \f$
 *  - phi (in):     \f$ \phi \f$
 *  - dx, dy (in):  grid cell size
 *  - *_gb (in):    index range for ghostbox
 *  - *_fb (in):    index range for fillbox
 *
 * Return value:        none
 */
void LSM2D_CENTRAL_GRAD_ORDER4( 
  double *phi_x,
  double *phi_y,
  const int *ilo_grad_phi_gb,
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb,
  const int *jhi_grad_phi_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*! 
 * LSM2D_LAPLACIAN_ORDER2() computes the second-order, central, 
 * finite difference approximation to the Laplacian of \f$ \phi \f$ 
 * using the formula:
 *
 *    \f[
 *
 *      \nabla^2 \phi \approx
 *         \frac{ \phi_{i+1,j,k} - 2 \phi_{i,j,k} + \phi_{i-1,j,k} }
 *              { dx^2 }
 *       + \frac{ \phi_{i,j+1,k} - 2 \phi_{i,j,k} + \phi_{i,j-1,k} }
 *              { dy^2 }
 *
 *    \f]
 *
 * Arguments:
 *  - laplacian_phi (out):  Laplacian of \f$ phi \f$
 *  - phi (in):             \f$ \phi \f$
 *  - dx (in):              grid cell size
 *  - *_gb (in):            index range for ghostbox
 *  - *_fb (in):            index range for fillbox
 *
 * Return value:            none
 */
void LSM2D_LAPLACIAN_ORDER2( 
  double *laplacian_phi,
  const int *ilo_laplacian_phi_gb,
  const int *ihi_laplacian_phi_gb,
  const int *jlo_laplacian_phi_gb,
  const int *jhi_laplacian_phi_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb,
  const double *dx,
  const double *dy);


/*!
 * LSM2D_PHI_UPWIND_GRAD_F() computes the \f$ \phi \f$-upwind gradient of a
 * function, F, using the following "upwinding" scheme to compute
 * the normal:
 *
 *   if \f$ \phi > 0 \f$:  upwind direction is direction where 
 *                         \f$ \phi \f$ is smaller
 *
 *   if \f$ \phi < 0 \f$:  upwind direction is direction where 
 *                         \f$ \phi \f$ is larger
 *
 * Arguments:
 *  - F_* (out):        components of \f$ \phi \f$-upwinded \f$ \nabla F \f$
 *  - F_*_plus (in):    components of \f$ \nabla F \f$ in plus direction
 *  - F_*_minus (in):   components of \f$ \nabla F \f$ in minus direction
 *  - phi (in):         level set function
 *  - *_gb (in):        index range for ghostbox
 *  - *_fb (in):        index range for fillbox
 *
 * Return value:        none
 *
 * NOTES:
 *  - \f$ \phi \f$ is REQUIRED to have at least one ghost cell in each
 *    coordinate direction for upwinding
 *  - the fillbox is defined in terms of the index range for 
 *    cell-centered data
 *
 */
void LSM2D_PHI_UPWIND_GRAD_F(
  double *F_x,
  double *F_y,
  const int *ilo_grad_F_gb,
  const int *ihi_grad_F_gb,
  const int *jlo_grad_F_gb,
  const int *jhi_grad_F_gb,
  double *F_x_plus,
  double *F_y_plus,
  const int *ilo_grad_F_plus_gb,
  const int *ihi_grad_F_plus_gb,
  const int *jlo_grad_F_plus_gb,
  const int *jhi_grad_F_plus_gb,
  double *F_x_minus,
  double *F_y_minus,
  const int *ilo_grad_F_minus_gb,
  const int *ihi_grad_F_minus_gb,
  const int *jlo_grad_F_minus_gb,
  const int *jhi_grad_F_minus_gb,
  const double *phi,
  const int *ilo_phi_gb,
  const int *ihi_phi_gb,
  const int *jlo_phi_gb,
  const int *jhi_phi_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb);


/*!
 * LSM2D_AVERAGE_GRAD_PHI() computes the average of the plus and minus
 * derivatives:
 *
 * \f[
 *
 *   \nabla \phi = (\nabla \phi_{plus} + \nabla \phi_{minus}) / 2
 *
 * \f]
 *
 * Arguments:
 *  - phi_* (out):       components of average \f$ \nabla \phi \f$
 *  - phi_*_plus (in):   components of \f$ \nabla \phi \f$ in plus direction
 *  - phi_*_minus (in):  components of \f$ \nabla \phi \f$ in minus direction
 *  - *_gb (in):         index range for ghostbox
 *  - *_fb (in):         index range for fillbox
 *
 * Return value:         none
 */
void LSM2D_AVERAGE_GRAD_PHI(
  double *phi_x,
  double *phi_y,
  const int *ilo_grad_phi_gb,
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb,
  const int *jhi_grad_phi_gb,
  double *phi_x_plus,
  double *phi_y_plus,
  const int *ilo_grad_phi_plus_gb,
  const int *ihi_grad_phi_plus_gb,
  const int *jlo_grad_phi_plus_gb,
  const int *jhi_grad_phi_plus_gb,
  double *phi_x_minus,
  double *phi_y_minus,
  const int *ilo_grad_phi_minus_gb,
  const int *ihi_grad_phi_minus_gb,
  const int *jlo_grad_phi_minus_gb,
  const int *jhi_grad_phi_minus_gb,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb);

#ifdef __cplusplus
}
#endif

#endif