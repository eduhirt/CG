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
#include "grafico.h"

# define M_PI           3.14159265358979323846

using namespace std;

//vetores
std::vector<int> v_amostra;
std::vector<float> v_dct, v_idct, v_dif, v_amostra_escalonada;

//objeto da classe Grafico
Grafico g;

//tamanho da amostra
int tamanho = 0;


//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{
    //Container dos graficos
    color(0.1,0.1,0.1);
    rectFill(0,0,500,250);
    
    color(0.3,0.3,0.3);
    rectFill(500,0,1000,250);
    
    color(0.3,0.3,0.3);
    rectFill(0,250,500,500);

    color(0.1,0.1,0.1);
    rectFill(500,250,1000,500);

    //Titulo dos graficos
    color(1,1,1);
    text(200,230,"IDCT:");
    text(700,230,"Diff:");
    text(200,480,"Amostra:");
    text(700,480,"DCT:");
 
    //IDCT
    g.desenha_grafico(tamanho, 20, 120, v_idct);

    //DCT
    g.desenha_grafico(tamanho, 520, 370, v_dct);

    //AMOSTRA
    g.desenha_grafico(tamanho, 20, 370, v_amostra_escalonada);

    //DIF
    g.desenha_grafico(tamanho, 520, 120, v_dif);

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

   Arquivo a;

   tamanho = a.getTamanho();

   //Define o tamanho dos vectors com base no tamanho do arquivo
   v_amostra_escalonada.resize(tamanho);
   v_dct.resize(tamanho);
   v_idct.resize(tamanho);
   v_dif.resize(tamanho);

   v_amostra = a.le_amostra(tamanho);
   v_amostra_escalonada = a.escalona_amostra(tamanho, v_amostra);
   v_dct = a.dct(v_amostra_escalonada, tamanho);
   v_idct = a.idct(v_dct, tamanho);
   v_dif = a.calc_dif(v_amostra_escalonada, v_idct, tamanho);
   a.salva(v_idct, tamanho);

   runCanvas();
}
