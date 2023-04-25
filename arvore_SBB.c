#include "arvore_SBB.h"

void Inicializa(Apontador* no){
    (*no) = NULL;
}

void EE(Apontador* Ap){
    Apontador Ap1;
    Ap1 = (*Ap)->Esq;
    (*Ap)->Esq = Ap1->Dir;
    Ap1->Dir = *Ap;
    Ap1->BitE = Vertical;
    (*Ap)->BitE = Vertical;
    *Ap = Ap1;
}

void ED(Apontador* Ap){
    Apontador Ap1, Ap2;
    Ap1 = (*Ap)->Esq; 
    Ap2 = Ap1->Dir;
    Ap1->BitD = Vertical; 
    (*Ap)->BitE = Vertical;
    Ap1->Dir = Ap2->Esq;
    Ap2->Esq = Ap1;
    (*Ap)->Esq = Ap2->Dir;
    Ap2->Dir = *Ap;
    *Ap = Ap2;
}

void DD(Apontador* Ap){
    Apontador Ap1;
    Ap1 = (*Ap)->Dir;
    (*Ap)->Dir = Ap1->Esq;
    Ap1->Esq = *Ap;
    Ap1->BitD = Vertical;
    (*Ap)->BitD = Vertical;
    *Ap = Ap1;
}

void DE(Apontador* Ap){
    Apontador Ap1, Ap2;
    Ap1 = (*Ap)->Dir; 
    Ap2 = Ap1->Esq;
    Ap1->BitE = Vertical; 
    (*Ap)->BitD = Vertical;
    Ap1->Esq = Ap2->Dir;
    Ap2->Dir = Ap1;
    (*Ap)->Dir = Ap2->Esq;
    Ap2->Esq = *Ap;
    *Ap = Ap2;
}

void Insere(Registro x, Apontador* Ap){
    short Fim;
    Inclinacao IAp;
    IInsere(x, Ap, &IAp, &Fim);
}

