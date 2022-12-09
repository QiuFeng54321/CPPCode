import sys
sys.stdin = open("planting.in", "r")
sys.stdout = open("planting.out", "w")

n = int(input())
tree = [[] for _ in range(n)]
ans = 0
for i in range(n - 1):
    a, b = map(int, input().split(" "))
    tree[a - 1].append(b - 1)
    tree[b - 1].append(a - 1)
# 父节点在tree中的位置和父节点被分配到的数，current同理
def dfs(parent, parentW, current, currentW):
    childW = 1
    for child in tree[current]:
        if child == parent: continue
        # 当前节点和父节点的weight排除
        while childW == currentW or childW == parentW:
            childW += 1
        global ans
        ans = max(ans, childW)
        dfs(current, currentW, child, childW)
        childW += 1
# 随便取个根（0），没有父节点Parent何ParentW就随便填
dfs(0, 0, 0, 1)
# print(weights)
print(ans)