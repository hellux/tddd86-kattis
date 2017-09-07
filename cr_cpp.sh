g++ $1 -Wall --std=c++11 &&\
time ./a.out < $2 > sample.out
echo OUTPUT:
cat sample.out
rm a.out
rm sample.out
