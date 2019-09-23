clc;
clear;
t=linspace(1,2*pi,7);
x=10*cos(t);
y=10*sin(t);
h=fill(x,y,'r');
xlim([-12,12])
ylim([-12,12])
axis square
hold on
for i=1:90
    rotate(h,[0,0,1],1)
    pause(0.1)
end
