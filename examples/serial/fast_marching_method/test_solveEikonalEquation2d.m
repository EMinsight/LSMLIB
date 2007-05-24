%
% File:        test_solveEikonalEquation2d.m
% Copyright:   (c) 2005-2006 Kevin T. Chu
% Revision:    $Revision: 1.1 $
% Modified:    $Date: 2006/08/10 21:37:02 $
% Description: MATLAB script to process the data file generated by
%              test_solveEikonalEquation2d
%

% geometric parameters
radius = 0.5;

% load data file
data = load('test_solveEikonalEquation2d.dat');
phi = data(:,1);
speed = data(:,2);

% compute the number of grid points
num_gridpts = length(phi);
N = round(sqrt(num_gridpts));

% reshape to 2D array
phi = reshape(phi,N,N);  phi = phi';
speed = reshape(speed,N,N);  speed = speed';

% generate mesh
dx = 2/(N-1);
X = -1:dx:1;
Y = X;

% show phi 
figure(1); clf;
pcolor(X,Y,phi);
shading interp
view([0 90]);
pbaspect([1 1 1]);
title('Solution to Eikonal Equation');
colorbar;

% show speed function
figure(2); clf;
pcolor(X,Y,speed);
shading interp
view([0 90]);
pbaspect([1 1 1]);
title('Speed Function');
colorbar;
