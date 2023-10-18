from ASCsoft.bla import Vector
from ASCsoft.bla import Matrix

x = Vector(3)
y = Vector(3)

print ("x =", x)
print ("y =", y)

x[:] = 1
print ("x =", x)

#for i in range(len(x)):
#    x[i] = i
#y[:] = 2    
#
#print ("x =", x)
#print ("y =", y)
#print ("x+3*y =", x+3*y)
#
#
#x = Vector(10)
#x[0:] = 1
#print (x)
#
#x[3:7] = 2
#print (x)
#print("_________________________________________")
#
#x[0:10:2] = 3
#print (x)
#
#from ASCsoft.bla import Matrix
#
#
##help(Matrix)
#X = Matrix(3, 3)
#Y = Matrix(3, 3)
#print ("I print zero")
#print (X)
#
#for i in range(3):
#    for j in range(3):
#        X[i,j] = 1
#        Y[i,j] = 2
#
#print (Y)
#
#
#Z  = X + Y
#
#X[0,0] = 1
#print (X)
#
#print(X[0,0] )
#
#print (Z*Z)
#print (Z.shape)
#
#h,w = Z.shape
#print (h)
#print (w)
#
#print(Y)
#Y[1, 2:3]=1
#print(Y)
#
#
#print(Y)
#Y[1, 2:3]=2
#print(Y)
#
#print(Y)
#Y[1, :]=1
#print(Y)
#
#v = Vector(3)
#print(v*Y)
#
#
X = Matrix(3, 3)
for i in range(3):
    for j in range(3):
        X[i,j] = 10*i +j

print (X)
print (X.T)