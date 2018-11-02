input="/tmp/input"
ans="/tmp/answers"

test_count=$1
interval=$2

for i in $(seq "$test_count"); do
    int_start=$((RANDOM%interval-interval/2))
    int_end=$((RANDOM%interval-interval/2))
    interval_count=$3;

    if [ "$int_end" -lt "$int_start" ]; then
        tmp=$int_start;
        int_start=$int_end;
        int_end=$tmp;
    fi

    echo $int_start $int_end
    echo $interval_count
    for i in $(seq $interval_count); do
        a=$((RANDOM%interval-interval/2))
        b=$((RANDOM%interval-interval/2))
        if [ "$a" -lt "$b" ];
        then echo $a $b
        else echo $b $a
        fi
    done
done > "$input"
