
#include "book.h"

char edits[100];
FILE *cptr;
char *locate;
char name[50];
Status edit_contact(BookInfo *book)
{
	int i,opt,count;
	char ch;
	int flag=0;
	while(1)
	{
		printf("\n1.NAME\n2.MOBILE.NO\n3.MAIL\n4.LOCATION\n5.SAVE\n6.EXIT\nEnter the choice to edit: ");
		scanf("%d",&opt);
		count=0;
		switch(opt)
		{
			case 1:
				{
					flag=1;
					printf("\nenter the name to be edited: ");
					scanf(" %[^\n]",book->name);
					if(search_book(book->fptr,book->name,&flag)==FAILURE)
					{
						printf("NAME NOT FOUND\n");
						flag=0;
					}
					if(flag!=1)
					{
						printf("\nenter any above name to be edited: ");
						scanf(" %[^\n]",book->name);
					}
					printf("enter the new name: ");
					scanf(" %[^\n]",edits);
					printf("\n");
					edit_book(book->fptr,book->name,1);
				}
				break;
			case 2:
				{
					flag=2;
					printf("\nenter the number to be edited: ");
					scanf(" %[^\n]",book->number);
					printf("enter the new number: ");
					scanf(" %[^\n]",edits);
					printf("\n");
					if(strlen(book->number)!=10 || atoi(book->number)==0)
					{
						printf("Invalid NUMBER try again\n");
						continue;
					}
					if(edit_book(book->fptr,book->number,2)==FAILURE)
					{
						printf("NUMBER NOT FOUND\n");
						flag=0;
					}
				}
				break;
			case 3:
				{
					flag=3;
					printf("\nEnter the mail id : ");
					scanf(" %[^\n]",book->mail);
					printf("enter the new mail: ");
					scanf(" %[^\n]",edits);
					printf("\n");
					if(search_book(book->fptr,book->mail,&flag)==FAILURE)
					{
						printf("MAIL NOT FOUND\n");
						flag=0;
						continue;
					}
					edit_book(book->fptr,book->mail,3);
				}
				break;
			case 4:
				{
					flag=4;
					printf("\nEnter the Location : ");
					scanf(" %[^\n]",book->location);
					if(search_book(book->fptr,book->location,&flag))
					{
						printf("LOCATION NOT FOUND\n");
						flag=0;
						continue;
					}
					if(flag!=1)
					{
						printf("\nEnter the name of the person : ");
						scanf(" %[^\n]",book->name);
						printf("enter the new location: ");
						scanf(" %[^\n]",edits);
						printf("\n");
						locate=book->location;
						edit_book(book->fptr,book->name,4);
					}
					else
					{
						printf("\nenter the new location: ");
						scanf(" %[^\n]",edits);
						printf("\n");
						locate=book->location;
						edit_book(book->fptr,book->location,5);
					}
				}
				break;
			case 5:
				{
					if(flag)
					{
						rewind(cptr);
						fclose(book->fptr);
						book->fptr=fopen(book->fname,"w+");
						if(book->fptr==NULL)
						{
							printf("Failed\n");
							break;
						}
						while(1)
						{
							fread(&ch,1,1,cptr);
							if(feof(cptr))
							{
								printf("SUCCESSFULLY SAVED\n");
								break;
							}
							fwrite(&ch,1,1,book->fptr);
						}
						flag=0;
						fclose(cptr);
						cptr=NULL;
					}
					else
					{
						printf("NO Content edited\n");
					}
					continue;
				}
				break;
			case 6:
				{
					return SUCCESS;
				}
			default:
				{
					printf("Invalid Choice\n");
					continue;
				}
		}
		printf("To save the changes enter 5\n");
	}
}

char str[100];			
Status edit_book(FILE *fptr,char *string,int pos)
{
	rewind(fptr);
	if(cptr==NULL)
		cptr=fopen("my_copy.csv","w+");
	else
		rewind(cptr);
	char ch;
	int flag=0;
	int ind=0,i;
	while(1)
	{
		i=0;
		ind=0;
		int count=0;
		while(1)
		{
			if(feof(fptr))
			{
				return FAILURE;
			}
			fread(&str[i],1,1,fptr);
			if(str[i]==',' || str[i]=='\n')
			{
				count++;
				ch=str[i];
				if(count==1)
				{
					str[i]='\0';
					strcpy(name,str);
				}
				if(count == pos ||(pos==5 && count== pos-1))
				{
					break;
				}
				if(count==1)
				{

					fwrite(str,i,1,cptr);
					fwrite(&ch,1,1,cptr);
				}
				else
				{
					fwrite(str,i+1,1,cptr);
				}
				i=0;
				continue;
			}
			i++;
		}
		str[i]='\0';
		if(strcmp(str,string)==0 || pos==4)
		{
			if(pos==4 && (strcmp(string,name) || strcmp(str,locate)))
			{
				fwrite(str,i,1,cptr);
				fwrite(&ch,1,1,cptr);
				continue;
			}
			flag++;
			i=0;
			while(edits[i])
			{
				fwrite(&edits[i],1,1,cptr);
				i++;
			}
			fwrite(&ch,1,1,cptr);
			while(1)
			{
				fread(&ch,1,1,fptr);
				if(feof(fptr))
				{
					return SUCCESS;
				}
				fwrite(&ch,1,1,cptr);
			}
		}
		fwrite(str,i,1,cptr);
		fwrite(&ch,1,1,cptr);
		if(pos<4)
		{
			ch='\0';
			while(ch!='\n')
			{
				fread(&ch,1,1,fptr);
				if(feof(fptr))
				{
					return FAILURE;
				}
				fwrite(&ch,1,1,cptr);
			}
		}
	}
}
