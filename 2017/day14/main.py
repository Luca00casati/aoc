def knot_hash(input_string):
    lengths = [ord(c) for c in input_string] + [17, 31, 73, 47, 23]
    nums = list(range(256))
    pos = 0
    skip = 0

    for _ in range(64):
        for length in lengths:
            if length > 0:
                indices = [(pos + i) % len(nums) for i in range(length)]
                values = [nums[i] for i in indices][::-1]
                for i, v in zip(indices, values):
                    nums[i] = v
            pos = (pos + length + skip) % len(nums)
            skip += 1

    dense_hash = []
    for i in range(0, 256, 16):
        block = 0
        for num in nums[i:i + 16]:
            block ^= num
        dense_hash.append(block)

    return ''.join(f'{b:02x}' for b in dense_hash)

def hex_to_binary(hex_string):
    return bin(int(hex_string, 16))[2:].zfill(128)

def count_used_bits(key):
    total_used = 0
    for row in range(128):
        row_key = f"{key}-{row}"
        knot_hash_value = knot_hash(row_key)
        binary_string = hex_to_binary(knot_hash_value)
        total_used += binary_string.count('1')
    return total_used

def count_regions(key):
    grid = []
    for row in range(128):
        row_key = f"{key}-{row}"
        knot_hash_value = knot_hash(row_key)
        binary_string = hex_to_binary(knot_hash_value)
        grid.append([int(bit) for bit in binary_string])

    def dfs(x, y):
        if x < 0 or y < 0 or x >= 128 or y >= 128 or grid[x][y] == 0:
            return
        grid[x][y] = 0
        dfs(x + 1, y)
        dfs(x - 1, y)
        dfs(x, y + 1)
        dfs(x, y - 1)

    regions = 0
    for i in range(128):
        for j in range(128):
            if grid[i][j] == 1:
                regions += 1
                dfs(i, j)

    return regions

key_string = "xlqgujun"

# Part 1
used_squares = count_used_bits(key_string)
print(f"Total used squares: {used_squares}")

# Part 2
total_regions = count_regions(key_string)
print(f"Total regions: {total_regions}")
