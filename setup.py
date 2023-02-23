import zipfile
import setuptools
import os
from distutils.core import Extension, setup
import glob
import shutil
import sys
from zipfile import ZipFile


module_name = 'basic_math_operations'
version = '1.0.0'

# Print current directory
print("Current directory: " + os.getcwd())

if (os.path.exists('dist/artifacts/linux-build/libbasic_math_operations-linux.zip') and os.name != 'nt'):
    with zipfile.ZipFile('dist/artifacts/linux-build/libbasic_math_operations-linux.zip', 'r') as zfile:
        zfile.extract('libbasic_math_operations.a')
    shutil.copy("libbasic_math_operations.a",
                "src/python-module/libbasic_math_operations.a")
if (os.path.exists('dist/artifacts/windows-build/libbasic_math_operations-windows.a') and os.name == 'nt'):
    shutil.copy("dist/artifacts/windows-build/libbasic_math_operations-windows.a",
                "src/python-module/libbasic_math_operations.a")
shutil.copy("dist/artifacts/version-info/version.txt",
        "src/python-module/version.txt")

with open('version.txt' if os.path.exists('version.txt') else 'src/python-module/version.txt', 'r') as f:
    version = f.read()
    version.replace('\n', '')

basic_math_operations_module = Extension(
    module_name,
    sources=['src/python-module/module.c'],
    extra_objects=['src/python-module/libbasic_math_operations.a']
)

setup(
    name="basic_math_operations",
    version=version,
    description="Biginteger library written in assembly and C.",
    author="avighnac",
    author_email="avighnakc@gmail.com",
    ext_modules=[basic_math_operations_module],
    setup_requires=['wheel'],
    include_package_data=True,
    packages=['src/python-module'],
    package_data={
        'src/python-module': ['src/python-module/libbasic_math_operations.a', 'src/python-module/version.txt']},
    data_files=[
        ('src/python-module', ['src/python-module/libbasic_math_operations.a', 'src/python-module/version.txt'])],
)

os.remove('src/python-module/libbasic_math_operations.a')
os.remove('src/python-module/version.txt')
