#define TAMANHOTELAY 15
#define TAMANHOTELAX 25
#define CORFUNDO 7
#define BLOCO '0'
#define VAZIO '-'
#include <ncurses.h>
#include "tela.h"
#include "peças.h"
#include "moduloauxengine.h"

/* A FAZER
* deletar opcao de subir
* deletar modulo de teste nao rigoroso, e suas funcoes aqui chamadas
* melhorar arquitetura (boniteza)
*/

int verificamorte(TipoTela tela[][25]){
	int i;
	for (i=0; i<TAMANHOTELAX-1;i++){
		if (tela[5][i].peca==BLOCO){
		return(1);
		}
	}
	return(0);
}

int verifica_colisao(TipoPeca *pecatetris, TipoTela tela[][25]){

	int i=0, colisao=0, tamanhopeca=0;

		if (pecatetris->orient==0){ 
			while(pecatetris->pecas[i].peca==BLOCO){
				if(tela[(pecatetris->y)][(pecatetris->x)+i].peca==BLOCO) colisao=1;
				i++;
			}
		}
		else{ 
			while(pecatetris->pecas[i].peca==BLOCO){
				if(tela[(pecatetris->y)+i][(pecatetris->x)].peca==BLOCO) colisao=1;
				i++;
			}
		}	
	return colisao;
}

void deletabloco(TipoTela *unidade){
	unidade->cor=CORFUNDO;
	unidade->peca=VAZIO;
}

void addbloco(TipoPeca *peca,TipoTela tela[][25]){
	int i;
	if (peca->orient==0){	
		for (i=0;i<5;i++) {
			if (peca->pecas[i].peca==BLOCO){
			tela[peca->y][(peca->x)+i]=peca->pecas[i];
			}
		}
	}	
	else{
		for (i=0;i<5;i++){
			if (peca->pecas[i].peca==BLOCO) tela[peca->y +i][(peca->x)]=peca->pecas[i];
		}
	}
}

void removebloco(TipoPeca *peca,TipoTela tela[][25]){
	int i;
	if (peca->orient==0)	
	for (i=0;i<5;i++) {if (peca->pecas[i].peca==BLOCO) deletabloco(&tela[peca->y][(peca->x)+i]);}
	else 
	for (i=0;i<5;i++) {if (peca->pecas[i].peca==BLOCO) deletabloco(&tela[(peca->y)+i][peca->x]);}
}

int verificalinhas(TipoTela tela[][TAMANHOTELAX]){//verifica se ha alguma linha completa
	int i,j, completa=1;	  //se houver, retorna a posicao y dela
	for(i=TAMANHOTELAY-1;i>=0;i--){
		for (j=0;j<TAMANHOTELAX;j++){
			if (tela[i][j].peca==VAZIO) {
				completa=0;
				j=100;
				}
			}
		if (completa==1) return i;
		completa=1;
		}
	return(-1); //caso nenhuma linha esteja completa, retorna -1
}

void gravidade(TipoTela tela[][TAMANHOTELAX],int posicaolinha){
	int j;
	for(;posicaolinha>0;posicaolinha--){
		for (j=0;j<TAMANHOTELAX;j++){
			tela[posicaolinha][j]=tela[posicaolinha-1][j];
			}
		}
}	

void deletalinhas(TipoTela tela[][TAMANHOTELAX],int *pontuacao){ 
	int linha=0, i;
	while (linha!=-1){
		linha=verificalinhas(tela);
		if (linha!=-1) {
			gravidade(tela, linha);
		//				for (i=0;i<TAMANHOTELAX;i++) deletabloco(&tela[linha][i]);
			*pontuacao+=100;
			}
	}
		//	gravidade(tela, linha);
}

void inicia_ncurses(){
	initscr();
}

void finaliza_ncurses(){
	endwin();
}

