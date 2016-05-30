#define TAMANHOTELAY 15
#define TAMANHOTELAX 25 
#define CORVERMELHO 4
#define CORFUNDO 7
#define BLOCO '0'
#define VAZIO '-'
#include <ncurses.h>
#include "tela.h"
#include "pecas.h"

#ifdef TEST_MODE
	#include "moduloauxengine.h"
#endif


enum inputs{
	ESQUERDA,
	BAIXO,
	DIREITA,
	CIMA,
	SAIR
} inp;

int VerificaMorte(TipoTela tela[][25]){
	int i;
	
	for (i=0; i<TAMANHOTELAX-1;i++){
		if (VerificaSeBloco(tela[5][i]))
		return(1);
		}	
	return(0);
	}

int VerificaColisao(TipoPeca *peca, TipoTela tela[][25]){
	int i=0, j=0, colisao=0;

	for(i=0;i<5;i++) for(j=0;j<5;j++){
		if(VerificaSeBloco(tela[(PecaGetY(peca))+j][PecaGetX(peca)+i]) && 
			VerificaSeBloco(PecaGetBloco(peca,j,i))) colisao=1;
		}
	return colisao;
	}

void DeletaBloco(TipoTela *unidade){
	SetPeca(unidade,VAZIO,CORFUNDO);
	}

void AddBloco(TipoPeca *peca,TipoTela tela[][25]){
	int i,j;

	for (i=0;i<5;i++) for (j=0;j<5;j++) {
		if (VerificaSeBloco(PecaGetBloco(peca,i,j))){
			tela[PecaGetY(peca)+i][(PecaGetX(peca))+j]=PecaGetBloco(peca,i,j);
			}
		}
	}

void RemoveBloco(TipoPeca *peca,TipoTela tela[][25]){
	int i, j;
	for (i=0;i<5;i++) for (j=0;j<5;j++) {
		if (VerificaSeBloco(PecaGetBloco(peca,i,j))){
			DeletaBloco(&tela[PecaGetY(peca)+i][(PecaGetX(peca))+j]);
		}
	}
	
}

int VerificaLinhas(TipoTela tela[][TAMANHOTELAX]){//verifica se ha alguma linha completa
	int i,j, completa=1;	  //se houver, retorna a posicao y dela
	
	for(i=TAMANHOTELAY-1;i>=0;i--){
		for (j=0;j<TAMANHOTELAX;j++){
			if (!VerificaSeBloco(tela[i][j])) {
				completa=0;
				j=100;
			}
		}
		if (completa==1) return i;
		completa=1;
	}
	return(-1); //caso nenhuma linha esteja completa, retorna -1
}

void Gravidade(TipoTela tela[][TAMANHOTELAX],int posicaolinha){
	int j;
	
	for(;posicaolinha>0;posicaolinha--){
		for (j=0;j<TAMANHOTELAX;j++){
			tela[posicaolinha][j]=tela[posicaolinha-1][j];
		}
	}
}	

void DeletaLinhas(TipoTela tela[][TAMANHOTELAX],int *pontuacao){ 
	int linha=0;
	
	while (linha!=-1){
		linha=VerificaLinhas(tela);
		if (linha!=-1) {
			Gravidade(tela, linha);
			*pontuacao+=100;
		}
	}
}

int PegaInput(){ //corrigir para as setas
	int input;
	
	switch(getch()){
		case KEY_LEFT: 
			input = ESQUERDA;
			break;	
		case KEY_DOWN:
			input = BAIXO;
			break;
		case KEY_RIGHT: 
			input = DIREITA;
			break;
		case KEY_UP: 
			input = CIMA;
			break;
		case 'q':
			input = SAIR;
			break;
	}
	return input;
}

