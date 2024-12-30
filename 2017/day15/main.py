def judge_count(startA, startB, iterations=40000000):
    factorA = 16807
    factorB = 48271
    modulus = 2147483647
    mask = 0xFFFF  # To extract the lowest 16 bits
    count = 0

    valueA = startA
    valueB = startB

    for _ in range(iterations):
        valueA = (valueA * factorA) % modulus
        valueB = (valueB * factorB) % modulus
        if (valueA & mask) == (valueB & mask):
            count += 1

    return count

def picky_judge_count(startA, startB, iterations=5000000):
    factorA = 16807
    factorB = 48271
    modulus = 2147483647
    mask = 0xFFFF  # To extract the lowest 16 bits
    multipleA = 4
    multipleB = 8
    count = 0

    valueA = startA
    valueB = startB

    # Generate only values that meet the new criteria
    for _ in range(iterations):
        while True:
            valueA = (valueA * factorA) % modulus
            if valueA % multipleA == 0:
                break
        while True:
            valueB = (valueB * factorB) % modulus
            if valueB % multipleB == 0:
                break

        if (valueA & mask) == (valueB & mask):
            count += 1

    return count

# Example inputs for both parts
startA = 883
startB = 879

# Part 1
result_part1 = judge_count(startA, startB)
print("Part 1: The judge's final count is", result_part1)

# Part 2
result_part2 = picky_judge_count(startA, startB)
print("Part 2: The judge's final count is", result_part2)
