#include <stdio.h>
#include <stdlib.h>

typedef struct Registro{
    int item;
} Registro;

typedef enum { Vertical, Horizontal } Inclinacao;
typedef enum { False, True} Condicao;

typedef struct  TipoNo* Apontador;
typedef struct TipoNo{
    Registro reg;
    Apontador Esq, Dir;
    Inclinacao BitE, BitD;
} TipoNo;

void Inicializa(Apontador* no);
void EE(Apontador* Ap);
void ED(Apontador* Ap);
void DD(Apontador* Ap);
void DE(Apontador* Ap);
void Insere(Registro x, Apontador* Ap);
void IInsere(Registro x, Apontador* Ap, Inclinacao * IAp, short* Fim);
void Retira(Registro x, Apontador* Ap);
void IRetira(Registro x, Apontador* Ap, short* Fim);
void Antecessor(Apontador q, Apontador *r, short* Fim);
void EsqCurto(Apontador* Ap, short* Fim);
void DirCurto(Apontador* Ap, short* Fim);
int Altura_Vertical(Apontador no);
int Altura_Arvore(Apontador no);
void Print(Apontador no);