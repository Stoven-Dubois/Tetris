#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>

#ifndef _FONCTION_H
#define _FONCTION_H

typedef struct board{
  int score;
  int next;
  int suivante;
  int piece_de_cote;
  int de_cote;
  int tableau[22][10];
  int choix[7];
  int move[22][10];
}Board;
#endif

Board* creer();
void spawn(Board* a);
int defaite(Board* a);
void descente(Board* a, Mix_Chunk* son_ligne);
void random(Board* a);
void check(Board* a, Mix_Chunk *son_ligne);
void continuer(Board* a);
void detruire(Board* a);
void descendre_lignes(Board* a, int ligne);
void pause();
void touche_haut(Board *a);
void touche_gauche(Board *a);
void touche_droite(Board *a);
void touche_bas(Board *a, Mix_Chunk* son_ligne);
void afficher(Board *a, SDL_Surface* cyan,SDL_Surface* violet, SDL_Surface* orange, SDL_Surface* bleu, SDL_Surface* rouge, SDL_Surface* vert, SDL_Surface* jaune, SDL_Surface* ecran, SDL_Rect positionPiece);
void display(int i, int j, SDL_Surface* piece, SDL_Surface* ecran, SDL_Rect positionPiece);
void echange_piece(Board* a);
void ombre(Board* a, SDL_Surface* gris,SDL_Surface* ecran, SDL_Rect positionPiece);
void afficher_prochaine(Board *a, SDL_Surface* piece_cyan,SDL_Surface* piece_violet, SDL_Surface* piece_orange, SDL_Surface* piece_bleu, SDL_Surface* piece_rouge, SDL_Surface* piece_vert, SDL_Surface* piece_jaune, SDL_Surface* ecran, SDL_Rect position_prochaine);
void afficher_reserve(Board *a, SDL_Surface* piece_cyan,SDL_Surface* piece_violet, SDL_Surface* piece_orange, SDL_Surface* piece_bleu, SDL_Surface* piece_rouge, SDL_Surface* piece_vert, SDL_Surface* piece_jaune, SDL_Surface* ecran, SDL_Rect position_reserve);
void effacer(Board *a);
