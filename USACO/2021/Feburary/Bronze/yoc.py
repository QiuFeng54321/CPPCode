zod = "Ox, Tiger, Rabbit, Dragon, Snake, Horse, Goat, Monkey, Rooster, Dog, Pig, Rat".split(", ")
d = {"Bessie": 1200}
n = int(input())
for i in range(n):
    cmd = input().split(" ")
    new = cmd[0]
    yr = zod.index(cmd[4])
    target = d[cmd[7]]
    t = target % 12
    if cmd[3] == "next":
        diff = yr - t
        if yr <= t:
            diff = yr + 12 - t
        d[new] = target + diff
    else:
        diff = t - yr
        if t <= yr:
            diff = t + 12 - yr
        d[new] = target - diff
    # print("\n", diff, yr, t)
# print(d)
print(abs(d["Bessie"] - d["Elsie"]))