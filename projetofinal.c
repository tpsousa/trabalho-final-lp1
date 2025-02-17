#include <stdio.h>
#include <stdlib.h>

#define MAX_PESSOAS 100

typedef struct No {
    int destino;
    struct No* proximo;
} No;

typedef struct {
    No* adj[MAX_PESSOAS]; 
    int num_pessoas;
} Grafo;

void inicializar_usuario(Grafo* g, int num_pessoas) {
    g->num_pessoas = num_pessoas;
    for (int i = 0; i < num_pessoas; i++) {
        g->adj[i] = NULL;
    }
}

void adicionarAmizade(Grafo* g, int p1, int p2) {
    No* novoNo1 = (No*)malloc(sizeof(No));
    novoNo1->destino = p2;
    novoNo1->proximo = g->adj[p1];
    g->adj[p1] = novoNo1;

    No* novoNo2 = (No*)malloc(sizeof(No));
    novoNo2->destino = p1;
    novoNo2->proximo = g->adj[p2];
    g->adj[p2] = novoNo2;
}

int podeAdicionarAoClique(Grafo* g, int* clique, int tamanho_clique, int pessoa) {
    for (int i = 0; i < tamanho_clique; i++) {
        int adjacente = 0;
        No* no = g->adj[clique[i]];
        while (no != NULL) {
            if (no->destino == pessoa) {
                adjacente = 1;
                break;
            }
            no = no->proximo;
        }
        if (!adjacente) { 
            return 0;
        }
    }
    return 1;
}

void Maximizar_usuario(Grafo* g, FILE* resultado) {
    int clique[MAX_PESSOAS];
    int tamanho_clique = 0;

    for (int i = 0; i < g->num_pessoas; i++) {
        if (tamanho_clique == 0) {
            clique[tamanho_clique++] = i;
        } else {
            if (podeAdicionarAoClique(g, clique, tamanho_clique, i)) {
                clique[tamanho_clique++] = i;
            }
        }
    }

    fprintf(resultado, "Tamanho do clique: %d\n", tamanho_clique);
    fprintf(resultado, "Pessoas no clique: ");
    for (int i = 0; i < tamanho_clique; i++) {
        fprintf(resultado, "%d ", clique[i] + 1); 
    }
    fprintf(resultado, "\n");
}

//quicksort para ordenar o grau dos vertices
/*
void quicksort(int arr[], int tamanho) {
    if (tamanho <= 1) return;

    int pivot = arr[tamanho - 1];  
    int menores[tamanho], maiores[tamanho];  
    int countMenores = 0, countMaiores = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        if (arr[i] < pivot)
            menores[countMenores++] = arr[i];
        else
            maiores[countMaiores++] = arr[i];
    }

    quicksort(menores, countMenores);
    quicksort(maiores, countMaiores);

    int k = 0;
    for (int i = 0; i < countMenores; i++) arr[k++] = menores[i];
    arr[k++] = pivot;
    for (int i = 0; i < countMaiores; i++) arr[k++] = maiores[i];
}
}*/
// Função para liberar a memória do grafo
void liberarGrafo(Grafo* g) {
    for (int i = 0; i < g->num_pessoas; i++) {
        No* no = g->adj[i];
        while (no != NULL) {
            No* temp = no;
            no = no->proximo;
            free(temp);
        }
    }
}

/*void mostrarGrafo(Grafo* g) {
    for (int i = 0; i < g->num_pessoas; i++) {
        No* no = g->adj[i];
        printf("Pessoa %d: ", i + 1); // Ajuste para 1-indexed
        while (no != NULL) {
            printf("%d ", no->destino + 1); // Ajuste para 1-indexed
            no = no->proximo;
        }
        printf("\n");
    }
}*/

int main() {
    Grafo g;
    FILE *entrada, *saida;
    int num_pessoas, num_amizades;
    char buffer[100];
    int p1, p2;

    entrada = fopen("5_6.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    fscanf(entrada, "%d %d", &num_pessoas, &num_amizades);

    inicializar_usuario(&g, num_pessoas);

    while (fgets(buffer, sizeof(buffer), entrada)) {
        if (buffer[0] == 'e') {
            sscanf(buffer, "e %d %d", &p1, &p2);
            adicionarAmizade(&g, p1 - 1, p2 - 1);
        }
    }

    fclose(entrada);
    saida = fopen("resultado.txt", "w");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    //mostrarGrafo(&g);

    Maximizar_usuario(&g, saida);
    fclose(saida);
    liberarGrafo(&g);
    printf(" o clique máximo foi escrito em 'resultado.txt'.\n");

    return 0;
}
