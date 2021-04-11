#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <string.h>
#include "type.h"

/*
    * ce int vas contenir le nombre d'item
    * d'un fichier à chaque foi q'un fichier
    * sera ouvert, ces items correspondes à
    * des informations par fichier
*/
int num_of_item = 0;
/*
    * cette variable globale sera
    * utiliée pour stocker la liste
    * des filières qui contienent des
    * etudiant chaque foi que la fonction
    * selection sera appellée
*/
char liste_des_filiers[ MAX_ARRAY_SIZE ];

void getString( char *str[], int length )
{
	/*
	   * cette fonction viens resoudre un
	   * probleme precis

	   * quand on utilise la fonction
	   * scanf pour recupperer une chaine
	   * de caractère en occurence si cette
	   * chaine est un nom, ce nom peut contenir
	   * des espaces. Si l'utilisateur entre un
	   * espace alors scanf sera arretée donc nos
	   * données seront corrompues
	   * d'ou la nécessité d'ecrire une
	   * fonction qui puisse lire une chaine
	   * de caracté avec les espaces
	*/
	char x, *content;
        content = malloc( sizeof( char ) * length );
            if ( content == 0 )
            	exit( 0 );
	int i;
	    scanf( "%\nc", &x );
	    for ( i = 0; i < ( length - 1 ); i++ )
	    {
	    	scanf( "%c", &x );
	    	    if( x == '\n' )
	    	    	break;
	    	            content[ i ] = x;
	    }
	        content[ i ] = '\0';
        sprintf( str, "%s", content );
	free( content );
}

void get_user_data( Candidat *ca,  Bacc *ba, Choix *ch )
{
	/*
	   * cette fonction vas juste recupperer
	   * toutes les informations sur un candidat
	   * et les stocker dans les structures Candidat
	   * Bacc, Choix dont leur adress a été passées en
	   * parametre
	*/
	printf( "\n\t---Entrer le numero de CNI:\n\t>>>" );
	    scanf( "%ld", &ca->ncin );
	    ba->ncin = ch->ncin = ca->ncin;

	printf( "\n\t---Entrer votre nom:\n\t>>>" );
	    getString( &ca->nom, 40 );

	printf( "\n\t---Entrer votre prenom:\n\t>>>" );
	    getString( &ca->prenom, 40 );

	printf( "\n\t---Entrer votre age:\n\t>>>" );
	    scanf( "%d", &ca->age );

	printf( "\n\t---Entrer votre Moyenne au bac:\n\t>>>" );
	    scanf( "%lf", &ba->moyenne );

	printf( "\n\t---Entrer votre Serie:\n\t>>>" );
	    getString( &ba->seriebacc, 10 );

	printf( "\n\t---Entrer votre Moyenne en math au bac:\n\t>>>" );
	    scanf( "%lf", &ba->moyenne_math );

	printf( "\n\t---Entrer votre Moyenneen physique au bac:\n\t>>>" );
	    scanf( "%lf", &ba->moyenne_phy );

	printf( "\n\t---Entrer votre choix2:\n\t>>>" );
	    getString( &ch->choix2, 10 );

	printf( "\n\t---Entrer votre choix3:\n\t>>>" );
	    getString( &ch->choix3, 10 );
}

void empty( char file_name[] )
{
	/*
	   * cette fonction prend en
	   * parametre le nom d'un
	   * fichier et va les vider
	*/
	FILE *f = fopen( file_name, "w" );
	        if ( f == NULL )
	        	return;
	                fprintf( f, "" );
	    fclose( f );
}

void save( char file_name[], char content[] )
{
	/*
	    * cette fonction prends en parametre le nom
	    * d'un fichier le comme 2eme parametre
	    * sont contenue et va ouvrir le fichier
	    * en question et lui engistrer le contenu
	*/
	FILE *f = fopen( file_name, "a" );
	        if ( f == NULL )
	        	return;
	                fprintf( f, content );
	fclose( f );
}

