import sys
sys.stdin = open("planting.in", "r")
sys.stdout = open("planting.out", "w")

n = int(input())
tree = [0 for _ in range(n)]
ans = 0
for i in range(n - 1):
    a, b = map(int, input().split(" "))
    tree[a - 1] += 1
    tree[b - 1] += 1

print(max(tree) + 1)