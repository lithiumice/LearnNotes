clc;
clear;
a=1;
b=2;
c=3;
x=linspace(-2*pi,2*pi,1000);
y=linspace(-2*pi,2*pi,1000);
[X,Y]=meshgrid(x,y);
tmp=1-(X/a)^2-(Y/b)^2;
Z=c*sqrt(tmp);
surf(X,Y,Z);

%y=x;
%[X,Y]=meshgrid(x,y);
%tmp=(X^2)/(a^2)+(Y^2)/(b^2);
%tmp=(1-tmp)*(c^2);
%Z=sqr(tmp);
%surf(X,Y,Z);
