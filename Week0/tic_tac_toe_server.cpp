/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}




// A C++ Program to play tic-tac-toe 

#define COMPUTER 1 
#define HUMAN 2 

#define SIDE 3 // Length of the board 

// Computer will move with 'O' 
// and human with 'X' 
#define COMPUTERMOVE 'O' 
#define HUMANMOVE 'X' 

char board[SIZE][SIZE];
int moves[SIDE*SIDE];
char buffer[256];

// A function to show the current board status 
void showBoard(char board[][SIDE]) 
{ 
	printf("\n\n"); 
	
	printf("\t\t\t %c | %c | %c \n", board[0][0], 
							board[0][1], board[0][2]); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t %c | %c | %c \n", board[1][0], 
							board[1][1], board[1][2]); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], 
							board[2][1], board[2][2]); 

	return; 
} 

// A function to show the instructions 
void showInstructions() 
{ 
	printf("\t\t\t Tic-Tac-Toe\n\n"); 
	printf("Choose a cell numbered from 1 to 9 as below"
			" and play\n\n"); 
	
	printf("\t\t\t 1 | 2 | 3 \n"); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t 4 | 5 | 6 \n"); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t 7 | 8 | 9 \n\n"); 
	
	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n"); 

	return; 
} 


// A function to initialise the game 
void initialise(char board[][SIDE], int moves[]) 
{ 
	// Initiate the random number generator so that 
	// the same configuration doesn't arises 
	
	// Initially the board is empty 
    board[0][0]=buffer[0]
    board[0][1]=buffer[1]
    board[0][2]=buffer[2]

    board[1][0]=buffer[3]
    board[1][1]=buffer[4]
    board[1][2]=buffer[5]

    board[2][0]=buffer[6]
    board[2][1]=buffer[7]
    board[2][2]=buffer[8]
	
	return; 
} 

// A function to declare the winner of the game 
void declareWinner(int whoseTurn) 
{ 
	if (whoseTurn == COMPUTER) 
		printf("COMPUTER has won\n"); 
	else
		printf("HUMAN has won\n"); 
	return; 
} 

// A function that returns true if any of the row 
// is crossed with the same player's move 
bool rowCrossed(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// A function that returns true if any of the column 
// is crossed with the same player's move 
bool columnCrossed(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// A function that returns true if any of the diagonal 
// is crossed with the same player's move 
bool diagonalCrossed(char board[][SIDE]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return(true); 

	return(false); 
} 

// A function that returns true if the game is over 
// else it returns a false 
bool gameOver(char board[][SIDE]) 
{ 
	return(rowCrossed(board) || columnCrossed(board) 
			|| diagonalCrossed(board) ); 
} 

// A function to play Tic-Tac-Toe 
void playTicTacToe(int whoseTurn) 
{ 
	// A 3*3 Tic-Tac-Toe board for playing 
	char board[SIDE][SIDE]; 
	
	int moves[SIDE*SIDE]; 
	
	// Initialise the game 
	initialise(board, moves); 
	
	// Show the instructions before playing 
	showInstructions(); 
	
	int moveIndex = 0, x, y; 
	
	// Keep playing till the game is over or it is a draw 
	while (gameOver(board) == false && 
			moveIndex != SIDE*SIDE) 
	{ 
		if (whoseTurn == COMPUTER) 
		{ 
			x = moves[moveIndex] / SIDE; 
			y = moves[moveIndex] % SIDE; 
			board[x][y] = COMPUTERMOVE; 
			printf("COMPUTER has put a %c in cell %d\n", 
					COMPUTERMOVE, moves[moveIndex]+1); 
			showBoard(board); 
			moveIndex ++; 
			whoseTurn = HUMAN; 
		} 
		
		else if (whoseTurn == HUMAN) 
		{ 
			x = moves[moveIndex] / SIDE; 
			y = moves[moveIndex] % SIDE; 
			board[x][y] = HUMANMOVE; 
			printf ("HUMAN has put a %c in cell %d\n", 
					HUMANMOVE, moves[moveIndex]+1); 
			showBoard(board); 
			moveIndex ++; 
			whoseTurn = COMPUTER; 
		} 
	} 

	// If the game has drawn 
	if (gameOver(board) == false && 
			moveIndex == SIDE * SIDE) 
		printf("It's a draw\n"); 
	else
	{ 
		// Toggling the user to declare the actual 
		// winner 
		if (whoseTurn == COMPUTER) 
			whoseTurn = HUMAN; 
		else if (whoseTurn == HUMAN) 
			whoseTurn = COMPUTER; 
		
		// Declare the winner 
		declareWinner(whoseTurn); 
	} 
	return; 
}

void print_board(){
    cout<<"Current Board\n";
    for(ll i=0;i<3;++i){
        for(ll j=0;j<3;++j){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
        
    else{
        showInstructions();
        int x, y; 
        while(true){
            bzero(buffer,256);
            n = read(newsockfd,buffer,255);
            if (n < 0) {
                error("ERROR reading from socket");
                exit(0);
            }
            initialise(board, moves);
            print_board();
            if(gameOver(board) == false){
                cout<<"Enter cell number for move\n";
                ll cell;
                cin>>cell;
                ll x=cell/3;
                ll y=cell%3;
                

            }
            
            
            printf("Here is the message: %s\n",buffer);
            n = write(newsockfd,"I got your message",18);
            if (n < 0) error("ERROR writing to socket");
            close(newsockfd);
            close(sockfd);
        }
    }
     return 0; 
}
