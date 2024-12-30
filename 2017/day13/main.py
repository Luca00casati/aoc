def calculate_severity_and_delay(filename):
    with open(filename, 'r') as file:
        layers = {}
        for line in file:
            depth, range_ = map(int, line.strip().split(': '))
            layers[depth] = range_

    severity = 0
    for depth, range_ in layers.items():
        if depth % ((range_ - 1) * 2) == 0:
            severity += depth * range_

    def is_caught(delay):
        for depth, range_ in layers.items():
            if (depth + delay) % ((range_ - 1) * 2) == 0:
                return True
        return False

    delay = 0
    while is_caught(delay):
        delay += 1

    return severity, delay

filename = 'input.txt'
severity, delay = calculate_severity_and_delay(filename)
print(f"Total severity if leaving immediately: {severity}")
print(f"Minimum delay to avoid being caught: {delay}")
