clc;
clear;
t = linspace(0, 2*pi, 361);
xc=10*cos(t);
yc=10*sin(t);
h=plot(xc,yc,'r-.');
xlim([-12,12]);
ylim([-12,12]);
axis square
hold on
x=xc(1)+cos(t);
y=yc(1)+sin(t);
h1=fill(x,y,'g');
for i=1:361
    x=xc(i)+cos(t);
    y=yc(i)+sin(t);
    set(h1,'xdata',x,'ydata',y)
    drawnow
end