xt = @(t) exp(-t/10) .* sin(5*t);
yt = @(t) exp(-t/10) .* cos(5*t);
zt = @(t) t;
fplot3(xt, yt, zt, [-10, 10])

fun = @(x, y) x.* exp(-x.^2 - y^2);
fsurf(fun, [-2, 2]) %默认为-5， 5
[X, Y] = meshgrid(-8: .5: 8);
R = sqrt(X.^2 + Y.^2);
Z = sin(R)./R;
mesh(X, Y, X)

[X, Y] = meshgrid(-2: 0.25: 2, -1: 0.2: 1);
Z = X.*exp(-X.^2 - Y.^2);
[U, V, W] = surfnorm(X, Y, Z);
quiver3(X, Y, Z, U, V, W)
hold on
surf(X, Y, Z)
colormap spring
view(-14, 15)
// axis([-2 2 -1 1 -.6.6])
hold off

load wind
[sx, sy, sz] = meshgrid(80, 20: 10: 50, 0: 5: 15);
streamline(x, y, z, u, v, w, sx, sy, sz);
view(3)

fsurf(@(x, y) x.*y)
shading flat
view([-17,13])
C = summer; %summer为常量
CC = [C; flipud(C)]; %flipud为矩阵倒置
colormap(CC)
spinmap(10)

x = 3*pi*(-1: 0.05: 1);
[X, Y] = meshgrid(x);
R = sqrt(X.^2 + Y.^2);
Z = sin (R)./R;
h = surf(X, Y, Z);
colormap(jet)
axis off
n = 15;
for i = 1: n
	rotate(h, [0 0 1], 25);
	m(i) = getframe;
end
movie(m, 10)