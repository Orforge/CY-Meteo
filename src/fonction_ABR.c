#include <Headers.h>


pArbre trivialt_vABR(pArbre pliste, Station1 e){    //Tri servant l'altitude
    pArbre new=creationArbre(e);                    //Tri les ID des stations correspondant dans l'ordre décroissant
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

pArbre trumidite_vABR(pArbre pliste, Station1 e){       //Tri servant l'humidité
    pArbre new=creationArbre(e);                        //Tri les ID des stations correspondant dans l'ordre décroissant
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


pArbre macABR(pArbre p,Station1 e){         //Met à jour les moyennes (somme/nombre_total) du noeud passé en argument
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
    if(krono(p->elmt.chrono,new->elmt.chrono)==0){      //Appel de la fonction krono (fonction_liste.c) qui compare deux dates passé en argument
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