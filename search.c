#include "book.h"
int search_contact(BookInfo *book)
{
	int i,opt,count=0;
	char ch;
	while(1)
	{
		printf("\n1.NAME\n2.MOBILE.NO\n3.MAIL\n4.LOCATION\n5.EXIT\nEnter the choice: ");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1:
				{
					count=1;
					printf("\nenter a unique name: ");
					scanf(" %[^\n]",book->name);
					printf("\n");
					if(search_book(book->fptr,book->name,&count)==FAILURE)
					{
						printf("NAME NOT FOUND\n");
					}
				}
				break;
			case 2:
				{
					count=2;
					printf("\nenter the new number: ");
					scanf(" %[^\n]",book->number);
					printf("\n");
					if(strlen(book->number)!=10 || atoi(book->number)==0)
					{
						printf("Invalid NUMBER try again\n");
						continue;
					}
					if(search_book(book->fptr,book->number,&count)==FAILURE)
					{
						printf("NUMBER NOT FOUND\n");
					}
				}
				break;
			case 3:
				{
					count=3;
					printf("\nEnter the mail id : ");
					scanf(" %[^\n]",book->mail);
					printf("\n");
					if(search_book(book->fptr,book->mail,&count)==FAILURE)
					{
						printf("MAIL NOT FOUND\n");
					}
				}
				break;
			case 4:
				{
					count=4;
					printf("\nEnter the Location : ");
					scanf(" %[^\n]",book->location);
					printf("\n");
					if(search_book(book->fptr,book->location,&count))
					{
						printf("LOCATION NOT FOUND\n");
					}
				}
				break;
			case 5:
				{
					printf("\n");
					return count;

				}
				break;
			default:
				printf("Invalid Choice\n");
		}
	}
}


char str[1000];			
Status search_book(FILE *fptr,char *string,int *pos)
{
	rewind(fptr);
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
				if(flag)
				{
					printf("\n%d DETAILS FOUND\n\n",flag);
					*pos=flag;
					return SUCCESS;
				}
				return FAILURE;
			}
			fread(&str[i],1,1,fptr);
			if(str[i]==',' || str[i]=='\n')
			{
				count++;
				if(count == *pos)
				{
					break;
				}
				str[i]='\0';
				ind+=strlen(str)+1;
				i=0;
				continue;
			}
			i++;
		}
		str[i]='\0';
		if(strstr(str,string)!=0)
		{
			flag++;
			fseek(fptr,-(strlen(str)+ind+1),SEEK_CUR);
			ch='\0';
			i=0;
			printf("%-10s : ",info[i]);
			while(ch!='\n')
			{
				if(feof(fptr))
				{
					return SUCCESS;
				}
				fread(&ch,1,1,fptr);
				if(ch==',')
				{
					printf("\n%-10s : ",info[++i]);	
					continue;
				}
				printf("%c",ch);
			}
			printf("\n");
			continue;
		}
		ind++;
		ch='\0';
		if(*pos!=4)
		{
			while(ch != '\n')
			{
				fread(&ch,1,1,fptr);
			}
		}
	}
}


