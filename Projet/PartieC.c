#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 256

struct Arbre{
    long Id;
    long Cap;
    long Cons;
    struct Arbre* G;
    struct Arbre* D;
    int eq;
};
typedef struct Arbre Arbre;

Arbre* creerArbre(long I, long Ca, long Co){
    Arbre* A = malloc(sizeof(Arbre));
    A->Id = I;
    A->Cap = Ca;
    A->Cons = Co;
    A->G = NULL;
    A->D = NULL;
    A->eq = 0;
    return A;
}

int max(long a, long b) {
    return (a > b) ? a : b;
}

int min(long a, long b) {
    return (a < b) ? a : b;
}

int max3(long a, long b, long c) {
    long max_val = a;
    if (b > max_val) {max_val = b;}
    if (c > max_val) {max_val = c;}
    return max_val;
}

int min3(long a, long b, long c) {
    long min_val = a; 
    if (b < min_val) {min_val = b;}
    if (c < min_val) {min_val = c;}
    return min_val; 
}

Arbre* rotationG(Arbre* a){
    Arbre * piv = NULL;
    int eqa, eqp;

    piv = a->D;
    a->D = piv->G;
    piv->G = a;
    eqa = a->eq;
    eqp = piv->eq;
    a->eq = eqa - max(eqp,0)-1;
    piv->eq = min3(eqa-2, eqa+eqp-2,eqp-1);
    a = piv;
    return a;
}

Arbre* rotationD(Arbre* a){
    Arbre * piv = NULL;
    int eqa, eqp;

    piv = a->G;
    a->G = piv->D;
    piv->D = a;
    eqa = a->eq;
    eqp = piv->eq;
    a->eq = eqa - min(eqp,0)+1;
    piv->eq = max3(eqa+2, eqa+eqp+2,eqp+1);
    a = piv;
    return a;
}

Arbre* doubleRotationG(Arbre* a){
    a->D = rotationD(a->D);
    return rotationG(a);
}

Arbre* doubleRotationD(Arbre* a){
    a->G = rotationG(a->G);
    return rotationD(a);
}

Arbre* equilibrageAVL(Arbre* a){
    if (a->eq >= 2){
        if ((a->D)->eq >= 0){return rotationG(a);}
        else{return doubleRotationG(a);}
    }
    else if (a->eq <= -2){
        if ((a->G)->eq <= 0){return rotationD(a);}
        else{return doubleRotationD(a);}
    }
    return a;
}

Arbre* insertionAVL(Arbre* a, long I, long Ca,long Co, int* h){
    if (a == NULL){
        *h = 1;
        return creerArbre(I,Ca,Co);
    }
    else if (I<(a->Id)){
        a->G = insertionAVL(a->G,I,Ca,Co,h);
        *h = -*h;
    }
    else if(I>(a->Id)){
        a->D = insertionAVL(a->D,I,Ca,Co,h);
    }
    else if(I == (a->Id)){
        a->Cap = Ca;
        a->Cons = Co;
        *h =0;
        return a;
    }
    else{*h =0;return a;}

    if (*h != 0){
        a->eq = a->eq + *h;
        a = equilibrageAVL(a);
        if (a->eq == 0){*h = 0;}
        else{*h = 1;}
    }
    return a;
}

void parcoursInfixe(Arbre* A){
    if (A != NULL){
        parcoursInfixe(A->G);
        printf("\nValeur de A : %ld // Equilibre : %d",A->Id, A->eq);
        parcoursInfixe(A->D);
    }
}

long Ajout_Station_AVL(Arbre* A, int colonne_condition, const char *valeur_condition) {
    
    int* h = malloc(sizeof(int));
    *h = 0;

    FILE *file = fopen("c-wire_v00.dat", "r");
    
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    long total = 0;

    // Parcourir le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)) {
        // Découper la ligne en colonnes
        char *colonnes[8];
        int i = 0;
        char *token = strtok(line, ";");

        while (token != NULL && i < 8) {
            colonnes[i] = token;
            token = strtok(NULL, ";");
            i++;
        }

        // Vérifier si la condition est remplie
        if (i > (colonne_condition - 1) && strcmp(colonnes[colonne_condition - 1], valeur_condition) == 0) {
            // Vérifier si la colonne à sommer n'est pas vide ou "-"
            if (i > 7 && strcmp(colonnes[7], "-") != 0) {
                total += atol(colonnes[7]);
                insertionAVL(A,colonnes[colonne_condition - 1],colonnes[6],total, h);                   //Transformer les char* en long !!!!!!!!!!!!
            }
        }
    }

    fclose(file);
    return total;
}



int main(){

    //FILE *file2 = fopen("hvb_comp.csv", "w");

    int* v = malloc(sizeof(int));
    *v = 0;
    Arbre* A = creerArbre(1,70,60);
    A = insertionAVL(A,2,70,60,v);
    A = insertionAVL(A,3,70,60,v);
    A = insertionAVL(A,4,70,60,v);
    A = insertionAVL(A,5,70,60,v);
    parcoursInfixe(A);
    return 0;
}