int pega_input(){ //corrigir para as setas

	int input;
	switch(getch())
	{
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


int posicaolivre(TipoTela pos){
	int livre=0;
	if (pos.peca != BLOCO) livre =1;
	return(livre);
}

int tamanho_peca(TipoPeca pecatetris){
	int tamanho=0;
	
	while (pecatetris.pecas[tamanho].peca==BLOCO) tamanho++; 
	return tamanho;
}

int loop(TipoTela tela[][TAMANHOTELAX]){
	int sair=0,x=10,y=0,prevx,prevy, tamanhopeca=0, colisaovertical=0, pontuacao=0,corpeca=2;
	TipoPeca currentpeca, oldpeca;

	criaaleatorio(tela, 2, 0.6);

	inicia_ncurses();
	inicio_tela();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	gera_peca (&currentpeca,&corpeca); //cria aleatoriamente
	addbloco(&currentpeca, tela); //aplica à matriz
	tamanhopeca=tamanho_peca(currentpeca);
	//while (currentpeca.pecas[tamanhopeca].peca==BLOCO) tamanhopeca++; // calcula tamanho da peca

	while (sair==0){
		oldpeca=currentpeca;

		prevx=x;
		prevy=y;	
	
		mostrar_tela(tela,pontuacao); //desenha

		switch(pega_input()){
			case 1: if (x>0)
				x--;
				break;

			case 2: 
				if (currentpeca.orient==1){
					if (y<TAMANHOTELAY-tamanhopeca)
					y++;
					else colisaovertical=1;
					}
				else {
					if (y<TAMANHOTELAY-1)
					y++;
					else colisaovertical=1;
					}
				break;

			case 3: 
				if (currentpeca.orient==0){
					if (x<TAMANHOTELAX-tamanhopeca)
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
		
		removebloco(&currentpeca,tela); //apaga peca do tetris da matriz tela
		move_peca_x(&currentpeca,x);    // atribui as propriedades de posicao
		move_peca_y(&currentpeca,y);

		if (!verifica_colisao(&currentpeca,tela)){ //verifica se o estado de posicao ja esta ocupado com alguma peca da matriz
			removebloco(&oldpeca, tela); //caso esteja vago, remove peca antiga
			addbloco(&currentpeca, tela); //e atualiza a peca
			}
		else{    //caso nao esteja vago
			x=prevx; //retorna a posicao x anterior, impedindo as sobreposicoes
			if (y!=prevy) { //significa que houve uma colisao no eixo y
				y=prevy;
				colisaovertical=1; //flag para fixar a peca e tomar as medidas necessarias
				}
			}
			// ou seja, caso haja uma colisao no eixo y
			move_peca_x(&currentpeca,x); //atribui posicoes anteriores
			move_peca_y(&currentpeca,y); 
			addbloco(&currentpeca, tela); //desenha na matriz tela

		if (colisaovertical) {
			if (verificamorte(tela)) sair=1;//morre se ha algum bloco na posicao y=5 <------------------
			gera_peca (&currentpeca, &corpeca); //cria aleatoriamente
			tamanhopeca=tamanho_peca(currentpeca);
			x=currentpeca.x; y=currentpeca.y;
			deletalinhas(tela, &pontuacao); //verifica se alguma linha foi completada
			//if (verifica_colisao(&currentpeca,tela)) sair=1; //game over se a peca nova se sobrepoe a alguma peca (n especificado)
			addbloco(&currentpeca, tela); //desenha a peca nova na matriz tela		
			}
		colisaovertical=0;
		

		if (sair==1) { //mostra o tragico momento de derrota 
			for(x=0;x<TAMANHOTELAX;x++) for(y=0;y<TAMANHOTELAY;y++) if(tela[y][x].peca==BLOCO)tela[y][x].cor=4 ; //vermelho dramatico
			mostrar_tela(tela,pontuacao); //desenha a tela, pela ultima vez :(
			getch();  		      // e o ultimo instante, para repensar e lastimar junto aos arrependimentos
			}
		clear();
	}
 	fim_tela(pontuacao); //a vida eh mesmo curta...
	finaliza_ncurses();

return(0);

}
