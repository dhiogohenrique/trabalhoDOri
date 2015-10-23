#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef struct Node node;/// definindo um tipo para o nó
struct Node/// estrutura de cada nó da árvore
{
    int *chaves;/// vetor de chaves
    int t;/// ordem
    node **filho;/// vetor de ponteiros de filho
    int n_chaves;/// número de chaves
    bool folha;
};

typedef struct Arvore arvore;/// definindo um tipo para árvore
struct Arvore
{
    node *raiz;/// ponteiro para o nó raiz
    int t;/// ordem
    bool vazia;
};

void CriaNode (node *N, int t)/// inicializa o nó
{
    N->folha = true;/// um nó sempre é iniciado como verdadeiro
    N->chaves = (int *) malloc ((2*t-1) * sizeof (int) );/// alocação de memória para número máximo de chaves
    N->filho = (node**) malloc ((2*t) * sizeof (node*));/// aloca memória para número máximo de ponteiros filho
    N->n_chaves = 0;
    N->t = t;
}
void CriaArvore (arvore *A,int t)///inicializa a árvore
{
    node N;
  //  CriaNode(&N,t);
    A->raiz = &N;/// inicializa a raíz como NULL
    A->t = t;/// inicializa a ordem com o t escolhido pelo usuário
    A->vazia = true;
}


/// função para dividir o filho y do nó inserido
/// i é um indice do nó y no vetor filho[] de x
/// a funçao é chamada quando y está com 2t-1 chaves (esta cheio)
/// x é pai de y e vai ser pai de z
void DivideFilho (node *x, int i, node *y)
{
    /// cria um nó que vai guardar t-1 chaves de y
    node z;
    CriaNode(&z,i);
    z.t = y->t;
    z.folha = y->folha;
    z.n_chaves = z.t - 1;

    /// copia as ultimas t-1 chavez de y para z
    int j;
    for ( j=0; j < y->t-1; j++)
    {
        z.chaves[j] = y->chaves[j + y->t];
    }

    if (y->folha = false)
    {
        /// copia os ultimos t filhos de y para z
        for(j = 0 ; j < y->t; j++ )
        {
            z.filho[j] = y->filho[j + y->t];
        }
    }

    /// diminuir o número de chaves de y
    y->n_chaves = y-> t - 1;

    /// criar espaço para o novo filho
    for(j = y->n_chaves; j >= i + 1; j--)
    {
        x->filho[j+1] = x->filho[j];
    }

    /// ligar o novo filho z ao nó x
    x->filho[i+1] = &z;

    /// uma chave de y sera movida para x.
    /// acha a localização da nova chave e move todas as chaves maiores uma espaço a frente
    for(j = x->chaves; j >= i; j--)
    {
         x->chaves[j+1] = x->chaves[j];
    }

    /// copia a chave do meio de para x
    x->chaves[i] = y->chaves[y->t - 1];

    /// incrementa a quantidade de chaves do nó x
    x->n_chaves = x->n_chaves + 1;
}

/// insere chave k no nó x assumindo que este não está cheio quando a função é chamada
void InsereNaoCheio (node *x, int k)
{
    /// inicializa o índice como o índice da chave mais a direita
    int i = x->n_chaves;

    if (x->folha == true)
    {
        /// encontra a localização da chave q será inserida acha a localização
        /// da nova chave e move todas as chaves maiores uma espaço a frente
        while (i >= 0 && x->chaves[i] > k)
        {
            x->chaves[i+1] = x->chaves[i];
            i--;
        }

        /// inserir a nova chave na localização encontrada
        /// e incrementa a quantidade de chaves do nó x
        x->chaves[i+1] = k;
        x->n_chaves = x->n_chaves + 1;
    }

    else
    {
        /// acha o filho que recebera a nova chave
        while (i >= 0 && x->chaves[i] > k)
            i--;

        /// verifica se o novo filho encontrado está cheio
        if (x->filho[i+1]->n_chaves == (2 * x->t) - 1)
        {
            /// caso ele estiver cheio, divide
            DivideFilho(x,i+1, x->filho[i+1]);

            /// depois de dividido, a chave do meio do filho vai para o pai e o filho é
            /// dividido em dois, escolhemos qual dos dois vamos colocar a nova chave
            if (x->filho[i+1]->chaves[i+1] < k)
                i++;
        }
        /// continua recursivamente
        InsereNaoCheio(x->filho[i+1],k);
    }
}
void Insere(arvore *T, int k)
{
    /// se a árvore estiver vazia
    if (T->vazia == true)
    {
        /// alocar memória para a raiz
        CriaNode(T->raiz, T->t);
        T->raiz->chaves[0] = k;  /// insere a chave
        T->raiz->n_chaves = 1;  /// atualizar o número de chaves na raiz
        T->vazia == false;

    }
    else /// se a árvore nao estiver vazia
    {
        /// se o nó está cheio a arvore aumenta sua altura
        if (T->raiz->n_chaves == 2*T->t-1)
        {
            /// aloca memória para o novo nó
            node *s;
            CriaNode(s,T->t);
            s->folha = false;

            /// antiga raíz se torna filha da nova raíz
            s->filho[0] = T->raiz;

            /// divide a antiga raíz e move uma chave para a nova
            DivideFilho(s,0, T->raiz);

            /// agora a nova raíz tem dois filhos e
            /// escolhemos qual dos dois vamos colocar a nova chave
            int i = 0;
            if (s->chaves[0] < k)
                i++;
            InsereNaoCheio(s->filho[i],k);

            /// muda a raíz
            T->raiz = s;
        }
        else
            /// se raíz não está cheia, chama a função
            InsereNaoCheio(T->raiz,k);
    }
}

 int main(){
node T;
arvore N;
CriaNode(&T,3);
CriaArvore(&N,3);
printf("%d\n",T.n_chaves);
printf("%d\n",T.t);
Insere(&N,78);
printf("%d\n\n",N.raiz->chaves[0]);

 printf("Compilou!!!!\n\n");

 return 0;
 }



