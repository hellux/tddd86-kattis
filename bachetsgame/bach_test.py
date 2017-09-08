def show_wins(stones, M):
    wins = [False for _ in range(stones)]

    for i in range(1, stones):
        for m in M:
            index = i - m
            if index >= 0 and not wins[index]:
                wins[i] = True
                break

    for i in range(1, stones):
        print("+" if wins[i] else "_", end="")
    print()

show_wins(124, [1, 8])
