#include <Headers.h>

int iMAX(int a,int b,int c){       //retourne le plus grand argument
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
            return DRG(b);
        }
    }
    else if(b->equilibre<=-2){
        if(b->fg->equilibre<=0){
            return RD(b);
        }
        else{
            return DRD(b);
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
    if(krono(p->elmt.chrono,new->elmt.chrono)==0){      //Appel de la fonction krono (fonction_liste.c) qui compare deux dates passé en argument
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