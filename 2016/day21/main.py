def read_operations(file_path):
    with open(file_path, 'r') as file:
        return file.readlines()

def swap_position(s, x, y):
    lst = list(s)
    lst[x], lst[y] = lst[y], lst[x]
    return ''.join(lst)

def swap_letter(s, x, y):
    return s.replace(x, '#').replace(y, x).replace('#', y)

def rotate_left(s, steps):
    steps %= len(s)
    return s[steps:] + s[:steps]

def rotate_right(s, steps):
    steps %= len(s)
    return s[-steps:] + s[:-steps]

def rotate_based_on_position_inverse(s, x):
    for i in range(len(s)):
        rotated = rotate_left(s, i)
        if rotate_based_on_position(rotated, x) == s:
            return rotated
    return s

def rotate_based_on_position(s, x):
    index = s.index(x)
    steps = 1 + index
    if index >= 4:
        steps += 1
    return rotate_right(s, steps)

def reverse_positions(s, x, y):
    if x > y:
        x, y = y, x
    return s[:x] + s[x:y+1][::-1] + s[y+1:]

def move_position(s, x, y):
    lst = list(s)
    char = lst.pop(x)
    lst.insert(y, char)
    return ''.join(lst)

def move_position_inverse(s, x, y):
    lst = list(s)
    char = lst.pop(y)
    lst.insert(x, char)
    return ''.join(lst)

def unscramble(password, operations):
    for operation in reversed(operations):
        parts = operation.split()
        if parts[0] == 'swap' and parts[1] == 'position':
            x, y = int(parts[2]), int(parts[5])
            password = swap_position(password, x, y)
        elif parts[0] == 'swap' and parts[1] == 'letter':
            x, y = parts[2], parts[5]
            password = swap_letter(password, x, y)
        elif parts[0] == 'rotate' and (parts[1] == 'left' or parts[1] == 'right'):
            steps = int(parts[2])
            if parts[1] == 'left':
                password = rotate_right(password, steps)
            else:
                password = rotate_left(password, steps)
        elif parts[0] == 'rotate' and parts[1] == 'based':
            x = parts[6]
            password = rotate_based_on_position_inverse(password, x)
        elif parts[0] == 'reverse':
            x, y = int(parts[2]), int(parts[4])
            password = reverse_positions(password, x, y)
        elif parts[0] == 'move':
            x, y = int(parts[2]), int(parts[5])
            password = move_position_inverse(password, x, y)
    return password


def scramble(password, operations):
    for operation in operations:
        parts = operation.split()
        if parts[0] == 'swap' and parts[1] == 'position':
            x, y = int(parts[2]), int(parts[5])
            password = swap_position(password, x, y)
        elif parts[0] == 'swap' and parts[1] == 'letter':
            x, y = parts[2], parts[5]
            password = swap_letter(password, x, y)
        elif parts[0] == 'rotate' and (parts[1] == 'left' or parts[1] == 'right'):
            steps = int(parts[2])
            if parts[1] == 'left':
                password = rotate_left(password, steps)
            else:
                password = rotate_right(password, steps)
        elif parts[0] == 'rotate' and parts[1] == 'based':
            x = parts[6]
            password = rotate_based_on_position(password, x)
        elif parts[0] == 'reverse':
            x, y = int(parts[2]), int(parts[4])
            password = reverse_positions(password, x, y)
        elif parts[0] == 'move':
            x, y = int(parts[2]), int(parts[5])
            password = move_position(password, x, y)
    return password

#part1
#file_path = 'input.txt'
#initial_password = 'abcdefgh'
#operations = read_operations(file_path)
#scrambled_password = scramble(initial_password, operations)
#print(f"Scrambled password: {scrambled_password}")

#part2
file_path = 'input.txt'
scrambled_password = 'fbgdceah'
operations = read_operations(file_path)
unscrambled_password = unscramble(scrambled_password, operations)
print(f"Unscrambled password: {unscrambled_password}")
