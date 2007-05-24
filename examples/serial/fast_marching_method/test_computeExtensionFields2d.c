/*
 * File:        test_computeExtensionFields2d.c
 * Copyright:   (c) 2005-2006 Kevin T. Chu
 * Revision:    $Revision: 1.3 $
 * Modified:    $Date: 2006/08/13 13:35:24 $
 * Description: Test program for the fast marching method functions
 */


// System headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Header for Fast Marching Method Algorithm class
#include "lsm_fast_marching_method.h"

/************************************************************************
 *
 * Test program for the Fast Marching Method classes.
 *
 ************************************************************************
 */


int main( int argc, char *argv[])
{
  /* field variables */
  double *phi;
  double *distance_function;
  double **source_fields;
  double **ext_fields;
  double *mask = 0;

  /* grid parameters */
  double X_lo[2] = {-1.0,-1.0}; 
  double X_hi[2] = {1.0,1.0}; 
  double dx[2];
  int N[2];
  int i,j,k;
  int idx;
  int num_gridpts;
  int num_ext_fields;
  int grid_dims[2];

  /* numerical parameters */
  int spatial_derivative_order = 1;

  /* auxilliary variables */
  double x,y;
  double dist1, dist2;
  double center1[2], center2[2];
  double radius1, radius2;

  /* file pointer to output results */
  FILE *data_file;

  /* set up grid */
  N[0] = 63;
  N[1] = 63;
  num_gridpts = 1;
  for (i = 0; i < 2; i++) {
    dx[i] = (X_hi[i]-X_lo[i])/N[i];
    grid_dims[i] = N[i]+1;
    num_gridpts *= grid_dims[i];
  }

  /* allocate memory for field data */
  num_ext_fields = 2;
  phi = (double*) malloc(num_gridpts*sizeof(double));
  distance_function = (double*) malloc(num_gridpts*sizeof(double));
  source_fields = (double**) malloc(num_ext_fields*sizeof(double*));
  ext_fields = (double**) malloc(num_ext_fields*sizeof(double*));
  for (i = 0; i < num_ext_fields; i++) {
    source_fields[i] = (double*) malloc(num_gridpts*sizeof(double));
    ext_fields[i] = (double*) malloc(num_gridpts*sizeof(double));
  }

  /* initialize data */
  center1[0] = 0.25; center1[1] = 0.25; radius1 = 0.2;
  center2[0] = -0.25; center2[1] = -0.25; radius2 = 0.2;
  for (j = 0; j < grid_dims[1]; j++) {
    for (i = 0; i < grid_dims[0]; i++) {
      idx = i+j*grid_dims[0];
      x = X_lo[0]+dx[0]*i;
      y = X_lo[1]+dx[1]*j;
      dist1 = sqrt( (x-center1[0])*(x-center1[0])
                   +(y-center1[1])*(y-center1[1]) ) - radius1;
      dist2 = sqrt( (x-center2[0])*(x-center2[0])
                   +(y-center2[1])*(y-center2[1]) ) - radius2;

      phi[idx] = (dist1 < dist2 ? dist1 : dist2);
    }
  }

  /* initialize source fields */
  for (k = 0; k < num_ext_fields; k++) {
    for (j = 0; j < grid_dims[1]; j++) {
      for (i = 0; i < grid_dims[0]; i++) {
        idx = i+j*grid_dims[0];
        x = X_lo[0]+dx[0]*i;
        y = X_lo[1]+dx[1]*j;
  
        source_fields[k][idx] = sin((k+1)*x)+cos((2*k+1)*y);
      }
    }
  }

  for (i = 0; i < num_gridpts; i++) {
    distance_function[i] = 0; 
  }
  for (j = 0; j < num_ext_fields; j++) {
    for (i = 0; i < num_gridpts; i++) {
      ext_fields[j][i] = 0; 
    }
  }

  /* Carry out FMM calculation */
  computeExtensionFields2d(
    distance_function,
    ext_fields,
    phi,
    mask,
    source_fields,
    num_ext_fields,
    spatial_derivative_order,
    grid_dims,
    dx);

  /* write results to output file */
  data_file = fopen("test_computeExtensionFields2d.dat","w");
  for (idx = 0; idx < num_gridpts; idx++) {
    fprintf(data_file,"%f %f %f %f %f %f\n", 
      distance_function[idx], phi[idx],
      ext_fields[0][idx], ext_fields[1][idx], 
      source_fields[0][idx], source_fields[1][idx]);
  }
  fclose(data_file);

  /* clean up memory */
  free(phi);  
  free(distance_function);  
  for (i = 0; i < num_ext_fields; i++) {
    free(source_fields[i]);  
    free(ext_fields[i]);  
  }
  free(source_fields);  
  free(ext_fields);  

  return(0);
}
