import sys
import math

def main():
    data = sys.stdin.read().strip().split()
    test_cases = int(data[0])

    output = []
    index = 1

    for _ in range(test_cases):
        side_a = float(data[index])
        distance_a = float(data[index + 1])
        distance_b = float(data[index + 2])
        distance_c = float(data[index + 3])
        index += 4

        area = 1.5 * side_a * distance_a

        side_b = side_a * distance_a / distance_b
        side_c = side_a * distance_a / distance_c

        circumradius = side_a * side_b * side_c / (4.0 * area)

        hg_square = (
            4.0 * circumradius * circumradius
            - (4.0 / 9.0) * (side_a * side_a + side_b * side_b + side_c * side_c)
        )

        hg_distance = math.sqrt(max(0.0, hg_square))

        output.append(f"{area:.3f} {hg_distance:.3f}")

    sys.stdout.write("\n".join(output))

if __name__ == "__main__":
    main()
