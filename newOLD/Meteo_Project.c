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

Chainon * creationChainon(Station1 a){
    Chainon *p=malloc(sizeof(Chainon));
    if(p==NULL){
        exit(1);
    }
    p->elmt=a;
    p->suivant=NULL;
    return p;
}

pArbre creationArbre(Station1 a){
    pArbre new= malloc(sizeof(Arbre));
    if(new==NULL){
        exit(1);
    }
    new->elmt=a;
    new->fg=NULL;
    new->fd=NULL;
    new->equilibre=0;
    return new;
}

Chainon *insertDebut(Chainon *pliste, Station1 a){
    Chainon* nouveau= creationChainon(a);
    nouveau->suivant=pliste;
    pliste=nouveau;
    return pliste;
}

Chainon *insertFin(Chainon *pliste, Station1 a){
    Chainon * nouveau= creationChainon(a);
    Chainon *p=pliste;
    while(p->suivant!=NULL){
        p=p->suivant;
    }
    p->suivant=nouveau;
    return pliste;
}


Chainon * tri(Chainon *pliste,Station1 a){      //Tri une liste chainée en fonction des ID de station, dans l'ordre croissant
    Chainon *new;
    new=creationChainon(a);
    Chainon *p=pliste;
    if(pliste==NULL){  
        pliste=new;
        return pliste;
    }
    
    if(new->elmt.ID<pliste->elmt.ID){
            pliste=insertDebut(pliste,a);
            return pliste;
    }
        
    while((p->suivant!=NULL) &&(p->suivant->elmt.ID<new->elmt.ID) ){
        p=p->suivant;

    }
    if(p->suivant==NULL){
        pliste= insertFin(pliste,a);
    }
    else {
        new->suivant=p->suivant;
        p->suivant=new;
    }
    return pliste;
}

int krono(Date a, Date e){      //Compare deux date passée en arguments
    if(a.an>e.an){
        return 1;
    }
    else if (a.an < e.an){
        return 0;
    }
    if(a.mois>e.mois){
        return 1;
    }
    else if(a.mois<e.mois){
        return 0;
    }
    if(a.jour>e.jour){
        return 1;
    }
    else if(a.jour<e.jour){
        return 0;
    }
    if(a.heure>e.heure){
        return 1;
    }
    else if(a.heure<e.heure){
        return 0;
    }
    return 2;
}

Chainon * majin(Chainon* p,Station1 e){     //Met à jour les moyennes (somme/nombre_total) du noeud passé en argument
    p->elmt.oye.somme+=e.max;
    p->elmt.oye.nmb+=1;
    return p;
}

Chainon * tribis(Chainon *pliste,Station1 a){       //Tri une liste chainée en fonction des date de relevé, dans l'ordre croissant
    int iii=0;
    Chainon *new;
    new=creationChainon(a);
    Chainon *p=pliste;
    if(pliste==NULL){  
        pliste=new;
        return pliste;
    }
    if(new->elmt.chrono.an<pliste->elmt.chrono.an){
            pliste=insertDebut(pliste,a);
            return pliste;
    }

    if(p->suivant==NULL){
        pliste= insertFin(pliste,a);
        return pliste;
    }
    while(p!=NULL){
        if(krono(a.chrono,p->elmt.chrono)==2){
            p=majin(p,a);
            return pliste;
        }
        
        else if(krono(p->elmt.chrono,a.chrono)==0){
            new->suivant=p->suivant;
            p->suivant=new;
            return pliste;
        }
        
        p=p->suivant;
    }
    return pliste;
}

Chainon * tribibis(Chainon *pliste,Station1 a){     //Tri une liste chainée en fonction des dates de relevé puis des ID de station, dans l'ordre croissant   
    int iii=0;
    Chainon *new;
    new=creationChainon(a);
    Chainon *p=pliste;
    if(pliste==NULL){  
        pliste=new;
        return pliste;
    }
    
    if(new->elmt.chrono.an<pliste->elmt.chrono.an){
            pliste=insertDebut(pliste,a);
            return pliste;
    }

    while((p->suivant!=NULL) &&(iii==0)){
        if(krono(new->elmt.chrono,p->elmt.chrono)==0){
            new->suivant=p->suivant;
            p->suivant=new;
            iii=1;
        }
        else if(krono(new->elmt.chrono,p->elmt.chrono)==2){
            p=tri(p,a);
            iii=1;
        }
        p=p->suivant;
    }
    
    if(p->suivant==NULL){
        pliste= insertFin(pliste,a);
    }
    
    return pliste;
}       

