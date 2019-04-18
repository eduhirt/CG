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
#include "funcoes_cpp.h"

# define M_PI           3.14159265358979323846

using namespace std;

//vetores
std::vector<signed char> v_amostra;
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

    //Define a escala no eixo X
    float tam_x = tamanho/9;
    //Auxiliar para contagem de espaçamentos
    float aux;
    //Define a posição dos dados no eixo Y
    float amostra;
    //Auxiliar para ligação dos pontos
    float prox_amostra;



    //IDCT
    color(0,0,0);
    aux = tam_x + 20;

    for(int i=0;i<(tamanho);i++){
        amostra = v_idct[i] + 120;
        prox_amostra = v_idct[i+1] + 120;

        circleFill(aux,amostra,2,10);
        if(i<tamanho-1){
            line(aux,amostra,aux+tam_x,prox_amostra);
        }

        aux = aux+tam_x;
    }


    //Amostra
    color(1,0,0);
    aux = tam_x + 20;

    for(int i=0;i<(tamanho);i++){
        amostra = v_amostra[i] + 370;
        prox_amostra = v_amostra[i+1] + 370;

        circleFill(aux,amostra,2,10);
        if(i<tamanho-1){
            line(aux,amostra,aux+tam_x,prox_amostra);
        }

        aux = aux+tam_x;
    }


    //Diff
    color(0,0,1);
    aux = tam_x + 520;

    for(int i=0;i<(tamanho);i++){
        amostra = v_dif[i] + 120;
        prox_amostra = v_dif[i+1] + 120;

        circleFill(aux,amostra,2,10);
        if(i<tamanho-1){
            line(aux,amostra,aux+tam_x,prox_amostra);
        }

        aux = aux+tam_x;
    }

    //DCT
    color(0,1,1);
    aux = tam_x + 520;

    for(int i=0;i<(tamanho);i++){
        amostra = v_dct[i] + 370;
        prox_amostra = v_dct[i+1] + 370;

        circleFill(aux,amostra,2,10);
        if(i<tamanho-1){
            line(aux,amostra,aux+tam_x,prox_amostra);
        }

        aux = aux+tam_x;
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

   Arquivo a;

   tamanho = a.getTamanho();

   v_amostra.resize(tamanho);
   v_dct.resize(tamanho);
   v_idct.resize(tamanho);
   v_dif.resize(tamanho);

   v_amostra = a.le_amostra(tamanho);
   v_dct = a.dct(v_amostra, tamanho);
   v_idct = a.idct(v_dct, tamanho);
   v_dif = a.calc_dif(v_amostra, v_idct, tamanho);
   a.salva(v_idct, tamanho);

   runCanvas();
}
