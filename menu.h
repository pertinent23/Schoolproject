#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "fn_list.h"

void showOptions()
{
	/*
	    * cette procédure va afficher
	    * toutes les options du menu
	    * chaque foi qu'elle sera 
	    * appellée dans le programme
	*/
	printf( "\n\n\t----------------------------------------------------------------------------------------------\n" );
	printf( "\t--------------------------------------------- MENU -------------------------------------------\n" );
	printf( "\t----------------------------------------------------------------------------------------------\n\n" );
	    char options[][ 160 ] = {
	    	"1) Ajouter un etudiant.",
	    	"2) Modifier les informations d'un etudiant.",
	    	"3) Suppriner les informations d'un etudiant.",
	    	"4) Afficher les candidats admis en informatique.",
	    	"5) Suppriner les admis ayant aumoins 20 ans.",
	    	"6) Separer les candidats par filiere.",
	    	"7) Pourcentage de candidats par filiere.",
	    	"8) Afficher les candidats par filiere.",
	    	"9) exit."
	    };
	    int i;
	        for ( i = 0; i < 9; i++ )
	        	printf( "\t\t%s\n", options[ i ] );
	printf( "\n\t------------------------------ Choisir une option \n" );
}

void Menu()
{
	char keycode[ MAX_ARRAY_SIZE ];
	int key = 0;
	    while( key != 9 ){
	    	/*
	    	    * cette fonction vas attendre que
	    	    * l'utilisateur entre un int sur la 
	    	    * console pour executer l'option
	    	    * choisie, dans le cas ou l'option
	    	    * n'existe pas le mene sera tout 
	    	    * simplement réaffichée
	    	*/
	    	showOptions();
	    	    printf( "\t>>>" );
	    	    scanf( "%s", &keycode );
	    	        key = atoi( keycode );
	    	            if ( key == 1 )
	    	            	ajouter();
	    	            else if( key == 2 )
	    	            	modifier();
	    	            else if( key == 3 )
	    	            	supprimer();
	    	            else if ( key == 4 )
	    	            	admis();
	    	            else if ( key == 5 )
	    	            	filter();
	    	            else if ( key == 6 )
	    	            	selection();
	    	            else if ( key == 7 )
	    	            	statistique();
	    	            else if ( key == 8 )
	    	            	afficher_filiere();
	    	            else if ( key == 9 )
	    	            	break;
	    	            else
	    	            	printf( "\t---%s, N'est pas une option.\n", keycode );
	    }
}

#endif // MENU_H_INCLUDED
