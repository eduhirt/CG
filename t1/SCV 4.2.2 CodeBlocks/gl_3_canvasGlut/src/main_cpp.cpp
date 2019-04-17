/*********************************************************************
// Canvas para desenho - Versao CPP.
//  Autor: Cesar Tadeu Pozzer
//         10/2007
//
//  Pode ser utilizada para fazer desenhos ou animacoes, como jogos simples.
//  Tem tratamento de mosue
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Instruções:
//    Para compilar em C, basta comentar o comando #define _CPP_
//    Para alterar a animacao, digite numeros entre 1 e 7
// *********************************************************************/


#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "gl_canvas2d.h"

# define M_PI           3.14159265358979323846

using namespace std;

//vetores
std::vector<signed short> v_amostra;
std::vector<float> v_dct, v_idct, v_dif;

//tamanho da amostra
int tamanho = 0;

//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")
//#pragma comment(lib, "glut32.lib")


//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{
    //Area dos graficos
    color(0.7,0.7,0.7);
    rectFill(0,0,500,250);
    
    color(0.5,0.5,0.5);
    rectFill(500,0,1000,250);
    
    color(0.3,0.3,0.3);
    rectFill(0,250,500,500);

    color(0.1,0.1,0.1);
    rectFill(500,250,1000,500);

    //Titulo dos graficos
    color(0,0,0);
    text(200,230,"IDCT:");
    text(700,230,"Diff:");

    color(1,1,1);
    text(200,480,"Amostra:");
    text(700,480,"DCT:");


    //IDCT
    color(0,1,0);
    int tam_x = 450/tamanho;
    int aux=tam_x;
    for(int i=0;i<(tamanho-1);i++){
        circleFill(aux,(int)v_idct[i]+120,2,10);
        line(aux,(int)v_idct[i]+120,aux+tam_x,(int)v_idct[i+1]+120);
        aux = aux+tam_x;
        if(i==(tamanho-2))
            circleFill(aux,(int)v_idct[i+1]+120,2,10);
    }

    //Amostra
    color(1,0,0);
    aux = tam_x;
    for(int i=0;i<(tamanho-1);i++){
        circleFill(aux,(int)v_amostra[i]+370,2,10);
        line(aux,(int)v_amostra[i]+370,aux+tam_x,(int)v_amostra[i+1]+370);
        aux = aux+tam_x;
        if(i==(tamanho-2))
            circleFill(aux,(int)v_amostra[i+1]+370,2,10);
    }


    //Diff
    color(2,5,1);
    aux = tam_x + 520;
    for(int i=0;i<(tamanho-1);i++){
        circleFill(aux,(int)v_dif[i]+120,2,10);
        line(aux,(int)v_dif[i]+120,aux+tam_x,(int)v_dif[i+1]+120);
        aux = aux+tam_x;
        if(i==(tamanho-2))
            circleFill(aux,(int)v_dif[i+1]+120,2,10);
    }

    //DCT
    color(0,1,1);
    aux = tam_x + 520;
    for(int i=0;i<(tamanho-1);i++){
        circleFill(aux,(int)v_dct[i]+370,2,10);
        line(aux,(int)v_dct[i]+370,aux+tam_x,(int)v_dct[i+1]+370);
        aux = aux+tam_x;
        if(i==(tamanho-2))
            circleFill(aux,(int)v_dct[i+1]+370,2,10);
    }
    

}

//IMPLEMENTAR COM CLASSES

// class Amostra{
// public:
//     Amostra(){
//         FILE *arq = fopen("samples.dct", "rb");
//         if(arq != NULL){
//             fread(&tamanho, sizeof(unsigned int), 1, arq);

//             v_amostra.resize(tamanho);
//             v_dct.resize(tamanho);
//             v_idct.resize(tamanho);
//             v_dif.resize(tamanho);

//             signed short am;
//             for(int i=0;i<tamanho;i++){
//                 fread(&am, sizeof(signed short), 1, arq);
                
//                 v_amostra[i]=am;
//             }
//         }
//         fclose(arq);
//     }
// };




//calcula a diferença entre amostra e idct
void calc_dif(){
    double aux;
    for(int i=0;i<tamanho;i++){
        aux=fabs((double)(v_amostra[i]-v_idct[i]));
        v_dif[i]=aux;
    }
}

//calcula a idct
void idct(){
    double c; //constante
    double pi= M_PI; //recebe valor de pi

    //zera valores dos vetores
    for(int x=0;x<tamanho;x++)
        v_idct[x]=0;


    for(int i=0; i<tamanho; i++){
        if(i==0){
            c=1/sqrt(2);
        }
        else{
            c=1;
        }
        for(int j=0; j<tamanho; j++){
            v_idct[i] += (double) v_dct[j] * cos((double) ((2.0*i+1) *j* pi/(2*tamanho))) *c;
        }
        v_idct[i] *= sqrt((double)2/tamanho);
    }

}

//calcula a dct para depois calcular a idct
void dct(){
    double c;
    double pi = M_PI;

    for(int x=0;x<tamanho;x++)
        v_dct[x]=0;

    for(int i=0; i<tamanho; i++){
        if(i==0)
            c=1/sqrt(2);
        else
            c=1;

        for(int j=0; j<tamanho; j++){
            v_dct[i] += (double) v_amostra[j] * cos((double) ((2*j+1)*pi*i/(2*tamanho))) *c;
        }
    v_dct[i] *= sqrt((double)2/tamanho);
    }
}

//le arquivo
void le_amostra(){
    FILE *arq = fopen("pozzer.dct", "rb");
    if(arq != NULL){
        fread(&tamanho, sizeof(unsigned int), 1, arq);

        v_amostra.resize(tamanho);
        v_dct.resize(tamanho);
        v_idct.resize(tamanho);
        v_dif.resize(tamanho);

        signed short am;
        for(int i=0;i<tamanho;i++){
            fread(&am, sizeof(signed short), 1, arq);
            if(am>100)
                am=100;
            if(am<-100)
                am=-100;
            v_amostra[i]=am;
        }
    }
    fclose(arq);
}

//salva idct
void salva(){
    FILE *arq = fopen("output.dct", "wb");
    fwrite(&tamanho, sizeof(unsigned int), 1, arq);
 
    signed short sv;
    for(int i=0;i<tamanho;i++){
        sv=v_idct[i];
        //limites
        if(sv<-100)
            sv=-100;
        if(sv>100)
            sv=100;
        fwrite(&sv, sizeof(signed short), 1, arq);
    }
    fclose(arq);
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   printf("\nTecla: %d" , key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    //acerta o mouse
    y=499-y;
}

int main(void)
{
   initCanvas(1000,500, "Trabalho 1 - Transformada Discreta de Cosseno");

   le_amostra();
   dct();
   idct();
   calc_dif();
   salva();

   runCanvas();
}
