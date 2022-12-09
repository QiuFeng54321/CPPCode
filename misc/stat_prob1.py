import random
k = 10000
choices = [0, 1, 2]
rand_choices = random.choices(choices, k=k)
trio_counts = [0, 0, 0]
for i in range(k):
    choice1 = random.choice([0, 1, 2])
    if choice1 == rand_choices[i]:
        trio_counts[0] += 1
    else:
        choice2 = random.choice([choice for choice in choices if choice != choice1])
        if choice2 == rand_choices[i]:
            trio_counts[1] += 1
        else:
            trio_counts[2] += 1
print(trio_counts)
