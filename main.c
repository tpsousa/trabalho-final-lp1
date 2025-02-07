
#include <stdio.h>;
#include <stdio.h>;

//define a qtd max de vertices
#define MAXV 1000


struct NODE{
    int adj;
    struct node * next;
}node;

typedef struct {
    node *vertices[MAXV + 1];
    int qntdVertices,qntdArestas,grau[MAXV + 1]  //armazena o grau de cada vertice;
}ComunityGraph;

//inicializar um grafo vazio
void CriaGrafo(ComunityGraph * g){
  g-> qntdVertices =0;
  g->vertices[i] = NULL;

  for(int i = 0 ; i < node_count; i++){
   g->grau[i] = 0;
   g->vertices[i]=NULL;
  }
}

//inserir arestas entre os nos e incrementar o grau
void insereAresta(ComunityGraph*g,int x,int y){
 node *tempPtr = malloc(sizeof(node));

 tempPtr->adj = y;
 tempPtr->next = g->vertices[x];
 g->vertices[x]= tempPtr;
 g->grau[x]++;
 g->qntdArestas++;
}

//funcao para ler o arquivo ... 
void elementos_do_grafo(ComunityGraph * g){
  int n,x,y;

  char entrada[100];

  FILE* fptr = fopen("arquivo.txt","r");

  if(fptr === NULL){
    printf("Erro: Arquivo invalido\n");
    exit(1);
  }

  CriarGrafo(g);

  if(fscanf(fptr,"%d %d",&(g->qtdVertices),&n)!=2){
    printf("Erro: Nao foi possivel ler o numero de vertices e arestas\n");
    exit(1);
  }

  for(int i=0; i <= n ; i++){
    if(fscanf(fptr,"%s %d %d",entrada, &x,&y)!=3){
      printf("Erro: Nao foi possivel ler os vertices\n");
      exit(1);
    }
    insereAresta(g,x,y);
    insereAresta(g,y,x);
  }
  fclose(fptr);
}

//salvar o resultado
void salvarResultado(int max_grafo_size,int *max_grafo){
  FILE *resultado = fopen("resultado.txt","w");

  if(resultado == NULL){
    printf("Erro ao criar arquivo de saida\n");
    exit(1);    
  }

  fprintf(resultado,"Tamanho da maior comunidade:%d\n",max_grafo_size);
  fprintf(resultado,"Membros:");

  for(int i=0; i < max_grafo_size;i++){
    fprintf(resultado,"%d",max_grafo[i]);
  }
  fprintf(resultado,"\n");

  fclose(resultado);
  
  printf("A resposta foi salva no arquivo resultado");
  }



/*//imprime o grafo na tela
void mostrarGrafo(ComunityGraph * node) {
  for(int i = 0 ; i <  node_count; i ++){

  }
}*/

//encontrar o vertice inicial que possue o maior numero de conexoes
//e a partir dele encontrar os outros vertices de maior grau
//e verificar se esses vertices estao conectados com o usuario inicial
void user(ComunityGraph * node){
  
}
//contar o grau de cada no e botar em uma classe de armazenamento
void count_node(ComunityGraph * node,count_node) {
 for(int i=0 ; i < node_count; i++){
   if(i != [temp->node]-next){
    count_node++;
   }    
 }
}

int main () {
 initialize_graph();


 //chamar uma funcao que le e executa o arquivo
  fs....

  //liberar o espaco de memoria do grafo
  free(graph);

  return  0;
  
}




