# t = int(input())


def solve(o):
    l = [0, 0, 0, 0]
    passed = {}
    for inp, res in o:
        if inp in passed.keys() and passed[inp] != res:
            return False
        passed[inp] = res
        l[res] |= inp
        l[res + 2] |= ~inp
    if l[0] ^ l[1] == 0 and l[2] ^ l[3] == 0:
        return False
    return True

# def solve():
#     n, m = map(int, input().split())
#     l=[]
#     for _ in range(m):
#         inp, res = input().split()
#         l.append((inp, int(res)))
#     for i in range(n):
#         r = [1] * 4
#         for j in range(l):
#             inp, res = j
#             r[res] &= inp[i]
#             r[res + 2] &= ~inp[i]


def gen():
    from random import randint, sample, choices
    import itertools
    k = 100
    n = randint(2, k)
    m = randint(2, min(100, 2**n))
    print(n, m)
    conds = list(zip(sample(range(n), k=n), choices('01', k=n), choices('01', k=n)))
    for i in range(len(conds)):
        c,e,r = conds[i]
        header = f"if (b[{c}] == {e})"
        if i != 0: header = f"elif (b[{c}] == {e})"
        if i == len(conds) - 1: header = "else"
        print(header, f"return {r}")
    res = []
    numseq = sample(range(min(100, 2**n)), k=m)
    for num in numseq:
        x = bin(num)[2:].rjust(n, '0')
        xres = str(randint(0, 1))
        for c, e, r in conds:
            if x[c] == e:
                xres = r
                break
        res.append((int(x, 2), int(xres)))
        print(x, xres)
    return solve(res)
    
for i in range(100):
    res = gen()
    if not res:
        print("??")
        break
    


# for _ in range(t):
#     n, m = map(int, input().split())
#     o = []
#     for i in range(m):
#         o.append((int(x, 2) for x in input().split()))
#     solve(o)
