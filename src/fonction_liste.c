#include <Headers.h>

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

Chainon* rewindlc(Chainon * a,Station1 e){        //Tri une liste chainée en fonction du vent de chaque station, dans l'ordre croissant           
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