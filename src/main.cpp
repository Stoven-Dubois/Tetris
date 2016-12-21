#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "fonction.h"
#include "shapes.h"
#include <time.h>

int main(int argc, char *argv[])
{
//Déclarations
    SDL_Surface *ecran = NULL, *piece = NULL, *texte_score=NULL, *texte_niveau = NULL, *fond=NULL, *image_ligne = NULL, *ligne = NULL, *texte_fin=NULL, *texte_prochaine = NULL, *texte_reserve=NULL, *transparent = NULL, *texte_credits1, *texte_credits2, *texte_credits3, *texte_credits4, *menu = NULL, *texte_menu1, *texte_menu2, *texte_menu3, *texte_menu4, *texte_commande1,*texte_commande2,*texte_commande3,*texte_commande4, *texte_commande5, *texte_commande6, *texte_commande7, *texte_commande8, *texte_commande9, *texte_option1, *texte_option2,*texte_option3, *texte_option4, *texte_option5, *texte_option6,*texte_option7;
    SDL_Rect positionPiece, position_niveau, position_score, position_fond, position_imageligne, position_ligne, position_fin, position_prochaine, position_texte_prochaine, position_reserve, position_texte_reserve, position_textecredit1, position_textecredit2, position_textecredit3, position_textecredit4, position_menu, position_textemenu1, position_textemenu2, position_textemenu3, position_textemenu4, position_textecommande1, position_textecommande2, position_textecommande3, position_textecommande4, position_textecommande5, position_textecommande6, position_textecommande7, position_textecommande8, position_textecommande9, position_texteoption1, position_texteoption2, position_texteoption3, position_texteoption4, position_texteoption5,position_texteoption6,position_texteoption7;
    SDL_Event event;
    TTF_Font *police = NULL, *police2 = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255}, couleurJaune = {255, 255, 0}, couleurRouge = {255, 0, 0};
    int continuer = 1, continuer2 = 1, compteur =1, action=0,tempsPrecedent = 0, tempsActuel = 0, def = 0, choix = 0, choix_commande = 0, choix_image = 0, choix_musique = 0, choix_niveau = 1;
    char Score[100] = "", Niveau[100] = "", Fin[100] = "", prochaine[100]="", reserve[100]="", credits1[100], credits2[100],credits3[100], credits4[100], menu1[100],menu2[100],menu3[100],menu4[100], commande1[100],commande2[100],commande3[100],commande4[100], commande5[100], commande6[100],commande7[100],commande8[100],commande9[100], option1[100], option2[100], option3[100], option4[100], option5[100], option6[100], option7[100];
    Mix_Music *musique;
    Mix_Chunk *son_ligne = NULL;

// Démarrage de la SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

// Ouverture de la fenêtre
    ecran = SDL_SetVideoMode(480, 720, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Tetris", NULL);

//Initialisation et test pour le son
    SDL_WM_SetCaption("SDL_Mixer", NULL);
    Mix_AllocateChannels(10);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
      printf("%s", Mix_GetError());
    }

//Initialisation des musiques et sons //Chargement de la musique
    son_ligne = Mix_LoadWAV("hit.wav");
    Mix_VolumeChunk(son_ligne, MIX_MAX_VOLUME/10);
    musique = Mix_LoadMUS("musique1.mp3");



