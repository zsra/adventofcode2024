from re import findall

with open("program.in") as file:
    numbers = [int(n) for n in findall(r"(\d+)", file.read())]

a, b, c, *program = numbers

def execute_program(program, a):
    ip, b, c, output = 0, 0, 0, []

    while 0 <= ip < len(program):
        literal = program[ip + 1]
        combo = [0, 1, 2, 3, a, b, c, 99999][program[ip + 1]]

        match program[ip]:
            case 0:  # Advance
                a = int(a / 2**combo)
            case 1:  # XOR with literal
                b ^= literal
            case 2:  # Bitwise operation
                b = combo % 8
            case 3:  # Jump if non-zero
                ip = ip if a == 0 else literal - 2
            case 4:  # XOR b and c
                b ^= c
            case 5:  # Append output
                output.append(combo % 8)
            case 6:  # Bitwise division of a
                b = int(a / 2**combo)
            case 7:  # Bitwise division of a for c
                c = int(a / 2**combo)
        ip += 2

    return output

part1_output = execute_program(program, a)
print("Answer #1:", ",".join(map(str, part1_output)))

def find_a(program, target_output, a=0, depth=0):
    if depth == len(target_output):
        return a

    for i in range(8):
        current_a = a * 8 + i
        output = execute_program(program, current_a)

        if output and output[0] == target_output[depth]:
            if result := find_a(program, target_output, current_a, depth + 1):
                return result

    return 0

reversed_target = program[::-1]
print("Answer #2:", find_a(program, reversed_target))
