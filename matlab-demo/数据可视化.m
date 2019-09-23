x = -pi : .1: pi;
y = sin (x);
plot(x, y);

y1 = tan ( sin (x)) - sin(tan(x));
plot(x, y, '--rs', 'LineWidth', 2, 'MarkerSize', 10, 'MakerEdgeColor', 'b', 'MakerFaceColor', [1, 1, 0]) %红色虚线

x = linspace(0, 2*pi, 36);
y1 = sin(x);
y2 = cos(x);
plot(x, y1, 'r');
figure(2)
plot(x, y2, 'b-^');

x = 14: .1 :4;
y = x.^2;
figure('Name', 'y = x^2', 'Color', 'red', 'menubar', 'none', 'Position', [100, 100, 300, 200], 'Units', 'pixel', 'ButtonDownFcn', 'plot(x, y)');

close all
hold on
subplot(m, n, p, ['replace'])
axis auto
axis tight
xlim ([-1, 1])
box on %显示坐标框
grid
title
xlabel
legend(str1, str2, ...) %显示图例
text(x, y, str)
gtext

x = 0: pi/50 : 2*pi;
y = sin(x);
plot(x, y);
xlabel('x axis')
ylabel('y axis')
title('sin plot', 'color', 'red')
text(pi, 0, '\leftarrow sin (\pi)', 'FontSize', 18)

%绘制双坐标图形
x = linspace(0, 10);
y = sin(x);
yyaxis left
plot(x, y)
z = sin(3*x) .*exp(0.5*x);
text(1, 0.6, '\fontsize {14} \ity=sin3x')
yyaxis right
plot(x, z)
ylim([-150, 150])
text(2.5, 3.5, ['\fontsize {14} \ity = sin3x\cdot^{x/2}']);

%极坐标绘图
function[] = rose(a, n)
theta = 0: 0.01: 2*pi;
	rho = a*cos(n*theta);
	polarplot(theta, rho)
end
%theta代表弧度参数, 向量rho代表极点开始是长度

x = 0: 0.1: 10; y = exp(-x);
subplot(2, 2, 1); semilogy(x, y);
grid on;

x = @(t) cos(3*t);
y = @(t) sin(2*t);
fplot(x, y)

f = @(x)sin(x)./x;
fplot(f, [-40, 40])

ezpolar('2*cos(2*(t - pi/8))')

bar(y, 'stacked')

pie(x, explode, label)
stem(X, Y, spec)%杆状图

clear
x0 = 0: 0.2: 6;
y0 = 0: 0.2: 3;
[x, y] = meshgrid(x0, y0);
dy = y.*(0.5-x) + 1;
dx = ones(size(dy))
d = sqrt(dx.^2 + dy.*2);
u = dx./d;
v = dy./d;
quiver(x, y, u, v)
h = streamline(x, y, u, v, 0, 0.2);
set(h, 'linewidth', 2, 'color', 'r')