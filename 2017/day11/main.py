def hex_distance(steps):
    # Initialize starting coordinates in cube coordinate system
    x, y, z = 0, 0, 0
    max_distance = 0

    # Define movements in cube coordinates
    moves = {
        'n': (0, 1, -1),
        's': (0, -1, 1),
        'ne': (1, 0, -1),
        'sw': (-1, 0, 1),
        'nw': (-1, 1, 0),
        'se': (1, -1, 0),
    }

    # Apply each step to the coordinates
    for step in steps:
        dx, dy, dz = moves[step]
        x += dx
        y += dy
        z += dz
        # Update the maximum distance
        max_distance = max(max_distance, max(abs(x), abs(y), abs(z)))

    # Calculate the distance from the origin
    final_distance = max(abs(x), abs(y), abs(z))
    return final_distance, max_distance

def read_steps_from_file(filename):
    with open(filename, 'r') as file:
        steps = file.read().strip().split(',')
    return steps

if __name__ == "__main__":
    filename = "input.txt"
    steps = read_steps_from_file(filename)
    final_distance, furthest_distance = hex_distance(steps)
    print(f"Final Distance: {final_distance}")
    print(f"Furthest Distance: {furthest_distance}")