from ASC_bla import Vector

x = Vector(3)
y = Vector(3)

for i in range(len(x)):
    x[i] = i
    y[i] = 2

print (x+y)

