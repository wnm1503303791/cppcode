#########################################################################
# File Name: test.sh
# Author: tuzhuo
# mail: xmb028@163.com
# Created Time: 2019年08月13日 星期二 16时20分49秒
#########################################################################
#!/bin/bash
#cd /home/tuzhuo/code/git/cppcode/bashcode
for file in $*
do
	if test -e $file
	then 
		echo "$file exit!"
	else
		echo "$file does not exit!"
	fi
done