/*
   * Ces fonction vont mettre les informations de
   * leurs structure appropier sous forme de chaine
   * de caractères et appeler la fonction save
   * pour les ajouter dans un fichier
*/

void save_candidat( Candidat ca )
{
	char content[ MAX_ARRAY_SIZE ];
	    sprintf( content, "%ld;%s;%s;%d\n", ca.ncin, ca.nom, ca.prenom, ca.age );
	    save( candidat_path, content );
}

void save_bacc( Bacc ba )
{
	char content[ MAX_ARRAY_SIZE ];
	    sprintf( content, "%ld;%f;%s;%f;%f\n", ba.ncin, ba.moyenne, ba.seriebacc, ba.moyenne_math, ba.moyenne_phy );
	    save( bacc_path, content );
}

void save_choix( Choix ch )
{
	char content[ MAX_ARRAY_SIZE ];
	    sprintf( content, "%ld;%s;%s\n", ch.ncin, ch.choix2, ch.choix3 );
	    save( choix_path, content );
}

void save_resultat( Resultat rs )
{
	char content[ MAX_ARRAY_SIZE ];
	    sprintf( content, "%ld;%f;%f;%d\n", rs.ncin, rs.moyenne, rs.moyenne_math_phy, rs.decision );
	    save( resultat_path, content );
}

void save_admis( Candidat ca )
{
	char content[ MAX_ARRAY_SIZE ];
	    sprintf( content, "%ld;%s;%s;%d\n", ca.ncin, ca.nom, ca.prenom, ca.age );
	    save( admis_path, content );
}

void show_candidat( Candidat ca )
{
	/*
	   * cette fonction va tout simplment afficher
	   * sur la console les informations contenue
	   * dans un structure Candidat
	*/
	printf( "\t\tNumero de CNI: %ld,\n\t\tNom: %s,\n\t\tPrenom: %s,\n\t\tAge: %d\n\n", ca.ncin, ca.nom, ca.prenom, ca.age );
}

String get_file_datas( char file_name[] )
{
	/*
	   * cette fonction va ouvrir un fichier
	   * dont le nom est passé en paremetre
	   * et le lire caratère par caractère
	   * retourner un structure String
	   * dont le champ content va contenir
	   * les informations contenues dans le
	   * fichier mais ligne par ligne
	   * et le champs length va contenir le
	   * nombre de ligne
	*/
	char c;
	String str;
	int
	    i = 0,
	    length = 0;
	FILE *fichier;
	      fichier = fopen( file_name, "r" );
	            if ( fichier != NULL ) {
	            	    do{
	                    	c = fgetc( fichier );
	                    	    if ( c == '\n' )
	                    	    {
	                    	    	if ( length == 0 )
	                    	    		break;
	                    	    	        str.content[ i ][ length ] = '\0';
	                    	    	        i++;
	                    	    	        length = 0;
	                    	    }
	                    	    else {
	                    	    	str.content[ i ][ length ] = c;
	                    	    	length++;
	                    	    }
	                    }while( c != EOF );
	                fclose( fichier );
	            }
	        /*
	           * une foi qu'on aura le nombre de
	           * ligne on va le strocker dans la
	           * variable globale num_of_item
	        */
	        num_of_item = i;
	    str.length = i;
	return str;
}

String split( char str[], char separator )
{
	/*
	   * cette fonction prends en parametre une
	   * chaine de caratère et un caractere.
	   * ELle va découper la chaine de caractères
	   * chaque foi qu'elle va trouver ce caratère
	   * dans la chaine et elle
	   * va retourner une Strucuture String dont
	   * le champ content va contenir un la liste
	   * des portions de la chaine sous forme
	   * de tableux et le champ length le nombre
	   * d'élement du tableaux
	*/
	char part;
	int num = 0, length = 0, i;
	String result;
	        for ( i = 0; i < strlen( str ); i++ )
	        {
	        	part = str[ i ];
	        	    if ( part == separator ) {
                        result.content[ num ][ length ] = '\0';
	        	    	num++;
	        	    	length = 0;
	        	    }
	        	    else {
	        	        result.content[ num ][ length ] = part;
	        	        length++;
	        	    }
	        }
	    result.content[ num ][ length ] = '\0';
	    result.length = ++num;
	return result;
}

