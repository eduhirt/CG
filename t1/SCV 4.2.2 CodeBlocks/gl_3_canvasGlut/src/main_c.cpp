/*********************************************************************
// Canvas para desenho - Versao C.
//  Autor: Cesar Tadeu Pozzer
//         10/2007
//
//  Pode ser utilizada para fazer desenhos ou animacoes, como jogos simples.
//  Tem tratamento de mosue
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 5
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "gl_canvas2d.h"
#define DIM_TELA 600

//variaveis globais
int   opcao  = 49;
float global = 0;

int cannon;
int shot = 0;
int shotPosX = 0;
int shotPosY = 0;

void CriaMenu()
{
   color(1,0,0);
   rectFill( 0,0, 40,20 );
   color(0,0,0);
   text(15, 5, "1");
   text(15, 25, "Menu Simplificado");

   color(0,1,0);
   rectFill( 40,0, 80, 20 );
   color(0,0,0);
   text(55, 5, "2");

   color(0,0,1);
   rectFill( 80,0, 120, 20 );
   color(0,0,0);
   text(95, 5, "3");
}

/*void engrenagem()
{
    float a = 0;
    float inc = PI_2/40.0;
    int x[4], y[4];
    for(a=0; a< 7; a+=(4*inc))
    {
        x[0] = sin(a)*100 + 200;
        y[0] = cos(a)*100 + 200;
        line(x[0], y[0], x[3], y[3]);

        x[1] = sin(a+inc)*100 + 200;
        y[1] = cos(a+inc)*100 + 200;

        x[2] = sin(a+inc+inc)*70 + 200;
        y[2] = cos(a+inc+inc)*70 + 200;

        x[3] = sin(a+inc+inc+inc)*70 + 200;
        y[3] = cos(a+inc+inc+inc)*70 + 200;

        line(x[0], y[0], x[1], y[1]);
        line(x[1], y[1], x[2], y[2]);
        line(x[2], y[2], x[3], y[3]);
    }

}*/

//Livro: Calculus, a new Horizon, sixth edition, pg 96
void desenhaPolinomio()
{
      float t;
      float x, y;
      for(t=-5; t< 2; t+=0.001)
      {
          x = cos(t) + 0.5*cos(7*t)+(1/3.0)*sin(17*t);
          y = sin(t) + 0.5*sin(7*t)+(1/3.0)*cos(17*t);

          point(x*100+200,y*100+200);
      }

      for(t=0; t < 14*3.14; t+=0.001)
      {
          x = 17.0*cos(t) + 7.0*cos((17/7.0)*t);
          y = 17.0*sin(t) - 7.0*sin((17/7.0)*t);

          //printf("%f ", x);
          point(x*5+500,y*5+400);
      }
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{
   //Sleep(10);

   CriaMenu();

   // desenhaPolinomio();



   if( opcao == 49) // = '3' linha animada
   {
      clear(1,1,1); //limpa a tela de branco
      color(0.7, 0, 0);
      line((int)global, 100, (int)global, 400);
      global += 0.5;
   }
   if( opcao == 50 ) // = '4' relogio
   {
      color(0,0,0);
      float raio = 1;
      for(float a = 0; a<30; a+=0.001)
      {
         int x = (int)(cos(a) * raio);
         int y = (int)(sin(a) * raio);
         point(x+200, y+200);
         raio += 0.001+(a*a*a)/220000;
      }
      global -= 0.01;
   }
   if( opcao == 51 ) // = '5' linha andando
   {
      clear(0,0,0);
      color(1, 1, 0);
      rect(200-(int)global, 200-(int)global, 200+(int)global, 200 + (int)global);
      global += 0.05;
   }
   if( opcao == 52) //= '6' quadrados parados
   {
        clear(0,0,0);
        color(0.7, 0.7, 0);
        circleFill(20,20, 10, 4);
        //rectFill(40,40,140,140);
        rect(140,140,240,240);
        color(0, 1, 0);
        point(300, 300);
   }
   if( opcao == 53 ) // = '7' senoide
   {
       //line( 10,10, 300,300 );
       //circle( 300,300, 100, 1150);
       float x=0, y;
       color(0, 1, 0);
       for(float i=0; i < 68; i+=0.001)
       {
          y = sin(i)*50;
          point((int)x, (int)y+100);
          x+=0.01;
       }
   }

   text(20,500,"Programa Demo Canvas C.");


   //trata o disparo
   if( shot == 1 )
   {
      circleFill(shotPosX, shotPosY, 10, 10);
      shotPosY+=2;
   }


   //desenha o quadrado movel
   rectFill(cannon, 40, cannon+100, 60);

   //engrenagem();
   /**/
}



//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   //printf("\nTecla: %d" , key);
   if( key <= 53 && key >= 49 )
   {
      opcao = key;
   }

   switch(key)
   {
      case 27:
	     exit(0);
	  break;
   }
}
//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   //printf("\nLiberou: %d" , key);
}


//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   y = DIM_TELA - y;
   //printf("\nmouse %d %d %d %d", button, state, x, y);
   cannon = x;

   if( state == 0 ) //atirou
   {
      printf("\nDisparou");
      shot = 1;
      shotPosX = cannon+50;
      shotPosY = 50;
   }
   if( x < 40 && y < 20)
      opcao = 49;
   else if( x < 80 && y < 20)
      opcao = 50;
   else if( x < 120 && y < 20)
      opcao = 51;
}

int main(void)
{

   initCanvas(DIM_TELA, DIM_TELA, "Demo CanvasGlut. Pressione 1, 2, 3, 4, 5");

   runCanvas();

}
