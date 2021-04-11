#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define MAX_ARRAY_SIZE 200

/*
   * s1 s2 s3 sont des
   * notes ceuilles pour les
   * selections
*/
const double
    s1 = 12.00,
    s2 = 11.5,
    s3 = 14.5;

/*
   * ici on a les chemins
   * vers chacun des fichiers
*/
char 
    candidat_path[] = "./files/candidat.txt",
    choix_path[] = "./files/choix.txt",
    bacc_path[] = "./files/bacc.txt",
    resultat_path[] = "./files/resultat.txt",
    admis_path[] = "./files/admis.txt",
    filelist_path[] = "./files/filelist.txt",
    doc_path[] = "./files/selection/";

typedef struct Candidat
{
	long ncin;
	char nom[ 40 ];
	char prenom[ 40 ];
	int age;
} Candidat;

typedef struct Bacc
{
	long ncin;
	double moyenne;
	char seriebacc[ 10 ];
	double moyenne_math;
	double moyenne_phy;
} Bacc;

typedef struct Choix
{
	long ncin;
	char choix2[ 10 ];
	char choix3[ 10 ];
} Choix;

typedef struct Resultat
{
	long ncin;
	double moyenne;
	double moyenne_math_phy;
	int decision;
} Resultat;

/*
   * String est une structure intermerdiares
   * pour la manipulation des fichiers
*/
typedef struct String
{
	char content[ MAX_ARRAY_SIZE ][ MAX_ARRAY_SIZE ];
	int length;
} String;

#endif // TYPE_H_INCLUDED