/*
    * ces fonctions vont ouvrir les fichiers
    * de chaque structures, les analyser et
    * retourner une liste de ces structures
    * sachant que chaque structurs va correspondre
    * aux informations d'une ligne du fichier
*/

Candidat *get_candidat()
{
	String datas = get_file_datas( candidat_path );
	String part;
	Candidat *ca;
	          ca = malloc( sizeof( Candidat ) * datas.length );
	int i;
	    for ( i = 0; i < datas.length; ++i ) {
	    	part = split( datas.content[ i ], ';' );
	    	    sscanf( part.content[ 0 ], "%ld", &ca[ i ].ncin );
	    	    sscanf( part.content[ 1 ], "%s", &ca[ i ].nom );
	    	    sscanf( part.content[ 2 ], "%s", &ca[ i ].prenom );
	    	    sscanf( part.content[ 3 ], "%d", &ca[ i ].age );
	    }
	return ca;
}

Candidat *get_candidat_from_file( char file_name[] )
{
	String datas = get_file_datas( file_name );
	String part;
	Candidat *ca;
	          ca = malloc( sizeof( Candidat ) * datas.length );
	int i;
	    for ( i = 0; i < datas.length; ++i ) {
	    	part = split( datas.content[ i ], ';' );
	    	    sscanf( part.content[ 0 ], "%ld", &ca[ i ].ncin );
	    	    sscanf( part.content[ 1 ], "%s", &ca[ i ].nom );
	    	    sscanf( part.content[ 2 ], "%s", &ca[ i ].prenom );
	    	    sscanf( part.content[ 3 ], "%d", &ca[ i ].age );
	    }
	return ca;
}

Choix *get_choix()
{
	String datas = get_file_datas( choix_path );
	String part;
	Choix *ch;
	        ch = malloc( sizeof( Choix ) * datas.length );
	int i;
	    for ( i = 0; i < datas.length; ++i ) {
	    	part = split( datas.content[ i ], ';' );
	    	    sscanf( part.content[ 0 ], "%ld", &ch[ i ].ncin );
	    	    sscanf( part.content[ 1 ], "%s", &ch[ i ].choix2 );
	    	    sscanf( part.content[ 2 ], "%s", &ch[ i ].choix3 );
	    }
	return ch;
}

Bacc *get_bacc()
{
	String datas = get_file_datas( bacc_path );
	String part;
	Bacc *ba;
	    ba = malloc( sizeof( Bacc ) * datas.length );
	int i;
	    for ( i = 0; i < datas.length; ++i ) {
	    	part = split( datas.content[ i ], ';' );
	    	    sscanf( part.content[ 0 ], "%ld", &ba[ i ].ncin );
	    	    sscanf( part.content[ 1 ], "%lf", &ba[ i ].moyenne );
	    	    sscanf( part.content[ 2 ], "%s", &ba[ i ].seriebacc );
	    	    sscanf( part.content[ 3 ], "%lf", &ba[ i ].moyenne_math );
	    	    sscanf( part.content[ 4 ], "%lf", &ba[ i ].moyenne_phy );
	    }
	return ba;
}

Resultat *get_resultat()
{
	String datas = get_file_datas( resultat_path );
	String part;
	Resultat *rs;
	    rs = malloc( sizeof( Resultat ) * datas.length );
	int i;
	    for ( i = 0; i < datas.length; ++i ) {
	    	part = split( datas.content[ i ], ';' );
	    	    sscanf( part.content[ 0 ], "%ld", &rs[ i ].ncin );
	    	    sscanf( part.content[ 1 ], "%lf", &rs[ i ].moyenne );
	    	    sscanf( part.content[ 2 ], "%lf", &rs[ i ].moyenne_math_phy );
	    	    sscanf( part.content[ 3 ], "%d", &rs[ i ].decision );
	    }
	return rs;
}

