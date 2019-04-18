#include <cmath>
#include <math.h>
#include <vector>

# define M_PI           3.14159265358979323846

using namespace std;

class Arquivo{
public:

	//calcula a diferença entre amostra e idct
	std::vector<float> calc_dif(std::vector<signed char> v_amostra, std::vector<float> v_idct, int tamanho){
	    double aux;
	    std::vector<float> v_dif;
	    v_dif.resize(tamanho);

	    for(int i=1;i<tamanho;i++){
	        aux=fabs((double)(v_amostra[i]-v_idct[i]));
	        v_dif[i]=aux;
	    }
	    return v_dif;
	}



	//calcula a idct
	std::vector<float> idct(std::vector<float> v_dct, int tamanho){
		std::vector<float> v_idct;
	    double c; //constante
	    double pi= M_PI; //recebe valor de pi
	    v_idct.resize(tamanho);

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
	    return v_idct;
	}



	//calcula a dct para depois calcular a idct
	std::vector<float> dct(std::vector<signed char> v_amostra, int tamanho){
	    double c;
	    double pi = M_PI;
	    std::vector<float> v_dct;
	    v_dct.resize(tamanho);

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

	    return v_dct;
	}



	//le arquivo
	std::vector<signed char> le_amostra(int tamanho){
		std::vector<signed char> v_amostra;
	    FILE *arq = fopen("input.dct", "rb");
	    v_amostra.resize(tamanho);

	    if(arq != NULL){
	    	//signed char = -127 a 128
	        signed char am;
	        //pular header
	        for(int i=0;i<tamanho+4;i++){
	            fread(&am, sizeof(signed char), 1, arq);
	            //Adicionada escala de 50% nos dados
	            if(i>3){
	            	v_amostra[i-4]=am*0.5;
	            }
	            
	        }
	    }
	    fclose(arq);
	    return v_amostra;
	}



	//le arquivo
	int getTamanho(){
		int tamanho;
	    FILE *arq = fopen("input.dct", "rb");
	    if(arq != NULL){
	        fread(&tamanho, sizeof(unsigned int), 1, arq);
	        fclose(arq);
		}
		return tamanho;
	}



	//salva idct
	void salva(std::vector<float> v_idct, int tamanho){
	    FILE *arq = fopen("output.dct", "wb");
	    fwrite(&tamanho, sizeof(unsigned int), 1, arq);
	 
	    signed char sv;
	    for(int i=0;i<tamanho;i++){
	    	//retorno da escala
	        sv=v_idct[i]*1,5;
	        fwrite(&sv, sizeof(signed char), 1, arq);
	    }
	    fclose(arq);
	}

};