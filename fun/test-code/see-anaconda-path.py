import numpy
import basenji
from distutils.sysconfig import get_python_lib

print(get_python_lib(numpy))
print(get_python_lib(basenji))