Chainon * maj(Chainon* p,Station1 e){       //Met à jour les moyennes (somme/nombre_total) du noeud passé en argument
    if(p->elmt.max<e.max){                  //Met aussi à jour si nécessaire le maximum et le minimum du noeud passé en argument
        p->elmt.max=e.max;
    }
    if(p->elmt.min>e.min){
        p->elmt.min=e.min;
    }
    p->elmt.oye.somme+=e.max;
    p->elmt.oye.nmb+=1;
    return p;
}

Chainon * majinwind(Chainon* p,Station1 e){     //Met à jour les moyennes (somme/nombre_total) des directions du vent (pour une même station) et de sa vitesse
    p->elmt.oye.somme+=e.vent.vitesse;
    p->elmt.oye.nmb+=1;
    p->elmt.wtf.somme+=e.vent.direction;
    p->elmt.wtf.nmb+=1;
    return p;
}

Chainon* recherche(Chainon * a,Station1 e){     //Verifie si l'élément a insérer a déjà une ID de station correspondante dans la liste, appel 'maj' si oui, 
    if(a==NULL){                                //ou appel la fonction 'tri' le cas échéant
        a=tri(a,e);
        return a;
    }
    else if(a->elmt.ID==e.ID){
        a=maj(a,e);
    }
    Chainon *p=a;
    while((p->suivant!=NULL) && (p->elmt.ID!=e.ID) ){
        p=p->suivant;
    }
    if (p->elmt.ID==e.ID){
        p=maj(p,e);
    }
    else if(p->suivant==NULL){
        a=tri(a,e);
    }
    return a;
}

Chainon* rewindlc(Chainon * a,Station1 e){      //Tri une liste chainée en fonction du vent de chaque station, dans l'ordre croissant  
    if(a==NULL){
        a=tri(a,e);
        return a;
    }
    else if(a->elmt.ID==e.ID){
        a=majinwind(a,e);
    }
    Chainon *p=a;
    while((p->suivant!=NULL) &&(p->elmt.ID!=e.ID) ){
        p=p->suivant;
    }
    if (p->elmt.ID==e.ID){
        a=majinwind(a,e);
    }
    else if(p->suivant==NULL){
        a=tri(a,e);
    }
    return a;
}

Chainon * trivialt_decr(Chainon* pliste, Station1 e){       //Tri une liste chainée en fonction de l'altitude de chaque station, dans l'ordre croissant
    Chainon* p=pliste;
    Chainon *new=creationChainon(e);
    if(pliste==NULL){
        pliste=new;
        return pliste;
    }
    if(pliste->elmt.ID<e.ID){
        pliste=insertDebut(pliste,e);
        return pliste;
    }
    //
    if(e.ID==pliste->elmt.ID){
		if(e.altitude>pliste->elmt.altitude){
			pliste->elmt.altitude==e.altitude;
		}
        return pliste;	
	}

    while((p->suivant!=NULL)&&(p->elmt.ID>e.ID)&&(p->elmt.ID!=e.ID)){
        p=p->suivant;
    }
    if(e.ID==p->elmt.ID){
		if(e.altitude>p->elmt.altitude){
			p->elmt.altitude==e.altitude;
		}
        return pliste;
	}
    else if(p->elmt.ID<new->elmt.ID){
        new->suivant=p->suivant;
        p->suivant=new;
    }
    return pliste;
}

Chainon * trumidite(Chainon* pliste, Station1 e){       //Tri une liste chainée en fonction de l'humidité de chaque station, dans l'ordre croissant
    Chainon* p=pliste;
    Chainon* new=creationChainon(e);
    if(pliste==NULL){
        pliste=new;
        return pliste;
    }
	else if(e.ID==pliste->elmt.ID){
		if(e.humidite>pliste->elmt.humidite){
			pliste->elmt.humidite==e.humidite;
		}
        return pliste;	
	}
    else if(pliste->elmt.ID<e.ID){
        pliste=insertDebut(pliste,e);
        return pliste;
    }    
    while((p->suivant!=NULL)&&(p->elmt.ID>e.ID)&&(p->elmt.ID!=e.ID)){
        p=p->suivant;
    }
    if(e.ID==p->elmt.ID){
		if(new->elmt.humidite>p->elmt.humidite){
			p->elmt.humidite==new->elmt.humidite;
		}
        return pliste;
	}
    else if((p->elmt.ID<e.ID) || (p->suivant==NULL)){
        new->suivant=p->suivant;
        p->suivant=new;
    }
    
    return pliste;
}