// Chargement de Piece
    piece = SDL_LoadBMP("block.bmp");
	SDL_Surface *cyan = SDL_LoadBMP("cyan.bmp");
	SDL_Surface *orange = SDL_LoadBMP("orange.bmp");
	SDL_Surface *violet = SDL_LoadBMP("violet.bmp");
	SDL_Surface *bleu = SDL_LoadBMP("bleu.bmp");
	SDL_Surface *rouge = SDL_LoadBMP("rouge.bmp");
	SDL_Surface *vert= SDL_LoadBMP("vert.bmp");
	SDL_Surface *jaune = SDL_LoadBMP("jaune.bmp");
	SDL_Surface *piece_cyan = IMG_Load("piece_cyan.png");
	SDL_Surface *piece_orange = IMG_Load("piece_orange.png");
	SDL_Surface *piece_violet = IMG_Load("piece_violet.png");
	SDL_Surface *piece_bleu = IMG_Load("piece_bleu.png");
	SDL_Surface *piece_rouge = IMG_Load("piece_rouge.png");
	SDL_Surface *piece_vert= IMG_Load("piece_vert.png");
	SDL_Surface *piece_jaune = IMG_Load("piece_jaune.png");
	SDL_Surface *gris = SDL_LoadBMP("gris.bmp");

// On centre Piece � l'�cran
    positionPiece.x = ecran->w / 2 - piece->w / 2;
    positionPiece.y = ecran->h / 2 - piece->h / 2;

// Initialisation du jeu
    SDL_EnableKeyRepeat(100, 100);
	police = TTF_OpenFont("kremlin.ttf", 20);
	police2 = TTF_OpenFont("buran.ttf", 22);

// Initialisation de l'affichage du fond pour le jeu
    position_fond.x=0;
    position_fond.y=0;
    fond = SDL_LoadBMP("tetrisD.bmp");

// Initialisation de l'affichage du fond pour le jeu
    position_imageligne.x=0;
    position_imageligne.y=0;
    image_ligne = SDL_LoadBMP("lignes.bmp");
    SDL_SetColorKey(image_ligne, SDL_SRCCOLORKEY, SDL_MapRGB(image_ligne->format, 0, 0, 0));

// Initialisation de l'affichage du fond pour le menu
    position_menu.x = 0;
    position_menu.y = 0;
    menu = SDL_LoadBMP("fond.bmp");

// Initialisation de l'affichage du score
    position_score.x = 350;
    position_score.y = 50;

// Initialisation de l'affichage du niveau
    position_niveau.x = 350;
    position_niveau.y = 650;

// Initialisation de l'affichage de l'écran de fin
    position_fin.x = 100;
    position_fin.y = 350;

// Initialisation de l'affichage de la prochaine pièce
    position_texte_prochaine.x = 330;
    position_texte_prochaine.y = 170;
    position_prochaine.x = 350;
    position_prochaine.y = 220;

// Initialisation de l'affichage de la pièce mise en réserve
    position_texte_reserve.x = 340;
    position_texte_reserve.y = 400;
    position_reserve.x = 350;
    position_reserve.y = 450;

// Initialisation de l'affichage du crédit
    position_textecredit1.x = 290;
    position_textecredit1.y = 20;
    position_textecredit2.x = 290;
    position_textecredit2.y = 80;
    position_textecredit3.x = 290;
    position_textecredit3.y = 140;
    position_textecredit4.x = 290;
    position_textecredit4.y = 200;
    sprintf(credits1, "Credits : ");
    sprintf(credits2, "Guenebaud Lucas");
    sprintf(credits3, "Stoven-Dubois Alexis");
    sprintf(credits4, "Retour");
    texte_credits1 = TTF_RenderText_Shaded(police2, credits1, couleurNoire, couleurBlanche);
    texte_credits2 = TTF_RenderText_Shaded(police2, credits2, couleurNoire, couleurBlanche);
    texte_credits3 = TTF_RenderText_Shaded(police2, credits3, couleurNoire, couleurBlanche);
    texte_credits4 = TTF_RenderText_Shaded(police2, credits4, couleurNoire, couleurJaune);

