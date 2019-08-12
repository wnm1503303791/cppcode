#########################################################################
# File Name: name.sh
# Author: tuzhuo
# mail: xmb028@163.com
# Created Time: 2019年08月12日 星期一 19时42分26秒
#########################################################################
#!/bin/bash
name="tuzhuo"
echo "my name is ${name}"
echo "my name is $name"
echo "I like my name"
echo "I like my $name"
readonly name
name="xjp"
mystring='hello,world!'
echo '$mystring'
echo "$mystring"
echo ${#mystring}
echo ${mystring:1:5}
mdataset=(1 2 3 4 5)
mdataset[7]=9
echo ${mdataset[7]} seperator  ${mdataset[3]}
echo ${mdataset[@]}
:<<!
this is the bullshit
!
