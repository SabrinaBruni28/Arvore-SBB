#include "arvore_SBB.h"
#include <time.h>

int main(){
    Apontador no;
    int n=20;
    Registro x[n], y;
    int vetor[] = {10,7,0,6,2,3,4,5,19,17,8,20,1,9,15,11,12,95,18,23};
    Inicializa(&no);
    int i;
    for(i=0; i<n; i++){
        x[i].item = vetor[i];
        Insere(x[i],&no);
    }
    while(1){
        Print(no);
        printf("\n");
        printf("Altura: %d\n", Altura_Arvore(no));
        printf("Altura Vertical: %d\n", Altura_Vertical(no));
        printf("Digite o item que deseja retirar: ");
        scanf("%d", &y.item);
        Retira(y, &no);
        Print(no);
        printf("\n");
    }
    return 0;
}
