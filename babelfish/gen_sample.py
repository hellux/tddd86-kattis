from string import ascii_lowercase

entryc = 100000
wordc = 100000
l = len(ascii_lowercase)

with open("babelfish/large.in", "w") as f:
    for i in range(entryc):
        chars = [(i % (l**x+1)) % (x+1) for x in range(10)]
        english = "".join([ascii_lowercase[char] for char in chars])
        foreign = english
        f.write("%s %s\n" % (english, foreign))

    f.write("\n")

    for i in range(wordc):
        chars = [(i % (l**x+1)) % (x+1) for x in range(10)]
        foreign = "".join([ascii_lowercase[char] for char in chars])
        f.write("%s\n" % foreign)
