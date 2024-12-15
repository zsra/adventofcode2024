# Load and parse the input file
grid, instructions = [i.split('\n') for i in open('coordinates.in').read().split('\n\n')]

# Initialize the map and find the starting point
map_state = {}
start = None
for r, line in enumerate(grid):
    for c, v in enumerate(line):
        map_state[(r, c)] = v
        if v == '@':
            start = (r, c)

# Movement directions
directions = {'<': (0, -1), '>': (0, 1), '^': (-1, 0), 'v': (1, 0)}

# Function to handle movement
def move(position, direction):
    r, c = position
    dr, dc = direction
    queue = [position]
    count = 0

    # Traverse until blocked or end
    for r, c in queue:
        if map_state[(r, c)] == '#':
            break
        nr, nc = r + dr, c + dc
        if (nr, nc) in map_state and map_state[(nr, nc)] == 'O':
            count += 1
            queue.append((nr, nc))
        elif map_state[(nr, nc)] == '.':
            queue.append((nr, nc))
            break

    # Update the map based on the queue
    result = None
    for i in reversed(queue):
        if count > 0:
            map_state[i] = 'O'
            count -= 1
        elif result is None:
            map_state[i] = '@'
            result = i
        else:
            map_state[i] = '.'

    return result

# Function to display the map
def draw_map(map_state):
    output = ''
    for r in range(len(grid)):
        for c in range(len(grid[0])):
            output += map_state.get((r, c), ' ')
        output += '\n'
    print(output)

# Execute Part 1
current_position = start
for instruction in ''.join(instructions):
    current_position = move(current_position, directions[instruction])

# Calculate the result for Part 1
part1_result = sum(100 * r + c for (r, c), v in map_state.items() if v == 'O')
print(part1_result)

# Part 2: Expand the map for double-width representation
expanded_map = {}
for r, line in enumerate(grid):
    for c, v in enumerate(line):
        if v == '#':
            expanded_map[(r, 2 * c)] = '#'
            expanded_map[(r, 2 * c + 1)] = '#'
        elif v == 'O':
            expanded_map[(r, 2 * c)] = '['
            expanded_map[(r, 2 * c + 1)] = ']'
        elif v == '.':
            expanded_map[(r, 2 * c)] = '.'
            expanded_map[(r, 2 * c + 1)] = '.'
        elif v == '@':
            start = (r, 2 * c)
            expanded_map[(r, 2 * c)] = '@'
            expanded_map[(r, 2 * c + 1)] = '.'

# Movement function for left/right
def move_lr(position, direction):
    r, c = position
    dr, dc = direction
    queue = [position]
    count = 0

    for r, c in queue:
        if expanded_map[(r, c)] == '#':
            break
        nr, nc = r + dr, c + dc
        if (nr, nc) in expanded_map and expanded_map[(nr, nc)] in '[]':
            count += 1
            queue.append((nr, nc))
        elif expanded_map[(nr, nc)] == '.':
            queue.append((nr, nc))
            break
        else:
            return position

    result = None
    for i in reversed(queue):
        if count > 0:
            r, c = i
            nr, nc = r - dr, c - dc
            expanded_map[i] = expanded_map[(nr, nc)]
            count -= 1
        elif result is None:
            expanded_map[i] = '@'
            result = i
        else:
            expanded_map[i] = '.'

    return result

# Movement function for up/down
def move_ud(position, direction):
    dr, dc = direction
    queue = [position]
    next_positions = {}

    for r, c in queue:
        if expanded_map[(r, c)] == '#':
            return position
        nr, nc = r + dr, c + dc
        next_positions[(nr, nc)] = expanded_map[(r, c)]
        if expanded_map[(nr, nc)] == '#':
            return position
        if expanded_map[(nr, nc)] in '[]':
            queue.append((nr, nc))
            if expanded_map[(nr, nc)] == '[':
                queue.append((nr, nc + 1))
            else:
                queue.append((nr, nc - 1))

    for pos in queue:
        expanded_map[pos] = '.'
    for pos, value in next_positions.items():
        expanded_map[pos] = value

    r, c = position
    return r + dr, c + dc

# Execute Part 2
current_position = start
for instruction in ''.join(instructions):
    if instruction in '<>':
        current_position = move_lr(current_position, directions[instruction])
    else:
        current_position = move_ud(current_position, directions[instruction])

# Calculate the result for Part 2
part2_result = sum(100 * r + c for (r, c), v in expanded_map.items() if v == '[')
print(part2_result)
