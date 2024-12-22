from collections import defaultdict
from itertools import pairwise

def generate_next(value):
    value ^= (value << 6) & 0xFFFFFF  # XOR with left-shifted value
    value ^= (value >> 5) & 0xFFFFFF  # XOR with right-shifted value
    value ^= (value << 11) & 0xFFFFFF # XOR with another left-shifted value
    return value

# Initialize variables
final_sum = 0
pattern_counts = defaultdict(int)

# Read input numbers from a file
with open('numbers.in') as file:
    for start_number in map(int, file):
        sequence = [start_number]
        for _ in range(2000):
            start_number = generate_next(start_number)
            sequence.append(start_number)

        final_sum += sequence[-1]

        differences = [b % 10 - a % 10 for a, b in pairwise(sequence)]

        seen_patterns = set()
        for i in range(len(differences) - 3):
            pattern = tuple(differences[i:i + 4])
            if pattern not in seen_patterns:
                pattern_counts[pattern] += sequence[i + 4] % 10
                seen_patterns.add(pattern)

# Output the results
print(final_sum, max(pattern_counts.values()))