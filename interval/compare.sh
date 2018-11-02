src1=$1
src2=$2
input=$3

tcc -run "$src1" < $input > /tmp/ans1
tcc -run "$src2" < $input > /tmp/ans2

diff --color /tmp/ans1 /tmp/ans2
