#ifndef PECAS_INST
#define PECAS_INST

#include "pecas.h"

TipoPeca* AlocaPecaInst();
void LiberaPecaInst(TipoPeca*);
void CopiaPecaInst(TipoPeca*, TipoPeca*);
void GeraPecaInst (TipoPeca *);
void MovePecaXInst (TipoPeca *, int);
void MovePecaYInst (TipoPeca *, int);
void RotacionaPecaInst(TipoPeca*);

#define MovePecaX MovePecaXInst
#define MovePecaY MovePecaYInst
#define AlocaPeca AlocaPecaInst
#define LiberaPeca LiberaPecaInst
#define CopiaPeca CopiaPecaInst
#define GeraPeca GeraPecaInst
#define RotacionaPeca RotacionaPecaInst


#endif
