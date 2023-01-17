#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S_R, S_G, S_B;
  
  if (argc != 6) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm SeuilRouge SeuilVert SeuilBleu \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&S_R);
   sscanf (argv[4],"%d",&S_G);
   sscanf (argv[5],"%d",&S_B);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille*3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille*3);
   
   for (int i=0; i < nH*3; i++){ 
        for (int j=0; j < nW; j++)
        {
            if (ImgIn[i*nW+j] < S_R) {
                ImgOut[i*nW+j]=0;
            } 
            else {
                ImgOut[i*nW+j]=255;
            }
            if (ImgIn[i*nW+(j+1)] < S_G) {
                ImgOut[i*nW+(j+1)]=0;
            } 
            else {
                ImgOut[i*nW+(j+1)]=255;
            } 
            if (ImgIn[i*nW+(j+2)] < S_B) {
                ImgOut[i*nW+(j+2)]=0; 
            } 
            else {
                ImgOut[i*nW+(j+2)]=255;
            } 
        }
   } 

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
