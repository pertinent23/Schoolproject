#ifndef FN_LIST_H_INCLUDED
#define FN_LIST_H_INCLUDED

#include "type.h"
#include "tools.h"

void ajouter()
{
	/*
	   * cette fonction va dans un premier
	   * temps prendre toutes les informations
	   * relative à un etudiant puis les mettres 
	   * dans les structures appropriées et les
	   * stocker dans les fichier corresdant
	*/
	Candidat ca;
	Bacc ba;
	Choix ch;
	    get_user_data( &ca, &ba, &ch ); // ici on prend toutes les données
	    save_candidat( ca ); // on souvegarde les données de la structure candidat
	    save_bacc( ba ); // on sauvegarde les données de la structure bacc
	    save_choix( ch ); // // ici ceux des la structure choix
	resultat( ca, ba, 0 ); // on ajoute les informations relatives au fichier resultat
}

void modifier()
{
	/*
	   * cette fonction va d'abord prendre le numero de
	   * CNI de l'etudiant et appeler la fonction
	   * update, si le numero est dans la base de donnée
	   * ( correspond à un candidat ) la fonction
	   * va renvoyer 1 sinon elle va renvoyer 0
	*/
	long ncin;
	    printf( "\n\t---Entrer votre numero de CNI: \n\t>>>" );
	    scanf( "%ld", &ncin );
	        if ( !update( ncin ) )
	        	printf( "\t--Aucun Candidat ne correspond.\n" );

}

void supprimer()
{
	/*
	   * cette fonction va d'abord prendre le numero de
	   * CNI de l'etudiant et appeler la fonction
	   * deletes, si correspond à un candidat la fonction
	   * va renvoyer 1 sinon elle va renvoyer 0
	*/
	long ncin;
	    printf( "\n\t---Entrer votre numero de CNI: \n\t>>>" );
	    scanf( "%ld", &ncin );
	        if ( !deletes( ncin ) )
	        	printf( "\t--Aucun Candidat ne correspond.\n" );

}

void admis()
{
	/*
	   * cette fonction va prendre dans le fichier
	   * resultat.txt tous les candidats dont le
	   * champ decision == 1 puis appeler la fonction
	   * show_candidat pour afficher chaque candidat
	*/
	Candidat *ca;
	printf( "\t------------------------------ Liste des Admis en Informatique -----------------------------------------\n\n" );
	int length, i;
	    ca = get_admis(); // retourne une liste de candidat selectionné sous forme d'array
	    length = num_of_item;
	        for ( i = 0; i < length; i++ )
	        	show_candidat( ca[ i ] ); // affiche un candidat
	free( ca );
}

void filter()
{
	/*
	   * cette fonction vas enlever dans la liste des
	   * candidat admis en informatique ceux qui sont 
	   * agé d'aumoins 20 ans
	*/
	Candidat *ca;
	Bacc *ba;
	int length, i;
	    ca = get_candidat(); // renvoie une liste de structures candidat
	    ba = get_bacc(); // renvoi une liste de structures bacc
	    length = num_of_item;
	        empty( resultat_path ); // ici on vide resultat.txt
	        empty( admis_path ); // ici on vide admis.txt
	            for( i = 0; i < length; i++ )
	            	resultat( ca[ i ], ba[ i ], 1 );
	        printf( "\t------------------------------ Admis de plus de 20ans supprimer -----------------------------------------\n\n" );
	    admis();
	free( ca );
	free( ba );
}

void selection()
{
	/*
	   * cette fonction va utiliser le fichier
	   * resultat.txt, candidat.txt et choix.txt
	   * pour classer les étudiants par
	   * filières
	*/
	printf( "\t------------------------------- Edudiant maintenant classes par filiere --------------------------------------\n\n" );
	Resultat *rs;
	Candidat *ca;
	Choix *ch;
	int length, i;
	    rs = get_resultat();
	    ca = get_candidat();
	    ch = get_choix();
	    length = num_of_item;
	        for ( i = 0; i < length; ++i )
	        	ajouter_dans_ca_filiere( ca[ i ], ch[ i ], rs[ i ] );
	    empty( filelist_path );
	    /*
	       * ici on enrgistre la liste des filieres
	       * dans un fichier
	    */
	        sprintf( liste_des_filiers, "%s\n", liste_des_filiers );
	    save( filelist_path, liste_des_filiers );
	sprintf( liste_des_filiers, "%s", "" );
	free( rs );
	free( ca );
	free( ch );
}

void afficher_filiere()
{
	/*
	    * cette fonction va d'abord classer les 
	    * etudiants par filieres puis afficher
	    * chaque liste d'etudiant
	*/
	selection();
    String list = split( get_file_datas( filelist_path ).content[ 0 ], '|' );
    char 
        filiere[ MAX_ARRAY_SIZE ], 
        path[ MAX_ARRAY_SIZE ], 
        header[ MAX_ARRAY_SIZE ];
    Candidat *ca;
	int i, j ;
	    for ( i = 0; i < list.length; i++ )
	    {
	    	sprintf( filiere, "%s", list.content[ i ] );
	    	sprintf( path, "%s%s.txt", doc_path, filiere );
	    	sprintf( header, "------------------------------ Filiere: %s -----------------------------------------", filiere );
	    	printf( "\t%s\n\n", header );
	    	    ca = get_candidat_from_file( path );
	    	        for( j = 0; j < num_of_item; j++ )
	    	        	show_candidat( ca[ j ] );
	    	free( ca );
	    }
}

void statistique()
{
	/*
	   * cette fonction pas prendre la
	   * list des etudiants de 
	   * de chaque filière et prendre le nombre
	   * d'etudiant total de l'université
	   * et les calculer les pourcentages 
	   * d'etudiant par filière
	*/
	selection();
	printf( "\n\t------------------------------ Statistique par filiere -----------------------------------------\n\n" );
	String list = split( get_file_datas( filelist_path ).content[ 0 ], '|' );
	char 
	    filiere[ MAX_ARRAY_SIZE ], 
	    path[ MAX_ARRAY_SIZE ], 
	    header[ MAX_ARRAY_SIZE ];
	int i, total;
	Candidat *ca;
	float pourcentage;
	    get_candidat();
	    total = num_of_item;
	        for ( i = 0; i < list.length; i++ )
	        {
	        	sprintf( filiere, "%s", list.content[ i ] );
	        	sprintf( path, "%s%s.txt", doc_path, filiere );
	        	    ca = get_candidat_from_file( path );
	        	    pourcentage = ( num_of_item * 100 ) / total;
	        	        sprintf( header, "----------------------\tFiliere %s: %d%c", filiere, ( int ) pourcentage, '%' );
	        	        printf( "\t%s\n\n", header );
	        	        free( ca );

	        }
}

#endif // FN_LIST_H_INCLUDED
