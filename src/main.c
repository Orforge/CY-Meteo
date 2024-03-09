#include <Headers.h>

int main(int argc,char *argv[]){
    FILE* f1=NULL;
    FILE* ff=NULL;
    Chainon *ers=NULL;
    pArbre rsa=NULL;
    int trime=3;
    int mode=0;
    int reverse=0;
    int nmbLigne=atoi(argv[3]);
    int h=0;
    f1=fopen(argv[1],"r");
    if(f1==NULL){
        exit(2);
    }
    ff=fopen(argv[2],"w");
    if(ff==NULL){
        exit(2);
    }
    
    for(int i=1;i<argc;i++){            //Regarde et analyse le contenu de argv[]
        if(strcmp(argv[i],"liste")==0){
            trime=1;
        }
        else if(strcmp(argv[i],"abr")==0){
            trime=2;
        }
        else if(strcmp(argv[i],"avl")==0){
            trime=3;
        }
        else if(strcmp(argv[i],"t1")==0){
            mode=1;
        }
        else if(strcmp(argv[i],"t2")==0){
            mode=2;
        }
        else if(strcmp(argv[i],"t3")==0){
            mode=3;
        }
        else if(strcmp(argv[i],"p1")==0){
            mode=4;
        }
        else if(strcmp(argv[i],"p2")==0){
            mode=5;
        }
        else if(strcmp(argv[i],"p3")==0){
            mode=6;
        }
        else if(strcmp(argv[i],"m")==0){
            mode=7;
        }
        else if(strcmp(argv[i],"w")==0){
            mode=8;
        }
        else if(strcmp(argv[i],"h")==0){
            mode=9;
        }
        else if(strcmp(argv[i],"r")==0){
            reverse=1;
        }
    }
    
    Station1 e;
    
    if((mode==1) || (mode==4)){
        if(trime==3){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%f\n",&e.ID,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
				e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                rsa=tri_ID_AVL(rsa,e,&h);
                
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%f\n",&e.ID,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
				e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                rsa=tri_IDABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%f\n",&e.ID,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                ers=recherche(ers,e);
            }
        }
    }
    
    else if((mode==2) || (mode==5)){
        if(trime==3){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d-%d-%dT%d:00:00+%d:00;%f\n",&e.chrono.an,&e.chrono.mois,&e.chrono.jour,&e.chrono.heure,&e.chrono.rien,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                rsa=tri_chrono_AVL(rsa,e,&h);
			}
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d-%d-%dT%d:00:00+%d:00;%f\n",&e.chrono.an,&e.chrono.mois,&e.chrono.jour,&e.chrono.heure,&e.chrono.rien,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                rsa=chronABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d-%d-%dT%d:00:00+%d:00;%f\n",&e.chrono.an,&e.chrono.mois,&e.chrono.jour,&e.chrono.heure,&e.chrono.rien,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                ers=tribis(ers,e);
            }
        }
    }

    else if((mode==3) || (mode==6)){
        if(trime==3){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d;%f",&e.chrono,&e.ID,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                rsa=tri_dateABR(rsa,e);
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d;%f",&e.chrono,&e.ID,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                rsa=tri_dateABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d;%f",&e.chrono,&e.ID,&e.max)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                ers=tribibis(ers,e);
            }
        }
    }

    else if(mode==7){
        if(trime==3){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d",&e.ID,&e.humidite)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                rsa=trhum_AVL(rsa,e,&h);
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d",&e.ID,&e.humidite)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                rsa=trumidite_vABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d",&e.ID,&e.humidite)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                ers=trumidite(ers,e);
            }
        }
    }
    
    else if(mode==8){
        if(trime==3){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d;%d",&e.ID,&e.vent.direction,&e.vent.vitesse)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                rsa=triwind_AVL(rsa,e,&h);   
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d;%d",&e.ID,&e.vent.direction,&e.vent.vitesse)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                rsa=rewindABR(rsa,e);   
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d;%d",&e.ID,&e.vent.direction,&e.vent.vitesse)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                e.oye.somme=e.vent.vitesse;
                e.oye.nmb=1;
                e.wtf.somme=e.vent.direction;
                e.wtf.nmb=1;
                ers=rewindlc(ers,e);
            }
        }
    }

    else if(mode==9){
        if(trime==3){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d",&e.ID,&e.altitude)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                rsa=trialt_AVL(rsa,e,&h);
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d",&e.ID,&e.altitude)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                rsa=trivialt_vABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                if(fscanf(f1,"%d;%d",&e.ID,&e.altitude)==0){
                    printf("Erreur lecture fichier");
                    exit (1);
                }
                ers=trivialt_decr(ers,e);
            }
        }
    }

