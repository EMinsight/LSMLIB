%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% UPWIND_HJ_ENO3_1D() computes the third-order upwind HJ ENO
% approximation to phi_x.
%
% Usage: phi_x = UPWIND_HJ_ENO3_1D(phi, vel_x, ghostcell_width, dx)
%
% Arguments:
% - phi:               function for which to compute upwind 
%                        derivative
% - vel_x:             velocity to use in upwinding
% - ghostcell_width:   number of ghostcells at boundary of 
%                        computational domain
% - dx:                grid cell size
%
% Return values:
% - phi_x:             third-order, upwind HJ ENO derivative
%
% NOTES:
% - phi_x has the same ghostcell width as phi.
% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Copyright:  (c) 2005-2008 Kevin T. Chu and Masa Prodanovic
% Revision:   $Revision: 1.3 $
% Modified:   $Date: 2006/04/24 00:52:40 $
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
