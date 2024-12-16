import heapq
from typing import List, Tuple, Dict, Set

# Type aliases for clarity
Grid = List[List[str]]
Point = Tuple[int, int]
State = Tuple[int, int, str]


def parse(lines: List[str]) -> Tuple[Grid, Point, Point]:
    grid = [list(line.strip()) for line in lines]

    start = end = None
    for r, row in enumerate(grid):
        for c, ch in enumerate(row):
            if ch == "S":
                start = (r, c)
            elif ch == "E":
                end = (r, c)

    if not (start and end):
        raise ValueError("Grid must contain a start (S) and end (E) position.")

    return grid, start, end


def dijkstra(grid: Grid, starts: List[State]) -> Dict[State, int]:
    directions = {"E": (0, 1), "W": (0, -1), "N": (-1, 0), "S": (1, 0)}
    dist = {}
    priority_queue = []

    for sr, sc, direction in starts:
        dist[(sr, sc, direction)] = 0
        heapq.heappush(priority_queue, (0, sr, sc, direction))

    while priority_queue:
        current_dist, row, col, direction = heapq.heappop(priority_queue)

        # Skip if a shorter path was already found
        if dist[(row, col, direction)] < current_dist:
            continue

        # Switch direction
        for next_dir in directions.keys():
            if next_dir != direction:
                new_dist = current_dist + 1000
                state = (row, col, next_dir)
                if state not in dist or dist[state] > new_dist:
                    dist[state] = new_dist
                    heapq.heappush(priority_queue, (new_dist, row, col, next_dir))

        # Move in the current direction
        dr, dc = directions[direction]
        next_row, next_col = row + dr, col + dc

        if (
            0 <= next_row < len(grid)
            and 0 <= next_col < len(grid[0])
            and grid[next_row][next_col] != "#"
        ):
            new_dist = current_dist + 1
            state = (next_row, next_col, direction)
            if state not in dist or dist[state] > new_dist:
                dist[state] = new_dist
                heapq.heappush(priority_queue, (new_dist, next_row, next_col, direction))

    return dist


def part1(input: Tuple[Grid, Point, Point]) -> int:
    grid, start, end = input
    sr, sc = start
    er, ec = end

    distances = dijkstra(grid, [(sr, sc, "E")])
    return min(distances.get((er, ec, dir), float("inf")) for dir in "EWNS")


def part2(input: Tuple[Grid, Point, Point]) -> int:
    grid, start, end = input
    sr, sc = start
    er, ec = end

    from_start = dijkstra(grid, [(sr, sc, "E")])
    from_end = dijkstra(grid, [(er, ec, dir) for dir in "EWNS"])
    optimal_distance = part1(input)

    flip = {"E": "W", "W": "E", "N": "S", "S": "N"}
    meeting_points = set()

    for row in range(len(grid)):
        for col in range(len(grid[0])):
            for direction in "EWNS":
                state_from_start = (row, col, direction)
                state_from_end = (row, col, flip[direction])

                if (
                    state_from_start in from_start
                    and state_from_end in from_end
                    and from_start[state_from_start] + from_end[state_from_end]
                    == optimal_distance
                ):
                    meeting_points.add((row, col))

    return len(meeting_points)


if __name__ == "__main__":
    with open("reindeer.in") as f:
        real_input = parse(f.readlines())

    print("Answer #1:", part1(real_input))
    print("Answer #2:", part2(real_input))
