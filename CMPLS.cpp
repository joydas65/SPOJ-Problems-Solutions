#include <bits/stdc++.h>
using namespace std;

static const int BUFFER_SIZE = 1 << 16;
static char inputBuffer[BUFFER_SIZE];
static int bufferIndex = 0, bufferSize = 0;

int getCharFast() {
    if (bufferIndex >= bufferSize) {
        bufferSize = fread(inputBuffer, 1, BUFFER_SIZE, stdin);
        bufferIndex = 0;
        if (bufferSize == 0) return EOF;
    }
    return inputBuffer[bufferIndex++];
}

int nextInt() {
    int c = getCharFast();

    while (c != EOF && c <= ' ') {
        c = getCharFast();
    }

    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = getCharFast();
    }

    int value = 0;
    while (c != EOF && c > ' ') {
        value = value * 10 + (c - '0');
        c = getCharFast();
    }

    return value * sign;
}

bool allElementsEqual(const vector<long long>& values) {
    for (int i = 1; i < (int)values.size(); i++) {
        if (values[i] != values[0]) {
            return false;
        }
    }
    return true;
}

int main() {
    int testCases = nextInt();

    string output;

    while (testCases--) {
        int sequenceLength = nextInt();
        int numbersToGenerate = nextInt();

        vector<long long> current(sequenceLength);

        for (int i = 0; i < sequenceLength; i++) {
            current[i] = nextInt();
        }

        vector<long long> lastValues;

        while (true) {
            lastValues.push_back(current.back());

            if (current.size() == 1 || allElementsEqual(current)) {
                break;
            }

            vector<long long> difference;
            difference.reserve(current.size() - 1);

            for (int i = 1; i < (int)current.size(); i++) {
                difference.push_back(current[i] - current[i - 1]);
            }

            current.swap(difference);
        }

        for (int step = 0; step < numbersToGenerate; step++) {
            for (int level = (int)lastValues.size() - 2; level >= 0; level--) {
                lastValues[level] += lastValues[level + 1];
            }

            if (step > 0) output.push_back(' ');
            output += to_string(lastValues[0]);
        }

        output.push_back('\n');
    }

    cout << output;

    return 0;
}
