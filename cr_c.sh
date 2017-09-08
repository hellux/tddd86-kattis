gcc $1 -Wall -g -O2 -std=gnu99 -lm -static
time ./a.out < $2 > sample.out
echo OUTPUT:
cat sample.out
rm a.out
rm sample.out
