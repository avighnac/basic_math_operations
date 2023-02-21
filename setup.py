import setuptools
import os
from distutils.core import Extension, setup



module_name = 'basic_math_operations'


basic_math_operations_module = Extension(
    module_name,
    sources=['src/python-module/module.c'],
    extra_objects=['build/src/library/libbasic_math_operations.a' if os.name != 'nt' else'build/src/library/Debug/basic_math_operations.lib']
)


setup(
    name="basic_math_operations",
    version="1.0.0",
    description="Biginteger library written in assembly and C.",
    author="avighnac",
    author_email="avighnakc@gmail.com",
    ext_modules=[basic_math_operations_module],
    setup_requires=['wheel']
)
