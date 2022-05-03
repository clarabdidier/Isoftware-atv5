#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Declaração das varáveis globais
int soma_total = 0;
void *increment(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main()
{
    //Informa o tamanho da matriz
    int tamanho, i, j;
    scanf("%d", &tamanho);
    int matriz[tamanho][tamanho];
    pthread_t threads[tamanho];

    
    //Pega os dados da matriz
    for(i = 0; i < tamanho; i++)
    {
        for(j = 0; j < tamanho; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    //Cria uma thread para cada linha da matriz
    for (i = 0; i < tamanho; i++) {
        int *linha = malloc(tamanho * sizeof(int));
        if (pthread_create(&(threads[i]), NULL, increment, (void*)linha)){
            printf("Thread %d not created", i);
        }
        for(j = 0; j < tamanho; j++){
            linha[j] = matriz[i][j];
        }
    }

    //Finaliza as threads
    for (i = 0; i < tamanho; i++){
        pthread_join (threads[i], NULL);
    }

    //Print da soma total
    printf("%d\n", soma_total);
}

//Função que realiza a soma dos números
void *increment(void *arg) {

    int soma = 0;
    int *l = (int *)arg;
    int comp = sizeof(*l);


    for(int index = 0; index < comp; index++){
        soma = soma + l[index];
    }

    pthread_mutex_lock(&mutex);
    soma_total = soma_total + soma;
    pthread_mutex_unlock(&mutex);
    return arg;
}