//----------------------------------------------------------------------------------ABR-----------------------------------------------------------------------------------------------------




pArbre trivialt_vABR(pArbre pliste, Station1 e){         //Tri servant à calculer l'altitude
    pArbre new=creationArbre(e);                         //Tri les ID des stations correspondant dans l'ordre décroissant
    pArbre p=pliste;
    if(pliste==NULL){
        pliste=new;
        return pliste;
    }
    if(p->elmt.ID<new->elmt.ID){
        p->fg=trivialt_vABR(p->fg,new->elmt);
    }
    else if(p->elmt.ID>new->elmt.ID){
        p->fd=trivialt_vABR(p->fd,new->elmt);
    }
    return pliste;
}

pArbre trumidite_vABR(pArbre pliste, Station1 e){   //Tri servant à calculer l'humidité
    pArbre new=creationArbre(e);                    //Tri les ID des stations correspondant dans l'ordre décroissant
    pArbre p=pliste;
    if(pliste==NULL){
        pliste=new;
        return pliste;
    }
	else if(new->elmt.ID==p->elmt.ID){
		if(new->elmt.humidite>p->elmt.humidite){
				p->elmt.humidite==new->elmt.humidite;
		}	
	}
    else if(p->elmt.ID>new->elmt.ID){
        p->fd=trumidite_vABR(p->fd,new->elmt);
    }
    else if(p->elmt.ID<new->elmt.ID){
        p->fg=trumidite_vABR(p->fg,new->elmt);
    }
    return pliste;
}

pArbre macABR(pArbre p,Station1 e){     //Met à jour les moyennes (somme/nombre_total) du noeud passé en argument
    if(p->elmt.max<e.max){              //Met aussi à jour si nécessaire le maximum et le minimum du noeud passé en argument
        p->elmt.max=e.max;
    }
    if(p->elmt.min>e.min){
        p->elmt.min=e.min;
    }
    p->elmt.oye.somme+=e.max;
    p->elmt.oye.nmb+=1;
    return p;
}

pArbre majinABR(pArbre p,Station1 e){       //Met à jour les moyennes (somme/nombre_total) du noeud passé en argument
    p->elmt.oye.somme+=e.max;
    p->elmt.oye.nmb+=1;
    return p;
}

pArbre tri_IDABR(pArbre pliste,Station1 e){     //Tri un ABR en fonction des ID de station, dans l'ordre croissant
    pArbre new=creationArbre(e);
    pArbre p=pliste;
    if(pliste==NULL){
        return new;
    }
    if(p->elmt.ID<new->elmt.ID){
        p->fd=tri_IDABR(p->fd,e);
    }
    else if(p->elmt.ID>new->elmt.ID){
        p->fg=tri_IDABR(p->fg,e);
    }
    else if(p->elmt.ID==new->elmt.ID){
        pliste=macABR(pliste,e);
    }
    return pliste;
}

pArbre chronABR(pArbre pliste,Station1 e){      //Tri un ABR en fonction des dates de relevé, dans l'ordre croissant
    pArbre new=creationArbre(e);
    pArbre p=pliste;
    if(pliste==NULL){
        pliste=new;
        return pliste;
    }
    if(krono(p->elmt.chrono,new->elmt.chrono)==0){      //Appel de la fonction krono qui compare deux dates passé en argument
        p->fg=chronABR(p->fg,e);
    }
    else if(krono(p->elmt.chrono,new->elmt.chrono)==1){
        p->fd=chronABR(p->fd,e);
    }
    else if(krono(p->elmt.chrono,new->elmt.chrono)==2){
        pliste=majinABR(pliste,e);
    }
    return pliste;
}

pArbre tri_dateABR(pArbre pliste, Station1 e){      //Tri un ABR en fonction des dates de relevé puis des ID de station, dans l'ordre croissant
    pArbre new=creationArbre(e);
    pArbre p=pliste;
    if(pliste==NULL){
        pliste=new;
        return pliste;
    }
    if(krono(p->elmt.chrono,new->elmt.chrono)==0){
        p=tri_dateABR(p,e);
    }
    else if(krono(p->elmt.chrono,new->elmt.chrono)==1){
        p=tri_dateABR(p,e);
    }
    else if(krono(p->elmt.chrono,new->elmt.chrono)==2){
        pliste=tri_IDABR(pliste,e);
    }
    return pliste;
}