Candidat *get_admis()
{
	String datas = get_file_datas( admis_path );
	String part;
	Candidat *ca;
	          ca = malloc( sizeof( Candidat ) * datas.length );
	int i;
	    for ( i = 0; i < datas.length; ++i ) {
	    	part = split( datas.content[ i ], ';' );
	    	    sscanf( part.content[ 0 ], "%ld", &ca[ i ].ncin );
	    	    sscanf( part.content[ 1 ], "%s", &ca[ i ].nom );
	    	    sscanf( part.content[ 2 ], "%s", &ca[ i ].prenom );
	    	    sscanf( part.content[ 3 ], "%d", &ca[ i ].age );
	    }
	return ca;
}

void resultat( Candidat ca, Bacc ba, int context )
{
	/*
	   * cette fonction vas recevoir 02
	   * arguments le premier une structure
	   * candidat et le second une structure
	   * Bacc et enfin un int elle
	   * va devoir rassembler les informations relatives
	   * a une structure résultat
	   * dans le cas ou le int == 1 pour tous les
	   * etudiant dont l'age >= 20 leur decision sera
	   * automatiquement 0
	*/
	Resultat rs;
	    rs.ncin = ca.ncin;
	    rs.moyenne = ba.moyenne;
	    rs.moyenne_math_phy = ( ba.moyenne_math + ba.moyenne_phy ) / 2;
	        if ( rs.moyenne >=  s1 )
	        	rs.decision = 1;
	            else if( ( s2 <= rs.moyenne && s1 >= rs.moyenne ) || rs.moyenne_math_phy >= s3 )
	            	rs.decision = 1;
	                else
	                	rs.decision = 0;

	            if ( context == 1 && ca.age >= 20 )
	            	rs.decision = 0;
	        save_resultat( rs );
	        /*
	           * ici on va sauvegarder dans le
	           * fichier admis.txt les candidats dont
	           * leur decision est == 1
	        */
	if ( rs.decision )
		save_admis( ca );
}

int update( long ncin )
{
	/*
	   * cette fonction va tout d'abord
	   * prendre la list des candidat , des
	   * bacc et des choix
	   * si aucun des candidats n'a un Numero de
	   * CNI egal à celui du parametre alors elle va
	   * retoutner 0 sinon elle vas modifier les
	   * structutes qui contienent les informations
	   * de ceux candidat puis effacer tous les
	   * fichiers et réenregistrer chaque fichier
	*/
	Candidat *ca_list;
	Bacc *ba_list;
	Choix *ch_list;
	int
	    length,
	    i, index;

	    ca_list = get_candidat();
	    ba_list = get_bacc();
	    ch_list = get_choix();
	    length = num_of_item;
	        for ( i = 0; i < length; i++ )
	        {
	        	if ( ca_list[ i ].ncin == ncin )
	        	{
	        		    printf( "\n\t---------------------- Modification des informations de %s %s -----------------------\n\n", ca_list[ i ].prenom, ca_list[ i ].nom );
	        		                        get_user_data( &ca_list[ i ], &ba_list[ i ], &ch_list[ i ] );
	        		                    empty( choix_path );
	        		                empty( bacc_path );
	        		            empty( admis_path );
	        		        empty( candidat_path );
	        		    empty( resultat_path );
	        		    for ( i = 0; i < length; i++ )
	        		    {
	        		    	            save_candidat( ca_list[ i ] );
	        		    	        save_choix( ch_list[ i ] );
	        		    	    save_bacc( ba_list[ i ] );
	        		    	resultat( ca_list[ i ], ba_list[ i ], 0 );
	        		    }
	        		    free( ba_list );
	        		    free( ca_list );
	        		    free( ch_list );
	        		return 1;
	        	}
	        }
	    free( ba_list );
	    free( ca_list );
	    free( ch_list );
	return 0;
}

