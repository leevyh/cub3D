#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <SDL.h>

int w; ///Largueur de l'ecran
int h; ///Hauteur de l'ecran
Uint8* inkeys; ///Permet la gestion des frappes sur les touches du clavier
SDL_Event event; ///Permet de gerer les différents evenements de SDL
SDL_Surface* scr; ///La surface simple de SDL utilisée
#define MAPWIDTH 24	/*! def Nombre de colonnes de la carte de jeu */
#define MAPHEIGHT 24 /*! def Nombres de lignes de la carte de jeu */

double posX = 2, posY = 2;  ///x et y position de depart
double dirX = -1, dirY = 0; ///initialisation du verteur directeur
double planeX = 0, planeY = 0.66; ///Raycaster la deuxieme version du plan de camera
 
double time = 0; ///Temps de la sequence courante
double oldTime = 0; ///Temps de l'image precedente
 
screen(512, 384, 0, "Raycaster");/// definition des parametres de l'ecran (512x384  avec le Titre "Raycaster")
 
while(!done()) /// tant que la fonction done() retourne faux, on ne quitte pas le programme
{
  for(int x = 0; x < w; x++)
  {
    /// Calcul de la position et de l'orientation du rayon
    double cameraX = 2 * x / double(w) - 1; /// Coordonnées x dans l'espace de la camera
    double rayPosX = posX;				          /// Coordonnées x de rayon dans l'espace
    double rayPosY = posY;                  /// Coordonnées y de rayon dans l'espace
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;
    /// Position de départ
    int mapX = int(rayPosX);
    int mapY = int(rayPosY);

    /// Longueur des rayons de la position actuelle au prochain x ou y
    double distMurX;                      /// Distance entre le joueur et 1e prochain mur vertical
    double distMurY;                      /// Distance entre le joueur et 1e prochain mur horizontal

    /// Longueur des rayons de la position du x ou y actuel au prochain x ou y
    double dist2MurX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)); /// Distance entre deux murs verticaux
    double dist2MurY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY)); /// Distance entre deux murs horizontaux
    double longueurMur;

    ///Etape du prochain mouvement
    int etapeX; ///si gauche x=-1, si droite x=+1
    int etapeY; ///si avance y=+1 et si recule y=-1

    int touche = 0; ///Y a-t-il un mur de detecter?
    int murVertiOuHori; ///est-ce un mur horizontal ou vertical?

    ///Calcul le sens de la prochaine etape et la distance entre le joueur et le mur vertical le plus proche en fonction de la prochaine etape x
    if (rayDirX < 0) /// Si le rayon est oriente vers la gauche
    {
      etapeX = -1;
      distMurX = (rayPosX - mapX) * dist2MurX; ///  On calcule la distance entre joueur et 1e prochain mur vertical
    }
    else ///Si le rayon est oriente vers la droite
    {
      etapeX = 1;
      distMurX = (mapX + 1.0 - rayPosX) * dist2MurX; /// On calcule la distance entre joueur et 1e prochain mur vertical
    }
    ///Calcul le sens de la prochaine etape et la distance entre le joueur et le mur horizontal le plus proche en fonction de la prochaine etape y
    if (rayDirY < 0)
    {
      etapeY = -1;///  On recule
      distMurY = (rayPosY - mapY) * dist2MurY;///  On calcule la distance entre le joueur et 1e prochain mur horizontal
    }
    else
    {
      etapeY = 1;///  On avance
      distMurY = (mapY + 1.0 - rayPosY) * dist2MurY;/// On calcule la distance entre joueur et 1e prochain mur horizontal
    }
    ///lance de DDA = Digital Differential Analysis (algorithme de detection des murs)
    while (touche == 0)
    {
      ///Saute au prochain carre de la map soit vers la  direction x, soit vers la direction y en fonction du mur le plus proche
      if (distMurX < distMurY)
      {
        distMurX += dist2MurX;
        mapX += etapeX;
        murVertiOuHori = 0; ///Mur vertical
      }
      else
      {
        distMurY += dist2MurY;
        mapY += etapeY;
        murVertiOuHori = 1; ///Mur vertical
      }
      ///Verifier si le rayon a detecte un mur
      if (worldMap[mapX][mapY] > 0) touche = 1;
    }
    ///Calcul de la distance projetee sur la direction de la camera (La distance oblique donnera un effet fisheye !)
    if (murVertiOuHori == 0)
      longueurMur = fabs((mapX - rayPosX + (1 - etapeX) / 2) / rayDirX);
    else
      longueurMur = fabs((mapY - rayPosY + (1 - etapeY) / 2) / rayDirY);

    ///Calculer la hauteur de la ligne appelee a l'ecran
    int hauteurMur = abs(int(h / longueurMur));

    ///Calculer le plus bas et le plus eleve des pixels a remplir dans la bande actuelle
    int drawStart = -hauteurMur / 2 + h / 2;
    if(drawStart < 0)drawStart = 0;
    int drawEnd = hauteurMur / 2 + h / 2;
    if(drawEnd >= h)drawEnd = h - 1;

    /// Definition de la couleur des murs
    Uint8 colorR;
    Uint8 colorG;
    Uint8 colorB;
    switch(worldMap[mapX][mapY])
    {
      case 1:  colorR = 0xFF; colorG = 0x00; colorB = 0x00;  break; ///rouge
      case 2:  colorR = 0x00; colorG = 0xFF; colorB = 0x00;  break; ///vert
      case 3:  colorR = 0x00; colorG = 0x00; colorB = 0xFF;   break; ///bleu
      case 4:  colorR = 0xFF; colorG = 0xFF; colorB = 0xFF;  break; ///blanc
      default: colorR = 0xFF; colorG = 0xFF; colorB = 0x00; break; ///jaune
    }

    ///On applique une couleur differente pour les murs verticaux (sinon on ne "ressent pas" la 3D)
    if (murVertiOuHori == 1)
    {
        colorR /= 2;
        colorB /= 2;
        colorG /= 2;
    }
    ///Dessine les pixels de l'ecran par ligne verticale
    verLine(x, drawStart, drawEnd, colorR, colorG, colorB);
  } ///Fin de la boucle for
  oldTime = time;
  time = getTicks();
  double frameTime = (time - oldTime) / 1000.0; /// temps de rafraichissement de l'ecran en seconde

  redraw();///Actualisation de l'ecran
  cls(); ///On efface l'ecran

  ///Variables des vitesses
  double moveSpeed = frameTime * 5.0;	/// la constante est en squares/second
  double rotSpeed = frameTime * 3.0;	/// la constante est en in radians/second
  inkeys = SDL_GetKeyState(NULL);

  ///Avancer s'il n'y a pas de mur en face
  if ((inkeys[SDLK_UP] != 0))
  {
    if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
  }
  ///Reculer s'il n'y a aucun mur derriere soi
  if ((inkeys[SDLK_DOWN] != 0))
  {
    if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
  }
  ///Effectuer une rotation vers la droite
  if ((inkeys[SDLK_RIGHT] != 0))
  {
    ///la direction ainsi que le plan de la caméra doivent également effectuer une rotation
    double oldDirX = dirX;
    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
  }
  ///effectuer une rotaion vers la gauche
  if ((inkeys[SDLK_LEFT] != 0))
  {
    ///la direction ainsi que le plan de la caméra doivent également effectuer une rotation
    double oldDirX = dirX;
    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
  }
}
