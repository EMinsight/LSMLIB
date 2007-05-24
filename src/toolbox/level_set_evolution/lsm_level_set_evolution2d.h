/*
 * File:        lsm_level_set_evolution2d.h
 * Copyright:   (c) 2005-2006 Kevin T. Chu
 * Revision:    $Revision: 1.8 $
 * Modified:    $Date: 2006/10/28 05:09:39 $
 * Description: Header file for 2D Fortran 77 level set evolution equation
 *              subroutines
 */

#ifndef INCLUDED_LSM_LEVEL_SET_EVOLUTION_2D_H
#define INCLUDED_LSM_LEVEL_SET_EVOLUTION_2D_H

#ifdef __cplusplus
extern "C" {
#endif

/*! \file lsm_level_set_evolution2d.h
 *
 * \brief
 * @ref lsm_level_set_evolution2d.h provides support for contributing to the
 * right-hand side of the level set evolution equation in two space
 * dimensions.
 * 
 */


/* Link between C/C++ and Fortran function names
 *
 *      name in                                name in
 *      C/C++ code                             Fortran code
 *      ----------                             ------------
 */
#define LSM2D_ZERO_OUT_LEVEL_SET_EQN_RHS       lsm2dzerooutlevelseteqnrhs_
#define LSM2D_ADD_ADVECTION_TERM_TO_LSE_RHS    lsm2daddadvectiontermtolserhs_
#define LSM2D_ADD_NORMAL_VEL_TERM_TO_LSE_RHS   lsm2daddnormalveltermtolserhs_
#define LSM2D_ADD_CONST_NORMAL_VEL_TERM_TO_LSE_RHS   \
                                          lsm2daddconstnormalveltermtolserhs_
#define LSM2D_ADD_CONST_CURV_TERM_TO_LSE_RHS   lsm2daddconstcurvtermtolserhs_


/*!
 * LSM2D_ZERO_OUT_LEVEL_SET_EQN_RHS() zeros out the right-hand side of 
 * the level set equation when it is written in the form:
 *
 * \f[
 *
 *  \phi_t = ...
 *
 * \f]
 *
 * Arguments:
 *  - lse_rhs (in/out):  right-hand of level set equation
 *  - *_gb (in):         index range for ghostbox
 *
 * Return value:         none
 */
void LSM2D_ZERO_OUT_LEVEL_SET_EQN_RHS(
  double *lse_rhs,
  const int *ilo_lse_rhs_gb, 
  const int *ihi_lse_rhs_gb,
  const int *jlo_lse_rhs_gb, 
  const int *jhi_lse_rhs_gb);


/*!
 * LSM2D_ADD_ADVECTION_TERM_TO_LSE_RHS() adds the contribution of an 
 * advection term (external vector velocity field) to the right-hand 
 * side of the level set equation when it is written in the form:
 *
 * \f[
 *
 *    \phi_t = -\vec{V} \cdot \nabla \phi + ...
 *
 * \f]
 *
 * Arguments:
 *  - lse_rhs (in/out):  right-hand of level set equation
 *  - phi_* (in):        components of \f$ \nabla \phi\f$ at t = t_cur
 *  - vel_* (in):        components of velocity at t = t_cur
 *  - *_gb (in):         index range for ghostbox
 *  - *_fb (in):         index range for fillbox
 *
 * Return value:         none
 */
void LSM2D_ADD_ADVECTION_TERM_TO_LSE_RHS(
  double *lse_rhs,
  const int *ilo_lse_rhs_gb, 
  const int *ihi_lse_rhs_gb,
  const int *jlo_lse_rhs_gb, 
  const int *jhi_lse_rhs_gb,
  const double *phi_x, 
  const double *phi_y,
  const int *ilo_grad_phi_gb, 
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb, 
  const int *jhi_grad_phi_gb,
  const double *vel_x, 
  const double *vel_y,
  const int *ilo_vel_gb, 
  const int *ihi_vel_gb,
  const int *jlo_vel_gb, 
  const int *jhi_vel_gb,
  const int *ilo_fb, 
  const int *ihi_fb,
  const int *jlo_fb,  
  const int *jhi_fb);


/*!
 * LSM2D_ADD_NORMAL_VEL_TERM_TO_LSE_RHS() adds the contribution of a 
 * normal (scalar) velocity term to the right-hand side of the level 
 * set equation when it is written in the form:
 *   
 * \f[
 *   
 *    \phi_t = -V_n |\nabla \phi| + ... 
 *   
 * \f]
 *   
 * Arguments:
 *  - lse_rhs (in/out):  right-hand of level set equation
 *  - phi_*_plus (in):   components of forward approx to \f$ \nabla \phi \f$
 *                       at t = t_cur
 *  - phi_*_minus (in):  components of backward approx to \f$ \nabla \phi \f$
 *                       at t = t_cur
 *  - vel_n (in):        normal velocity at t = t_cur
 *  - *_gb (in):         index range for ghostbox
 *  - *_fb (in):         index range for fillbox
 *
 * Return value:         none
 */
void LSM2D_ADD_NORMAL_VEL_TERM_TO_LSE_RHS(
  double *lse_rhs,
  const int *ilo_lse_rhs_gb, 
  const int *ihi_lse_rhs_gb,
  const int *jlo_lse_rhs_gb, 
  const int *jhi_lse_rhs_gb,
  const double *phi_x_plus, 
  const double *phi_y_plus,
  const int *ilo_grad_phi_plus_gb, 
  const int *ihi_grad_phi_plus_gb,
  const int *jlo_grad_phi_plus_gb, 
  const int *jhi_grad_phi_plus_gb,
  const double *phi_x_minus, 
  const double *phi_y_minus,
  const int *ilo_grad_phi_minus_gb, 
  const int *ihi_grad_phi_minus_gb,
  const int *jlo_grad_phi_minus_gb, 
  const int *jhi_grad_phi_minus_gb,
  const double *vel_n,
  const int *ilo_vel_gb, 
  const int *ihi_vel_gb,
  const int *jlo_vel_gb, 
  const int *jhi_vel_gb,
  const int *ilo_fb, 
  const int *ihi_fb,
  const int *jlo_fb,  
  const int *jhi_fb);


/*!
 * LSM2D_ADD_CONST_NORMAL_VEL_TERM_TO_LSE_RHS() adds the contribution 
 * of a normal (scalar) velocity term to the right-hand side of the 
 * level set equation when it is written in the form:
 *   
 * \f[
 *   
 *    \phi_t = -V_n |\nabla \phi| + ... 
 *   
 * \f]
 *  
 * where the normal velocity, \f$ V_n \f$ is a constant.
 *
 * Arguments:
 *  - lse_rhs (in/out):  right-hand of level set equation
 *  - phi_*_plus (in):   components of forward approx to \f$ \nabla \phi \f$
 *                       at t = t_cur
 *  - phi_*_minus (in):  components of backward approx to \f$ \nabla \phi \f$
 *                       at t = t_cur
 *  - vel_n (in):        constant normal velocity at t = t_cur
 *  - *_gb (in):         index range for ghostbox
 *  - *_fb (in):         index range for fillbox
 *
 * Return value:         none
 */
void LSM2D_ADD_CONST_NORMAL_VEL_TERM_TO_LSE_RHS(
  double *lse_rhs,
  const int *ilo_lse_rhs_gb, 
  const int *ihi_lse_rhs_gb,
  const int *jlo_lse_rhs_gb, 
  const int *jhi_lse_rhs_gb,
  const double *phi_x_plus, 
  const double *phi_y_plus,
  const int *ilo_grad_phi_plus_gb, 
  const int *ihi_grad_phi_plus_gb,
  const int *jlo_grad_phi_plus_gb, 
  const int *jhi_grad_phi_plus_gb,
  const double *phi_x_minus, 
  const double *phi_y_minus,
  const int *ilo_grad_phi_minus_gb, 
  const int *ihi_grad_phi_minus_gb,
  const int *jlo_grad_phi_minus_gb, 
  const int *jhi_grad_phi_minus_gb,
  const double *vel_n,
  const int *ilo_fb, 
  const int *ihi_fb,
  const int *jlo_fb,  
  const int *jhi_fb);
   

/*!
 * LSM2D_ADD_CONST_CURV_TERM_TO_LSE_RHS() adds the contribution 
 * of a normal (scalar) velocity term to the right-hand side of the 
 * level set equation when it is written in the form:
 *   
 * \f[
 *   
 *    \phi_t = -b kappa |\nabla \phi| + ... 
 *   
 * \f]
 *  
 * where the \f$ kappa \f$ is the mean curvature and \f$ b \f$ is a 
 * constant.
 *
 * Arguments:
 *  - lse_rhs (in/out):  right-hand of level set equation
 *  - phi_* (in):        first- and second-order partial derivatives 
 *                       of \f$ \phi \f$ 
 *  - b (in):            proporationality constant relating curvature
 *                       to the normal velocity
 *  - *_gb (in):         index range for ghostbox
 *  - *_fb (in):         index range for fillbox
 *
 * Return value:         none
 */
void   LSM2D_ADD_CONST_CURV_TERM_TO_LSE_RHS(
  const double  *lse_rhs,
  const int *ilo_lse_rhs_gb, 
  const int *ihi_lse_rhs_gb,
  const int *jlo_lse_rhs_gb, 
  const int *jhi_lse_rhs_gb,
  const double *phi_x, 
  const double *phi_y,
  const int *ilo_grad_phi_gb,
  const int *ihi_grad_phi_gb,
  const int *jlo_grad_phi_gb,
  const int *jhi_grad_phi_gb,
  const  double *phi_xx,
  const  double *phi_xy,
  const  double *phi_yy,
  const  int *ilo_grad2_phi_gb,
  const  int *ihi_grad2_phi_gb,
  const  int *jlo_grad2_phi_gb, 
  const  int *jhi_grad2_phi_gb,
  const double *b,
  const int *ilo_fb,
  const int *ihi_fb,
  const int *jlo_fb,
  const int *jhi_fb);  
  
#ifdef __cplusplus
}
#endif

#endif