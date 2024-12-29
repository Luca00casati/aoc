def knot_hash_part1(lengths, list_size=256):
    numbers = list(range(list_size))
    current_position = 0
    skip_size = 0
    
    for length in lengths:
        sublist = [numbers[(current_position + i) % list_size] for i in range(length)]
        
        for i in range(length):
            numbers[(current_position + i) % list_size] = sublist[length - 1 - i]
        
        current_position = (current_position + length + skip_size) % list_size
        skip_size += 1
    
    return numbers[0] * numbers[1]

def knot_hash_part2(lengths, list_size=256, rounds=64):
    numbers = list(range(list_size))
    current_position = 0
    skip_size = 0
    
    for _ in range(rounds):
        for length in lengths:
            sublist = [numbers[(current_position + i) % list_size] for i in range(length)]
            
            for i in range(length):
                numbers[(current_position + i) % list_size] = sublist[length - 1 - i]
            
            current_position = (current_position + length + skip_size) % list_size
            skip_size += 1
    
    return numbers

def dense_hash(sparse_hash):
    dense = []
    for i in range(0, 256, 16):
        block = sparse_hash[i:i + 16]
        result = block[0]
        for num in block[1:]:
            result ^= num
        dense.append(result)
    return dense

def to_hex(dense_hash):
    return ''.join(f'{num:02x}' for num in dense_hash)

def get_knot_hash_part2(input_string):
    lengths = list(map(ord, input_string))
    lengths += [17, 31, 73, 47, 23]
    sparse_hash = knot_hash_part2(lengths)
    dense = dense_hash(sparse_hash)
    return to_hex(dense)

input_string = "120,93,0,90,5,80,129,74,1,165,204,255,254,2,50,113"
input_lengths = [120, 93, 0, 90, 5, 80, 129, 74, 1, 165, 204, 255, 254, 2, 50, 113]
result1 = knot_hash_part1(input_lengths)
print("Result (Part 1):", result1)

result2 = get_knot_hash_part2(input_string)
print("Knot Hash (Part 2):", result2)
