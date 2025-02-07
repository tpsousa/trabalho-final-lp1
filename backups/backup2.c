#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000  // Número máximo de vértices

// Estrutura do nó da lista de adjacência
typedef struct NODE {
    int adj;
    struct NODE *next;
} Node;

// Estrutura do grafo com listas de adjacência
typedef struct {
    Node *vertices[MAXV];
    int qntdVertices, qntdArestas, grau[MAXV];  // Graus dos vértices
} ComunityGraph;

// Inicializa um grafo vazio
void CriaGrafo(ComunityGraph *g) {
    g->qntdVertices = 0;
    g->qntdArestas = 0;
    for (int i = 0; i < MAXV; i++) {
        g->grau[i] = 0;
        g->vertices[i] = NULL;
    }
}

// Insere aresta entre os nós e incrementa o grau
void insereAresta(ComunityGraph *g, int x, int y) {
    Node *novoNo = (Node *)malloc(sizeof(Node));
    novoNo->adj = y;
    novoNo->next = g->vertices[x];
    g->vertices[x] = novoNo;
    g->grau[x]++;

    // Como o grafo é não-direcionado, adicionamos a aresta no outro sentido
    novoNo = (Node *)malloc(sizeof(Node));
    novoNo->adj = x;
    novoNo->next = g->vertices[y];
    g->vertices[y] = novoNo;
    g->grau[y]++;

    g->qntdArestas++;
}

// Função para encontrar o vértice com maior grau
int encontrar_vertice_max_grau(ComunityGraph *g) {
    int max_grau = -1, v_max = -1;
    for (int i = 0; i < g->qntdVertices; i++) {
        if (g->grau[i] > max_grau) {
            max_grau = g->grau[i];
            v_max = i;
        }
    }
    return v_max;
}

// Verifica se um vértice está conectado a todos os vértices da comunidade
int conectado_a_comunidade(ComunityGraph *g, int v, int *comunidade, int tam_comunidade) {
    for (int i = 0; i < tam_comunidade; i++) {
        int encontrado = 0;
        Node *aux = g->vertices[v];
        while (aux) {
            if (aux->adj == comunidade[i]) {
                encontrado = 1;
                break;
            }
            aux = aux->next;
        }
        if (!encontrado) return 0;
    }
    return 1;
}

// Algoritmo para encontrar a maior comunidade (clique máximo)
void encontrar_comunidade(ComunityGraph *g) {
    int comunidade[MAXV];
    int tam_comunidade = 0;

    int v_inicial = encontrar_vertice_max_grau(g);
    comunidade[tam_comunidade++] = v_inicial;

    for (int v = 0; v < g->qntdVertices; v++) {
        if (v != v_inicial && conectado_a_comunidade(g, v, comunidade, tam_comunidade)) {
            comunidade[tam_comunidade++] = v;
        }
    }

    // Exibir a comunidade encontrada
    printf("Maior clique encontrado:\nTamanho: %d\nMembros: ", tam_comunidade);
    for (int i = 0; i < tam_comunidade; i++) {
        printf("%d ", comunidade[i]);
    }
    printf("\n");

    // Salvar resultado em um arquivo
    FILE *resultado = fopen("resultado.txt", "w");
    if (resultado == NULL) {
        printf("Erro ao criar arquivo de saída\n");
        exit(1);
    }
    fprintf(resultado, "Tamanho da maior comunidade: %d\nMembros: ", tam_comunidade);
    for (int i = 0; i < tam_comunidade; i++) {
        fprintf(resultado, "%d ", comunidade[i]);
    }
    fprintf(resultado, "\n");
    fclose(resultado);

    printf("A resposta foi salva no arquivo resultado.txt\n");
}

// Função para ler o arquivo e construir o grafo
void elementos_do_grafo(ComunityGraph *g, char *filename) {
    int n, x, y;
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("Erro: Arquivo inválido\n");
        exit(1);
    }

    CriaGrafo(g);

    if (fscanf(fptr, "%d %d", &(g->qntdVertices), &n) != 2) {
        printf("Erro: Não foi possível ler o número de vértices e arestas\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(fptr, "%d %d", &x, &y) != 2) {
            printf("Erro: Não foi possível ler os vértices\n");
            exit(1);
        }
        insereAresta(g, x, y);
    }
    fclose(fptr);
}

int main() {
    ComunityGraph graph;

    // Ler grafo do arquivo
    elementos_do_grafo(&graph, "arquivo.txt");

    // Encontrar maior clique
    encontrar_comunidade(&graph);

    return 0;
}
