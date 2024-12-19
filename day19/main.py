import sys
from functools import lru_cache, partial

@lru_cache(None)
def count(design, op=any):
    if not design:
        return True

    matches = filter(design.startswith, towels)
    return op(count(design[len(m):], op) for m in matches)


lines = open('design.in').read().splitlines()

towels = lines[0].split(', ')
designs = lines[2:]

total1 = sum(map(count, designs))
print('Part 1:', total1)

total2 = sum(map(partial(count, op=sum), designs))
print('Part 2:', total2)