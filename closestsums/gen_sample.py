from random import randint

n = 1000
m = 25

with open("closestsums/large.in", "w") as f:
    f.write("%d\n" % n)
    for _ in range(n):
        f.write("%d\n" % randint(-10**7, 10**7))

    f.write("%d\n" %  m)
    for _ in range(m):
        f.write("%d\n" % randint(-10**7, 10**7))