pArbre majinwind_ABR(pArbre p,Station1 e){      //Met à jour les moyennes (somme/nombre_total) des directions du vent (pour une même station) et de sa vitesse
    p->elmt.oye.somme+=e.vent.vitesse;
    p->elmt.oye.nmb+=1;
    p->elmt.wtf.somme+=e.vent.direction;
    p->elmt.wtf.nmb+=1;
    return p;
}

pArbre rewindABR(pArbre pliste,Station1 e){     //Tri la direction et la vitesse du vent pour chaque station, dans l'ordre croissant
    pArbre new=creationArbre(e);
    pArbre p=pliste;
    if(pliste==NULL){
        pliste=tri_IDABR(pliste,e);
        return pliste;
    }
    else if(p->elmt.ID==new->elmt.ID){
        p=majinwind_ABR(p,e);
    }
    else if(p->elmt.ID>new->elmt.ID){
        p->fg=tri_IDABR(p->fg,e);
    }
    else if(p->elmt.ID<new->elmt.ID){
        p->fd=tri_IDABR(p->fd,e);
    }
    return pliste;
}







//----------------------------------------------------------------------------------AVL--------------------------------------------------------------------------------------





int iMAX(int a,int b,int c){        //retourne le plus grand argument
    if(a>b){
        if(a>c){
            return a;
        }
        return c;
    }
    else if(b>c){
        return b;
    }
    return c;
}

int Minnie(int a,int b,int c){      //retourne le plus petit argument
    if(a<b){
        if(a<c){
            return a;
        }
        return c;
    }
    else if(b<c){
        return b;
    }
    return c;
}

pArbre RG(pArbre a){
    pArbre pivot=NULL;
    int eqa,eqp;
    pivot=a->fd;
    a->fd=pivot->fg;
    pivot->fg=a;
    eqa=a->equilibre;
    eqp=pivot->equilibre;
    a->equilibre=eqa-iMAX(eqp,0,0)-1;
    pivot->equilibre=Minnie(eqa-2,eqa+eqp-2,eqp-1);
    a=pivot;
    return a;
}

pArbre RD(pArbre a){
    pArbre pivot=NULL;
    int eqa,eqp;
    pivot=a->fg;
    a->fg=pivot->fd;
    pivot->fd=a;
    eqa=a->equilibre;
    eqp=pivot->equilibre;
    a->equilibre=eqa-Minnie(eqp,0,1)+1;
    pivot->equilibre=iMAX(eqa+2,eqa+eqp+2,eqp+1);
    a=pivot;
    return a;
}

pArbre DRG(pArbre a){
    a->fd=RD(a->fd);
    return RG(a);
}

pArbre DRD(pArbre a){
    a->fg=RG(a->fg);
    return RD(a);
}

pArbre equilibrageAVL(pArbre a){
    pArbre b=a;
    if(b->equilibre>=2){
        if(b->fd->equilibre>=0){
           return RG(b);
        }
        else{
        }
    }
    else if(b->equilibre<=-2){
        if(b->fg->equilibre<=0){
            return RD(b);
        }
        else{
        }
    }
    return a;
}

// Rotations pour un tri effectué dans l'orde décroissant

pArbre RGBis(pArbre a){
    pArbre pivot=NULL;
    int eqa,eqp;
    pivot=a->fg;
    a->fg=pivot->fd;
    pivot->fd=a;
    eqa=a->equilibre;
    eqp=pivot->equilibre;
    a->equilibre=eqa-iMAX(eqp,0,0)-1;
    pivot->equilibre=Minnie(eqa-2,eqa+eqp-2,eqp-1);
    a=pivot;
    return a;
}

pArbre RDBis(pArbre a){
    pArbre pivot=NULL;
    int eqa,eqp;
    pivot=a->fd;
    a->fd=pivot->fg;
    pivot->fg=a;
    eqa=a->equilibre;
    eqp=pivot->equilibre;
    a->equilibre=eqa-Minnie(eqp,0,1)+1;
    pivot->equilibre=iMAX(eqa+2,eqa+eqp+2,eqp+1);
    a=pivot;
    return a;
}

pArbre DRG2(pArbre a){
    a->fg=RDBis(a->fg);
    return RGBis(a);
}

