#!/bin/bash

set -e

# Set default command to download archive from
DOWNLOAD_CMD="wget -q"

# Set default install prefix to /usr
PREFIX="${PREFIX:-/usr}"

# Check if the user is root
if [ "$(id -u)" -ne 0 ]
then
  echo -e "\e[31mPlease run as root!\e[0m" > /dev/stderr
  exit
fi

# Check for '--local' flag to perform a local install instead.
if [ "$1" = "--local" ]; then
  # Check for current_dir/build/src/library/libbasic_math_operations.a
  if [ -f "build/src/library/libbasic_math_operations.a" ]; then
    echo -e "\e[32mFound local build, installing...\e[0m"
    mkdir -p $PREFIX/lib
    mkdir -p $PREFIX/include
    cp -r build/src/library/libbasic_math_operations.a $PREFIX/lib/
    # Copy the header files to /usr/include
    cd src/library
    find . -name '*.h' -exec cp -prv '{}' "$PREFIX/include" ";"
    find . -name '*.hpp' -exec cp -prv '{}' "$PREFIX/include" ";"
    cd ../../../../
    echo -e "\e[32mInstallation complete!\e[0m"
    exit
  else
    echo -e "\e[31mNo local build found!\e[0m" > /dev/stderr
    exit
  fi
fi

# Check for unzip and wget
echo -e "Testing for unzip..."
if ! command -v unzip &> /dev/null
then
  echo -e "\e[31munzip not installed!\e[0m" > /dev/stderr
  exit
fi
echo -e "Testing for wget..."
if ! command -v wget &> /dev/null
then
  echo -e "\e[31mwget not installed, defaulting to curl!\e[0m"  > /dev/stderr
  DOWNLOAD_CMD="curl -O -L -J -s"
  if ! command -v curl &> /dev/null
  then
    echo -e "\e[31mcurl not installed!\e[0m"  > /dev/stderr
    exit
  fi
fi



cd /tmp
# If the directory exists, delete it
if [ -d "basic_math_operations-install" ]; then
  rm -rf basic_math_operations-install
fi
mkdir basic_math_operations-install
cd basic_math_operations-install
# Download the latest release
$DOWNLOAD_CMD https://github.com/avighnac/basic_math_operations/releases/latest/download/libbasic_math_operations-linux.zip


echo "Sucessfully downloaded the latest release."

unzip "libbasic_math_operations-linux.zip" -d libs

echo "Sucessfully extracted the files."

# Copy the libs to /usr/lib, if they exist then replace them
mkdir -p $PREFIX/lib
mkdir -p $PREFIX/include
cp -r libs/libbasic_math_operations.a $PREFIX/lib/
# Copy the header files to /usr/include
cd libs
find . -name '*.h' -exec cp -prv '{}' "$PREFIX/include" ";"
find . -name '*.hpp' -exec cp -prv '{}' "$PREFIX/include" ";"
cd ..
echo -e "\e[32mInstallation complete!\e[0m"

# Delete the temporary directory
cd ..
rm -rf basic_math_operations-install
