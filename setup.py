import setuptools
import os
from distutils.core import Extension, setup
import glob
import sys
from zipfile import ZipFile

    
module_name = 'basic_math_operations'

library_path = glob.glob("**/*.a", recursive=True)
def check_for_zip():
    global library_path
    zip_path = [i for i in glob.glob("**/*.zip", recursive=True) if "basic_math_operations" in i]
    if not zip_path:
        print("\u001b[30mERROR!\u001b[0m You need to compile the library first", file=sys.stderr)
        sys.exit(1)
    zipFile = ZipFile(zip_path[0])
    try:
        zipFile.extract("libbasic_math_operations.a")
    except:
        print("\u001b[30mERROR!\u001b[0m You need to compile the library first", file=sys.stderr)
        sys.exit(1)
    library_path = "libbasic_math_operations.a"
if os.name == 'nt':
    library_path_win = glob.glob("**/*.lib", recursive=True)
    library_path = [i for i in library_path if i.endswith(("libbasic_math_operations.a", "libbasic_math_operations-windows.a"))]
    if not library_path_win and not library_path:
        print("\u001b[30mERROR!\u001b[0m You need to compile the library first", file=sys.stderr)
        sys.exit(1)
    library_path = library_path_win[0] if library_path_win else library_path[0]
elif not library_path:
    check_for_zip()
else:
    library_path = [i for i in library_path if i.endswith(("libbasic_math_operations.a", "libbasic_math_operations-linux.a"))]
    if not library_path:
        check_for_zip()
    else:
        library_path = library_path[0]
        
    


basic_math_operations_module = Extension(
    module_name,
    sources=['src/python-module/module.c'],
    extra_objects=[library_path]
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
