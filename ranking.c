///	Gerencia a criação e manipulação do placar.
/// Este módulo implementa o placar do jogo, bem
/// como gerencia as operações relacionados a ele.
///	
/// \file ranking.c
///	\author André
/// \since 11/04/16
/// \version 2.1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "ranking.h"

///	Função que recebe o apelido do jogador.
///
///	\return um ponteiro para o apelido.

int* ReceberApelido (){
	int *apelido, pos=22, i=0;

	apelido=(int *)malloc(6*sizeof(int));
	move(19,3);
	printw("INSIRA SEU APELIDO:_____");
	move(19,22);
	apelido[i]='D';
	while (apelido[i]!='\n') {
    	apelido[i] = getch();
    	switch(apelido[i]){
    		case KEY_BACKSPACE:
    			if(i==0){
    				move(19,22);
    			}
    			else{
    				pos--;
    				i--; 
    				printw("_");
    				move(19,pos);  				
    			}
    			break;
    		case '\n':
    			break;
    		default:
    			if ((apelido[i]>='a' && apelido[i]<='z') || (apelido[i]>='A' && apelido[i]<='Z')){
    				if(i!=5){
    					pos++;
    					i++;
    				}
    				else{
    					move(19,pos);
    					delch();
    					move(19,pos);
    				}	
    			}
    			else{
    				move(19,pos);
    				if(i!=5)printw("_");
    				else delch();
    				move(19,pos);
    			}
    			break;
    	}
    }
    if(apelido[0]=='\n'){
    	apelido[0]='a';
    	apelido[1]='n';
    	apelido[2]='o';
    	apelido[3]='n';
    	apelido[4]='\n';
    }
    return apelido;
}

///	Função que converte o apelido de um vetor de caracteres
/// para um vetor de inteiros.
///
/// \param *apelido ponteiro para o apelido do jogador
/// \param *jogador ponteiro para a estrutura contendo os
/// dados do jogador.

void ConverterApelido(int *apelido, TipoJogador *jogador){
	int i=0;

	while(apelido[i]!='\n'){
		jogador->apelido[i]=apelido[i];
		i++;
	}
	jogador->apelido[i]='\0';
}

///	Função que recebe a data em que o jogo foi executado.
///
///	\param *jogador ponteiro para a estrutura contendo os
/// dados do jogador.

void ReceberData(TipoJogador *jogador){
	struct tm *local;
	time_t t;

	t= time(NULL);
	local=localtime(&t);

	jogador->dia=local->tm_mday;
	jogador->mes=local->tm_mon+1;
	jogador->ano=local->tm_year+1900;
}	

///	Função que verifica a existência de um arquivo com o placar.
///
/// \return 1 ou 0, caso exista ou não um arquivo, respectivamente.

int VerificaPlacar(){
	FILE *fp;

	fp=fopen(ARQUIVO,"r+");
	
	if (fp==NULL){
		return 0;
	}	
	else{
		fclose(fp);
		return 1;
	}	
}	

///	Função que cria um arquivo com o placar.
///
/// \param jogador estrutura contendo os dados do jogador.

void CriaPlacar (TipoJogador jogador){
	FILE *fp;

	fp=fopen(ARQUIVO,"w");
	fprintf(fp, "%s %d %d/%d/%d %d\n", jogador.apelido,jogador.pontos, jogador.dia,jogador.mes,jogador.ano,jogador.tempo);
	fclose(fp);
}

///	Função que atualiza o placar.
///
/// \param jogador estrutura contendo os dados do jogador.

void AtualizaPlacar (TipoJogador jogador){
	FILE *fp, *fp2;
	TipoJogador jogador2;
	int i=0, flag=0;

	fp=fopen(ARQUIVO, "a+");
	fp2=fopen(AUX, "w+");

	while (fscanf(fp, "%s %d %d/%d/%d %d\n", jogador2.apelido,&jogador2.pontos, &jogador2.dia,&jogador2.mes,&jogador2.ano,&jogador2.tempo)!=EOF && i<5){
		if(jogador2.pontos<jogador.pontos && flag==0){
			fprintf(fp2, "%s %d %d/%d/%d %d\n", jogador.apelido,jogador.pontos, jogador.dia,jogador.mes,jogador.ano,jogador.tempo);
			flag=1;
			i++;
		}
		if(i<5){
			fprintf(fp2, "%s %d %d/%d/%d %d\n", jogador2.apelido,jogador2.pontos, jogador2.dia,jogador2.mes,jogador2.ano,jogador2.tempo);
			i++;
		}
	}
	if(i<5 && flag==0){
		fprintf(fp2, "%s %d %d/%d/%d %d\n", jogador.apelido,jogador.pontos, jogador.dia,jogador.mes,jogador.ano,jogador.tempo);
	}
	fclose(fp);
	fclose(fp2);
	remove(ARQUIVO);
	rename(AUX,ARQUIVO);
}