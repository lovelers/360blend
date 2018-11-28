x = [0:0.01:1]
y = sin(x * pi) * 0.3

coff = polyfit(x, y, 2)
result = polyval(coff, x)

plot(x, y, 'r')
hold on
plot(x, result, 'b')
