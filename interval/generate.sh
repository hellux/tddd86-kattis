src="$1"
input="/tmp/input"
ans="/tmp/answers"

test_count=$2

for i in $(seq "$test_count"); do
    int_start=$((RANDOM-16384))
    int_end=$((RANDOM-16384))
    interval_count=$((RANDOM % ($3+1)));

    if [ "$int_end" -lt "$int_start" ]; then
        tmp=$int_start;
        int_start=$int_end;
        int_end=$tmp;
    fi

    echo $int_start $int_end
    echo $interval_count
    for i in $(seq $interval_count); do
        a=$((RANDOM-16384))
        b=$((RANDOM-16384))
        if [ "$a" -lt "$b" ];
        then echo $a $b
        else echo $b $a
        fi
    done
done > "$input"

echo Generated, running...

tcc -run "$src" < "$input" > "$ans"
