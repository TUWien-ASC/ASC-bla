from ASCsoft.bla import Vector
from ASCsoft.bla import Matrix

x = Vector(3)
y = Vector(3)

print ("x =", x)
print ("y =", y)

x[:] = 1
print ("x =", x)
n = 10
X = Matrix(n,n)
for i in range(n):
    for j in range(n):
        X[i,j] = 10*i + j
 
print(X)

        
#print (X)
#print (X.T)
#
#print(X.inv)


print((X)[0:3,0])