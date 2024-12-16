#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 256

struct Arbre{
    int v;
    struct Arbre* G;
    struct Arbre* D;
    int eq;
};
typedef struct Arbre Arbre;

Arbre* creerArbre(int E){
    Arbre* A = malloc(sizeof(Arbre));
    A->v = E;
    A->G = NULL;
    A->D = NULL;
    A->eq = 0;
    return A;
}

Arbre* creerAVL_hvb(){
    FILE *file = fopen("c-wire_v00.dat", "r");
    if (file ==NULL){exit(1);}

    char buff[1024];
    if(fgets(buff,sizeof(buff),file)==NULL){fclose(file); exit(1);}
    
    
    char line[MAX_LINE_LENGTH];
    long total = 0;

    // Parcourir le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)) {
        // Découper la ligne en colonnes
        charcolonnes[10]; // Supposons qu'il y a au maximum 10 colonnes
        int i = 0;
        char token = strtok(line, ";");

        while (token != NULL && i < 10) {
            colonnes[i++] = token;
            token = strtok(NULL, ";");
        }

        // Vérifier si la condition est remplie
        if (i > colonne_condition - 1 && strcmp(colonnes[colonne_condition - 1], valeur_condition) == 0) {
            // Vérifier si la colonne à sommer n'est pas vide ou "-"
            if (i > colonne_a_sommer - 1 && strcmp(colonnes[colonne_a_sommer - 1], "-") != 0) {
                total += atol(colonnes[colonne_a_sommer - 1]);
            }
        }
    }

    fclose(file);
    return total;
}




int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max3(int a, int b, int c) {
    int max_val = a;
    if (b > max_val) {max_val = b;}
    if (c > max_val) {max_val = c;}
    return max_val;
}

int min3(int a, int b, int c) {
    int min_val = a; 
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

Arbre* insertionAVL(Arbre* a, int e, int* h){
    if (a == NULL){
        *h = 1;
        return creerArbre(e);
    }
    else if (e<(a->v)){
        a->G = insertionAVL(a->G,e,h);
        *h = -*h;
    }
    else if(e>(a->v)){
        a->D = insertionAVL(a->D,e,h);
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

Arbre* suppMinAVL(Arbre* a, int* h, int* e){
    Arbre* tmp = malloc(sizeof(Arbre));

    if(a->G == NULL){
        *e = a->v;
        *h = -1;
        tmp = a;
        a = a->D;
        free(tmp);
        return a;
    }
    else{
        a->G = suppMinAVL(a->G, h, e);
        *h = -*h;
    }
    if ( *h != 0){
        a->eq = a->eq + *h;
        a = equilibrageAVL(a);
        if (a->eq == 0){*h = -1;}
        else{*h = 0;}
    }
    return a;    
}

Arbre* suppressionAVL(Arbre* a, int e, int* h){
    Arbre * tmp = malloc(sizeof(Arbre));
    if(a == NULL){*h = 1;return a;}
    else if(e > a->v){a->D = suppressionAVL(a->D,e,h);}
    else if(e < a->v){a->G = suppressionAVL(a->G,e,h);*h = -*h;}
    else if(a->D != NULL){a->D = suppMinAVL(a->D, h, &(a->v));}
    else{
        tmp = a;
        a = a->G;
        free(tmp);
        *h = -1;
        return a;
    }
    if (a == NULL){return a;}
    if (*h != 0){
        a->eq = a->eq + *h;
        a = equilibrageAVL(a);
        if (a->eq == 0){*h = -1;}
        else{*h = 0;}
    }
    return a;
}

void parcoursInfixe(Arbre* A){
    if (A != NULL){
        parcoursInfixe(A->G);
        printf("\nValeur de A : %d // Equilibre : %d",A->v, A->eq);
        parcoursInfixe(A->D);
    }
}

int main(){

    FILE *file2 = fopen("hvb_comp.csv", "w");




    int* h = malloc(sizeof(int));
    *h = 0;
    int* v = malloc(sizeof(int));
    *v = 0;
    Arbre* A = creerArbre(9);
    return 0;
}