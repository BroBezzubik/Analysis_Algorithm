best = [2, 2]
wors = [2, 2]

for i in range(2, 100):
    best.append(14 + best[i // 2] + best[i - (i // 2)] + 6 * (i // 2))
    wors.append(14 + wors[i // 2] + wors[i - (i // 2)] + 6 * (i - 1))

for i in range(100):
    print("{};{};{}".format(i, best[i], wors[i]))

# worse[i] = worse[i-1] + 2 * (8 + 3 * 2 ^ ln2(i)) # n * log(n)
