#define TAMANHOTELAY 15
#define TAMANHOTELAX 25 
#define CORVERMELHO 4
#define CORFUNDO 7
#define BLOCO '0'
#define VAZIO '-'
#include <ncurses.h>
#include "tela.h"
#include "pecas.h"
#include "time.h"
#include "ranking.h"
#define TEST_MODE

static int globalTempo = 0; //armazena o tempo de jogo decorrido a cada ciclo

enum comandos{
	ESQUERDA,
	BAIXO,
	DIREITA,
	CIMA,
	SAIR
} com;

int VerificaMorte(TipoTela tela[][25]){
	int i;
	
	for (i=0; i<TAMANHOTELAX;i++){
		if (VerificaSeBloco(tela[5][i]))
		return(1);
		}	
	return(0);
	}

int VerificaColisao(TipoPeca *peca, TipoTela tela[][25]){
	int i=0, j=0, colisao=0;

	//verifica colisao com parede:
	for(i=0;i<5;i++) for(j=0;j<5;j++){
		if (VerificaSeBloco(PecaGetBloco(peca,i,j))) {
			     if ( (PecaGetX(peca)+j)>TAMANHOTELAX-1) colisao=1; //colide à direita
			else if ((PecaGetX(peca)+j)<0) colisao=1; 		//colide à esquerda	
			else if ( (PecaGetY(peca)+i)>TAMANHOTELAY-1) colisao=1; //colide abaixo
			else if ((PecaGetY(peca)+i)<0) colisao=1; 		//colide acima
		}
	}
	

	//verifica colisao com blocos:
	if(!colisao)
		for(i=0;i<5;i++) for(j=0;j<5;j++){
			if (VerificaSeBloco(PecaGetBloco(peca,j,i)))
				if(VerificaSeBloco(tela[(PecaGetY(peca))+j][PecaGetX(peca)+i])) 
					colisao=1;
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
		default :
			input = -1;
			break;
	}
	return input;
}


int Temporizador(int milissegundos, TipoPeca * peca, int *flagDesce){
/*	consta aqui o loop que cordena o tempo do jogo.
*	Ha tres motivos para o jogo sair deste loop e realizar
*	alguma açao. a primeira é: alguma tecla válida
*	foi pressionada, segunda: é chegada a hora da 
*	peça descer. E por último: o "tempo de jogo" nao é
*	mais o mesmo e precisa ser redesenhado na tela.
*/
	int constante = CLOCKS_PER_SEC/1000;
	int input;
	static int tempo;

	milissegundos /= PecaGetSpeed(peca) ;

	//enquanto o tempo de descer nao chega
	while(((int)clock() - tempo) < milissegundos * constante){
		input = PegaInput();
		//sai caso o alguma tecla valida foi pressionada
		if(input!=-1) 
			break;
		//sai caso o tempo deva ser mudado
		if(globalTempo!= (int)clock()/CLOCKS_PER_SEC){
			break;
			}
	}
	//caso o tempo de descer tenha chegado, atualiza o valor do tempo base
	if (((int)clock() - tempo) >= milissegundos * constante) {
		tempo = (int)clock ();
		input =-1;
		*flagDesce = 1;
		}

	return input;
};


int Loop(TipoTela tela[][TAMANHOTELAX]){
	int rotaciona=0,
	    sair=0,
	    x=0,
	    y=0,
	    prevX=0,
	    prevY=0,
	    FlagcolisaoVertical=0,
	    pontuacao=0,
	    flagDesce=0,
	    input=-1,
	    *apelido;

	TipoJogador jogador;
	
	TipoPeca *pecaAgora = AlocaPeca(),
		 *pecaAntes = AlocaPeca();

	initscr();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	InicioTela();
	apelido=ReceberApelido();
	clear();
	noecho();
	nodelay(stdscr, TRUE);

	GeraPeca(pecaAgora); //cria aleatoriamente
	PoePecaNoTopo(pecaAgora, tela);
	x=PecaGetX(pecaAgora); y=PecaGetY(pecaAgora);
	AddBloco(pecaAgora, tela); //aplica à matriz

	while (sair==0){
		CopiaPeca(pecaAgora,pecaAntes);
		prevX=x;
		prevY=y;	
		MostrarTela(tela,pontuacao,globalTempo); //desenha
		input = Temporizador(1000 /*1000 mSec*/, pecaAgora, &flagDesce);
		globalTempo=clock()/CLOCKS_PER_SEC;

		switch(input){
			case ESQUERDA:
				x--;
				break;

			case BAIXO: 
				SpeedUp(pecaAgora,2);
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
			
			default:
				break;
				
		}	

		if (flagDesce) {
			y++;
			flagDesce = 0;
			}

		RemoveBloco(pecaAgora,tela); //remove peca do tetris da matriz tela
		MovePecaX(pecaAgora,x);    // atribui as propriedades de posicao
		MovePecaY(pecaAgora,y);
		if (rotaciona){
			RotacionaPeca(pecaAgora);
			rotaciona = 0;
			}

		if (!VerificaColisao(pecaAgora,tela)) //verifica se nao está colidindo
			AddBloco(pecaAgora, tela);    //e atualiza a peca
			
		else{    //caso esteja colidindo
			if (y>prevY) { //se verdedairo significa que houve uma colisao no eixo y
				FlagcolisaoVertical=1; //flag para fixar a peca e tomar as medidas necessarias
				}
			x=prevX; //retorna a posicao x anterior, impedindo as sobreposicoes
			y=prevY;
			CopiaPeca(pecaAntes,pecaAgora);
			AddBloco(pecaAgora, tela); //atribui à matriz tela

			if (FlagcolisaoVertical) {
				DeletaLinhas(tela, &pontuacao); //verifica se alguma linha foi completada
				if (VerificaMorte(tela)) 
					sair=1;			//morre se ha algum bloco na posicao y=5 <------------------
				GeraPeca (pecaAgora); //cria aleatoriamente
				PoePecaNoTopo(pecaAgora, tela);
				x=PecaGetX(pecaAgora); y=PecaGetY(pecaAgora);
				if (sair!=1) 
					AddBloco(pecaAgora, tela); // desenha só se nao tiver morrido
				FlagcolisaoVertical=0;
				}
		}
		if (sair==1) { //mostra o momento de derrota 
			//pinta os blocos de vermelho dramático
			for(x=0;x<TAMANHOTELAX;x++){
				for(y=0;y<TAMANHOTELAY;y++){
					if(VerificaSeBloco(tela[y][x]))SetPecaCor(&tela[y][x],CORVERMELHO);
				}
			}//desenha a tela, pela ultima vez :(
			nodelay(stdscr, FALSE);
			MostrarTela(tela,pontuacao,globalTempo);
			getch();
			}
		clear();
	}
	LiberaPeca(pecaAgora);
	LiberaPeca(pecaAntes);
	ReceberData(&jogador);
	jogador.pontos=pontuacao;
	jogador.tempo=globalTempo;
	ConverterApelido(apelido,&jogador);
	if(VerificaPlacar())AtualizaPlacar(jogador);
	else CriaPlacar(jogador);
	FimTela(pontuacao);
	endwin();

return(0);

}