int deletes( long ncin )
{
	/*
	   * cette fonction va parcourir la
	   * list des candidats et si un des numeros
	   * de CNI correcpond, elle supprime le candidat
	   * et retourne 1
	   * dans le cas ou aucun numero de CNI
	   * ne correpond, elle retourne 0
	*/
	Candidat
	    *ca_list,
	    *new_ca_list;
	Bacc
	    *ba_list,
	    *new_ba_list;
	Choix
	    *ch_list,
	    *new_ch_list;
	int
	    length, new_length = 0,
	    i, index, is_find = 0;

	    ca_list = get_candidat();
	    ba_list = get_bacc();
	    ch_list = get_choix();

        length = num_of_item;

	    new_ch_list = malloc( sizeof( Choix ) * length );
	    new_ba_list = malloc( sizeof( Bacc ) * length );
	    new_ca_list = malloc( sizeof( Candidat ) * length );
	    if ( new_ba_list == NULL || new_ca_list == NULL || new_ch_list == NULL )
	    	return 0;

	        for ( i = 0; i < length; i++ )
	        {
	        	if ( ca_list[ i ].ncin != ncin )
	        	{
	        		new_ca_list[ new_length ] = ca_list[ i ];
	        		new_ba_list[ new_length ] = ba_list[ i ];
	        		new_ch_list[ new_length ] = ch_list[ i ];
	        		new_length++;
	        	}
	        	else {
	        		    printf( "\n\t---------------------- Suppression des informations de %s %s effectuee -----------------------\n\n", ca_list[ i ].prenom, ca_list[ i ].nom );
	        		is_find = 1;
	        	}
	        }

	            if ( !is_find )
	            {
	            	    free( new_ca_list );
	            	    free( new_ch_list );
	            	    free( new_ba_list );
	            	    free( ca_list );
	            	    free( ch_list );
	            	    free( ba_list );
	            	return is_find;
	            }

	        empty( choix_path );
	        empty( bacc_path );
	        empty( candidat_path );
	        empty( resultat_path );
	        empty( admis_path );

	        for ( i = 0; i < new_length; i++ )
	        {
	        	    save_candidat( new_ca_list[ i ] );
	        	    save_choix( new_ch_list[ i ] );
	        	    save_bacc( new_ba_list[ i ] );
	        	resultat( new_ca_list[ i ], new_ba_list[ i ], 0 );
	        }
	    free( new_ca_list );
	    free( new_ch_list );
	    free( new_ba_list );
	    free( ca_list );
	    free( ch_list );
	    free( ba_list );
	return is_find;
}

int ajouter_dans_ca_filiere( Candidat ca, Choix ch, Resultat rs )
{
	/*
	   * cette fonction vas d'abord identifier
	   * le filière du du candidat dans le
	   * cas ou le fichier de sa filiere n'existe pas
	   * il sera créé et le candidat sera ajouté
	   * dans le cas contraire le candidat sera
	   * tout simplement ajouté dans la liste
	   * des etudiants de sa filiere
	*/
	char
	    file_name[ MAX_ARRAY_SIZE ],
	    filier[ MAX_ARRAY_SIZE ],
	    datas[ MAX_ARRAY_SIZE ];
	int i;
	    strcpy( filier, rs.decision == 1 ? "infos" : ch.choix2 );
	        sprintf( file_name, "%s%s.txt", doc_path, filier );
                sprintf( datas, "%ld;%s;%s;%d\n", ca.ncin, ca.nom, ca.prenom, ca.age );
    String list = split( liste_des_filiers, '|' );
        for ( i = 0; i < list.length; i++ ) {
        	if ( strcmp( filier, list.content[ i ] ) == 0 ) {
        		    save( file_name, datas );
        		return 0;
        	}
        }
                !liste_des_filiers[ 0 ] ? strcpy( liste_des_filiers, filier )
                                        : sprintf( liste_des_filiers, "%s|%s", liste_des_filiers, filier );
            empty( file_name );
        save( file_name, datas );
    return 1;
}

#endif // TOOLS_H_INCLUDED
