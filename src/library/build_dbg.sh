cd linux
for file in *.asm
do
  yasm -g dwarf2 -f elf64 $file
done
mv *.o ../
cd ..
gcc basic_math_operations.c -O3 -c

v=""
for file in *.o
do
  v+=$file
  v+=" "
done

g++ ../tests/test.cpp $v -I.
rm *.o