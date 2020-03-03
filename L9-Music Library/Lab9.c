#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {//Declaration of the node in the linked list
	char *artist;
	char *songName;
	char *genre;
	struct node *next;
} Node;

typedef struct linkedList {//Declaration of linked list with pointer head
	Node *head;
} List;
	
#define MAX_LENGTH  1024
void inputStringFromUser(char *prompt, char *s, int arraySize);
void songNameDuplicate(char *songName);
void songNameFound(char *songName);
void songNameNotFound(char *songName);
void songNameDeleted(char *deleteSong);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);
Node *createNode(char *songName, char *artist, char *genre);
bool isEmpty(List *musicLibrary);
void insertAtFront(List *musicLibrary, char *songName, char *artist, char *genre);
bool nodeSearch(List *musicLibrary, char *songName);
void insertIntoOrderedList (List *musicLibrary, char *songName, char *artist, char* genre);
void printList(List *musicLibrary);
void deleteNode(List *musicLibrary, char *deleteSong);
void findNode(List *musicLibrary, char *findSong);
void deleteAllNodes(List *musicLibrary);

//A music library program that allows the user to create a music library using linked lists with functions such as deleting, adding, deleting all etc.

int main(void) {
	char response;
	char *songName=NULL;//Strings that get passed into functions
	char *findSong=NULL;
	char *artist=NULL;
	char *deleteSong=NULL;
	char *genre=NULL;
	char input[MAX_LENGTH +1];
	List musicLibrary;
	
	
	
	printf("Personal Music Library.\n\n");
	printf("Commands are I (insert), D (delete), S (search by song name),\nP (print), Q (quit).\n");
	
	do {
		inputStringFromUser("\nCommand", input, MAX_LENGTH); 
		
		response=toupper(input[0]);//converts response to upper case

		if(response=='I') {
			songName=(char *) malloc((MAX_LENGTH+1) *sizeof(char));//allocating memory for the three variables that are used
			artist=(char *) malloc((MAX_LENGTH+1) *sizeof(char));
			genre=(char *) malloc((MAX_LENGTH+1) *sizeof(char));
			inputStringFromUser("Song name", songName, MAX_LENGTH);//Prompts user to enter song name and saves the reply to songName
			inputStringFromUser("Artist", artist, MAX_LENGTH);//Prompts user to enter the artist and saves the reply to artist
			inputStringFromUser("Genre", genre, MAX_LENGTH);//Prompts user to enter genre and saves the reply to genre
			insertIntoOrderedList(&musicLibrary, songName, artist, genre); //Takes the scanned inputs and inserts it into a musicLibrary list
		}
		
		else if (response=='D') {
			deleteSong=(char *) malloc((MAX_LENGTH+1) *sizeof(char));// memory allocation
			inputStringFromUser("\nEnter the name of the song to be deleted", deleteSong, MAX_LENGTH);
			deleteNode(&musicLibrary, deleteSong);//calls the deleteNode function
		}
		
		else if (response=='S') {
			findSong=(char *) malloc((MAX_LENGTH+1)*sizeof(char));//memory allocation
			inputStringFromUser("\nEnter the name of the song to search for", findSong, MAX_LENGTH);
			findNode(&musicLibrary, findSong);//Searches and prints node using findNode
		}
		
		else if (response=='P') {
			if(isEmpty(&musicLibrary)) {
				printMusicLibraryEmpty(); //if the library is empty
			}
			else {
				printMusicLibraryTitle();//Prints title and the linked list musicLibrary
				printList(&musicLibrary);
			}
		}
		
		else if (response=='Q') {
			continue;
		}
		
		else {
			printf("\nInvalid command.\n");
		}

	} while(response!='Q');
	
	deleteAllNodes(&musicLibrary); //when the user enters 'Q', leaves the loop and deletes all nodes
	if(isEmpty(&musicLibrary)) {
		printMusicLibraryEmpty(); //prints the library to ensure that it is empty
	}
	
	else {
		printList(&musicLibrary);//should not enter the else if the deleteAllNodes worked properly
	}
	free(songName);//frees all the variables that were malloced earlier
	free(artist);
	free(genre);
	free(deleteSong);
	free(findSong);
	return 0;
}

void inputStringFromUser(char *prompt, char *s, int arraySize) { //takes the users string and enteres it into char *s which is the string variable passed in main
	int i=0;
	char c;
	
	printf("%s --> ", prompt);	
	while (i < arraySize && (c = getchar()) != '\n') { //when user press enter, it puts \n at the end of the string
		s[i++] = c;
		s[i] = '\0';
	}
}

void songNameDuplicate(char *songName) {// prints that the song entered already exists in the library
	printf("\nA song with the name '%s' is already in the music library.\nNo new song entered.\n", songName);
}

void songNameFound(char *songName) {// used for searching when the song is found
	printf("\nThe song name '%s' was found in the music library.\n", songName);
}

void songNameNotFound(char *songName) {// user for searching when the song is not found
	printf("\nThe song name '%s' was not found in the music library.\n", songName);
}

