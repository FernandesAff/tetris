#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h" 
#include "engine.h"
#include "peças.h"

void teste_corpeca_corfundo (void){
	TipoPeca peca;
	int resultado=0, cores=2, i;

	gera_peca(&peca, &cores);
	for(i=0;i<5;i++){
		if(peca.pecas[i].cor==1){
			resultado=1;
		}	
	}
	CU_ASSERT_FALSE(resultado);		
}

void teste_corpeca_diferente (void){
	TipoPeca peca1, peca2;
	int resultado=1, cor=2;

	gera_peca(&peca1,&cor);
	gera_peca(&peca2, &cor);

	if(peca1.pecas[1].cor==peca2.pecas[1].cor){
		resultado=0;
	}
	CU_ASSERT_TRUE(resultado);	
}

void teste_limpa_linha(void){
	TipoTela tela[15][25];
	int resultado=0, i,j,pont=0;

	criar_tela(tela);
	for(i=0;i<25;i++){
		tela[7][i].peca='0';
		tela[7][i].cor=5;
	}

	deletalinhas(tela, &pont);

	for(i=0;i<15;i++){
		for(j=0;j<25;j++){
			if(tela[i][j].peca!='-' || tela[i][j].cor!=7){
				resultado=1;
			}
		}	
	}

	CU_ASSERT_FALSE(resultado);	
}

void testa_tamanho(void){
	TipoPeca peca;
	int resultado=0, tam, cor=2;

	gera_peca(&peca, &cor);
	tam=get_tamanho(peca);

	if (tam>=3 && tam<=5){
		resultado=1;
	}
	CU_ASSERT_TRUE(resultado);
}

void  adicionar_suite(void){
	CU_pSuite suite;
	
	suite = CU_add_suite("Testes de datas e nomes",NULL,NULL);
	
	CU_ADD_TEST(suite, teste_corpeca_corfundo);
	CU_ADD_TEST(suite, teste_corpeca_diferente);
	CU_ADD_TEST(suite, teste_limpa_linha);
	CU_ADD_TEST(suite, testa_tamanho);
}

int main(){
	
	if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();

   	adicionar_suite();
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	
	CU_basic_run_tests();
	
	CU_cleanup_registry();

	return CU_get_error();
}