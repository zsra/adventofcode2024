from collections import Counter

codes = open("codes.in").read().split("\n")

key_positions = {c: (i % 3, i // 3) for i, c in enumerate("789456123 0A")}
direction_positions = {c: (i % 3, i // 3) for i, c in enumerate(" ^A<v>")}

def steps(grid: dict[complex, str], sequence: str, multiplier=1):
    px, py = grid["A"]
    bx, by = grid[" "]
    movement_counts = Counter()

    for char in sequence:
        npx, npy = grid[char]
        is_crossing_blank = (npx == bx and py == by) or (npy == by and px == bx)
        movement_counts[(npx - px, npy - py, is_crossing_blank)] += multiplier
        px, py = npx, npy

    return movement_counts

def calculate_result(iterations):

    total_result = 0

    for code in codes:
        movement_counts = steps(key_positions, code)

        for _ in range(iterations + 1):
            movement_counts = sum(
                (
                    steps(
                        direction_positions,
                        ("<" * -x + "v" * y + "^" * -y + ">" * x)[::-1 if is_crossing else 1] + "A",
                        count,
                    )
                    for (x, y, is_crossing), count in movement_counts.items()
                ),
                Counter(),
            )

        total_result += movement_counts.total() * int(code[:3])

    return total_result

print(calculate_result(2))
print(calculate_result(25))
