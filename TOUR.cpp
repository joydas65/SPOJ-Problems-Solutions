#include <bits/stdc++.h>
using namespace std;

class FastScanner {
private:
    static const int BUFFER_SIZE = 1 << 16;
    char buffer[BUFFER_SIZE];
    int index, size;

public:
    FastScanner() {
        index = 0;
        size = 0;
    }

    int getChar() {
        if (index >= size) {
            size = fread(buffer, 1, BUFFER_SIZE, stdin);
            index = 0;
            if (size == 0) return EOF;
        }
        return buffer[index++];
    }

    int nextInt() {
        int c = getChar();

        while (c <= ' ' && c != EOF) {
            c = getChar();
        }

        int value = 0;
        while (c > ' ' && c != EOF) {
            value = value * 10 + (c - '0');
            c = getChar();
        }

        return value;
    }
};

void dfsOrder(
    int node,
    const vector<vector<int>>& graph,
    vector<int>& visited,
    vector<int>& order
) {
    visited[node] = 1;

    for (int neighbour : graph[node]) {
        if (!visited[neighbour]) {
            dfsOrder(neighbour, graph, visited, order);
        }
    }

    order.push_back(node);
}

void dfsComponent(
    int node,
    int componentId,
    const vector<vector<int>>& reverseGraph,
    vector<int>& component,
    int& componentSize
) {
    component[node] = componentId;
    componentSize++;

    for (int neighbour : reverseGraph[node]) {
        if (component[neighbour] == -1) {
            dfsComponent(neighbour, componentId, reverseGraph, component, componentSize);
        }
    }
}

int main() {
    FastScanner scanner;

    int testCases = scanner.nextInt();

    while (testCases--) {
        int n = scanner.nextInt();

        vector<vector<int>> graph(n + 1);
        vector<vector<int>> reverseGraph(n + 1);

        for (int participant = 1; participant <= n; participant++) {
            int betterCount = scanner.nextInt();

            for (int j = 0; j < betterCount; j++) {
                int betterParticipant = scanner.nextInt();

                graph[betterParticipant].push_back(participant);
                reverseGraph[participant].push_back(betterParticipant);
            }
        }

        vector<int> visited(n + 1, 0);
        vector<int> order;
        order.reserve(n);

        for (int participant = 1; participant <= n; participant++) {
            if (!visited[participant]) {
                dfsOrder(participant, graph, visited, order);
            }
        }

        vector<int> component(n + 1, -1);
        vector<int> componentSizes;

        int componentCount = 0;

        for (int i = n - 1; i >= 0; i--) {
            int participant = order[i];

            if (component[participant] == -1) {
                int size = 0;
                dfsComponent(
                    participant,
                    componentCount,
                    reverseGraph,
                    component,
                    size
                );

                componentSizes.push_back(size);
                componentCount++;
            }
        }

        vector<int> indegree(componentCount, 0);

        for (int u = 1; u <= n; u++) {
            for (int v : graph[u]) {
                int componentU = component[u];
                int componentV = component[v];

                if (componentU != componentV) {
                    indegree[componentV]++;
                }
            }
        }

        int sourceComponent = -1;
        int sourceCount = 0;

        for (int c = 0; c < componentCount; c++) {
            if (indegree[c] == 0) {
                sourceCount++;
                sourceComponent = c;
            }
        }

        if (sourceCount == 1) {
            printf("%d\n", componentSizes[sourceComponent]);
        } else {
            printf("0\n");
        }
    }

    return 0;
}
