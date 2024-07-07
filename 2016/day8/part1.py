import numpy as np

def create_screen(width, height):
    return np.zeros((height, width), dtype=int)

def apply_instruction(screen, instruction):
    if instruction.startswith("rect"):
        a, b = map(int, instruction.split()[1].split('x'))
        screen[:b, :a] = 1
    elif instruction.startswith("rotate row"):
        y, b = map(int, instruction.split('=')[1].split(' by '))
        screen[y] = np.roll(screen[y], b)
    elif instruction.startswith("rotate column"):
        x, b = map(int, instruction.split('=')[1].split(' by '))
        screen[:, x] = np.roll(screen[:, x], b)
    return screen

def count_lit_pixels(screen):
    return np.sum(screen)

def read_instructions_from_file(file_path):
    with open(file_path, 'r') as file:
        instructions = file.readlines()
    return [instruction.strip() for instruction in instructions]

def print_screen(screen):
    for row in screen:
        print(''.join('#' if pixel else '.' for pixel in row))

def main(file_path):
    screen = create_screen(50, 6)
    instructions = read_instructions_from_file(file_path)
    
    for instruction in instructions:
        screen = apply_instruction(screen, instruction)
    
    lit_pixels = count_lit_pixels(screen)
    print(f"Number of lit pixels: {lit_pixels}")
    print("Final screen state:")
    print_screen(screen)

main('part1input.txt')
"ZJHRKCPLYJ"
