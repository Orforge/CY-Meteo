#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

typedef struct date{
    int an;
    int mois;
    int jour;
    int heure;
    int rien;
}Date;

typedef struct moye{
    float somme;
    int nmb;
    float total;
}Moye;

typedef struct wind{
    float vitesse;
    int direction;
}Wind;

typedef struct station1 {
    int ID;
    float max;
    float min;
    int altitude;
    int humidite;
    Date chrono;
    Wind vent;
    Moye oye;
    Moye wtf;
}Station1;

typedef struct chainon {
    Station1 elmt;
    struct chainon * suivant;
}Chainon;

typedef struct arbre{
    Station1 elmt;
    struct arbre* fg;
    struct arbre* fd;
    int equilibre;
}Arbre;

typedef Arbre* pArbre;

Chainon* creationChainon(Station1 a);
pArbre creationArbre(Station1 a);
Chainon *insertDebut(Chainon *pliste, Station1 a);
Chainon *insertFin(Chainon *pliste, Station1 a);
Chainon * tri(Chainon *pliste,Station1 a);
int krono(Date a, Date e);
Chainon * majin(Chainon* p,Station1 e);
Chainon * tribis(Chainon *pliste,Station1 a);
Chainon * tribibis(Chainon *pliste,Station1 a);
Chainon * maj(Chainon* p,Station1 e);
Chainon * majinwind(Chainon* p,Station1 e);
Chainon* recherche(Chainon * a,Station1 e);
Chainon* rewindlc(Chainon * a,Station1 e);
Chainon * trivialt_decr(Chainon* pliste, Station1 e);
Chainon * trumidite(Chainon* pliste, Station1 e);
pArbre trivialt_vABR(pArbre pliste, Station1 e);
pArbre trumidite_vABR(pArbre pliste, Station1 e);
pArbre macABR(pArbre p,Station1 e);
pArbre majinABR(pArbre p,Station1 e);
pArbre tri_IDABR(pArbre pliste,Station1 e);
pArbre chronABR(pArbre pliste,Station1 e);
pArbre tri_dateABR(pArbre pliste, Station1 e);
pArbre majinwind_ABR(pArbre p,Station1 e);
pArbre rewindABR(pArbre pliste,Station1 e);
int iMAX(int a,int b,int c);
int Minnie(int a,int b,int c);
pArbre RG(pArbre a);
pArbre RD(pArbre a);
pArbre DRG(pArbre a);
pArbre DRD(pArbre a);
pArbre equilibrageAVL(pArbre a);
pArbre RGBis(pArbre a);
pArbre RDBis(pArbre a)
pArbre DRG2(pArbre a);
pArbre DRD2(pArbre a);
pArbre equilibrageBAVL(pArbre a);
pArbre tri_ID_AVL(pArbre a,Station1 e,int *h);
pArbre tri_chrono_AVL(pArbre a,Station1 e,int *h);
pArbre tri_chronoID_AVL(pArbre a,Station1 e,int *h);
pArbre triwind_AVL(pArbre a,Station1 e,int *h);
pArbre trialt_AVL(pArbre a,Station1 e,int *h);
pArbre trhum_AVL(pArbre a,Station1 e,int *h);
void parcoursInfixeM1_4(pArbre a,FILE* ff);
void parcoursInfixeM2_5(pArbre a,FILE* ff);
void parcoursInfixeM3_6(pArbre a,FILE* ff);
void parcoursInfixeM7(pArbre a,FILE* ff);
void parcoursInfixeM8(pArbre a,FILE* ff);
void parcoursInfixeM9(pArbre a,FILE* ff);