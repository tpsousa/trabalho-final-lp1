#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

typedef struct {
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    char nodes[MAX_NODES][50];
    int nodeCount;
} MaxConnectedGraph;

// Inicializa o grafo
void initGraph(MaxConnectedGraph *graph) {
    graph->nodeCount = 0;
    memset(graph->adjacencyMatrix, 0, sizeof(graph->adjacencyMatrix));
}

// Adiciona um nó ao grafo
void addNode(MaxConnectedGraph *graph, const char *node) {
    int i;
    // Verifica se o nó já existe
    for (i = 0; i < graph->nodeCount; i++) {
        if (strcmp(graph->nodes[i], node) == 0) {
            printf("Nó '%s' já existe no grafo.\n", node);
            return;
        }
    }

    // Adiciona o nó ao grafo
    strcpy(graph->nodes[graph->nodeCount], node);

    // Conecta o novo nó a todos os outros nós existentes
    for (i = 0; i < graph->nodeCount; i++) {
        graph->adjacencyMatrix[graph->nodeCount][i] = 1;
        graph->adjacencyMatrix[i][graph->nodeCount] = 1;
    }

    graph->nodeCount++;
}

// Exibe o grafo
void displayGraph(MaxConnectedGraph *graph) {
    int i, j;
    printf("Grafo (matriz de adjacência):\n");
    for (i = 0; i < graph->nodeCount; i++) {
        printf("%s -> ", graph->nodes[i]);
        for (j = 0; j < graph->nodeCount; j++) {
            if (graph->adjacencyMatrix[i][j]) {
                printf("%s ", graph->nodes[j]);
            }
        }
        printf("\n");
    }
}

// Realiza a busca em profundidade (DFS)
void dfs(MaxConnectedGraph *graph, int startIndex, int visited[]) {
    visited[startIndex] = 1;
    printf("%s ", graph->nodes[startIndex]);

    for (int i = 0; i < graph->nodeCount; i++) {
        if (graph->adjacencyMatrix[startIndex][i] && !visited[i]) {
            dfs(graph, i, visited);
        }
    }
}

// Função principal
int main() {
    MaxConnectedGraph graph;
    initGraph(&graph);

    addNode(&graph, "A");
    addNode(&graph, "B");
    addNode(&graph, "C");
    addNode(&graph, "D");

    printf("Grafo:\n");
    displayGraph(&graph);

    printf("\nDFS a partir do nó 'A':\n");
    int visited[MAX_NODES] = {0};
    dfs(&graph, 0, visited); // Começa do índice 0 (nó "A")

    return 0;
}








