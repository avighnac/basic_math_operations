import os
from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext

module_name = 'basic_math_operations'


class custom_build_ext(build_ext):
    def run(self):
        lib_path = '../../build/src/library/libbasic_math_operations.a'
        if not os.path.exists(lib_path):
            raise Exception(
                f"static library 'libbasic_math_operations.a' not found in the directory: {lib_path}")
        self.extensions[0].extra_objects = [lib_path]
        build_ext.run(self)


basic_math_operations_module = Extension(
    module_name,
    sources=[module_name+'module.c'],
    extra_objects=['../../build/src/library/libbasic_math_operations.a']
)


setup(
    name="basic_math_operations",
    version="1.0.0",
    description="Biginteger library written in assembly and C.",
    author="avighnac",
    author_email="avighnakc@gmail.com",
    ext_modules=[basic_math_operations_module],
    cmdclass={'build_ext': custom_build_ext}
)
