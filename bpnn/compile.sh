#########################################################################
# File Name: compile.sh
# Author: tuzhuo
# mail: xmb028@163.com
# Created Time: Tue 21 Apr 2020 06:47:37 PM CST
#########################################################################
#!/bin/bash

g++ -o bpnn bpnn.cpp
./bpnn
rm bpnn

