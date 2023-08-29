.. ASC-bla documentation master file, created by
   sphinx-quickstart on Tue Aug 29 06:39:02 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to ASC-bla's documentation!
===================================

ASC-bla is a C++ library for basic linear algebra operations.

Installation is via git-clone:

    git clone https://github.com/JSchoeberl/ASC-bla.git

To configure and build some tests do

    cd ASC-bla
    mkdir build
    cd build
    cmake ..
    make
    

    
The library provides template classes **Vector** and **Matrix**.

You can create vectors and compute with vectors like

   Vector<double> x(5), y(5), z(5);
   for (int i = 0; i < x.Size(); i++)
      x(i) = i;
   y = 5.0
   z = x+3*y;
   cout << "z = " << z << endl;


   
.. toctree::
   :maxdepth: 2
   :caption: Contents:



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
