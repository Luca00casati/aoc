def run_assembunny_code(instructions):
    registers = {'a': 0, 'b': 0, 'c': 1, 'd': 0}
    operations = [line.split() for line in instructions.strip().split('\n')]
    i = 0
    
    while i < len(operations):
        op = operations[i]
        
        if op[0] == 'cpy':
            x = op[1]
            y = op[2]
            if y in registers:
                if x in registers:
                    registers[y] = registers[x]
                else:
                    registers[y] = int(x)
        
        elif op[0] == 'inc':
            x = op[1]
            if x in registers:
                registers[x] += 1
        
        elif op[0] == 'dec':
            x = op[1]
            if x in registers:
                registers[x] -= 1
        
        elif op[0] == 'jnz':
            x = op[1]
            y = int(op[2])
            if (x in registers and registers[x] != 0) or (x.isdigit() and int(x) != 0):
                i += y
                continue
        
        i += 1
    
    return registers['a']

instructions = """
cpy 1 a
cpy 1 b
cpy 26 d
jnz c 2
jnz 1 5
cpy 7 c
inc d
dec c
jnz c -2
cpy a c
inc a
dec b
jnz b -2
cpy c b
dec d
jnz d -6
cpy 19 c
cpy 14 d
inc a
dec d
jnz d -2
dec c
jnz c -5
"""

print(run_assembunny_code(instructions))