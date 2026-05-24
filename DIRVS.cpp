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

    int value = 0;
    while (c != EOF && c > ' ') {
        value = value * 10 + (c - '0');
        c = getCharFast();
    }

    return value;
}

int rowsCount, columnsCount;
int terrain[205][205];

bool hasDirectVisibility(int sourceRow, int sourceCol, int targetRow, int targetCol) {
    if (sourceRow == targetRow && sourceCol == targetCol) {
        return true;
    }

    int rowDelta = targetRow - sourceRow;
    int colDelta = targetCol - sourceCol;

    int rowStep = (rowDelta > 0) ? 1 : (rowDelta < 0 ? -1 : 0);
    int colStep = (colDelta > 0) ? 1 : (colDelta < 0 ? -1 : 0);

    int absoluteRowDelta = abs(rowDelta);
    int absoluteColDelta = abs(colDelta);

    const long double INF = 1e100L;
    const long double EPS = 1e-12L;

    long double nextRowBoundary =
        absoluteRowDelta == 0 ? INF : 0.5L / absoluteRowDelta;
    long double nextColBoundary =
        absoluteColDelta == 0 ? INF : 0.5L / absoluteColDelta;

    long double rowBoundaryStep =
        absoluteRowDelta == 0 ? INF : 1.0L / absoluteRowDelta;
    long double colBoundaryStep =
        absoluteColDelta == 0 ? INF : 1.0L / absoluteColDelta;

    int currentRow = sourceRow;
    int currentCol = sourceCol;

    long double currentTime = 0.0L;

    long double sourceHeight = terrain[sourceRow][sourceCol];
    long double heightDelta = terrain[targetRow][targetCol] - terrain[sourceRow][sourceCol];

    while (true) {
        long double exitTime = min(nextRowBoundary, nextColBoundary);
        if (exitTime > 1.0L) {
            exitTime = 1.0L;
        }

        if (exitTime > currentTime + EPS) {
            long double checkTime;

            if (heightDelta >= 0) {
                checkTime = currentTime;
            } else {
                checkTime = exitTime;
            }

            long double lineHeight = sourceHeight + 0.5L + checkTime * heightDelta;

            if (lineHeight < terrain[currentRow][currentCol] - EPS) {
                return false;
            }
        }

        if (currentRow == targetRow && currentCol == targetCol && exitTime >= 1.0L - EPS) {
            break;
        }

        if (nextRowBoundary < nextColBoundary - EPS) {
            currentTime = nextRowBoundary;
            currentRow += rowStep;
            nextRowBoundary += rowBoundaryStep;
        } else if (nextColBoundary < nextRowBoundary - EPS) {
            currentTime = nextColBoundary;
            currentCol += colStep;
            nextColBoundary += colBoundaryStep;
        } else {
            currentTime = nextRowBoundary;
            currentRow += rowStep;
            currentCol += colStep;
            nextRowBoundary += rowBoundaryStep;
            nextColBoundary += colBoundaryStep;
        }
    }

    return true;
}

int main() {
    int testCases = nextInt();

    while (testCases--) {
        rowsCount = nextInt();
        columnsCount = nextInt();

        for (int row = 0; row < rowsCount; row++) {
            for (int col = 0; col < columnsCount; col++) {
                terrain[row][col] = nextInt();
            }
        }

        int startRow = nextInt() - 1;
        int startCol = nextInt() - 1;
        int targetRow = nextInt() - 1;
        int targetCol = nextInt() - 1;

        int totalCells = rowsCount * columnsCount;

        vector<int> distance(totalCells, -1);
        vector<signed char> visibilityCache(totalCells, -1);

        auto cellId = [&](int row, int col) {
            return row * columnsCount + col;
        };

        auto isVisibleFromAtLeastOneBTS = [&](int row, int col) -> bool {
            int id = cellId(row, col);

            if (visibilityCache[id] != -1) {
                return visibilityCache[id] == 1;
            }

            bool visible =
                hasDirectVisibility(startRow, startCol, row, col) ||
                hasDirectVisibility(targetRow, targetCol, row, col);

            visibilityCache[id] = visible ? 1 : 0;
            return visible;
        };

        queue<int> bfsQueue;

        int startId = cellId(startRow, startCol);
        int targetId = cellId(targetRow, targetCol);

        distance[startId] = 0;
        bfsQueue.push(startId);

        int rowMove[4] = {-1, 1, 0, 0};
        int colMove[4] = {0, 0, -1, 1};

        while (!bfsQueue.empty()) {
            int currentId = bfsQueue.front();
            bfsQueue.pop();

            if (currentId == targetId) {
                break;
            }

            int currentRow = currentId / columnsCount;
            int currentCol = currentId % columnsCount;

            for (int direction = 0; direction < 4; direction++) {
                int nextRow = currentRow + rowMove[direction];
                int nextCol = currentCol + colMove[direction];

                if (nextRow < 0 || nextRow >= rowsCount || nextCol < 0 || nextCol >= columnsCount) {
                    continue;
                }

                int nextId = cellId(nextRow, nextCol);

                if (distance[nextId] != -1) {
                    continue;
                }

                int heightDifference = terrain[nextRow][nextCol] - terrain[currentRow][currentCol];

                if (heightDifference > 1 || heightDifference < -3) {
                    continue;
                }

                if (!isVisibleFromAtLeastOneBTS(nextRow, nextCol)) {
                    continue;
                }

                distance[nextId] = distance[currentId] + 1;
                bfsQueue.push(nextId);
            }
        }

        if (distance[targetId] == -1) {
            printf("Mission impossible!\n");
        } else {
            printf("The shortest path is %d steps long.\n", distance[targetId]);
        }
    }

    return 0;
}
