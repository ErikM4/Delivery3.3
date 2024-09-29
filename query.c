#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int err;
	// Initialize the MySQL library
	mysql_library_init(0, NULL, NULL);
	
	if (mysql_library_init(0, NULL, NULL) != 0) {
		printf("Error initializing MySQL library: %u %s\n",
			   mysql_errno(NULL), mysql_error(NULL));
		exit(1);
	}
	
	//We create a connection to the MYSQL server
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf("Error creating connection: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//initialize the connection
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Uno",0, NULL, 0);
	if (conn==NULL) {
		printf("Error initializing connection: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
		
	char player[80];
	char game[80];
	
	// I ask the player and game ID
	printf("Give me the ID of the player\n");
	scanf("%s", player);
	printf("Give me the ID of the game\n");
	scanf("%s",game);
	atoi (player);
	atoi (game);
	
	// Execute the query
	char query[80];
	strcpy (query,"SELECT Deck.CardID FROM Deck WHERE Deck.PlayerID = ");
	strcat (query, player);
	strcat (query," AND Deck.GameID = ");
	strcat (query, game);
	
	
	err=mysql_query (conn, query);
	if (err!=0) {
		printf ("Error while querying data from database %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	
	// Get the result
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	if (row == NULL)
		printf("No data was obtained in the query\n");
	else
		printf("The cards of player 1 are:\n");
		while (row !=NULL) {
			// column 3 contains the card's ID
			printf("%s\n", row[3]);
			// get the next row
			row = mysql_fetch_row(res);
	}
	
	// Free the result
	mysql_free_result(res);
	
	// Close the connection
	mysql_close(conn);
	
	// Deinitialize the MySQL library
	mysql_library_end();
	
	exit(0);
}
}