/*-------------------------------------------------------  ECRITURE DANS LE FICHIER DE SORTI  ------------------------------------------------------------------------
-----------------------------------------------------------------  LISTE CHAINE  -----------------------------------------------------------------------------------*/
    if(trime==1){
        Chainon *p=ers;

        if((mode==1) || (mode==4)){
            while(p!=NULL){
                p->elmt.oye.total=p->elmt.oye.somme/p->elmt.oye.nmb;
                fprintf(ff,"%d %f %f %f\n",p->elmt.ID,p->elmt.max,p->elmt.min,p->elmt.oye.total);
                p=p->suivant;
            }
        }
        else if((mode==2) || (mode==5)){
            while(p!=NULL){
                p->elmt.oye.total=p->elmt.oye.somme/p->elmt.oye.nmb;
                fprintf(ff,"%d-%d-%dT%d:00:00 %f\n",p->elmt.chrono.an,p->elmt.chrono.mois,p->elmt.chrono.jour,p->elmt.chrono.jour,p->elmt.oye.total);
                p=p->suivant;
            }
        }
        else if((mode==3) || (mode==6)){
            while(p!=NULL){
                p->elmt.oye.total=p->elmt.oye.somme/p->elmt.oye.nmb;
                fprintf(ff,"%d %d %d %d %f\n",p->elmt.ID,p->elmt.chrono.an,p->elmt.chrono.mois,p->elmt.chrono.jour,p->elmt.oye.total);
                p=p->suivant;
            }
        }
        else if(mode==7){
            while(p!=NULL){
                fprintf(ff,"%d %d\n",p->elmt.ID,p->elmt.humidite);
                p=p->suivant;
            }
        }
        else if(mode==8){
            while(p!=NULL){
                p->elmt.oye.total=p->elmt.oye.somme/p->elmt.oye.nmb;
                p->elmt.wtf.total=p->elmt.wtf.somme/p->elmt.wtf.nmb;
                fprintf(ff,"%d %f %f\n",p->elmt.ID,p->elmt.oye.total,p->elmt.wtf.total);
                p=p->suivant;
            }
        }
        else if(mode==9){
            while(p!=NULL){
                fprintf(ff,"%d %d\n",p->elmt.ID,p->elmt.altitude);
                p=p->suivant;
            }
        }
    }

    /*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    -------------------------------------------------------     ABR   ||   AVL     ---------------------------------------------------------------------------------------
    --------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    else if((trime==2) || (trime==3)){
        pArbre a=rsa;
        
        if((mode==1) || (mode==4)){
            parcoursInfixeM1_4(a,ff);
        }
        else if((mode==2) || (mode==5)){
            parcoursInfixeM2_5(a,ff);
        }
        else if((mode==3) || (mode==6)){
            parcoursInfixeM3_6(a,ff);
        }
        else if(mode==7){
            parcoursInfixeM7(a,ff);
        }
        else if(mode==8){
            parcoursInfixeM8(a,ff);
        }
        else if(mode==9){
            parcoursInfixeM9(a,ff);
        }
    }

    fclose(f1);
    fclose(ff);
}