#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status

INSTALL_DIR="/tmp/basic_math_operations_install"
ZIP_URL="https://github.com/avighnac/basic_math_operations/releases/latest/download/libbasic_math_operations-macos-x86_64.zip"
ZIP_FILE="basic_math_operations.zip"

# Create a temporary directory
mkdir -p "$INSTALL_DIR"
cd "$INSTALL_DIR"

# Download the zip file
curl -L -o "$ZIP_FILE" "$ZIP_URL"

# Extract the zip file
unzip "$ZIP_FILE"

# Move the library to /usr/local/lib
sudo mv libbasic_math_operations.a /usr/local/lib/

# Move the headers to /usr/local/include
sudo mv basic_math_operations.h /usr/local/include/
sudo mv basic_math_operations.hpp /usr/local/include/

# Cleanup
cd ~
rm -rf "$INSTALL_DIR"

echo "Installation complete!"
