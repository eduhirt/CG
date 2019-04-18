#include "gl_canvas2d.h"

class Grafico{
public:
	void desenha_grafico(int tamanho, int pos_x,int pos_y, std::vector<float> vet){
		//Define a escala no eixo X:
		float tam_x = tamanho/9;
		//Auxiliar para contagem de espaçamentos:
		float aux;
		//Define a posição dos dados no eixo Y:
		float amostra;
		//Auxiliar para ligação dos pontos:
		float prox_amostra;
		//Define onde o grafico fica no eixo y:
		float lim_sup_x, lim_sup_y, lim_inf_x, lim_inf_y;

		aux = tam_x + pos_x;

		color(1, 1, 1);
		for(int i=0;i<(tamanho);i++){
		    amostra = vet[i] + pos_y;
		    prox_amostra = vet[i+1] + pos_y;

		    circleFill(aux , amostra, 2, 10);
		    if(i < tamanho - 1){
		        line(aux, amostra, aux+tam_x, prox_amostra);
		    }
		    aux = aux + tam_x;
		}

		//Desenha as bases do grafico
		lim_sup_x = aux;
		lim_sup_y = pos_y + 128*0.5;
		lim_inf_x = tam_x + pos_x;
		lim_inf_y = pos_y - 127*0.5;

		color(0.5,0.5,0.5);
		line(lim_inf_x,pos_y,aux,pos_y);
		line(lim_inf_x, lim_inf_y, lim_inf_x, lim_sup_y);
		text(lim_inf_x, lim_sup_y,"128");
		text(lim_inf_x, lim_inf_y,"-127");

	}
};