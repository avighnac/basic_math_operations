# Check if sudo, if not, exit
if [ "$(id -u)" -ne 0 ]
  then echo "Please run as root!"
  exit
fi

cd /tmp
# If the directory exists, delete it
if [ -d "basic_math_operations-install" ]; then
  rm -rf basic_math_operations-install
fi
mkdir basic_math_operations-install
cd basic_math_operations-install
curl -s https://api.github.com/repos/avighnac/basic_math_operations/releases/latest \
| grep "browser_download_url.*zip" \
| cut -d : -f 2,3 \
| tr -d \" \
| wget -qi -

echo "Sucessfully downloaded the latest release."

unzip "libbasic_math_operations-linux.zip" -d libs

echo "Sucessfully extracted the files."

# Copy the libs to /usr/lib, if they exist then replace them
cp -r libs/libbasic_math_operations.a /usr/lib/
cp -r libs/libbasic_math_operations.so /usr/lib/
# Copy the header files to /usr/include
cp -r libs/basic_math_operations.h /usr/include/
cp -r libs/basic_math_operations.hpp /usr/include/

echo "Installation complete!"

# Delete the temporary directory
cd ..
rm -rf basic_math_operations-install