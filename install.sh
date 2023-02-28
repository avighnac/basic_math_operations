#!/bin/bash

# Check if sudo, if not, exit

COMMAND=wget

if [ "$(id -u)" -ne 0 ]
then 
  echo -e "\e[32mPlease run as root!\e[0m"
  exit
fi

echo -e "Testing for unzip..."
if ! command -v unzip &> /dev/null
then
  echo -e "\e[32munzip not installed!\e[0m"
  exit
fi

if ! command -v unzip &> /dev/null
then
  echo -e "\e[32mwget not installed, defaulting to curl!\e[0m"
  COMMAND="curl -O -J"
  if ! command -v curl &> /dev/null
  then
    echo -e "\e[32mcurl not installed!\e[0m"
    exit
  fi
fi

latest
cd /tmp
# If the directory exists, delete it
if [ -d "basic_math_operations-install" ]; then
  rm -rf basic_math_operations-install
fi
mkdir basic_math_operations-install
cd basic_math_operations-install
$COMMAND -q https://github.com/avighnac/basic_math_operations/releases/latest/download/libbasic_math_operations-linux.zip 


echo "Sucessfully downloaded the latest release."

unzip "libbasic_math_operations-linux.zip" -d libs

echo "Sucessfully extracted the files."

# Copy the libs to /usr/lib, if they exist then replace them
cp -r libs/libbasic_math_operations.a /usr/lib/
# Copy the header files to /usr/include
cp -r libs/basic_math_operations.h /usr/include/
cp -r libs/basic_math_operations.hpp /usr/include/

echo "Installation complete!"

# Delete the temporary directory
cd ..
rm -rf basic_math_operations-install
