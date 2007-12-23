%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% computeLevelSetEvolutionEqnRHS() computes the right-hand side of the 
% level set evolution equation. 
%
% Usage: lse_rhs = computeLevelSetEvolutionEqnRHS( ...
%                    phi, velocity, ...
%                    ghostcell_width, ...
%                    dX, spatial_derivative_order)
%
% Arguments:
%   phi:                       phi(t_cur)
%   velocity:                  velocity field at t = t_cur
%   ghostcell_width:           number of ghostcells for phi at boundary 
%                                of computational domain
%   dX:                        array containing the grid spacing
%                                in coordinate directions
%   spatial_derivative_order:  order of discretization for spatial derivative 
%                                (default = 5)
%
% Return value:
%   lse_rhs:                   right-hand side of level set evolution equation
%
% NOTES:
% - The returned lse_rhs data array is the same size as the phi data array.
%   However, the right-hand side of the level set evolution equation is
%   only computed on the _interior_ of the computational grid.  In other 
%   words, the RHS of the level set evolution equation is _not_ computed
%   in the ghostcells; the value in the ghostcells is set to 0.
%
% - The velocity _must_ be passed in as a cell array of numerical arrays
%   containing the components of the velocity field.  When advancing the 
%   level set equation using an external (vector) velocity field, each 
%   cell represents one component of the velocity field (velocity{1} holds 
%   the velocity in x-direction, velocity{2} holds the velocity in the 
%   y-direction, etc.).  When advancing the level set equation using the
%   velocity in the normal direction, velocity{1} should hold the value
%   of the normal velocity.
%
% - When vector velocity data is supplied, the data arrays for the 
%   components of the velocity are assumed to be the same.
%
% - When dX is a scalar, it is assumed that the grid spacing in each
%   coordinate direction is the same.  Otherwise, dX is treated as
%   a vector with dX(1) = the grid spacing in the x-direction, 
%   dX(2) = the grid spacing in the y-direction, etc.
%
% - The phi data array _must_ have larger dimensions than the 
%   velocity data array, and the velocity data array _must_ have 
%   larger dimensions than the the phi data array with ghostcells
%   removed.
%
% - All input data arrays are assumed to be in the order generated by the
%   MATLAB meshgrid() function.  That is, for 2D arrays, data corresponding
%   to the point (x_i,y_j) is stored at index (j,i); for 3D arrays, data
%   corresponding to the point (x_i,y_j,z_k) is stored at index (j,i,k).
%   The output data arrays will be returned with the same ordering as the
%   input data arrays. 
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Copyright:  (c) 2005-2008 Kevin T. Chu and Masa Prodanovic
% Revision:   $Revision: 1.4 $
% Modified:   $Date: 2006/09/18 16:19:28 $
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function lse_rhs = computeLevelSetEvolutionEqnRHS(phi, velocity, ...
                                                  ghostcell_width, dX, ...
                                                  spatial_derivative_order)

% parameter checks
if (nargin < 4)
  error('MATLAB:missingArgs','computeLevelSetEvolutionEqnRHS:missing arguments');
end

if (nargin < 5)
  spatial_derivative_order = 5;
else 
  if ( (spatial_derivative_order ~= 1) & (spatial_derivative_order ~= 2) ...
     & (spatial_derivative_order ~= 3) & (spatial_derivative_order ~= 5) )

    error('computeLevelSetEvolutionEqnRHS:Invalid spatial derivative order...only 1, 2, 3, and 5 are supported');
  end
end

% determine dimensionality of problem
num_dims = ndims(phi);
if (num_dims < 1 | num_dims > 3)
  error('computeLevelSetEvolutionEqnRHS:Invalid dimension...only 1D, 2D, and 3D problems supported');
end

% determine if the velocity is an external velocity field or normal velocity
num_vel_components = length(velocity);
if ( (num_vel_components > 1) | (num_dims == 1) ) 
  use_ext_velocity = 1;

  % check that dimensions of velocity components are the same
  size_vel_x = size(velocity{1});
  if ( (num_dims > 1) & ~isempty(find(size_vel_x~=size(velocity{2}))) )
    error('computeLevelSetEvolutionEqnRHS:External velocity specified, but velocity data array dimensions are different.');
  end
  if ( (num_dims > 2) & ~isempty(find(size_vel_x~=size(velocity{3}))) )
    error('computeLevelSetEvolutionEqnRHS:External velocity specified, but velocity data array dimensions are different.');
  end

