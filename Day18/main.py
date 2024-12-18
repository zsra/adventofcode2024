bytes_positions = [tuple(map(int, line.strip().split(','))) for line in open('space.in').readlines()]

def initialize_grid():
    return {(x, y): '.' for x in range(71) for y in range(71)}

def bfs_find_shortest_path(grid, start, target):
    seen = {}
    queue = [(0, start)]
    while queue:
        score, position = queue.pop(0)
        if position in seen and seen[position] <= score:
            continue
        seen[position] = score

        for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            neighbor = (position[0] + dx, position[1] + dy)
            if neighbor in grid and grid[neighbor] != '#':
                queue.append((score + 1, neighbor))

    return seen.get(target, None)

grid = initialize_grid()
for i in range(1024):
    grid[bytes_positions[i]] = '#'

result_part1 = bfs_find_shortest_path(grid, (0, 0), (70, 70))
print('Answer #1:', result_part1)

for i, byte in enumerate(bytes_positions):
    grid = initialize_grid()
    for j in range(i + 1):
        grid[bytes_positions[j]] = '#'

    seen = set()
    queue = [(0, 0)]
    while queue:
        position = queue.pop(0)
        if position in seen:
            continue
        seen.add(position)

        for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            neighbor = (position[0] + dx, position[1] + dy)
            if neighbor in grid and grid[neighbor] != '#':
                queue.append(neighbor)

    if (70, 70) not in seen:
        print('Answer #2:', byte)
        break
