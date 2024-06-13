#ifndef BOOK_H
#define BOOK_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



static char *info[]={"NAME","MOBILE.NO","GMAIL","LOCATION"};

typedef struct 
{
	char name[30];
	char number[10];
	char mail[40];
	char location[50];

	FILE *fptr;
	char *fname;

}BookInfo;


typedef enum
{
	SUCCESS,
	FAILURE
}Status;


Status read_and_validation(BookInfo *book,char *argv);

Status add_contact(BookInfo *book);

int search_contact(BookInfo *book);
Status search_name(BookInfo *book);
Status search_book(FILE *fptr,char *string,int *pos);

Status delete_contact(BookInfo *book);
Status delete_book(FILE *fptr,char *string,int pos);

Status edit_book(FILE *fptr,char *string,int pos);
Status edit_contact(BookInfo *book);

Status print_contact(FILE *fptr);




#endif
