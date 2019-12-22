'''
	> File Name: 3darray.py
	> Author: tuzhuo
	> Mail: xmb028@163.com 
	> Created Time: Mon 16 Dec 2019 08:58:14 AM CST
'''

import numpy as np

arr3d = np.array([[[1,2,3],[4,5,6]],[[7,8,9],[10,11,12]]]) 
print(arr3d.shape)
print(arr3d[0]) 
print(arr3d[1][0]) 
print(arr3d[0][0][1])

