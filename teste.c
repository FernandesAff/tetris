///	Gerencia os testes de funcionamento do programa.
///	
/// \file teste.c
///	\author Cristóvão
/// \since 11/04/16
/// \version 2.6

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h" 
#include "engine.h"
#include "pecas.h"
#include "ranking.h"

/// Função que testa a conversão de um vetor de inteiros para
/// uma string.

void TesteConverteVetor(void){
	TipoJogador jogador;
	int *apelido=(int *)malloc(6*sizeof(int)), i;

	for(i=0;i<5;i++){
		apelido[i]='a'+i;
	}
	apelido[i]='\n';
	ConverterApelido(apelido,&jogador);
	CU_ASSERT_STRING_EQUAL(jogador.apelido, "abcde")
} 

/// Função que testa o valor máximo do dia recebido.

void TesteData(void){
	TipoJogador jogador;
	int flag;

	ReceberData(&jogador);

	flag=0;
	if(jogador.dia>31)flag=1;
	CU_ASSERT_FALSE(flag);

	flag=0;
	if(jogador.dia<1)flag=1;
	CU_ASSERT_FALSE(flag);

	flag=0;
	if(jogador.mes>12)flag=1;
	CU_ASSERT_FALSE(flag);

	flag=0;
	if(jogador.mes<0)flag=1;
	CU_ASSERT_FALSE(flag);

	flag=0;
	if(jogador.ano>2016)flag=1;
	CU_ASSERT_FALSE(flag);
}

/// Função que testa a criação de um arquivo contendo o placar.

void TesteEntradaPlacar(void){
	TipoJogador jogador;
	char apelido[2]="A";

	strcpy(jogador.apelido, apelido);
	jogador.pontos=100;
	jogador.dia=1;
	jogador.mes=1;
	jogador.ano=2016;
	jogador.tempo=10;

	CU_ASSERT_FALSE(VerificaPlacar());
	CriaPlacar (jogador);
	CU_ASSERT_TRUE(VerificaPlacar());
}

/// Função que testa a inserção de novos dados no arquivo
/// contendo o placar.

void TesteAtualizaPlacar(void){
	FILE *fp;
	TipoJogador jogador[2];
	int flag=0,i=0;
	char	apelido[2][2];

	apelido[0][0]='A';
	apelido[0][1]='\0';
	apelido[1][0]='B';
	apelido[1][1]='\0';

	fp=fopen("ranking.txt", "r");
	fscanf(fp, "%s %d %d/%d/%d %d\n", jogador[0].apelido,&jogador[0].pontos, &jogador[0].dia,&jogador[0].mes,&jogador[0].ano,&jogador[0].tempo);
	if(strcmp(jogador[0].apelido,apelido[0]) || jogador[0].pontos!=100 || jogador[0].dia!=1 || jogador[0].mes!=1 || jogador[0].ano!=2016 || jogador[0].tempo!=10) flag=1;
	fclose(fp);
	CU_ASSERT_FALSE(flag);

	strcpy(jogador[1].apelido, apelido[1]);
	jogador[1].pontos=50;
	jogador[1].dia=1;
	jogador[1].mes=1;
	jogador[1].ano=2016;
	jogador[1].tempo=5;

	flag=0;
	AtualizaPlacar(jogador[1]);
	fp=fopen("ranking.txt", "r");

	while(fscanf(fp, "%s %d %d/%d/%d %d\n", jogador[i].apelido,&jogador[i].pontos, &jogador[i].dia,&jogador[i].mes,&jogador[i].ano,&jogador[i].tempo)!=EOF){
		if(strcmp(jogador[i].apelido,apelido[i]) || jogador[i].pontos!=100/(i+1) || jogador[i].dia!=1 || jogador[i].mes!=1 || jogador[i].ano!=2016 || jogador[i].tempo!=10/(i+1)) flag=1;
		i++;
	}
	CU_ASSERT_FALSE(flag);
	remove("ranking.txt");
}

/// Função que cria  suíte de testes do módulo ranking.

void  AdicionarSuiteRanking(void){
	CU_pSuite suite;
	
	suite = CU_add_suite("Testes do ranking",NULL,NULL);

	CU_ADD_TEST(suite, TesteConverteVetor);
	CU_ADD_TEST(suite, TesteData);
	CU_ADD_TEST(suite, TesteEntradaPlacar);
	CU_ADD_TEST(suite, TesteAtualizaPlacar);
}

///	Função que testa a alocação de peças.

void TesteAlocaPeca (void){
	int flagNulo = 0;
	TipoPeca *peca;
	peca = AlocaPeca();
	if (peca == NULL) flagNulo = 1;
	CU_ASSERT_FALSE(flagNulo);

	LiberaPeca(peca);
}

///	Função que testa as cores das peças.

void TesteCorPecaCorFundo (void){
	TipoPeca *peca;
	int resultado=0, i,j;
	peca = AlocaPeca();
	GeraPeca(peca);
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(PecaGetBloco(peca,i,j).cor==1)
				resultado=1;
			
	
	CU_ASSERT_FALSE(resultado);
	LiberaPeca(peca);		
}

///	Função que testa se as cores das peças geradas são
/// diferentes a cada rodada.

void TesteCorPecaDiferente (void){
	TipoPeca *peca1, *peca2;
	int resultado=1;
	peca1 = AlocaPeca();
	peca2 = AlocaPeca();
	GeraPeca(peca1);
	GeraPeca(peca2);

	if(PecaGetCor(peca1)==PecaGetCor(peca2))
		resultado=0;

	CU_ASSERT_TRUE(resultado);	
	LiberaPeca(peca1);
	LiberaPeca(peca2);
}

