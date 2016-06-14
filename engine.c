///	Gerencia o funcionamento completo do jogo. 
///	Este módulo implementa o funcionamento mecânico
///	do jogo e agrega os demais conceitos implementados
///	pelos outros módulos.
///	
/// \file engine.c
///	\author Cristóvão
/// \since 11/04/16
/// \version 2.8

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
#include "engine.h"
#define TEST_MODE

///	Variável global que armazena o tempo de jogo decorrido.

static int globalTempo = 0;

/// Comandos.
/// Enumeração dos comandos que podem ser inseridos.

enum comandos{
	ESQUERDA,
	BAIXO,
	DIREITA,
	CIMA,
	SAIR
} com;

///	Função que verifica se há algum bloco na linha limítrofe.
///	Verifica se algum bloco atingiu o limite do jogo, ou seja,
/// a posição 5.
///
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.
/// \return um inteiro com valor 0 ou 1 que indica se a linha de 
/// limite foi atingida.

int VerificaMorte(TipoTela tela[][TAMANHOTELAX]){ 
	int i;
	
	for (i=0; i<TAMANHOTELAX;i++){
		if (VerificaSeBloco(tela[5][i]))
		return(1);
	}	
	return(0);
}

///	Função que verifica a colisão de blocos.
/// Verifica se uma peça colidiu com algum bloco presente na tela.
///
/// \param *peca ponteiro para a peça atual e sua posição na tela.
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.
/// \return um inteiro com valor 0 ou 1 que indica se a peça colidiu.

int VerificaColisao(TipoPeca *peca, TipoTela tela[][TAMANHOTELAX]){
	int i=0,
		j=0, 
		colisao=0;

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
	if(!colisao){
		for(i=0;i<5;i++) for(j=0;j<5;j++){
			if (VerificaSeBloco(PecaGetBloco(peca,j,i))){
				if(VerificaSeBloco(tela[(PecaGetY(peca))+j][PecaGetX(peca)+i]))colisao=1;
			}
		}
	}
	return colisao;
}

///	Função que insere uma peça na matriz da tela.
/// Insere na parte superior da tela a peça da rodada atual do jogo.
///
/// \param *peca ponteiro para a peça atual.
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.

void PoePecaNoTopo(TipoPeca *peca, TipoTela tela[][TAMANHOTELAX]){
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

///	Função que limpa um campo da matriz da tela.
///
///	\param *unidade uma posição na tela que deve ser excluída.

void DeletaBloco(TipoTela *unidade){
	SetPeca(unidade,VAZIO,CORFUNDO);
}

///	Função que insere um bloco na matriz da tela.
///
/// \param *peca ponteiro para a peça atual e sua posição na tela.
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.

void AddBloco(TipoPeca *peca,TipoTela tela[][TAMANHOTELAX]){
	int i,
		j;

	for (i=0;i<5;i++) for (j=0;j<5;j++) {
		if (VerificaSeBloco(PecaGetBloco(peca,i,j))){
			tela[PecaGetY(peca)+i][(PecaGetX(peca))+j]=PecaGetBloco(peca,i,j);
		}
	}
}

///	Função que remove um bloco da matriz da tela.
///
/// \param *peca ponteiro para a peça atual e sua posição na tela.
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.

void RemoveBloco(TipoPeca *peca,TipoTela tela[][TAMANHOTELAX]){
	int i, 
		j;

	for (i=0;i<5;i++) for (j=0;j<5;j++) {
		if (VerificaSeBloco(PecaGetBloco(peca,i,j))){
			DeletaBloco(&tela[PecaGetY(peca)+i][(PecaGetX(peca))+j]);
		}
	}
}

///	Função que verifica se há uma linha completa.
///
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.
/// \return a linha que está completa ou -1 caso não exista uma
/// linha completa.

int VerificaLinhas(TipoTela tela[][TAMANHOTELAX]){
	int i,
		j,
		completa=1;	  //se houver, retorna a posicao y dela
	
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

///	Função que decrementa a posição de uma linha da tela.
///
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.
/// \param posicaolinha inteiro que representa a posição de uma 
/// linha.

void Gravidade(TipoTela tela[][TAMANHOTELAX],int posicaolinha){
	int j;
	
	for(;posicaolinha>0;posicaolinha--){
		for (j=0;j<TAMANHOTELAX;j++){
			tela[posicaolinha][j]=tela[posicaolinha-1][j];
		}
	}
}	

///	Função que deleta uma linha completa na matriz da tela.
/// Incrementa a pontuação do jogador em 100 pontos.
///
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.
/// \param *pontuacao um ponteiro para a pontuação atual do jogador.

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

///	Função que recebe o comando o usuário.
///	Atribui determinados comandos de acordo com as teclas pressionadas.
///
/// \return o comando do usuário.

int PegaInput(){ 
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

///	Função que coordena o tempo de jogo.
/// Mantém um loop que incrementa o tempo conforme ele passa. O loop é
///	interrompido caso alguma tecla válida seja pressionada, é chegada a
/// hora de uma peça descer ou quando o contador deve ser atualizado na
/// tela.
///
/// \param milissegundos um inteiro que representa um segundo.
///	\param *peca ponteiro para a peça atual do jogo.
/// \param *flagdesce flag que indica se a peça deve descer na tela.
/// \return o comando inserido pelo usuário.

int Temporizador(int milissegundos, TipoPeca * peca, int *flagDesce){
	int constante = CLOCKS_PER_SEC/1000;
	int input;
	static int tempo; //static para que o valor se altere a cada vez que essa funcao é chamada

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
}

///	Função que gerencia todas as funções do jogo.
/// Mantém o um loop que deve ser percorrido a cada ação realizada,
/// bem como a interpretação dos inputs e as decisões que devem ser
/// tomadas pela engine.
///
///	\param tela[][TAMANHOTELAX] uma matriz que representa a
/// tela do jogo.
/// \return 0 caso não aconteça nenhum erro.

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

	WINDOW * window= initscr();
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
		globalTempo=((int)clock())/CLOCKS_PER_SEC;

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
		//remove peca do tetris da matriz tela
		RemoveBloco(pecaAgora,tela); 
		//atribui as propriedades de posicao
		MovePecaX(pecaAgora,x);
		MovePecaY(pecaAgora,y);
		if (rotaciona){
			RotacionaPeca(pecaAgora);
			rotaciona = 0;
			}

		//verifica se não está colidindo
		if (!VerificaColisao(pecaAgora,tela))
			//atualiza peça
			AddBloco(pecaAgora, tela);  
		//se estiver colidindo:
		else{
			//se houver uma colisao no eixo y
			if (y>prevY) { 
				//flag para fixar a peca e tomar as medidas necessarias
				FlagcolisaoVertical=1; 
				}
			//retorna a posicao x anterior, impedindo as sobreposicoes
			x=prevX; 
			y=prevY;
			CopiaPeca(pecaAntes,pecaAgora);
			//atribui à matriz tela
			AddBloco(pecaAgora, tela);

			if (FlagcolisaoVertical) {
				//verifica se alguma linha foi completada
				DeletaLinhas(tela, &pontuacao); 
				//morre se ha algum bloco na posicao y=5
				if (VerificaMorte(tela)) 
					sair=1;		
				//cria nova peca aleatoriamente	 
				GeraPeca (pecaAgora);
				PoePecaNoTopo(pecaAgora, tela);
				x=PecaGetX(pecaAgora); y=PecaGetY(pecaAgora);
				if (sair!=1) 
					// desenha só se nao tiver morrido
					AddBloco(pecaAgora, tela);
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