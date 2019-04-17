#include <stdio.h>

#define NUM 4

int  main()
{
    int elems =  NUM  ;
    char vet[NUM]; //vetor com as amostras
    vet[0] = -128;
    vet[1] = 0;
    vet[2] = 127;
    vet[3] = -30;

    FILE *fp;
    fp = fopen("pozzer.dct", "wb");

    //grava o numero de elementos (int)
    fwrite(&elems, sizeof(int), 1, fp);

    //grava os elementos (char = int de 8 bits com sinal)
    for(int i=0; i < NUM; i++)
    {
       fwrite(&vet[i], sizeof(char), 1, fp);
    }
    fclose(fp);

    //resseta os valores
    elems = 0;
    vet[0] = 0;
    vet[1] = 0;
    vet[2] = 0;
    vet[4] = 0;


    //reabre o arquivo para leitura
    fp = fopen("pozzer.dct", "rb");

    //le o numero de elementos (int)
    fread(&elems, sizeof(int), 1, fp);

    //le os elementos (char = int de 8 bits com sinal)
    for(int i=0; i < NUM; i++)
    {
       fread(&vet[i], sizeof(char), 1, fp);
    }
    fclose(fp);

    //imprime dos dados lidos
    printf("\n%d", elems);
    printf("\n%d", vet[0]);
    printf("\n%d", vet[1]);
    printf("\n%d", vet[2]);
    printf("\n%d", vet[3]);

   return 0;
}
