#include "fonction.h"
#include "shapes.h"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

Board* creer(){
//allocation de la m�moire
Board *a = (Board *)malloc(sizeof(Board));
//affectation des valeurs au scores et � la section prochaine pi�ce
  a->score = 0;
  a->next = (rand()%7)+1;
  a->piece_de_cote = 0;
  a->de_cote = 0;
  a->suivante = (rand()%7)+1;
//initialisation du tableau � z�ro
  int i=0;
  int j=0;
 for(j=0; j<22;j++){
     for(i=0; i<10;i++){
        a->tableau[j][i]=0;
     }
  }
 //initialisation de la partie mobile � z�ro
  for(j=0; j<22;j++){
     for(i=0; i<10;i++){
        a->move[j][i]=0;
     }
  }

  for(i=0;i<7;i++){
    a->choix[i]=1;
  }
  a->choix[a->next-1] = 0;
  a->choix[a->suivante-1] = 0;
return a;
}

void random(Board* a){
    srand(time(NULL));
    int i, cpt=0, coup;
    for(i=0;i<7;i++){
        if(a->choix[i]!=0){
            cpt++;
        }
    }
    coup=(rand()%7)+1;
    if(cpt==0){
        for(i=0;i<7;i++){
            a->choix[i]=1;
        }
    }
    do{
        coup = ((coup)%7)+1;
    }while(a->choix[coup-1]==0);
    a->choix[coup-1]=0;
    a->suivante = coup;
}

void check(Board* a, Mix_Chunk *son_ligne, int chute_simultanee){
int i,j;
int compteur=0;
   for(i=0; i<22; i++){
	   compteur = 0;
	   for(j=0; j<10;j++){
		   if(a->tableau[i][j]==0){compteur = compteur + 1;}
	   }
	   if(compteur==0){
			a->score=a->score+1;
			Mix_PlayChannel(1, son_ligne, 0);
			for(j=0;j<10;j++){
				a->tableau[i][j]=0;
			}
			descendre_lignes(a,i);
			a->score = a->score+chute_simultanee;
			check(a, son_ligne, 1);
	   }

              }

return;
}

void descendre_lignes(Board* a, int ligne){
	int i,j;
	for(i=ligne; i<21; i++){
		for(j=0;j<10;j++){
			a->tableau[i][j]=a->tableau[i+1][j];
		}
	}

}

int defaite(Board* a){
	int j;
	for(j=0;j<10;j++){
		if(a->tableau[20][j]!=0){return 1;}
	}
	return 0;
}

void descente(Board* a, Mix_Chunk *son_ligne){
	int i,j;
	int stop=0;
	for(i=0;i<22;i++){
		for(j=0;j<10;j++)
			if(a->move[i][j]!=0){
				if(a->tableau[i-1][j]!=0 || i==0){stop=stop+1;}
		}
	}
	if(stop!=0){
		for(i=0;i<22;i++){
			for(j=0;j<10;j++){
				if(a->move[i][j]!=0){
					a->tableau[i][j]=a->move[i][j];
					a->move[i][j]=0;
					a->de_cote = 0;
				}
			}
		}
		if(defaite(a)==0){
			continuer(a);
		}
		check(a, son_ligne,0);
		return;
	}
	else{
		for(i=0;i<21;i++){
			for(j=0;j<10;j++){
				a->move[i][j]=a->move[i+1][j];
			}
		}
		for(j=0;j<10;j++){
				a->move[21][j]=0;
			}
		}
}

void continuer(Board* a){
	int i,j;
	int stop=0;
	for(i=0;i<22;i++){
		for(j=0;j<10;j++){
			if(a->move[i][j]!=0){stop++;}
		}
	}
	if(stop==0){
	a->next = a->suivante;
	random(a);
	spawn(a);
	}
}

void detruire(Board* a){
	free(a);
	return;
}

void spawn(Board* a){
	int i,j;
	for(i=0;i<4;i++){
			for(j=0;j<4;j++){
					a->move[i+18][j+3]=PIECES[a->next][0][i][j];
			}
		}
}