// Initialisation de l'affichage du menu
    position_textemenu1.x = 300;
    position_textemenu1.y = 20;
    position_textemenu2.x = 300;
    position_textemenu2.y = 80;
    position_textemenu3.x = 300;
    position_textemenu3.y = 140;
    position_textemenu4.x = 300;
    position_textemenu4.y = 200;
    sprintf(menu1, "Jouer");
    sprintf(menu2, "Commandes");
    sprintf(menu3, "Options");
    sprintf(menu4, "Credits");

    // Initialisation de l'affichage des commandes
    position_textecommande1.x = 80;
    position_textecommande1.y = 100;
    position_textecommande2.x = 80;
    position_textecommande2.y = 225;
    position_textecommande3.x = 80;
    position_textecommande3.y = 350;
    position_textecommande4.x = 80;
    position_textecommande4.y = 475;
    position_textecommande5.x = 100;
    position_textecommande5.y = 600;
    position_textecommande6.x = 100;
    position_textecommande6.y = 125;
    position_textecommande7.x = 100;
    position_textecommande7.y = 250;
    position_textecommande8.x = 100;
    position_textecommande8.y = 375;
    position_textecommande9.x = 100;
    position_textecommande9.y = 500;
    sprintf(commande1, "Quitter le jeu ou la partie : ");
    sprintf(commande2, "Selectionner un choix : ");
    sprintf(commande3, "Se diriger : ");
    sprintf(commande4, "Mettre ou echanger la piece en reserve : ");
    sprintf(commande5, "Retour");
    sprintf(commande6, "Touche ' echap '");
    sprintf(commande7, "Touche ' entree '");
    sprintf(commande8, "Fleche directionelles");
    sprintf(commande9, "Touche ' h '");
    texte_commande1 = TTF_RenderText_Shaded(police2, commande1, couleurNoire, couleurBlanche);
    texte_commande2 = TTF_RenderText_Shaded(police2, commande2, couleurNoire, couleurBlanche);
    texte_commande3 = TTF_RenderText_Shaded(police2, commande3, couleurNoire, couleurBlanche);
    texte_commande4 = TTF_RenderText_Shaded(police2, commande4, couleurNoire, couleurBlanche);
    texte_commande5 = TTF_RenderText_Shaded(police2, commande5, couleurNoire, couleurJaune);
    texte_commande6 = TTF_RenderText_Shaded(police2, commande6, couleurNoire, couleurBlanche);
    texte_commande7 = TTF_RenderText_Shaded(police2, commande7, couleurNoire, couleurBlanche);
    texte_commande8 = TTF_RenderText_Shaded(police2, commande8, couleurNoire, couleurBlanche);
    texte_commande9 = TTF_RenderText_Shaded(police2, commande9, couleurNoire, couleurBlanche);

// Initialisation de l'affichage des options
    position_texteoption1.x = 80;
    position_texteoption1.y = 100;
    position_texteoption2.x = 100;
    position_texteoption2.y = 125;
    position_texteoption3.x = 80;
    position_texteoption3.y = 250;
    position_texteoption4.x = 100;
    position_texteoption4.y = 275;
    position_texteoption5.x = 80;
    position_texteoption5.y = 400;
    position_texteoption6.x = 100;
    position_texteoption6.y = 425;
    position_texteoption7.x = 80;
    position_texteoption7.y = 600;
    sprintf(option1, "Fond d'ecran : ");
    sprintf(option2, "Espace1");
    sprintf(option3, "Musique : ");
    sprintf(option4, "Tetris");
    sprintf(option5, "Niveau de depart : ");
    sprintf(option6, "    %d    ", compteur);
    sprintf(option7, "Retour");
    texte_option1 = TTF_RenderText_Shaded(police2, option1, couleurNoire, couleurJaune);
    texte_option2 = TTF_RenderText_Shaded(police2, option2, couleurNoire, couleurBlanche);
    texte_option3 = TTF_RenderText_Shaded(police2, option3, couleurNoire, couleurBlanche);
    texte_option4 = TTF_RenderText_Shaded(police2, option4, couleurNoire, couleurBlanche);
    texte_option5 = TTF_RenderText_Shaded(police2, option5, couleurNoire, couleurBlanche);
    texte_option6 = TTF_RenderText_Shaded(police2, option6, couleurNoire, couleurBlanche);
    texte_option7 = TTF_RenderText_Shaded(police2, option7, couleurNoire, couleurBlanche);

