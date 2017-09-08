def pos(array, start, end, value):
    while (start <= end):
        middle = (start + end) / 2
        current = array[middle]

        if current < value:
            start = middle + 1

jack_catalog = []
jack, jill = map(int, input().split())

for _ in range(jack):
    jack_catalog.append(int(input()))

sell = 0
for _ in range(jill):
    if int(input()) in jack_catalog:
        sell += 1

print(sell)