void IInsere(Registro x, Apontador* Ap, Inclinacao * IAp, short* Fim){
    if(*Ap == NULL){
        *Ap = (Apontador)malloc(sizeof(TipoNo));
        *IAp = Horizontal;
        (*Ap)->reg = x;
        (*Ap)->BitE = Vertical;
        (*Ap)->BitD = Vertical;
        (*Ap)->Esq = NULL;
        (*Ap)->Dir = NULL;
        *Fim = False;
        return;
    }
    if(x.item == (*Ap)->reg.item){
        printf("\nERRO: item já está na árvore\n");
        *Fim = True; return;
    }
    if(x.item < (*Ap)->reg.item){
        IInsere(x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
        if(*Fim) return;
        if((*Ap)->BitE != Horizontal){
            *Fim = True; return;
        }
        if((*Ap)->Esq->BitE == Horizontal){
            EE(Ap);
            *IAp = Horizontal; return;
        }
        if((*Ap)->Esq->BitD == Horizontal){
            ED(Ap);
            *IAp = Horizontal; return;
        }
        return;
    }
    if(x.item > (*Ap)->reg.item){
        IInsere(x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
        if(*Fim) return;
        if((*Ap)->BitD != Horizontal){
            *Fim = True; return;
        }
        if((*Ap)->Dir->BitD == Horizontal){
            DD(Ap);
            *IAp = Horizontal; return;
        }
        if((*Ap)->Dir->BitE == Horizontal){
            DE(Ap);
            *IAp = Horizontal; return;
        }
        return;
    }
}

void Retira(Registro x, Apontador* Ap){
    short Fim;
    IRetira(x, Ap, &Fim);

}

void IRetira(Registro x, Apontador* Ap, short* Fim){
    TipoNo* aux;
    if(*Ap == NULL){
        printf("\nChave não está na árvore\n");
        *Fim = True; return;
    }
    if(x.item < (*Ap)->reg.item){
        IRetira(x, &(*Ap)->Esq, Fim);
        if(!Fim) EsqCurto(Ap, Fim);
        return;
    }
    if(x.item > (*Ap)->reg.item){
        IRetira(x, &(*Ap)->Dir, Fim);
        if(!Fim) DirCurto(Ap, Fim);
        return;
    }
    *Fim = False;
    aux = *Ap;
    if(aux->Dir == NULL){
        *Ap = aux->Esq;
        free(aux);
        if(*Ap != NULL) *Fim = True;
        return;
    }
    if(aux->Esq == NULL){
        *Ap = aux->Dir;
        free(aux);
        if(*Ap != NULL) *Fim = True;
        return;
    }
    Antecessor(aux, &aux->Esq, Fim);
    if(*Fim) EsqCurto(Ap, Fim);
}

void Antecessor(Apontador q, Apontador *r, short* Fim){
    if((*r)->Dir != NULL){
        Antecessor(q, &(*r)->Dir, Fim);
        if(!Fim) DirCurto(r, Fim);
        return;
    }
    q->reg = (*r)->reg;
    q = *r;
    *r = (*r)->Esq;
    free(q);
    if(*r != NULL) *Fim = True;
}

void EsqCurto(Apontador* Ap, short* Fim){
    Apontador Ap1;
    if((*Ap)->BitE == Horizontal){
        (*Ap)->BitE = Vertical;
        *Fim = True;
        return;
    }
    if((*Ap)->BitD == Horizontal){
        Ap1 = (*Ap)->Dir;
        (*Ap)->Dir = Ap1->Esq;
        Ap1->Esq = *Ap;
        *Ap = Ap1;
        if((*Ap)->Esq->Dir->BitE == Horizontal){
            DE(&(*Ap)->Esq);
            (*Ap)->BitE = Horizontal;
        }
        else if((*Ap)->Esq->Dir->BitD == Horizontal){
            DD(&(*Ap)->Esq);
            (*Ap)->BitE = Horizontal;
        }
        *Fim = True; return;
    }
    (*Ap)->BitD = Horizontal;
    if((*Ap)->Dir->BitE == Horizontal){
        DE(Ap);
        *Fim = True;
        return;
    }
    if((*Ap)->Dir->BitD == Horizontal){
        DD(Ap);
        *Fim = True;
    }
}

void DirCurto(Apontador* Ap, short* Fim){
    Apontador Ap1;
    if((*Ap)->BitD == Horizontal){
        (*Ap)->BitD = Vertical;
        *Fim = True;
        return;
    }
    if((*Ap)->BitE == Horizontal){
        Ap1 = (*Ap)->Esq;
        (*Ap)->Esq = Ap1->Dir;
        Ap1->Dir = *Ap;
        *Ap = Ap1;
        if((*Ap)->Dir->Esq->BitD == Horizontal){
            ED(&(*Ap)->Dir);
            (*Ap)->BitD = Horizontal;
        }
        else if((*Ap)->Dir->Esq->BitE == Horizontal){
            EE(&(*Ap)->Dir);
            (*Ap)->BitD = Horizontal;
        }
        *Fim = True; return;
    }
    (*Ap)->BitE = Horizontal;
    if((*Ap)->Esq->BitD == Horizontal){
        ED(Ap);
        *Fim = True;
        return;
    }
    if((*Ap)->Esq->BitE == Horizontal){
        EE(Ap);
        *Fim = True;
    }
}

int Altura_Vertical(Apontador no){
    if(no == NULL) return -1;
    else{
        int he = Altura_Vertical(no->Esq);
        int hd = Altura_Vertical(no->Dir);
        if(he>hd){
            if(no->BitE == Vertical) return he+1;
            else return he;
        }
        else{
            if(no->BitD == Vertical)  return hd+1;
            else return hd;
        }
    }
}

int Altura_Arvore(Apontador no){
    if(no == NULL) return -1;
    else{
        int he = Altura_Arvore(no->Esq);
        int hd = Altura_Arvore(no->Dir);
        if(he < hd) return hd +1;
        else return he +1;
    }
}
 
void Print(Apontador no){
    if(no != NULL){
        Print(no->Esq);
        printf("%d ", no->reg.item);
        Print(no->Dir);
    }
}