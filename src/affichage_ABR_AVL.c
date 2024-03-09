#include <Headers.h>

//Procedures servant à parcourir l'arbre (pour les ABR et les AVL) dans le sens voulu, en écrivant chaque noeuds dans le fichier de sorti

void parcoursInfixeM1_4(pArbre a,FILE* ff){
    if(a!=NULL){
        parcoursInfixeM1_4(a->fg,ff);
        a->elmt.oye.total=a->elmt.oye.somme/a->elmt.oye.nmb;
        fprintf(ff,"%d %f %f %f\n",a->elmt.ID,a->elmt.max,a->elmt.min,a->elmt.oye.total);
        parcoursInfixeM1_4(a->fd,ff);
    }
}

void parcoursInfixeM2_5(pArbre a,FILE* ff){
    if(a!=NULL){
        parcoursInfixeM2_5(a->fg,ff);
        a->elmt.oye.total=a->elmt.oye.somme/a->elmt.oye.nmb;
        fprintf(ff,"%d %d %d %f\n",a->elmt.chrono.an,a->elmt.chrono.mois,a->elmt.chrono.jour,a->elmt.oye.total);
        parcoursInfixeM2_5(a->fd,ff);
    }
}

void parcoursInfixeM3_6(pArbre a,FILE* ff){
    if(a!=NULL){
        parcoursInfixeM3_6(a->fg,ff);
        a->elmt.oye.total=a->elmt.oye.somme/a->elmt.oye.nmb;
        fprintf(ff,"%d %d %d %d %f\n",a->elmt.ID,a->elmt.chrono.an,a->elmt.chrono.mois,a->elmt.chrono.jour,a->elmt.oye.total);
        parcoursInfixeM3_6(a->fd,ff);
    }
}

void parcoursInfixeM7(pArbre a,FILE* ff){
    if(a!=NULL){
        parcoursInfixeM7(a->fg,ff);
        fprintf(ff,"%d %d\n",a->elmt.ID,a->elmt.humidite);
        parcoursInfixeM7(a->fd,ff);
    }
}

void parcoursInfixeM8(pArbre a,FILE* ff){
    if(a!=NULL){
        parcoursInfixeM8(a->fg,ff);
        a->elmt.oye.total=a->elmt.oye.somme/a->elmt.oye.nmb;
        a->elmt.wtf.total=a->elmt.wtf.somme/a->elmt.wtf.nmb;
        fprintf(ff,"%d %f %f\n",a->elmt.ID,a->elmt.oye.total,a->elmt.wtf.total);
        parcoursInfixeM8(a->fd,ff);
    }
}

void parcoursInfixeM9(pArbre a,FILE* ff){
    if(a!=NULL){
        parcoursInfixeM9(a->fg,ff);
        fprintf(ff,"%d %d\n",a->elmt.ID,a->elmt.altitude);
        parcoursInfixeM9(a->fd,ff);
    }
}