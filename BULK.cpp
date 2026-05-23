#include <bits/stdc++.h>
using namespace std;

static const int MAX_COORD = 1000;
static const int MAX_POINTS = 205;
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

struct Face {
    int fixedX;
    int pointCount;
    int y[MAX_POINTS];
    int z[MAX_POINTS];
    int minZ;
    int maxZ;
};

struct SegmentTree {
    int count[4096];
    long long alternatingSum[4096];

    void clear() {
        memset(count, 0, sizeof(count));
        memset(alternatingSum, 0, sizeof(alternatingSum));
    }

    void toggle(int node, int left, int right, int position) {
        if (left == right) {
            count[node] ^= 1;
            alternatingSum[node] = count[node] ? -1LL * left : 0LL;
            return;
        }

        int mid = (left + right) >> 1;

        if (position <= mid) {
            toggle(node << 1, left, mid, position);
        } else {
            toggle(node << 1 | 1, mid + 1, right, position);
        }

        int leftNode = node << 1;
        int rightNode = leftNode | 1;

        count[node] = count[leftNode] + count[rightNode];

        if (count[leftNode] & 1) {
            alternatingSum[node] = alternatingSum[leftNode] - alternatingSum[rightNode];
        } else {
            alternatingSum[node] = alternatingSum[leftNode] + alternatingSum[rightNode];
        }
    }

    long long currentInsideLength() const {
        return alternatingSum[1];
    }
};

static vector<int> eventsAtY[1001];
static SegmentTree segmentTree;

int main() {
    int testCases = nextInt();

    while (testCases--) {
        int faceCount = nextInt();

        vector<Face> xFaces;
        xFaces.reserve(faceCount);

        vector<int> yCoordinates;
        vector<int> zCoordinates;

        int x[MAX_POINTS], y[MAX_POINTS], z[MAX_POINTS];

        for (int faceIndex = 0; faceIndex < faceCount; faceIndex++) {
            int pointCount = nextInt();

            for (int i = 0; i < pointCount; i++) {
                x[i] = nextInt();
                y[i] = nextInt();
                z[i] = nextInt();
            }

            bool isXFace = true;

            for (int i = 1; i < pointCount; i++) {
                if (x[i] != x[0]) {
                    isXFace = false;
                    break;
                }
            }

            if (!isXFace) continue;

            Face face;
            face.fixedX = x[0];
            face.pointCount = pointCount;
            face.minZ = z[0];
            face.maxZ = z[0];

            for (int i = 0; i < pointCount; i++) {
                face.y[i] = y[i];
                face.z[i] = z[i];

                face.minZ = min(face.minZ, z[i]);
                face.maxZ = max(face.maxZ, z[i]);

                yCoordinates.push_back(y[i]);
                zCoordinates.push_back(z[i]);
            }

            xFaces.push_back(face);
        }

        if (xFaces.empty()) {
            printf("The bulk is composed of 0 units.\n");
            continue;
        }

        sort(yCoordinates.begin(), yCoordinates.end());
        yCoordinates.erase(unique(yCoordinates.begin(), yCoordinates.end()), yCoordinates.end());

        sort(zCoordinates.begin(), zCoordinates.end());
        zCoordinates.erase(unique(zCoordinates.begin(), zCoordinates.end()), zCoordinates.end());

        static int yIndexOf[1001];
        static int zIndexOf[1001];

        fill(yIndexOf, yIndexOf + 1001, -1);
        fill(zIndexOf, zIndexOf + 1001, -1);

        for (int i = 0; i < (int)yCoordinates.size(); i++) {
            yIndexOf[yCoordinates[i]] = i;
        }

        for (int i = 0; i < (int)zCoordinates.size(); i++) {
            zIndexOf[zCoordinates[i]] = i;
        }

        int ySegmentCount = (int)yCoordinates.size() - 1;
        int zSegmentCount = (int)zCoordinates.size() - 1;

        long long volume = 0;
        int intersections[MAX_POINTS];

        for (int zIndex = 0; zIndex < zSegmentCount; zIndex++) {
            for (int yIndex = 0; yIndex <= ySegmentCount; yIndex++) {
                eventsAtY[yIndex].clear();
            }

            int zLow = zCoordinates[zIndex];
            int zHeight = zCoordinates[zIndex + 1] - zCoordinates[zIndex];

            for (const Face& face : xFaces) {
                if (!(face.minZ <= zLow && zLow < face.maxZ)) {
                    continue;
                }

                int intersectionCount = 0;

                for (int i = 0; i < face.pointCount; i++) {
                    int j = (i + 1 == face.pointCount) ? 0 : i + 1;

                    int z1 = face.z[i];
                    int z2 = face.z[j];

                    if (z1 == z2) continue;

                    int lowZ = min(z1, z2);
                    int highZ = max(z1, z2);

                    if (lowZ <= zLow && zLow < highZ) {
                        intersections[intersectionCount++] = face.y[i];
                    }
                }

                if (intersectionCount < 2) continue;

                sort(intersections, intersections + intersectionCount);

                for (int i = 0; i + 1 < intersectionCount; i += 2) {
                    int startY = intersections[i];
                    int endY = intersections[i + 1];

                    if (startY == endY) continue;

                    int startIndex = yIndexOf[startY];
                    int endIndex = yIndexOf[endY];

                    eventsAtY[startIndex].push_back(face.fixedX);
                    eventsAtY[endIndex].push_back(face.fixedX);
                }
            }

            segmentTree.clear();

            for (int yIndex = 0; yIndex < ySegmentCount; yIndex++) {
                for (int fixedX : eventsAtY[yIndex]) {
                    segmentTree.toggle(1, 0, MAX_COORD, fixedX);
                }

                long long insideLengthX = segmentTree.currentInsideLength();

                if (insideLengthX != 0) {
                    long long yWidth = yCoordinates[yIndex + 1] - yCoordinates[yIndex];
                    volume += insideLengthX * yWidth * zHeight;
                }
            }
        }

        printf("The bulk is composed of %lld units.\n", volume);
    }

    return 0;
}