void pause(){
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

void touche_droite(Board* a) {
	int i, j;
	int stop = 0;
	for (i = 0; i<22; i++) {
		if(a->move[i][0]!=0){stop++;}
		for (j = 1; j<10; j++)
			if (a->move[i][j] != 0) {
				if (a->tableau[i][j-1] != 0) { stop = stop + 1; }
			}
	}
	if (stop == 0) {
		for (i = 0; i<22; i++) {
			for (j = 1; j<10; j++) {
				a->move[i][j-1] = a->move[i][j];
			}
		}
		for (j = 0; j<22; j++) {
			a->move[j][9] = 0;
		}
	}
}

void touche_gauche(Board* a) {
	int i, j;
	int stop = 0;
	for (i = 0; i<22; i++) {
		if(a->move[i][9]!=0){stop++;}
		for (j = 8; j>=0; j--)
			if (a->move[i][j] != 0) {
				if (a->tableau[i][j+1] != 0) { stop = stop + 1; }
			}
	}
	if (stop == 0) {
		for (i = 0; i<22; i++) {
			for (j = 8; j>=0; j--) {
				a->move[i][j+1] = a->move[i][j];
			}
		}
		for (j = 0; j<22; j++) {
			a->move[j][0] = 0;
		}
	}
}

void touche_bas(Board *a, Mix_Chunk *son_ligne) {
        descente(a, son_ligne);
}

void touche_haut(Board *a) {
	int i=0,j=0;
	int x=0,y=0;
	int val=0;
	int stop=0;
	for(i=0;i<22;i++){
			for(j=0;j<10;j++){
				if(a->move[i][j]>100){
					x=j;
					y=i;
					val=a->move[y][x];
			}
		}
	}
    for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(PIECES[val/100][(((val%100)/10)+1)%4][i][j]!=0){
                if(((i+y-1)<0)||(i+y-1>21)||(j+x-2>9)||(j+x-2<0)){
                    stop++;

                }else{
                    if(a->tableau[y+i-1][j+x-2]!=0){
                    stop++;
                    }

                }
            }
		}
	}

	if(stop==0){
        for(i=0;i<22;i++){
            for(j=0;j<10;j++){
                a->move[i][j]=0;
            }
        }
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                a->move[i+y-1][j+x-2]=PIECES[val/100][(((val%100)/10)+1)%4][i][j];
            }
        }
    }
}

void afficher(Board *a, SDL_Surface* cyan,SDL_Surface* violet, SDL_Surface* orange, SDL_Surface* bleu, SDL_Surface* rouge, SDL_Surface* vert, SDL_Surface* jaune, SDL_Surface* ecran, SDL_Rect positionPiece){
	int i,j;
	for(i=0;i<22;i++){
			for(j=0;j<10;j++){
				//Cyan
				if(a->tableau[i][j]%10==1){
					display(i,j,cyan,ecran,positionPiece);
				}
				if(a->move[i][j]%10==1){
					display(i,j, cyan,ecran, positionPiece);
				}
				//Violet
				if(a->tableau[i][j]%10==2){
					display(i,j,violet,ecran,positionPiece);
				}
				if(a->move[i][j]%10==2){
					display(i,j, violet,ecran, positionPiece);
				}
				//Orange
				if(a->tableau[i][j]%10==3){
					display(i,j,orange,ecran,positionPiece);
				}
				if(a->move[i][j]%10==3){
					display(i,j, orange,ecran, positionPiece);
				}
				//bleu
				if(a->tableau[i][j]%10==4){
					display(i,j,bleu,ecran,positionPiece);
				}
				if(a->move[i][j]%10==4){
					display(i,j, bleu,ecran, positionPiece);
				}
				//Rouge
				if(a->tableau[i][j]%10==5){
					display(i,j,rouge,ecran,positionPiece);
				}
				if(a->move[i][j]%10==5){
					display(i,j, rouge,ecran, positionPiece);
				}
				//vert
				if(a->tableau[i][j]%10==6){
					display(i,j,vert,ecran,positionPiece);
				}
				if(a->move[i][j]%10==6){
					display(i,j, vert,ecran, positionPiece);
				}
				//jaune
				if(a->tableau[i][j]%10==7){
					display(i,j,jaune,ecran,positionPiece);
				}
				if(a->move[i][j]%10==7){
					display(i,j, jaune,ecran, positionPiece);

				}
			}
		}
}

void display(int i, int j, SDL_Surface* piece, SDL_Surface* ecran, SDL_Rect positionPiece){
    positionPiece.x=279-31*j;
	positionPiece.y=690-31*i;
	SDL_BlitSurface(piece, NULL, ecran, &positionPiece);
}

