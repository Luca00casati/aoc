def parse_input(data):
    graph = {}
    for line in data.strip().split("\n"):
        program, connections = line.split(" <-> ")
        graph[int(program)] = list(map(int, connections.split(", ")))
    return graph

def dfs(graph, start, visited):
    stack = [start]
    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            stack.extend(graph[node])

def count_group_members(graph, start):
    visited = set()
    dfs(graph, start, visited)
    return len(visited)

def count_groups(graph):
    visited = set()
    groups = 0
    
    for program in graph:
        if program not in visited:
            groups += 1
            dfs(graph, program, visited)
    
    return groups

with open("input.txt", "r") as file:
    input_data = file.read()

graph = parse_input(input_data)

group_size = count_group_members(graph, 0)
total_groups = count_groups(graph)

print(f"Size of the group containing program ID 0: {group_size}")
print(f"Total number of groups: {total_groups}")
