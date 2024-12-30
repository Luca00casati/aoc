def perform_dance(programs, moves):
    for move in moves:
        if move[0] == 's':
            size = int(move[1:])
            programs = programs[-size:] + programs[:-size]
        elif move[0] == 'x':
            pos_a, pos_b = map(int, move[1:].split('/'))
            programs[pos_a], programs[pos_b] = programs[pos_b], programs[pos_a]
        elif move[0] == 'p':
            prog_a, prog_b = move[1:].split('/')
            idx_a, idx_b = programs.index(prog_a), programs.index(prog_b)
            programs[idx_a], programs[idx_b] = programs[idx_b], programs[idx_a]
    return programs

def read_moves_from_file(filename):
    with open(filename, 'r') as file:
        moves = file.read().strip().split(',')
    return moves

def find_final_order_after_repeated_dances(programs, moves, repetitions):
    seen_orders = {}
    current_order = programs[:]
    count = 0
    
    while tuple(current_order) not in seen_orders:
        seen_orders[tuple(current_order)] = count
        current_order = perform_dance(current_order, moves)
        count += 1

    cycle_length = count - seen_orders[tuple(current_order)]
    remaining_dances = (repetitions - seen_orders[tuple(current_order)]) % cycle_length
    for _ in range(remaining_dances):
        current_order = perform_dance(current_order, moves)
    
    return current_order

def part_1():
    initial_programs = list("abcdefghijklmnop")
    dance_moves = read_moves_from_file("input.txt")
    final_order = perform_dance(initial_programs, dance_moves)
    print("Part 1 final order:", "".join(final_order))

def part_2():
    initial_programs = list("abcdefghijklmnop")
    dance_moves = read_moves_from_file("input.txt")
    repetitions = 1000000000
    final_order = find_final_order_after_repeated_dances(initial_programs, dance_moves, repetitions)
    print("Part 2 final order:", "".join(final_order))

part_1()
part_2()