else
  use_ext_velocity = 0;
end

% check that the phi data array is larger than the velocity data array
if ( ~isempty(find(size(phi)<size(velocity{1}))) )
  error('computeLevelSetEvolutionEqnRHS:velocity data array is smaller than phi data array in at least one dimension.');
end

% compute dX 
if (isscalar(dX))
  dX = dX*ones(num_dims,1);
end

% initialize RHS of level set evolution equation
lse_rhs = zeros(size(phi));

% compute RHS of level set evolution equation
if (use_ext_velocity == 1) 
  % case: external velocity specified

  % compute right-hand side of level set evolution equation
  switch (num_dims)

    % case: 1D
    case 1  

      % compute upwind spatial derivative
      phi_x = computeUpwindDerivatives1D(phi, ...
                                         velocity{1}, ...
                                         ghostcell_width, ...
                                         dX, ...
                                         spatial_derivative_order);
 
      % compute index spaces for data
      size_grad_phi = length(phi_x);
      size_vel = length(velocity{1});
      shift = ghostcell_width - floor( size_grad_phi - size_vel )/2;
      index_lo_vel = 1+shift; 
      index_hi_vel = size_vel-shift;
      index_lo_grad_phi = 1+ghostcell_width; 
      index_hi_grad_phi = size_grad_phi-ghostcell_width;
      index_lo_interior = 1+ghostcell_width; 
      index_hi_interior = size(phi)-ghostcell_width;

      % compute RHS
      lse_rhs(index_lo_interior(1):index_hi_interior(1)) = ...
        -velocity{1}(index_lo_vel(1):index_hi_vel(1)) ...
      .* phi_x(index_lo_grad_phi(1):index_hi_grad_phi(1));

    % end 1D case

    % case: 2D
    case 2

      % compute upwind spatial derivative
      [phi_x, phi_y] = computeUpwindDerivatives2D(phi, ...
                                                  velocity{1}, ...
                                                  velocity{2}, ...
                                                  ghostcell_width, ...
                                                  dX, ...
                                                  spatial_derivative_order);
 
      % compute index spaces for data
      size_grad_phi = size(phi_x);
      size_vel = size(velocity{1});
      shift = ghostcell_width - floor( size_grad_phi - size_vel )/2;
      index_lo_vel = [1 1]+shift; 
      index_hi_vel = size_vel-shift;
      index_lo_grad_phi = [1 1]+ghostcell_width; 
      index_hi_grad_phi = size_grad_phi-ghostcell_width;
      index_lo_interior = [1 1]+ghostcell_width; 
      index_hi_interior = size(phi)-ghostcell_width;

      % compute RHS
      lse_rhs(index_lo_interior(1):index_hi_interior(1), ...
              index_lo_interior(2):index_hi_interior(2)) = ...
        -velocity{1}(index_lo_vel(1):index_hi_vel(1), ...
                     index_lo_vel(2):index_hi_vel(2)) ...
      .* phi_x(index_lo_grad_phi(1):index_hi_grad_phi(1), ...
               index_lo_grad_phi(2):index_hi_grad_phi(2)) ...
      -  velocity{2}(index_lo_vel(1):index_hi_vel(1), ...
                     index_lo_vel(2):index_hi_vel(2)) ...
      .* phi_y(index_lo_grad_phi(1):index_hi_grad_phi(1), ...
               index_lo_grad_phi(2):index_hi_grad_phi(2));

    % end 2D case

    % case: 3D
    case 3

      % compute upwind spatial derivative
      [phi_x, phi_y, phi_z] = ...
        computeUpwindDerivatives3D(phi, ...
                                   velocity{1}, ...
                                   velocity{2}, ...
                                   velocity{3}, ...
                                   ghostcell_width, ...
                                   dX, ...
                                   spatial_derivative_order);

      % compute index spaces for data
      size_grad_phi = size(phi_x);
      size_vel = size(velocity{1});
      shift = ghostcell_width - floor( size_grad_phi - size_vel )/2;
      index_lo_vel = [1 1 1]+shift; 
      index_hi_vel = size_vel-shift;
      index_lo_grad_phi = [1 1 1]+ghostcell_width; 
      index_hi_grad_phi = size_grad_phi-ghostcell_width;
      index_lo_interior = [1 1 1]+ghostcell_width; 
      index_hi_interior = size(phi)-ghostcell_width;

      % compute RHS
      lse_rhs(index_lo_interior(1):index_hi_interior(1), ...
              index_lo_interior(2):index_hi_interior(2), ...
              index_lo_interior(3):index_hi_interior(3)) = ...
        -velocity{1}(index_lo_vel(1):index_hi_vel(1), ...
                     index_lo_vel(2):index_hi_vel(2), ...
                     index_lo_vel(3):index_hi_vel(3)) ...
      .* phi_x(index_lo_grad_phi(1):index_hi_grad_phi(1), ...
               index_lo_grad_phi(2):index_hi_grad_phi(2), ...
               index_lo_grad_phi(3):index_hi_grad_phi(3)) ...
      -  velocity{2}(index_lo_vel(1):index_hi_vel(1), ...
                     index_lo_vel(2):index_hi_vel(2), ...
                     index_lo_vel(3):index_hi_vel(3)) ...
      .* phi_y(index_lo_grad_phi(1):index_hi_grad_phi(1), ...
               index_lo_grad_phi(2):index_hi_grad_phi(2), ...
               index_lo_grad_phi(3):index_hi_grad_phi(3)) ...
      -  velocity{3}(index_lo_vel(1):index_hi_vel(1), ...
                     index_lo_vel(2):index_hi_vel(2), ...
                     index_lo_vel(3):index_hi_vel(3)) ...
      .* phi_z(index_lo_grad_phi(1):index_hi_grad_phi(1), ...
               index_lo_grad_phi(2):index_hi_grad_phi(2), ...
               index_lo_grad_phi(3):index_hi_grad_phi(3));

    % end 3D case

  end

