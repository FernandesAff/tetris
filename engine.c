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


enum comandos{
	ESQUERDA,
	BAIXO,
	DIREITA,
	CIMA,
	SAIR
} com;

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

	//verifica colisao com blocos:
	for(i=0;i<5;i++) for(j=0;j<5;j++){
		if(VerificaSeBloco(tela[(PecaGetY(peca))+j][PecaGetX(peca)+i]) && 
			VerificaSeBloco(PecaGetBloco(peca,j,i))) colisao=1;
		}

	//verifica colisao com parede:
	if(!colisao){
		for(i=0;i<5;i++) for(j=0;j<5;j++){
			if (VerificaSeBloco(PecaGetBloco(peca,i,j))) {
				     if ( (PecaGetX(peca)+j)>TAMANHOTELAX-1) colisao=1; //colide à direita
				else if ((PecaGetX(peca)+j)<0) colisao=1; 		//colide à esquerda	
				else if ( (PecaGetY(peca)+i)>TAMANHOTELAY-1) colisao=1; //colide abaixo
				else if ((PecaGetY(peca)+i)<0) colisao=1; 		//colide acima
			}
		}
	}

		

	return colisao;
	}

void PoePecaNoTopo(TipoPeca *peca, TipoTela tela[][25]){
	int y=0;
	TipoPeca *pecaAux = AlocaPeca();
	CopiaPeca(peca,pecaAux);
	y=PecaGetY(peca);

	while(!VerificaColisao(pecaAux,tela)) {
		y--;
		MovePecaY(pecaAux,y);
		if (!VerificaColisao(pecaAux,tela)) CopiaPeca(pecaAux,peca);
		}
	LiberaPeca(pecaAux);
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
				break;
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
	int rotaciona=0,
	    sair=0,
	    x=0,
	    y=0,
	    prevX=0,
	    prevY=0,
	    colisaoVertical=0,
	    pontuacao=0,
	    flagDesce=0;

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
	PoePecaNoTopo(pecaAgora, tela);
	x=PecaGetX(pecaAgora); y=PecaGetY(pecaAgora);
	AddBloco(pecaAgora, tela); //aplica à matriz

	while (sair==0){
		CopiaPeca(pecaAgora,pecaAntes);
		prevX=x;
		prevY=y;	
		MostrarTela(tela,pontuacao); //desenha

		switch(PegaInput()){
			case ESQUERDA:
				x--;
				break;

			case BAIXO: 
				y++;
				flagDesce = 1;
				break;

			case DIREITA: 
				x++;
				break;

			case CIMA:
				
				rotaciona = 1 ;
				break;

			case SAIR:
				sair = 1 ;
				break;
		}	
		RemoveBloco(pecaAgora,tela); //remove peca do tetris da matriz tela
		MovePecaX(pecaAgora,x);    // atribui as propriedades de posicao
		MovePecaY(pecaAgora,y);
		if (rotaciona){
			RotacionaPeca(pecaAgora);
			rotaciona = 0;
			}

		if (!VerificaColisao(pecaAgora,tela)) //verifica se está colidindo
			AddBloco(pecaAgora, tela);    //e atualiza a peca
			
		else{    //caso nao esteja vago
			if (y>prevY) { //se verdedairo significa que houve uma colisao no eixo y
				colisaoVertical=1; //flag para fixar a peca e tomar as medidas necessarias
				}
			x=prevX; //retorna a posicao x anterior, impedindo as sobreposicoes
			y=prevY;
			CopiaPeca(pecaAntes,pecaAgora);
			AddBloco(pecaAgora, tela); //atribui à matriz tela

			if (colisaoVertical) {
				if (VerificaMorte(tela)) 
					sair=1;			//morre se ha algum bloco na posicao y=5 <------------------
				GeraPeca (pecaAgora); //cria aleatoriamente
				PoePecaNoTopo(pecaAgora, tela);
				x=PecaGetX(pecaAgora); y=PecaGetY(pecaAgora);
				DeletaLinhas(tela, &pontuacao); //verifica se alguma linha foi completada
				if (sair!=1) 
					AddBloco(pecaAgora, tela); // desenha só se nao tiver morrido
				colisaoVertical=0;
				}
		}
		

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
