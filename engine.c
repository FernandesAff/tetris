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


int VerificaMorte(TipoTela tela[][25]){
	int i;
	
	for (i=0; i<TAMANHOTELAX-1;i++){
		if (VerificaSeBloco(tela[5][i]))
		return(1);
	}	
	return(0);
}

int VerificaColisao(TipoPeca *peca, TipoTela tela[][25]){
	int i=0, colisao=0;

		if(PecaGetOrient(peca)==0){ 
			while(VerificaSeBloco(PecaGetBloco(peca,i)) ){
				if(VerificaSeBloco(tela[(PecaGetY(peca))][PecaGetX(peca)+i]) ) colisao=1;
				i++;
			}
		}
		else{ 
			while(VerificaSeBloco(PecaGetBloco(peca,i))){
				if(VerificaSeBloco(tela[PecaGetY(peca)+i][PecaGetX(peca)]) ) colisao=1;
				i++;
			}
		}	
	return colisao;
}

void DeletaBloco(TipoTela *unidade){
	SetPeca(unidade,VAZIO,CORFUNDO);
}

void AddBloco(TipoPeca *peca,TipoTela tela[][25]){
	int i;
	
	if (PecaGetOrient(peca)==0){	
		for (i=0;i<5;i++) {
			if (VerificaSeBloco(PecaGetBloco(peca,i))){
			tela[PecaGetY(peca)][(PecaGetX(peca))+i]=PecaGetBloco(peca,i);
			}
		}
	}	
	else{
		for (i=0;i<5;i++){
			if (VerificaSeBloco(PecaGetBloco(peca,i))) tela[PecaGetY(peca) +i][PecaGetX(peca)]=PecaGetBloco(peca,i);
		}
	}
}

void RemoveBloco(TipoPeca *peca,TipoTela tela[][25]){
	int i;
	
	if (PecaGetOrient(peca)==0){
		for (i=0;i<5;i++) {
			if (VerificaSeBloco(PecaGetBloco(peca,i))){
				DeletaBloco(&tela[PecaGetY(peca)][PecaGetX(peca)+i]);
			}	
		}
	}	
	else{
		for (i=0;i<5;i++) {
			if (VerificaSeBloco(PecaGetBloco(peca,i)) ){
				DeletaBloco(&tela[PecaGetY(peca)+i][PecaGetX(peca)]);
			}
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
			input=1;
			break;	
		case KEY_DOWN:
			input=2;
			break;
		case KEY_RIGHT: 
			input=3;
			break;
		case KEY_UP: 
			input=4;
			break;
		case 'q':
			input=5;
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
	    tamanhoPeca=0,
	    colisaoVertical=0,
	    pontuacao=0;


//	TipoPeca currentPeca, 
//		 oldPeca;

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
	tamanhoPeca=PecaGetTamanho(pecaAgora);

	while (sair==0){
		CopiaPeca(pecaAgora,pecaAntes);

		prevX=x;
		prevY=y;	
		MostrarTela(tela,pontuacao); //desenha

		switch(PegaInput()){
			case 1: if (x>0)
				x--;
				break;

			case 2: 
				if (PecaGetOrient(pecaAgora)==1){
					if (y<TAMANHOTELAY-tamanhoPeca)
					y++;
					else colisaoVertical=1;
					}
				else {
					if (y<TAMANHOTELAY-1)
					y++;
					else colisaoVertical=1;
					}
				break;

			case 3: 
				if (PecaGetOrient(pecaAgora)==0){
					if (x<TAMANHOTELAX-tamanhoPeca)
					x++;
					}
				else  if (x<TAMANHOTELAX-1) x++;
				break;

/*			case 4: if (y>0) opcao de teste para subir
*				y--;
*				break;
*/
			case 5: sair=1;
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
			if (y!=prevY) { //significa que houve uma colisao no eixo y
				y=prevY;
				colisaoVertical=1; //flag para fixar a peca e tomar as medidas necessarias
				}
			}
			// ou seja, caso haja uma colisao no eixo y
			MovePecaX(pecaAgora,x); //atribui posicoes anteriores
			MovePecaY(pecaAgora,y); 
			AddBloco(pecaAgora, tela); //desenha na matriz tela

		if (colisaoVertical) {
			if (VerificaMorte(tela)) sair=1;//morre se ha algum bloco na posicao y=5 <------------------
			GeraPeca (pecaAgora); //cria aleatoriamente
			tamanhoPeca=PecaGetTamanho(pecaAgora);
			x=PecaGetX(pecaAgora); y=PecaGetY(pecaAgora);
			DeletaLinhas(tela, &pontuacao); //verifica se alguma linha foi completada
			//if (VerificaColisao(&currentPeca,tela)) sair=1; //game over se a peca nova se sobrepoe a alguma peca (n especificado)
			if (sair!=1) AddBloco(pecaAgora, tela); // desenha só se nao tiver morrido
			}
		colisaoVertical=0;
		

		if (sair==1) { //mostra o tragico momento de derrota 
			//pinta os blocos de vermelho, bem dramático
			for(x=0;x<TAMANHOTELAX;x++)
				for(y=0;y<TAMANHOTELAY;y++)
					if(VerificaSeBloco(tela[y][x]))SetPecaCor(&tela[y][x],CORVERMELHO);
			 //desenha a tela, pela ultima vez :(
			MostrarTela(tela,pontuacao);
			getch();   // e o ultimo instante, para repensar e lastimar junto aos arrependimentos
			}
		clear();
	}
	LiberaPeca(pecaAgora);
	LiberaPeca(pecaAntes);
 	FimTela(pontuacao); //a vida eh mesmo curta...
	endwin();

return(0);

}
