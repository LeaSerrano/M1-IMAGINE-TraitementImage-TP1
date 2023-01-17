#include <stdio.h>
#include "image_ppm.h"
#include <fstream>

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.dat\n"); 
       exit (1) ;
     }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite) ;

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    int tabIdR[256];
    int tabIdG[256];
    int tabIdB[256];

    for (int elt=0; elt < 256; elt++)
    {
        tabIdR[elt] = 0;
        tabIdG[elt] = 0;
        tabIdB[elt] = 0;
    }

    //Dans ce tableau, on va compter l'occurence du rouge, vert et bleu de l'image
    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j+=3)
        {
            tabIdR[ImgIn[i*nW+j]] += 1;
            tabIdG[ImgIn[i*nW+(j+1)]] += 1;
            tabIdB[ImgIn[i*nW+(j+2)]] += 1;
        }
    }

    //On va ensuite mettre toutes les valeurs dans le fichier "histo_C.dat"
    std::ofstream fichier(cNomImgEcrite);

    for (int k = 0; k < 256; k++) 
    {
        fichier << k << " " << tabIdR[k] << " " << tabIdG[k] << " " << tabIdB[k] << "\n";
    }

    fichier.close();

}