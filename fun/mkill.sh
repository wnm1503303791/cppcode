#########################################################################
# File Name: mkill.sh
# Author: tuzhuo
# mail: xmb028@163.com
# Created Time: Sun 03 Nov 2019 04:07:01 PM CST
#########################################################################
#!/bin/bash

g++ recursion.cpp -o kill
./kill
rm -rf kill
