#include <stdio.h>
#include "image_ppm.h"
#include <fstream>

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250], info;
    int nH, nW, nTaille, indice;

    if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.dat info(l ou c) indice \n"); 
       exit (1) ;
     }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite) ;
    sscanf (argv[3],"%s",&info) ;
    sscanf (argv[4],"%i",&indice);
    
    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    std::ofstream fichier(cNomImgEcrite);

    if (info == 'l')
    {
        int tabId[nW];

        for (int j=0; j < nW; j++)
        {
            tabId[j] = ImgIn[indice*nW+j];
            printf("%i %i\n", j, tabId[j]);
            fichier << j << " " << tabId[j] << "\n";
        } 
    }
    else if (info == 'c')
    {
        int tabId[nH];

        for (int i=0; i < nH; i++)
        {
            tabId[i] = ImgIn[i*nW+indice];
            printf("%i %i\n", i, tabId[i]);
            fichier << i << " " << tabId[i] << "\n";
        }
    }
    fichier.close();

}