from collections import deque
import heapq


def part1(data):
    # Parse data into blocks and gaps
    blocks = deque(enumerate(int(n) for n in data[::2]))
    gaps = deque(int(n) for n in data[1::2])

    # Remove all the gaps
    nogaps = []
    while blocks:
        front_block = blocks.popleft()
        nogaps.append(front_block)
        if gaps:
            front_gap = gaps.popleft()
            while blocks and front_gap:
                bid, bsize = blocks.pop()
                if bsize <= front_gap:
                    nogaps.append((bid, bsize))
                    front_gap -= bsize
                else:
                    nogaps.append((bid, front_gap))
                    blocks.append((bid, bsize - front_gap))
                    front_gap = 0

    # Calculate the required checksum
    total = 0
    i = 0
    for bid, bsize in nogaps:
        total += bid * bsize * (2 * i + bsize - 1) // 2
        i += bsize
    return total


def part2(data):
    # Parse data into blocks and gaps
    is_block = True
    blocks = []
    gaps = [[] for _ in range(10)]
    pos, b_id = 0, 0

    for d in data:
        d = int(d)
        if is_block:
            blocks.append([pos, b_id, d])
            b_id += 1
        else:
            heapq.heappush(gaps[d], pos)
        pos += d
        is_block = not is_block

    # Process each block in reverse order
    checksum = 0
    for b in range(len(blocks))[::-1]:
        bpos, bid, bsize = blocks[b]
        best_pos = bpos

        # Find all gap candidates for the current block
        candidates = [
            (heapq.heappop(gaps[i]), i)
            for i in range(10) if gaps[i] and i >= bsize
        ]
        if candidates:
            gpos, glen = min(candidates)
            if gpos < bpos:
                best_pos = gpos
                candidates.remove((gpos, glen))
                heapq.heappush(gaps[glen - bsize], gpos + bsize)
            for gpos, glen in candidates:
                heapq.heappush(gaps[glen], gpos)
            blocks[b][0] = best_pos

        # Update checksum
        checksum += bid * bsize * (2 * best_pos + bsize - 1) // 2

    return checksum


data = open("filesystem.in").read()
print("Answer #1:", part1(data))
print("Answer #2:", part2(data))
