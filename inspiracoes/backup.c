#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000  // Número máximo de vértices

typedef struct NODE {
    int adj;
    struct NODE *next;
} Node;

typedef struct {
    Node *vertices[MAXV + 1];
    int qntdVertices, qntdArestas, grau[MAXV + 1];
} ComunityGraph;

// Função para criar um grafo vazio
void CriaGrafo(ComunityGraph *g) {
    g->qntdVertices = 0;
    g->qntdArestas = 0;
    for (int i = 0; i < MAXV; i++) {
        g->grau[i] = 0;
        g->vertices[i] = NULL;
    }
}

// Inserir aresta no grafo
void insereAresta(ComunityGraph *g, int x, int y) {
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->adj = y;
    novo->next = g->vertices[x];
    g->vertices[x] = novo;
    g->grau[x]++;

    Node *novo2 = (Node *)malloc(sizeof(Node));
    novo2->adj = x;
    novo2->next = g->vertices[y];
    g->vertices[y] = novo2;
    g->grau[y]++;
}

// Ler o grafo do arquivo
void elementos_do_grafo(ComunityGraph *g, const char *filename) {
    int n, x, y;
    char entrada[10];

    FILE *fptr = fopen(filename, "r");
    if (!fptr) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Lendo a quantidade de vértices e arestas
    if (fscanf(fptr, "%d %d", &(g->qntdVertices), &n) != 2) {
        printf("Erro: Formato inválido no arquivo (linha 1)\n");
        exit(1);
    }

    // Inicializa o grafo
    CriaGrafo(g);

    // Lendo as arestas
    for (int i = 0; i < n; i++) {
        if (fscanf(fptr, "%s %d %d", entrada, &x, &y) != 3) {
            printf("Erro: Formato inválido ao ler as arestas\n");
            exit(1);
        }

        // Insere aresta apenas se "e" for encontrado no início da linha
        if (entrada[0] == 'e') {
            insereAresta(g, x, y);
        }
    }

    fclose(fptr);
}

// Verifica se um vértice está conectado a toda a comunidade atual
int estaConectadoATodos(ComunityGraph *g, int v, int comunidade[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int achou = 0;
        Node *temp = g->vertices[v];
        while (temp) {
            if (temp->adj == comunidade[i]) {
                achou = 1;
                break;
            }
            temp = temp->next;
        }
        if (!achou) return 0; // Se não está conectado a algum, retorna falso
    }
    return 1;
}

// Encontra a maior comunidade conectada
void encontrarMaiorComunidade(ComunityGraph *g, int *maiorComunidade, int *tamanho) {
    int maxGrau = -1, inicial = -1;

    // Encontrar o vértice com maior grau
    for (int i = 1; i <= g->qntdVertices; i++) {
        if (g->grau[i] > maxGrau) {
            maxGrau = g->grau[i];
            inicial = i;
        }
    }

    if (inicial == -1) {
        *tamanho = 0;
        return;
    }

    int comunidade[MAXV];
    int tamanhoAtual = 0;
    comunidade[tamanhoAtual++] = inicial;

    // Tentar adicionar os próximos vértices de maior grau
    for (int i = 1; i <= g->qntdVertices; i++) {
        if (i != inicial && g->grau[i] > 0) {
            if (estaConectadoATodos(g, i, comunidade, tamanhoAtual)) {
                comunidade[tamanhoAtual++] = i;
            }
        }
    }

    // Copiar o resultado para a saída
    *tamanho = tamanhoAtual;
    for (int i = 0; i < tamanhoAtual; i++) {
        maiorComunidade[i] = comunidade[i];
    }
}

// Salvar resultado no arquivo
void salvarResultado(int maxTamanho, int *maiorComunidade) {
    FILE *resultado = fopen("resultado.txt", "w");

    if (resultado == NULL) {
        printf("Erro ao criar arquivo de saída\n");
        exit(1);
    }

    fprintf(resultado, "Tamanho da maior comunidade: %d\n", maxTamanho);
    fprintf(resultado, "Membros: ");
    for (int i = 0; i < maxTamanho; i++) {
        fprintf(resultado, "%d ", maiorComunidade[i]);
    }
    fprintf(resultado, "\n");

    fclose(resultado);
    printf("A resposta foi salva no arquivo resultado.txt\n");
}

int main() {
    ComunityGraph graph;
    int maiorComunidade[MAXV], tamanho;

    // Ler o grafo do arquivo
    elementos_do_grafo(&graph, "arquivo.txt");

    // Encontrar a maior comunidade conectada
    encontrarMaiorComunidade(&graph, maiorComunidade, &tamanho);

    // Salvar o resultado
    salvarResultado(tamanho, maiorComunidade);

    return 0;
}