void echange_piece(Board* a){
    if(a->de_cote == 0){
        int x, y, i=0, j=0, val;
        for(i=0;i<22;i++){
            for(j=0;j<10;j++){
                if(a->move[i][j]>100){
                    x=j;
                    y=i;
                    val=(a->move[y][x])/100;
                }
            }
        }
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                a->move[i+y-1][j+x-2]=0;
            }
        }
        if(a->piece_de_cote==0){
            a->next = a->suivante;
            a->choix[a->next-1] = 0;
            random(a);
        }else{
            a->next = a->piece_de_cote;
        }
        a->piece_de_cote = val;
        spawn(a);
        a->de_cote = 1;
    }
}

void ombre(Board* a, SDL_Surface* gris,SDL_Surface* ecran, SDL_Rect positionPiece){
    int x, y, i=0, j=0, val, stop = 30;
    for(i=0;i<22;i++){
        for(j=0;j<10;j++){
            if(a->move[i][j]!=0){
                val = 1;
                while((a->tableau[i-val][j]==0)&&(val!=i+1)&&(i!=0)){
                    val++;
                }
                if(stop>val){
                    stop = val;
                }
            }
        }
    }
    for(i=0;i<22;i++){
        for(j=0;j<10;j++){
            if(a->move[i][j]!=0){
                display(i-stop+1, j, gris, ecran, positionPiece);
            }
        }
    }
}

void afficher_prochaine(Board *a, SDL_Surface* piece_cyan,SDL_Surface* piece_violet, SDL_Surface* piece_orange, SDL_Surface* piece_bleu, SDL_Surface* piece_rouge, SDL_Surface* piece_vert, SDL_Surface* piece_jaune, SDL_Surface* ecran, SDL_Rect position_prochaine){
    //Cyan
    if(a->suivante==1){
        SDL_BlitSurface(piece_cyan, NULL, ecran, &position_prochaine);
    }
    //Violet
    if(a->suivante==2){
        SDL_BlitSurface(piece_violet, NULL, ecran, &position_prochaine);
    }
    //Orange
    if(a->suivante==3){
        SDL_BlitSurface(piece_orange, NULL, ecran, &position_prochaine);
    }
    //bleu
    if(a->suivante==4){
        SDL_BlitSurface(piece_bleu, NULL, ecran, &position_prochaine);
    }
    //Rouge
	if(a->suivante==5){
        SDL_BlitSurface(piece_rouge, NULL, ecran, &position_prochaine);
    }
    //vert
    if(a->suivante==6){
        SDL_BlitSurface(piece_vert, NULL, ecran, &position_prochaine);
    }
    //jaune
    if(a->suivante==7){
        SDL_BlitSurface(piece_jaune, NULL, ecran, &position_prochaine);
    }
}

void afficher_reserve(Board *a, SDL_Surface* piece_cyan,SDL_Surface* piece_violet, SDL_Surface* piece_orange, SDL_Surface* piece_bleu, SDL_Surface* piece_rouge, SDL_Surface* piece_vert, SDL_Surface* piece_jaune, SDL_Surface* ecran, SDL_Rect position_reserve){
    //Cyan
    if(a->piece_de_cote==1){
        SDL_BlitSurface(piece_cyan, NULL, ecran, &position_reserve);
    }
    //Violet
    if(a->piece_de_cote==2){
        SDL_BlitSurface(piece_violet, NULL, ecran, &position_reserve);
    }
    //Orange
    if(a->piece_de_cote==3){
        SDL_BlitSurface(piece_orange, NULL, ecran, &position_reserve);
    }
    //bleu
    if(a->piece_de_cote==4){
        SDL_BlitSurface(piece_bleu, NULL, ecran, &position_reserve);
    }
    //Rouge
	if(a->piece_de_cote==5){
        SDL_BlitSurface(piece_rouge, NULL, ecran, &position_reserve);
    }
    //vert
    if(a->piece_de_cote==6){
        SDL_BlitSurface(piece_vert, NULL, ecran, &position_reserve);
    }
    //jaune
    if(a->piece_de_cote==7){
        SDL_BlitSurface(piece_jaune, NULL, ecran, &position_reserve);
    }
}

void effacer(Board *a){
    int i,j;
    a->score = 0;
    a->next = (rand()%7)+1;
    a->piece_de_cote = 0;
    a->de_cote = 0;
    a->suivante = (rand()%7)+1;

    for(i=0;i<22;i++){
        for(j=0;j<10;j++){
            a->tableau[j][i] = 0;
            a->move[j][i] = 0;
        }
    }
    for(i=0;i<7;i++){
        a->choix[i]=1;
    }
    a->choix[a->next-1] = 0;
    a->choix[a->suivante-1] = 0;
}







