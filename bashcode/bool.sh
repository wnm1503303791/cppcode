#########################################################################
# File Name: bool.sh
# Author: tuzhuo
# mail: xmb028@163.com
# Created Time: 2019年08月13日 星期二 11时19分39秒
#########################################################################
#!/bin/bash
if [ $1 -eq $2 ]
then 
	echo -e "$1 equals $2\n"
else
	echo "$1 is not equals to $2"
fi

if [ $1 -gt $2 ]
then
	echo "$1 bigger than $2"
elif [ $1 -eq $2 ]
then
	:
else
	echo "$1 smaller than $2"
fi

echo "\"test\"\n"
echo `date`
