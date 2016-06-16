#ifndef ARMRULELIB1_H
#define ARMRULELIB1_H
#include <sstream>
#include <math.h>
#include <string>
#include <cstdio>


#define L1 7.3
#define L2 14.8
#define L3 18.5
#define L4 8.7

extern "C"{
    #include "ufrn_al5d.h"
}

using namespace std;
int serial_retorno;

void init()
{
    ufrn_header();
    serial_retorno = abrir_porta();
    if (configurar_porta(serial_retorno) == -1){
	   printf("Erro na abertura da porta\n");
       close(serial_retorno);
    }
}


int calcular_posicao_base(float teta)
{
    int pos = 0.00623456790123454 * pow(teta, 2) - 9.95 * teta + 1345; 
    return trava(0, pos);
}

int calcular_posicao_ombro(float teta)
{
    int pos = 0.00444444444444433 * pow(teta, 2) + 8.35555555555557 * teta + 649; 
    return pos;//trava(1, pos);
}

int calcular_posicao_cotovelo(float teta)
{
    int pos = 0.0149794238683127 * pow(teta, 2) - 7.65185185185186 * teta + 803; 
    return pos;//trava(2, pos);
}

int calcular_posicao_punho(float teta)
{
    int pos = -0.00277777777777781 * pow(teta, 2) + 10.1500000000000 * teta + 1503; 
    return trava(3, pos);
}

double degreesToRadians(double graus){
    return (graus * M_PI)/180.0;
}

double radiansToDegrees(double rad){
    return ((rad * 180.0)/M_PI);
}

void calcularCinematicaInversa(double posX, double posY, double posZ, double orientacao){

    orientacao = degreesToRadians(orientacao);
    double lTotalXY = sqrt(pow(posY,2) + pow(posX,2));
    double sinThetaBase = posY/lTotalXY;
    double cosThetaBase = posX/lTotalXY;
    double thetaBase = atan2(sinThetaBase, cosThetaBase);

    double x4 =  (cos(orientacao))*L4;
    double z4 =  (sin(orientacao))*L4;

    double x41 = lTotalXY - x4;
    double z41 = posZ - L1 - z4;

    double cosThetaCotovelo = (pow(x41, 2) + pow(z41, 2) - pow(L2, 2) - pow(L3,2))/(2*L2*L3);
    double sinThetaCotovelo = (-1)*sqrt(1 - pow(cosThetaCotovelo,2));

    double thetaCotovelo = atan2(sinThetaCotovelo, cosThetaCotovelo);

    double lXZ41 = sqrt(pow(x41, 2)+ pow(z41,2));

    double sinAlpha = (posZ - L1 - z4)/lXZ41;
    double cosAlpha = (lTotalXY - x4)/lXZ41;

    double sinBeta = (L3*sin(thetaCotovelo))/lXZ41;
    double cosBeta = (L2 + L3*cos(thetaCotovelo))/lXZ41;

    double alpha = atan2(sinAlpha, cosAlpha);
    double beta = atan2(sinBeta, cosBeta);

    double thetaOmbro = alpha - beta;


    double thetaPunho = orientacao - thetaOmbro - thetaCotovelo;

    ostringstream pBase, pOmbro, pCotovelo, pPunho;
    pBase << calcular_posicao_base(radiansToDegrees(thetaBase));
    pOmbro << calcular_posicao_ombro(radiansToDegrees(thetaOmbro));
    pCotovelo << calcular_posicao_cotovelo(radiansToDegrees(thetaCotovelo));
    pPunho << calcular_posicao_punho(radiansToDegrees(thetaPunho));
    //converter
    string posBase = pBase.str();
    string posOmbro = pOmbro.str();
    string posCotovelo = pCotovelo.str();
    string posPunho = pPunho.str();

    string comando = "#0P"+posBase+"S100#1P"+posOmbro+"S100#2P"+posCotovelo+"S100#3P"+posPunho+"S100";
    // printf("%s\n", strdup(comando.c_str()));
    // printf("%d\n",serial_retorno);
    enviar_comando(strdup(comando.c_str()), serial_retorno);
}

    void pegar(){
        enviar_comando("#4P2000S100T5000", serial_retorno); 
    }
    void soltar(){
        enviar_comando("#4P1500S100T5000", serial_retorno); 
    }
    void mover(double x, double y, double z, double phi){

        calcularCinematicaInversa(x, y, z, phi);
    }
    void repouso(){
        enviar_comando("#0P0000S500#1P0000S500#2P0000S500#3P0000S500#4P0000S500", serial_retorno); 
    }
#endif