pArbre DRD2(pArbre a){
    a->fd=RGBis(a->fd);
    return RDBis(a);
}

pArbre equilibrageBAVL(pArbre a){
    pArbre b=a;
    if(b->equilibre>=2){
        if(b->fg->equilibre>=0){
           return RGBis(b);
        }
        else{
            return DRG2(b);
        }
    }
    else if(b->equilibre<=-2){
        if(b->fd->equilibre<=0){
            return RDBis(b);
        }
        else{
            return DRD2(b);
        }
    }
    return a;
}

pArbre tri_ID_AVL(pArbre a,Station1 e,int *h){      //Tri un AVL en fonction des ID de station, dans l'ordre croissant
    pArbre new=creationArbre(e);
	pArbre p=a;
    if(a==NULL){
        *h=1;
        return new;
    }
	else if(new->elmt.ID==p->elmt.ID){
		a=macABR(a,e);
	}
    else if(new->elmt.ID<p->elmt.ID){
        p->fg=tri_ID_AVL(p->fg,e,h);
        *h=-*h;
    }
    else if(new->elmt.ID>p->elmt.ID){
        p->fd=tri_ID_AVL(p->fd,e,h);
    }
    else{
        *h=0;
        return a;
    }
    if(*h!=0){
        a->equilibre=a->equilibre + *h;
        a=equilibrageAVL(a);
        if(a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}

pArbre tri_chrono_AVL(pArbre a,Station1 e,int *h){      //Tri un AVL en fonction des dates de relevé, dans l'ordre croissant
    pArbre new=creationArbre(e);
    pArbre p=a;
    if(a==NULL){
        *h=1;
        return new;
    }
    if(krono(p->elmt.chrono,new->elmt.chrono)==0){
        p->fg=tri_chrono_AVL(p->fg,e,h);
        *h=-*h;
    }
    else if(krono(p->elmt.chrono,new->elmt.chrono)==1){
        p->fd=tri_chrono_AVL(p->fd,e,h);
    }
	else if(krono(p->elmt.chrono,new->elmt.chrono)==2){
		a=majinABR(a,e);
	}
    else{
        *h=0;
        return a;
    }
    if(*h!=0){
        a->equilibre=a->equilibre + *h;
        a=equilibrageAVL(a);
        if(a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}

pArbre tri_chronoID_AVL(pArbre a,Station1 e,int *h){        //Tri un AVL en fonction des dates de relevé puis des ID de station, dans l'ordre croissant
    pArbre new=creationArbre(e);
    pArbre p=a;
    if(a==NULL){
        *h=1;
        return new;
    }
    if(krono(p->elmt.chrono,new->elmt.chrono)==0){
        p->fg=tri_chronoID_AVL(p->fg,e,h);
        *h=-*h;
    }
    else if(krono(p->elmt.chrono,new->elmt.chrono)==1){
        p->fd=tri_chronoID_AVL(p->fd,e,h);
    }
	else if(krono(p->elmt.chrono,new->elmt.chrono)==2){
		a=tri_ID_AVL(a,e,h);
	}
    else{
        *h=0;
        return a;
    }
    if(*h!=0){
        a->equilibre=a->equilibre + *h;
        a=equilibrageAVL(a);
        if(a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}

pArbre triwind_AVL(pArbre a,Station1 e,int *h){     //Tri la direction et la vitesse du vent pour chaque station, dans l'ordre croissant
    pArbre new=creationArbre(e);
	pArbre p=a;
    if(a==NULL){
        *h=1;
        return new;
    }
	else if(new->elmt.ID==p->elmt.ID){
		a=majinABR(a,e);
	}
    else if(new->elmt.ID<p->elmt.ID){
        p->fg=tri_ID_AVL(p->fg,e,h);
        *h=-*h;
    }
    else if(new->elmt.ID>p->elmt.ID){
        p->fd=tri_ID_AVL(p->fd,e,h);
    }
    else{
        *h=0;
        return a;
    }
    if(*h!=0){
        a->equilibre=a->equilibre + *h;
        a=equilibrageAVL(a);
        if(a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}

pArbre trialt_AVL(pArbre a,Station1 e,int *h){      //Tri l'altitude de chaque station, dans l'ordre décroissant
    pArbre new=creationArbre(e);
	pArbre p=a;
    if(a==NULL){
        *h=1;
        return new;
    }
    else if(new->elmt.ID<p->elmt.ID){
        p->fd=trialt_AVL(p->fd,e,h);
        *h=-*h;
    }
    else if(new->elmt.ID>p->elmt.ID){
        p->fg=trialt_AVL(p->fg,e,h);
    }
    else{
        *h=0;
        return a;
    }
    if(*h!=0){
        a->equilibre=a->equilibre + *h;
        a=equilibrageBAVL(a);
        if(a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}

pArbre trhum_AVL(pArbre a,Station1 e,int *h){       //Tri l'humidité de chaque station, dans l'ordre décroissant
    pArbre new=creationArbre(e);
	pArbre p=a;
    if(a==NULL){
        *h=1;
        return new;
    }
	else if(new->elmt.ID==p->elmt.ID){
		if(new->elmt.humidite>p->elmt.humidite){
				p->elmt.humidite==new->elmt.humidite;
		}	
	}
    else if(new->elmt.ID<p->elmt.ID){
        p->fd=trhum_AVL(p->fd,e,h);
        *h=-*h;
    }
    else if(new->elmt.ID>p->elmt.ID){
        p->fg=trhum_AVL(p->fg,e,h);
    }
    else{
        *h=0;
        return a;
    }
    if(*h!=0){
        a->equilibre=a->equilibre + *h;
        a=equilibrageBAVL(a);
        if(a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}


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
                fscanf(f1,"%d;%f\n",&e.ID,&e.max);
				e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                rsa=tri_ID_AVL(rsa,e,&h);
                
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%f\n",&e.ID,&e.max);
				e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                rsa=tri_IDABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%f\n",&e.ID,&e.max);
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
                fscanf(f1,"%d-%d-%dT%d:00:00+%d:00;%f\n",&e.chrono.an,&e.chrono.mois,&e.chrono.jour,&e.chrono.heure,&e.chrono.rien,&e.max);
                e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                rsa=tri_chrono_AVL(rsa,e,&h);
			}
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d-%d-%dT%d:00:00+%d:00;%f\n",&e.chrono.an,&e.chrono.mois,&e.chrono.jour,&e.chrono.heure,&e.chrono.rien,&e.max);
                e.min=e.max;
                e.oye.somme=e.max;
                e.oye.nmb=1;
                rsa=chronABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d-%d-%dT%d:00:00+%d:00;%f\n",&e.chrono.an,&e.chrono.mois,&e.chrono.jour,&e.chrono.heure,&e.chrono.rien,&e.max);
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
                fscanf(f1,"%d;%d;%f",&e.chrono,&e.ID,&e.max);
                rsa=tri_dateABR(rsa,e);
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d;%f",&e.chrono,&e.ID,&e.max);
                rsa=tri_dateABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d;%f",&e.chrono,&e.ID,&e.max);
                ers=tribibis(ers,e);
            }
        }
    }

    else if(mode==7){
        if(trime==3){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d",&e.ID,&e.humidite);
                rsa=trhum_AVL(rsa,e,&h);
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d",&e.ID,&e.humidite);
                rsa=trumidite_vABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d",&e.ID,&e.humidite);
                ers=trumidite(ers,e);
            }
        }
    }
    
    else if(mode==8){
        if(trime==3){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d;%d",&e.ID,&e.vent.direction,&e.vent.vitesse);
                rsa=triwind_AVL(rsa,e,&h);   
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d;%d",&e.ID,&e.vent.direction,&e.vent.vitesse);
                rsa=rewindABR(rsa,e);   
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d;%d",&e.ID,&e.vent.direction,&e.vent.vitesse);
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
                fscanf(f1,"%d;%d",&e.ID,&e.altitude);
                rsa=trialt_AVL(rsa,e,&h);
            }
        }
        else if(trime==2){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d",&e.ID,&e.altitude);
                rsa=trivialt_vABR(rsa,e);
            }
        }
        else if(trime==1){
            for(int i=0;i<nmbLigne;i++){
                fscanf(f1,"%d;%d",&e.ID,&e.altitude);
                ers=trivialt_decr(ers,e);
            }
        }
    }


/*----------------------------------------------------------     ECRITURE DANS LE FICHIER DE SORTI       ---------------------------------------------------------------------
------------------------------------------------------------------       LISTES CHAINEES     ----------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        

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

    /*--------------------------------------------------------------------------------------------------------------------------------------------
    -------------------------------------------------------     ABR   ||   AVL     ---------------------------------------------------------------
    --------------------------------------------------------------------------------------------------------------------------------------------*/


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