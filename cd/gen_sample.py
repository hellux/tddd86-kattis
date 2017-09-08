from random import randint

MAX_CAT = 2*10**6

jack = 10**6
jill = 10**6

with open("cd/cds.txt", "w") as f:
    previous = 0

    f.write("%d %d\n" % (jack, jill))

    for i in range(jack):
        add = randint(1, MAX_CAT//jack)
        current = previous+add
        f.write("%d\n" % (current))
        previous = current

    previous = 0
    for i in range(jill):
        add = randint(1, MAX_CAT//jill)
        current = previous+add
        f.write("%d\n" % (current))
        previous = current
