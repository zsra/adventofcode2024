data = open('cheats.in').read().strip().split('\n')

grid = {}
start, end, cnt = None, None, 2

for r, l in enumerate(data):
    for c, v in enumerate(l):
        grid[(r, c)] = v
        if v == 'S':
            start = (r, c)
        if v == 'E':
            end = (r, c)
        if v == '.':
            cnt += 1

ds = ((1, 0), (-1, 0), (0, 1), (0, -1))

def bfs(start_pos):
    dist_map = {start_pos: 0}
    queue = [start_pos]

    while queue:
        r, c = queue.pop(0)
        d = dist_map[(r, c)]
        for dr, dc in ds:
            nr, nc = r + dr, c + dc
            if (nr, nc) not in dist_map and grid.get((nr, nc)) != '#':
                queue.append((nr, nc))
                dist_map[(nr, nc)] = d + 1
    return dist_map

def calculate_cheats_part_1(dist_map):
    cheats = {}
    for r, c in dist_map:
        for dr, dc in ds:
            nr, nc = r + 2 * dr, c + 2 * dc
            if (nr, nc) in dist_map:
                diff = dist_map[(r, c)] - dist_map[(nr, nc)] - 2
                if diff > 0:
                    cheats[((r, c), (nr, nc))] = diff
    return cheats

def calculate_cheats_part_2(dist_map):
    cheats = {}
    for r, c in dist_map:
        for i in range(-20, 21):
            for j in range(-20, 21):
                if abs(i) + abs(j) <= 20:
                    nr, nc = r + i, c + j
                    if (nr, nc) in dist_map:
                        diff = dist_map[(r, c)] - dist_map[(nr, nc)] - (abs(i) + abs(j))
                        if diff > 0:
                            cheats[((r, c), (nr, nc))] = diff
    return cheats

def count_cheats(cheats, threshold):
    return sum(1 for n in cheats.values() if n >= threshold)

start_map = bfs(start)

cheats_1 = calculate_cheats_part_1(start_map)
p1 = count_cheats(cheats_1, 100)
print(f"Part 1: {p1}")

cheats_2 = calculate_cheats_part_2(start_map)
p2 = count_cheats(cheats_2, 100)
print(f"Part 2: {p2}")
