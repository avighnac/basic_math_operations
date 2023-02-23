cd linux || exit
for file in *.asm
do
  yasm -g dwarf2 -f elf64 $file
done
mv ./*.o ../
cd ../cross-platform || exit
for file in *.c
do
  gcc $file -g -c
done
mv ./*.o ../
cd ..
gcc basic_math_operations.c -g -c

v=""
for file in *.o
do
  v+=$file
  v+=" "
done

gcc remove_zeroes.c -g -c

g++ ../tests/test.cpp $v -I.
# rm ./*.o