void AdicionarSuitePecas(void){
	CU_pSuite suite;
	
	suite = CU_add_suite("Testes de peças",NULL,NULL);

	CU_ADD_TEST(suite, TesteAlocaPeca);	
	CU_ADD_TEST(suite, TesteCorPecaCorFundo);
	CU_ADD_TEST(suite, TesteCorPecaDiferente);
}

///	Função que testa se o jogo acaba com a chegada no
/// limite.

void TestaMorte(void){
	int morte = 0,
	    i = 0;
	
	TipoTela tela[15][25];
	TipoTela bloco,
		 vazio;
	bloco.cor = 5;
	bloco.peca = '0';
	vazio.cor = 7;
	vazio.peca = '-';

	CriarTela(tela);

	morte = VerificaMorte(tela);
	
	CU_ASSERT_FALSE(morte);

	//completa uma fileira de blocos até antes da linha de morte 
	for(i=15; i>5; i--) 
		tela[i][14] = bloco;

	//testa se, para cada posicao de morte, a funcao retorna a morte
	for(i=0; i<25; i++){
		tela[5][i] = bloco;
		morte = VerificaMorte(tela);
		CU_ASSERT_TRUE(morte);
		tela[5][i] = vazio;
		}	

	//nao deve alertar morte, pois fileira [5][i] está vazia.
	morte = VerificaMorte(tela);

	CU_ASSERT_FALSE(morte); 
}

///	Função que testa a colisão com as paredes da tela.


void TestaColisaoParede(void){ 

	TipoTela tela[15][25] ;
	TipoPeca *peca;
	int colisao =0;


	CriarTela(tela);
	peca = AlocaPeca();
	GeraPecaEspecifica(peca, 3, 0); 

	MovePecaX (peca, -2);
	MovePecaY (peca, 0);
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_TRUE(colisao);

	MovePecaX (peca, 22);
	MovePecaY (peca, 0);
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_TRUE(colisao);
	MovePecaX (peca, 0); 
	MovePecaY (peca, -2); 
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_TRUE(colisao);
	MovePecaX (peca, 0); 
	MovePecaY (peca, 12);
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_TRUE(colisao);

	CU_ASSERT_TRUE(colisao);
	MovePecaX (peca, 0); 
	MovePecaY (peca, 0);
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_FALSE(colisao);

	LiberaPeca(peca);
}


/// Funçao que testa a colisao da peca com os blocos da tela.

void TestaColisaoBloco(void){ 

	TipoTela tela[15][25];
	TipoPeca *peca;
	int colisao =0;


	CriarTela(tela);
	peca = AlocaPeca();
	GeraPecaEspecifica(peca, 3, 0); // peca de indice 3, rotacao 0
	
	MovePecaX (peca, 0); 
	MovePecaY (peca, 0);

	//copia a peca pra matriz da tela
	AddBloco(peca,tela); 

	// verifica se a peca colide com a matriz tela (deveria)
	colisao = VerificaColisao(peca, tela); 

	CU_ASSERT_TRUE(colisao);

	//desloca o bloco para onde nao colide 
	MovePecaX (peca, 4); 

	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_FALSE(colisao);

	LiberaPeca(peca);
}

///	Função que testa se uma linha completa é limpada.

void TesteLimpaLinha(void){
	TipoTela tela[15][25];
	int resultado = 0, 
	    i = 0,
	    j = 0,
	    pont = 0;

	CriarTela(tela);
	for(j=0;j<15;j++){
		for(i=0;i<25;i++){
			tela[7][i].peca='0';
			tela[7][i].cor=5;
		}
	}

	DeletaLinhas(tela, &pont);

	for(i=0;i<15;i++){
		for(j=0;j<25;j++){
			if(tela[i][j].peca!='-' || tela[i][j].cor!=7){
				resultado=1;
			}
		}	
	}
	CU_ASSERT_FALSE(resultado);	
}

///	Função que testa a inclusão de uma nova peça na tela.

void TestaPecaNoTopo(void){

	TipoTela tela[15][25];
	TipoPeca *peca;
	int colisao = 0,
	    i;

	CriarTela(tela);
	peca = AlocaPeca();
	GeraPeca(peca);
	MovePecaX(peca, 10);
	MovePecaY(peca, 10);
	
	PoePecaNoTopo(peca,tela);
	
	// A peça nao deve ultrapassar os limites da tela
	colisao = VerificaColisao(peca,tela);

	CU_ASSERT_FALSE(colisao);

	// Aplica a peça à tela
	AddBloco(peca, tela);

	colisao = 0;

	//deve haver pelo menos um bloco na posicao [0][i]
	for(i=0; i<25; i++){
		if (VerificaSeBloco(tela[0][i])) colisao = 1;
	}

	CU_ASSERT_TRUE(colisao);
}

///	Função que cria a suíte de testes do modulo de pecas.

void AdicionarSuiteEngine(void){
	CU_pSuite suite;
	
	suite = CU_add_suite("Testes de engine",NULL,NULL);

	CU_ADD_TEST(suite, TestaMorte);
	CU_ADD_TEST(suite, TesteLimpaLinha);
	CU_ADD_TEST(suite, TestaColisaoParede);
	CU_ADD_TEST(suite, TestaColisaoBloco);
	CU_ADD_TEST(suite, TestaPecaNoTopo);
}

int main(){
	
	if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();

   	AdicionarSuiteRanking();
   	AdicionarSuitePecas();
   	AdicionarSuiteEngine();
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
