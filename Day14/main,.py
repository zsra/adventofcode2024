import re

# Define the width and height of the grid
GRID_WIDTH, GRID_HEIGHT = 101, 103

with open('factors.in') as file:
    bots = [list(map(int, re.findall(r'-?\d+', line))) for line in file]

def calculate_danger_score(time):
    # Initialize counters for each quadrant
    quadrant_1 = quadrant_2 = quadrant_3 = quadrant_4 = 0

    for x, y, velocity_x, velocity_y in bots:
        # Calculate the position of the bot at time `time`
        current_x = (x + velocity_x * time) % GRID_WIDTH
        current_y = (y + velocity_y * time) % GRID_HEIGHT

        # Determine which quadrant the bot is in
        if current_x > GRID_WIDTH // 2 and current_y > GRID_HEIGHT // 2:
            quadrant_1 += 1  # Top-right quadrant
        elif current_x > GRID_WIDTH // 2 and current_y < GRID_HEIGHT // 2:
            quadrant_2 += 1  # Bottom-right quadrant
        elif current_x < GRID_WIDTH // 2 and current_y > GRID_HEIGHT // 2:
            quadrant_3 += 1  # Top-left quadrant
        elif current_x < GRID_WIDTH // 2 and current_y < GRID_HEIGHT // 2:
            quadrant_4 += 1  # Bottom-left quadrant

    # Return the product of counts in all quadrants
    return quadrant_1 * quadrant_2 * quadrant_3 * quadrant_4

# Print the danger score at time 100
print("Danger score at time 100:", calculate_danger_score(100))

# Find the time within the range [0, 9999] that minimizes the danger score
optimal_time = min(range(10_000), key=calculate_danger_score)
print("Optimal time with minimum danger score:", optimal_time)
