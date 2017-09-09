#!/bin/env python

tests = int(input())
l = 'left'
r = 'right'

for _ in range(tests):
    length, cars = map(int, input().split())
    length *= 100

    queues = {l : [], r : []}

    for _ in range(cars):
        car_length, car_bank = input().split()
        queues[car_bank].append(int(car_length))

    bank = l
    space = length
    trips = 1

    while (queues[l] or queues[r]):
        if not queues[bank]:
            pass
        elif queues[bank][0] <= space:
            space -= queues[bank].pop(0)
            continue

        bank = r if bank == l else l
        trips += 1
        space = length

    print(trips)
