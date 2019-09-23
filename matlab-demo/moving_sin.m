clc;
clear;
t = linspace(0, 2*pi, 361);
xc=10*cos(t);
yc=10*sin(t);
h=plot(xc,yc,'r-.');
xlim([-12,12]);

