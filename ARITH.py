import sys

def print_add_or_subtract(first, second, operator):
    if operator == '+':
        result = str(int(first) + int(second))
    else:
        result = str(int(first) - int(second))

    second_line = operator + second
    dash_length = max(len(second_line), len(result))
    total_width = max(len(first), dash_length)

    lines = []
    lines.append(first.rjust(total_width))
    lines.append(second_line.rjust(total_width))
    lines.append(('-' * dash_length).rjust(total_width))
    lines.append(result.rjust(total_width))

    return lines

def print_multiply(first, second):
    result = str(int(first) * int(second))
    second_line = '*' + second

    partial_results = []
    for digit in reversed(second):
        value = int(first) * int(digit)
        partial_results.append(str(value))

    first_dash_length = max(len(second_line), len(partial_results[0]))

    if len(second) == 1:
        total_width = max(len(first), len(second_line), first_dash_length, len(result))

        lines = []
        lines.append(first.rjust(total_width))
        lines.append(second_line.rjust(total_width))
        lines.append(('-' * first_dash_length).rjust(total_width))
        lines.append(result.rjust(total_width))
        return lines

    second_dash_length = len(result)

    for shift, partial in enumerate(partial_results):
        second_dash_length = max(second_dash_length, len(partial) + shift)

    total_width = max(len(first), len(second_line), first_dash_length, second_dash_length)

    lines = []
    lines.append(first.rjust(total_width))
    lines.append(second_line.rjust(total_width))
    lines.append(('-' * first_dash_length).rjust(total_width))

    for shift, partial in enumerate(partial_results):
        lines.append(partial.rjust(total_width - shift))

    lines.append(('-' * second_dash_length).rjust(total_width))
    lines.append(result.rjust(total_width))

    return lines

def solve_expression(expression):
    for operator in ['+', '-', '*']:
        if operator in expression:
            first, second = expression.split(operator)
            if operator == '*':
                return print_multiply(first, second)
            else:
                return print_add_or_subtract(first, second, operator)

def main():
    data = sys.stdin.read().strip().split()
    test_cases = int(data[0])

    output = []

    for i in range(1, test_cases + 1):
        expression = data[i]
        output.extend(solve_expression(expression))
        output.append("")

    sys.stdout.write("\n".join(output))

if __name__ == "__main__":
    main()