int Loop(TipoTela tela[][TAMANHOTELAX]){
	int sair=0,
	    x=10,
	    y=0,
	    prevX=0,
	    prevY=0,
	    tamanhoPecaX=0,
	    tamanhoPecaY=0,
	    colisaoVertical=0,
	    pontuacao=0;

	TipoPeca *pecaAgora = AlocaPeca(),
		 *pecaAntes = AlocaPeca();

	#ifdef TEST_MODE	
		criaaleatorio(tela, 2, 0.6);
	#endif

	initscr();
	InicioTela();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
//	timeout(300);

	GeraPeca (pecaAgora); //cria aleatoriamente
	AddBloco(pecaAgora, tela); //aplica à matriz
	tamanhoPecaX=PecaGetTamanhoX(pecaAgora);
	tamanhoPecaY=PecaGetTamanhoY(pecaAgora);

	while (sair==0){
		CopiaPeca(pecaAgora,pecaAntes);

		prevX=x;
		prevY=y;	
		MostrarTela(tela,pontuacao); //desenha

		switch(PegaInput()){
			case ESQUERDA: if (x>0)
				x--;
				break;

			case BAIXO: 
				if (y<TAMANHOTELAY-tamanhoPecaY-1)
				y++;
				else colisaoVertical=1; 

				break;

			case DIREITA: 
				if (x<TAMANHOTELAX-tamanhoPecaX-1)
				x++;
				break;

			case CIMA: if (y>0) //opcao de teste para subir
				y--;
				break;

			case SAIR: sair=1;
				break;
		}
	
		RemoveBloco(pecaAgora,tela); //remove peca do tetris da matriz tela
		MovePecaX(pecaAgora,x);    // atribui as propriedades de posicao
		MovePecaY(pecaAgora,y);

		if (!VerificaColisao(pecaAgora,tela)){ //verifica se o estado de posicao ja esta ocupado com alguma peca da matriz
			RemoveBloco(pecaAntes, tela); //caso esteja vago, remove peca antiga
			AddBloco(pecaAgora, tela); //e atualiza a peca
			}
		else{    //caso nao esteja vago
			x=prevX; //retorna a posicao x anterior, impedindo as sobreposicoes
			if (y!=prevY) { //se verdedairo significa que houve uma colisao no eixo y
				y=prevY;
				colisaoVertical=1; //flag para fixar a peca e tomar as medidas necessarias
				}
			MovePecaX(pecaAgora,x); //atribui posicoes anteriores
			MovePecaY(pecaAgora,y); 
			AddBloco(pecaAgora, tela); //atribui à matriz tela
			}

		if (colisaoVertical) {
			if (VerificaMorte(tela)) sair=1;//morre se ha algum bloco na posicao y=5 <------------------
			GeraPeca (pecaAgora); //cria aleatoriamente
			tamanhoPecaX=PecaGetTamanhoX(pecaAgora);
			tamanhoPecaY=PecaGetTamanhoY(pecaAgora);
			x=PecaGetX(pecaAgora); y=PecaGetY(pecaAgora);
			DeletaLinhas(tela, &pontuacao); //verifica se alguma linha foi completada
			//if (VerificaColisao(&currentPeca,tela)) sair=1; //game over se a peca nova se sobrepoe a alguma peca (n especificado)
			if (sair!=1) AddBloco(pecaAgora, tela); // desenha só se nao tiver morrido
			}
		colisaoVertical=0;
		

		if (sair==1) { //mostra o momento de derrota 
			//pinta os blocos de vermelho dramático
			for(x=0;x<TAMANHOTELAX;x++)
				for(y=0;y<TAMANHOTELAY;y++)
					if(VerificaSeBloco(tela[y][x]))SetPecaCor(&tela[y][x],CORVERMELHO);
			 //desenha a tela, pela ultima vez :(
			MostrarTela(tela,pontuacao);
			getch();  
			}
		clear();
	}
	LiberaPeca(pecaAgora);
	LiberaPeca(pecaAntes);
 	FimTela(pontuacao);
	endwin();

return(0);

}
