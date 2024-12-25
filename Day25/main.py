import itertools
import sys
from collections import Counter, defaultdict
from copy import deepcopy
from heapq import heappop, heappush
from typing import List, Set, Tuple

import multiprocess as mp
import numpy as np

sys.setrecursionlimit(100000)

def read_lines_to_list() -> List[str]:
    """Reads lines from the input file and returns them as a list of strings."""
    lines: List[str] = []
    with open('pairs.in', "r", encoding="utf-8") as f:
        for line in f:
            lines.append(line.strip())
    return lines

def parse_input(lines: List[str]) -> Tuple[List[List[int]], List[List[int]]]:
    locks, keys = [], []
    current_item = [-1, -1, -1, -1, -1]
    is_lock = None

    for line in lines:
        if line == "":
            if is_lock:
                locks.append(current_item)
            else:
                keys.append(current_item)
            current_item = [-1, -1, -1, -1, -1]
            is_lock = None
            continue

        if is_lock is None:
            is_lock = line == "#####"

        for index, char in enumerate(line):
            if char == "#":
                current_item[index] += 1

    if is_lock:
        locks.append(current_item)
    else:
        keys.append(current_item)

    return locks, keys

def part_one():
    lines = read_lines_to_list()
    locks, keys = parse_input(lines)

    valid_combinations = sum(
        1 for lock in locks for key in keys if all(a + b <= 5 for a, b in zip(lock, key))
    )

    print(f"Answer #1: {valid_combinations}")

def main():
    part_one()

if __name__ == '__main__':
    main()