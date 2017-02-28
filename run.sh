echo compile library
gcc tensor.c -c -o test/tensor.o -std=c99
echo compile done
echo testing
cd test
for i in *.c;
do
    echo $i;
    gcc tensor.o $i;
    ./a.out;
done;
echo test done