else 
  % case: normal velocity specified

  % compute right-hand side of level set evolution equation
  switch (num_dims)

    % case: 1D - handled by external velocity case

    % case: 2D
    case 2

      % compute plus and minus spatial derivative
      [phi_x_plus, phi_y_plus, phi_x_minus, phi_y_minus] = ...
        computePlusAndMinusDerivatives2D(phi, ...
                                         ghostcell_width, ...
                                         dX, ...
                                         spatial_derivative_order);
 
      % compute RHS
      index_lo_interior = [1 1]+ghostcell_width; 
      index_hi_interior = size(phi)-ghostcell_width;
      lse_rhs = COMPUTE_NORMAL_VELOCITY_TERM_FOR_LSE_RHS_2D( ...
                  phi, ghostcell_width, ...
                  velocity{1}, ...
                  phi_x_plus, phi_y_plus, ...
                  phi_x_minus, phi_y_minus);

    % end 2D case

    % case: 3D
    case 3

      % compute plus and minus spatial derivative
      [phi_x_plus, phi_y_plus, phi_z_plus, ...
       phi_x_minus, phi_y_minus, phi_z_minus] = ...
        computePlusAndMinusDerivatives3D(phi, ...
                                         ghostcell_width, ...
                                         dX, ...
                                         spatial_derivative_order);
 
      % compute RHS
      index_lo_interior = [1 1 1]+ghostcell_width; 
      index_hi_interior = size(phi)-ghostcell_width;
      lse_rhs = COMPUTE_NORMAL_VELOCITY_TERM_FOR_LSE_RHS_3D( ...
                  phi, ghostcell_width, ...
                  velocity{1}, ...
                  phi_x_plus, phi_y_plus, phi_z_plus, ...
                  phi_x_minus, phi_y_minus, phi_z_plus);

    % end 3D case

  end

end  % end computation of right-hand side of level set evolution equation