void songNameDeleted(char *deleteSong) {// when the deleteNode function is called, prints the song that is being deleted
	printf("\nDeleting a song with name '%s' from the music library.\n", deleteSong);
}

void printMusicLibraryEmpty(void) { //prints this if the music library is empty
	printf("\nThe music library is empty.\n");
}

void printMusicLibraryTitle(void) {// Title of the music library to be used when P is entered
	printf("\nMy Personal Music Library: \n");
}

Node *createNode(char *songName, char *artist, char *genre) { //creates a new node in the linked list
	Node *newNode=(Node *)malloc(sizeof(Node));// allocates memory for the node
	newNode->songName=songName;
	newNode->artist=artist;
	newNode->genre=genre;
	newNode->next=NULL;//the node points to NULL
	return newNode;
}
bool isEmpty(List *musicLibrary) {// checks if the list is empty and returns true or false accordingly
	if(musicLibrary->head==NULL) {
		return true;
	}
	return false;
}

void insertAtFront(List *musicLibrary, char *songName, char *artist, char *genre) { //inserts at the beginning of the link list
	if(isEmpty(musicLibrary)) {
		musicLibrary->head=createNode(songName, artist, genre);//if its empty, then head points to it
	}
	
	else {
		Node *temp=createNode(songName, artist, genre);//creates a new node
		temp->next=musicLibrary->head; //the node is entered into the front and now points the node that head used to point to
		musicLibrary->head=temp;// the head now points to the newly created node
	}
}

bool nodeSearch(List *musicLibrary, char *songName) {// search that returns true if it finds the given song in the library
	Node *temp1=musicLibrary->head;
	while(temp1!=NULL) {
		if(strcmp(temp1->songName,songName)==0) {
			return true;
		}
		temp1=temp1->next;
	}
	return false;
}

void insertIntoOrderedList (List *musicLibrary, char *songName, char *artist, char* genre) { //inserts the node into the musicLibrary based on if it alphabetically preceeds 
	if(nodeSearch(musicLibrary, songName)) { //if the songName already exists
		songNameDuplicate(songName);
		return;
	}
	
	else {
		if(isEmpty(musicLibrary)) { //if the library is already empty, insertAtFront will work since no nodes exists
			insertAtFront(musicLibrary, songName, artist, genre);
			return;
		}
		if(strcmp(songName, musicLibrary->head->songName)<0) {//if the new song alphabetically preceeds the very first songName
			insertAtFront(musicLibrary, songName, artist, genre);
			return;
		}
		Node *newNode1=createNode(songName, artist, genre); //If the first 2 cases are not met
		Node *n=musicLibrary->head;
		while(n->next!=NULL && (strcmp(songName, n->next->songName)>0)) { //while not the end of list and while the new song is alphabetically after the one in the existing list
			n=n->next;
		}
		newNode1->next=n->next;
		n->next=newNode1;
	}
	
}

void printList(List *musicLibrary) { //Prints the entire list
	Node *temp2=musicLibrary->head;
	while(temp2!=NULL) {
		printf("\n%s\n", temp2->songName);
		printf("%s\n", temp2->artist);
		printf("%s\n", temp2->genre);
		temp2=temp2->next;
	}
}

void deleteNode(List *musicLibrary, char *deleteSong) { // deletes the specified node by the user
	if (nodeSearch(musicLibrary, deleteSong)) { //if the songName entered by user exists
		if(strcmp(musicLibrary->head->songName, deleteSong)==0) { //when the 2 strings are the same, the  very first song
			songNameDeleted(deleteSong);
			Node *temp3=musicLibrary->head->next;
			free(musicLibrary->head); //free memory used by node
			musicLibrary->head=temp3;
			return;
		}
		Node *temp4=musicLibrary->head; //if it isnt equal
		while(temp4->next!=NULL && strcmp(temp4->next->songName, deleteSong)!=0) { //traverses through the list while the 2 songs arent equal
			temp4=temp4->next;
		}
		
		if(temp4->next!=NULL) {
			songNameDeleted(deleteSong);
			Node *temp5 = temp4->next; // temp is the node we must delete
			temp4->next = temp5->next; // Update n so that temp is no longer linked
			free(temp5);// free memory
			return;
		}
	}
	else {
		songNameNotFound(deleteSong); //if the song entered doesnt exist
	}
}

void findNode(List *musicLibrary, char *findSong) {//finds and prints the associated artist and genre
	Node *temp5=musicLibrary->head; 
	while(nodeSearch(musicLibrary, findSong)) {
		if(strcmp(temp5->songName,findSong)==0) {
			songNameFound(findSong);
			printf("\n%s\n", temp5->songName);
			printf("%s\n", temp5->artist);
			printf("%s\n", temp5->genre);
			return;
		}
		temp5=temp5->next;
	}
	songNameNotFound(findSong);
}

void deleteAllNodes(List *musicLibrary) { //deletes all the nodes as well as the memory with them
	while(!isEmpty(musicLibrary)) {
		Node *newHead=musicLibrary->head->next;
		songNameDeleted(musicLibrary->head->songName);
		free(musicLibrary->head);
		musicLibrary->head=newHead;
	}
	musicLibrary->head=NULL;
}