src="ic.c"
input="/tmp/input"
ans="/tmp/answers"

test_count=$1

for i in $(seq "$test_count"); do
    int_start=$((RANDOM-16384))
    int_end=$((RANDOM-16384))
    interval_count=$((RANDOM % ($2+1)));

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

tcc -run "$src" < "$input" > "$ans"