// Initialisation de la pré-visualisation
    transparent = SDL_LoadBMP("transparent.bmp");
    SDL_SetAlpha(transparent, SDL_SRCALPHA, 64);


while(continuer){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
            case SDLK_RETURN:
               if(choix == 0){ /* Cas de la touche jouer : afficher le jeu et gérer les touches avec lesquelles le joueur joue.*/
                    Board* a = creer();
                    spawn(a);
                    Mix_PlayMusic(musique, -1);
                while (continuer2){
                //Calcul du niveau
                    if((10*compteur<=(a->score))&&(a->score <161)){
                        compteur=compteur+1;
                    }

                    //Temporisation entre chaque descente de la pièce
                    tempsActuel = SDL_GetTicks();
                    if (tempsActuel - tempsPrecedent > 1000-(75*compteur)){
                        descente(a, son_ligne);
                        tempsPrecedent = tempsActuel;
                    }

                    // Gestion des touches sur lesquelles appuie le joueur
                    while(SDL_PollEvent(&event)){
                        switch(event.type){
                            case SDL_QUIT:
                            continuer2 = 0;
                            break;
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym){
                                case SDLK_UP: // Fl�che haut
                                    touche_haut(a);
                                    break;
                                case SDLK_DOWN: // Fl�che bas
                                    touche_bas(a, son_ligne);
                                    break;
                                case SDLK_LEFT: // Fl�che gauche
                                    touche_gauche(a);
                                    break;
                                case SDLK_RIGHT: // Fl�che gauche
                                    touche_droite(a);
                                    break;
                                case SDLK_ESCAPE: //Quitter avec escape
                                    continuer2=0;
                                    effacer(a);
                                    compteur = choix_niveau;
                                    break;
                                case SDLK_h:
                                    echange_piece(a);
                                    break;
                                default:
                                    continuer2=1;
                                    continuer = 1;
                            }
                            break;
                        }
                    }
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
                    SDL_BlitSurface(fond, NULL, ecran, &position_fond);
                    SDL_BlitSurface(image_ligne, NULL, ecran, &position_imageligne);

                    //Affichage du jeu
                    ombre(a, transparent, ecran, positionPiece);
                    afficher(a,cyan,violet, orange, bleu, rouge, vert, jaune,ecran,positionPiece);

                    //Affichage de la prochaine pièce
                    SDL_FreeSurface(texte_prochaine);
                    sprintf(prochaine, "Prochaine : ");
                    texte_prochaine = TTF_RenderText_Shaded(police, prochaine, couleurNoire, couleurBlanche);
                    SDL_BlitSurface(texte_prochaine, NULL, ecran, &position_texte_prochaine);
                    afficher_prochaine(a, piece_cyan, piece_violet, piece_orange, piece_bleu, piece_rouge, piece_vert, piece_jaune, ecran,  position_prochaine);

                    //Affichage de la pièce mise en réserve
                    SDL_FreeSurface(texte_reserve);
                    sprintf(reserve, "Réserve : ");
                    texte_reserve = TTF_RenderText_Shaded(police, reserve, couleurNoire, couleurBlanche);
                    SDL_BlitSurface(texte_reserve, NULL, ecran, &position_texte_reserve);
                    afficher_reserve(a, piece_cyan, piece_violet, piece_orange, piece_bleu, piece_rouge, piece_vert, piece_jaune, ecran,  position_reserve);

                    //Affichage du nouveau score
                    SDL_FreeSurface(texte_score);
                    sprintf(Score, "Score: %d", a->score);
                    texte_score = TTF_RenderText_Shaded(police, Score, couleurNoire, couleurBlanche);
                    SDL_BlitSurface(texte_score, NULL, ecran, &position_score);

                    // Affichage du nouveau niveau
                    SDL_FreeSurface(texte_niveau);
                    sprintf(Niveau, "Niveau: %d", compteur);
                    texte_niveau = TTF_RenderText_Shaded(police, Niveau, couleurNoire, couleurBlanche);
                    SDL_BlitSurface(texte_niveau, NULL, ecran, &position_niveau);

                    // Affichage du texte de fin de partie et changement de musique
                    if(defaite(a)!=0){
                    SDL_FreeSurface(texte_fin);
                    sprintf(Fin, "Perdu!\nScore final :  %d", a->score);
                    texte_fin = TTF_RenderText_Shaded(police, Fin, couleurNoire, couleurBlanche);
                    SDL_BlitSurface(texte_fin, NULL, ecran, &position_fin);
                    }
                    SDL_Flip(ecran);

                }
                Mix_HaltMusic();
                continuer2 = 1;
                }
                if(choix == 1){ /* Cas où le joueur veut voir les commandes */
                    while(continuer2){
                        while(SDL_PollEvent(&event)){
                            switch(event.type){
                                case SDL_QUIT:
                                continuer2 = 0;
                                break;
                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym){
                                    case SDLK_ESCAPE: //Quitter avec escape
                                        continuer2=0;
                                        break;
                                    case SDLK_RETURN:
                                        continuer2=0;
                                        choix = 0;
                                        break;
                                    default:
                                        continuer2=1;
                            }
                            break;
                        }
                    }
                                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
                                        SDL_BlitSurface(menu, NULL, ecran, &position_menu);
                                        SDL_BlitSurface(texte_commande1, NULL, ecran, &position_textecommande1);
                                        SDL_BlitSurface(texte_commande2, NULL, ecran, &position_textecommande2);
                                        SDL_BlitSurface(texte_commande3, NULL, ecran, &position_textecommande3);
                                        SDL_BlitSurface(texte_commande4, NULL, ecran, &position_textecommande4);
                                        SDL_BlitSurface(texte_commande5, NULL, ecran, &position_textecommande5);
                                        SDL_BlitSurface(texte_commande6, NULL, ecran, &position_textecommande6);
                                        SDL_BlitSurface(texte_commande7, NULL, ecran, &position_textecommande7);
                                        SDL_BlitSurface(texte_commande8, NULL, ecran, &position_textecommande8);
                                        SDL_BlitSurface(texte_commande9, NULL, ecran, &position_textecommande9);
                                        SDL_Flip(ecran);
                    }
                                        continuer2 = 1;
                }
                if(choix == 2){ /*Cas où le joueur veut changer les options : on utilise simplement des 'switch' pour changer les variables d'image de fond, de musique, et de niveau de départ */
                    while(continuer2){
                        while(SDL_PollEvent(&event)){
                            switch(event.type){
                                case SDL_QUIT:
                                continuer2 = 0;
                                break;
                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym){
                                    case SDLK_ESCAPE: //Quitter avec escape
                                        continuer2=0;
                                        break;
                                    case SDLK_RETURN:
                                        if(choix_commande == 0){
                                            choix_image++;
                                            if(choix_image == 5){
                                                choix_image = 0;}
                                            switch(choix_image){
                                                case 0 :
                                                    fond = SDL_LoadBMP("tetrisD.bmp");
                                                    sprintf(option2, "Espace1");
                                                    break;
                                                case 1 :
                                                    fond = SDL_LoadBMP("tetrisC.bmp");
                                                    sprintf(option2, "Espace2");
                                                    break;
                                                case 2 :
                                                    fond = SDL_LoadBMP("tetrisB.bmp");
                                                    sprintf(option2, "Humanoide");
                                                    break;
                                                case 3 :
                                                    fond = SDL_LoadBMP("tetrisA.bmp");
                                                    sprintf(option2, "Ville");
                                                    break;
                                                case 4:
                                                    fond = SDL_LoadBMP("tetrisE.bmp");
                                                    sprintf(option2, "Anime");
                                                    break;
                                            }
                                        }
                                        if(choix_commande == 1){
                                            choix_musique++;
                                            if(choix_musique == 4){
                                                choix_musique = 0;
                                            }
                                            switch(choix_musique){
                                                case 0 :
                                                    musique = Mix_LoadMUS("musique1.mp3");
                                                    sprintf(option4, "Tetris");
                                                    break;
                                                case 1 :
                                                    musique = Mix_LoadMUS("musique2.mp3");
                                                    sprintf(option4, "Motherland");
                                                    break;
                                                case 2 :
                                                    musique = Mix_LoadMUS("musique3.mp3");
                                                    sprintf(option4, "Kickass");
                                                    break;
                                                case 3 :
                                                    musique = Mix_LoadMUS("musique4.mp3");
                                                    sprintf(option4, "Katyusha");
                                                    break;
                                            }
                                        }
                                        if(choix_commande == 2){
                                            choix_niveau++;
                                            if(choix_niveau == 11){
                                                choix_niveau = 0;
                                            }
                                            compteur = choix_niveau;
                                            sprintf(option6, "    %d    ", compteur);
                                        }
                                        if(choix_commande == 3){
                                            continuer2=0;
                                            choix = 0;
                                            choix_commande = 0;
                                            break;
                                        }
                                        break;
                                    case SDLK_DOWN :
                                        if(choix_commande<3){
                                            choix_commande++;
                                        }
                                        break;
                                    case SDLK_UP :
                                        if(choix_commande>0){
                                            choix_commande--;
                                        }
                                    break;
                                    default:
                                        continuer2=1;
                            }
                            break;
                        }
                    }
                                        switch(choix_commande){
                                            case 0 :
                                                    texte_option1 = TTF_RenderText_Shaded(police2, option1, couleurNoire, couleurJaune);
                                                    texte_option2 = TTF_RenderText_Shaded(police2, option2, couleurNoire, couleurJaune);
                                                    texte_option3 = TTF_RenderText_Shaded(police2, option3, couleurNoire, couleurBlanche);
                                                    texte_option4 = TTF_RenderText_Shaded(police2, option4, couleurNoire, couleurBlanche);
                                                    texte_option5 = TTF_RenderText_Shaded(police2, option5, couleurNoire, couleurBlanche);
                                                    texte_option6 = TTF_RenderText_Shaded(police2, option6, couleurNoire, couleurBlanche);
                                                    texte_option7 = TTF_RenderText_Shaded(police2, option7, couleurNoire, couleurBlanche);
                                                break;
                                            case 1 :
                                                texte_option1 = TTF_RenderText_Shaded(police2, option1, couleurNoire, couleurBlanche);
                                                texte_option2 = TTF_RenderText_Shaded(police2, option2, couleurNoire, couleurBlanche);
                                                texte_option3 = TTF_RenderText_Shaded(police2, option3, couleurNoire, couleurJaune);
                                                texte_option4 = TTF_RenderText_Shaded(police2, option4, couleurNoire, couleurJaune);
                                                texte_option5 = TTF_RenderText_Shaded(police2, option5, couleurNoire, couleurBlanche);
                                                texte_option6 = TTF_RenderText_Shaded(police2, option6, couleurNoire, couleurBlanche);
                                                texte_option7 = TTF_RenderText_Shaded(police2, option7, couleurNoire, couleurBlanche);
                                                break;
                                            case 2 :
                                                texte_option1 = TTF_RenderText_Shaded(police2, option1, couleurNoire, couleurBlanche);
                                                texte_option2 = TTF_RenderText_Shaded(police2, option2, couleurNoire, couleurBlanche);
                                                texte_option3 = TTF_RenderText_Shaded(police2, option3, couleurNoire, couleurBlanche);
                                                texte_option4 = TTF_RenderText_Shaded(police2, option4, couleurNoire, couleurBlanche);
                                                texte_option5 = TTF_RenderText_Shaded(police2, option5, couleurNoire, couleurJaune);
                                                texte_option6 = TTF_RenderText_Shaded(police2, option6, couleurNoire, couleurJaune);
                                                texte_option7 = TTF_RenderText_Shaded(police2, option7, couleurNoire, couleurBlanche);
                                                break;
                                            case 3 :
                                                texte_option1 = TTF_RenderText_Shaded(police2, option1, couleurNoire, couleurBlanche);
                                                texte_option2 = TTF_RenderText_Shaded(police2, option2, couleurNoire, couleurBlanche);
                                                texte_option3 = TTF_RenderText_Shaded(police2, option3, couleurNoire, couleurBlanche);
                                                texte_option4 = TTF_RenderText_Shaded(police2, option4, couleurNoire, couleurBlanche);
                                                texte_option5 = TTF_RenderText_Shaded(police2, option5, couleurNoire, couleurBlanche);
                                                texte_option6 = TTF_RenderText_Shaded(police2, option6, couleurNoire, couleurBlanche);
                                                texte_option7 = TTF_RenderText_Shaded(police2, option7, couleurNoire, couleurJaune);
                                                break;
                                            }
                                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
                                        SDL_BlitSurface(menu, NULL, ecran, &position_menu);
                                        SDL_BlitSurface(texte_option1, NULL, ecran, &position_texteoption1);
                                        SDL_BlitSurface(texte_option2, NULL, ecran, &position_texteoption2);
                                        SDL_BlitSurface(texte_option3, NULL, ecran, &position_texteoption3);
                                        SDL_BlitSurface(texte_option4, NULL, ecran, &position_texteoption4);
                                        SDL_BlitSurface(texte_option5, NULL, ecran, &position_texteoption5);
                                        SDL_BlitSurface(texte_option6, NULL, ecran, &position_texteoption6);
                                        SDL_BlitSurface(texte_option7, NULL, ecran, &position_texteoption7);
                                        SDL_Flip(ecran);
                    }

                                        continuer2 = 1;

                }
                if(choix == 3){/* Affichage des crédits */
                    while(continuer2){
                        while(SDL_PollEvent(&event)){
                            switch(event.type){
                                case SDL_QUIT:
                                continuer2 = 0;
                                break;
                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym){
                                    case SDLK_ESCAPE: //Quitter avec escape
                                        continuer2=0;
                                        break;
                                    case SDLK_RETURN:
                                        continuer2=0;
                                        choix = 0;
                                        break;
                                    default:
                                        continuer2=1;
                            }
                            break;
                        }
                    }
                                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
                                        SDL_BlitSurface(menu, NULL, ecran, &position_menu);
                                        SDL_BlitSurface(texte_credits1, NULL, ecran, &position_textecredit1);
                                        SDL_BlitSurface(texte_credits2, NULL, ecran, &position_textecredit2);
                                        SDL_BlitSurface(texte_credits3, NULL, ecran, &position_textecredit3);
                                        SDL_BlitSurface(texte_credits4, NULL, ecran, &position_textecredit4);
                                        SDL_Flip(ecran);
                    }
                                        /*SDL_FreeSurface(texte_credits1);
                                        SDL_FreeSurface(texte_credits2);
                                        SDL_FreeSurface(texte_credits3);*/
                                        continuer2 = 1;
                }
                break;
            case SDLK_DOWN :
                if(choix<3){
                    choix++;
                }
                break;
            case SDLK_UP :
                if(choix>0){
                    choix--;
                }
                break;
            case SDLK_ESCAPE: //Quitter avec escape
                continuer2=0;
                continuer=0;
                break;
            default:
                continuer=1;
            }
        break;
        }
    }
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
    SDL_BlitSurface(menu, NULL, ecran, &position_menu);
    switch(choix){
        case 0 :
            texte_menu1 = TTF_RenderText_Shaded(police, menu1, couleurNoire, couleurJaune);
            texte_menu2 = TTF_RenderText_Shaded(police, menu2, couleurNoire, couleurBlanche);
            texte_menu3 = TTF_RenderText_Shaded(police, menu3, couleurNoire, couleurBlanche);
            texte_menu4 = TTF_RenderText_Shaded(police, menu4, couleurNoire, couleurBlanche);
            break;
        case 1 :
            texte_menu1 = TTF_RenderText_Shaded(police, menu1, couleurNoire, couleurBlanche);
            texte_menu2 = TTF_RenderText_Shaded(police, menu2, couleurNoire, couleurJaune);
            texte_menu3 = TTF_RenderText_Shaded(police, menu3, couleurNoire, couleurBlanche);
            texte_menu4 = TTF_RenderText_Shaded(police, menu4, couleurNoire, couleurBlanche);
            break;
        case 2 :
            texte_menu1 = TTF_RenderText_Shaded(police, menu1, couleurNoire, couleurBlanche);
            texte_menu2 = TTF_RenderText_Shaded(police, menu2, couleurNoire, couleurBlanche);
            texte_menu3 = TTF_RenderText_Shaded(police, menu3, couleurNoire, couleurJaune);
            texte_menu4 = TTF_RenderText_Shaded(police, menu4, couleurNoire, couleurBlanche);
            break;
        case 3 :
            texte_menu1 = TTF_RenderText_Shaded(police, menu1, couleurNoire, couleurBlanche);
            texte_menu2 = TTF_RenderText_Shaded(police, menu2, couleurNoire, couleurBlanche);
            texte_menu3 = TTF_RenderText_Shaded(police, menu3, couleurNoire, couleurBlanche);
            texte_menu4 = TTF_RenderText_Shaded(police, menu4, couleurNoire, couleurJaune);
            break;
    }
    SDL_BlitSurface(texte_menu1, NULL, ecran, &position_textemenu1);
    SDL_BlitSurface(texte_menu2, NULL, ecran, &position_textemenu2);
    SDL_BlitSurface(texte_menu3, NULL, ecran, &position_textemenu3);
    SDL_BlitSurface(texte_menu4, NULL, ecran, &position_textemenu4);
    SDL_Flip(ecran);
}


        /* Blit du texte */
        /*SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(piece, NULL, ecran, &positionPiece);
        SDL_Flip(ecran);*/

    TTF_CloseFont(police);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_FreeMusic(musique);

    SDL_FreeSurface(ecran);
    SDL_FreeSurface(piece);
    SDL_FreeSurface(ligne);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(texte_score);
    SDL_FreeSurface(texte_niveau);
    SDL_FreeSurface(texte_commande1);
    SDL_FreeSurface(texte_commande2);
    SDL_FreeSurface(texte_commande3);
    SDL_FreeSurface(texte_commande4);
    SDL_FreeSurface(texte_commande6);
    SDL_FreeSurface(texte_commande7);
    SDL_FreeSurface(texte_commande8);
    SDL_FreeSurface(texte_commande9);
    SDL_FreeSurface(texte_credits1);
    SDL_FreeSurface(texte_credits2);
    SDL_FreeSurface(texte_credits3);
    SDL_FreeSurface(texte_credits4);
    SDL_FreeSurface(texte_fin);
    SDL_FreeSurface(texte_menu1);
    SDL_FreeSurface(texte_menu2);
    SDL_FreeSurface(texte_menu3);
    SDL_FreeSurface(texte_menu4);
    SDL_FreeSurface(texte_niveau);
    SDL_FreeSurface(texte_option1);
    SDL_FreeSurface(texte_option2);
    SDL_FreeSurface(texte_option3);
    SDL_FreeSurface(texte_option4);
    SDL_FreeSurface(texte_option5);
    SDL_FreeSurface(texte_option6);
    SDL_FreeSurface(texte_option7);
    SDL_FreeSurface(texte_prochaine);
    SDL_FreeSurface(texte_reserve);
    SDL_FreeSurface(texte_score);
    SDL_FreeSurface(transparent);
    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}











