# C-Control

This repo contain some basic math functions, some swerve math, and motion profiling code. This repo now requires the use of eigen (specifically the SwerveMath component). See: http://eigen.tuxfamily.org/dox/GettingStarted.html for install instructions. Some testing code used just for motion profiling require gnuplot.

To compile tester.cpp use g++ tester.cpp 900Math.cpp SwerveMath.cpp -std=c++11 -I <path to eigen> 

TODO:

* Generally fix functions which don't work and add needed functions.
* Clean up spacing and make code more readable.
* Highly optimize most code -- most is called each loop iteration

