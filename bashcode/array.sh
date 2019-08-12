#########################################################################
# File Name: array.sh
# Author: tuzhuo
# mail: xmb028@163.com
# Created Time: 2019年08月12日 星期一 20时13分28秒
#########################################################################
#!/bin/bash
name="tuzhup"
num=111
data=("hello,world!" 124 21.7 c name num $1)
echo ${data[*]}
echo ${data[0]}
