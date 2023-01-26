#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nouveauSeuil, maxVar, somme, sommeB, q1, intensiteMax, sigma;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
  nouveauSeuil = maxVar = somme = sommeB = q1 = 0;
  intensiteMax = 255;

  int histogramme[256];

    for (int elt = 0; elt <= intensiteMax; elt++)
    {
        histogramme[elt] = 0;
    }

    for (int i = 0; i < nTaille; i++)
    {
        histogramme[ImgIn[i]] += 1;
    }

    for (int j = 0; j <= intensiteMax; j++){
      somme += j * histogramme[j];
    } 

    for (int t = 0; t <= intensiteMax; t++){
      q1 += histogramme[t];
      sommeB += t * histogramme[t];
      
      float elt = somme * q1 - sommeB;

      sigma = elt * elt / (q1 * (1 - q1));

      if (sigma > maxVar) {
        nouveauSeuil = t;
        maxVar = sigma;
      } 
    } 

    for (int i = 0; i < nTaille; i++){
      if (ImgIn[i] > nouveauSeuil){
        ImgOut[i] = 255;
      } 
      else{
        ImgOut[i] = 0;
      } 
    } 

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}

