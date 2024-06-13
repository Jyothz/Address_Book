#include "book.h"

FILE *cptr;

Status delete_contact(BookInfo *book)
{
	int opt;
	char ch;
	int flag=0;
	int pos=1;
	cptr=fopen("my_cpy.csv","w+");
	while(1)
	{
		pos=1;
		printf("\nEnter the name of the Contact you need to delete: \n");
		scanf(" %[^\n]",book->name);

		if(search_book(book->fptr,book->name,&pos)==FAILURE)
		{
			printf("NAME NOT FOUND\n");
			printf("Try again\n");
			continue;
		}
		if(pos>1)
		{
			printf("Enter the Contact you want to delete: \n");
			scanf(" %[^\n]",book->name);
		}
		delete_book(book->fptr,book->name,1);
		
		printf("\n1.SAVE CHANGES\n2.CONTINUE\n3.EXIT\nEnter the choice: ");
		scanf("%d",&opt);
		switch (opt)
		{
			case 1:
				{
					fclose(book->fptr);
					rewind(cptr);
					book->fptr=NULL;
					book->fptr=fopen(book->fname,"w+");
					while(1)
					{
						fread(&ch,1,1,cptr);
						if(feof(cptr))
						{
							break;
						}
						fwrite(&ch,1,1,book->fptr);
					}
					printf("SAVED SUCCESSFULLY\n\n");
					return SUCCESS;
				}
				break;
			case 2:
				continue;
			case 3:
				return SUCCESS;
			default:
				printf("Invalid Option\n");
		}		

	}

}

Status delete_book(FILE *fptr,char *string,int pos)
{
	rewind(fptr);
	rewind(cptr);
	char ch,str[100];
	int i;
	while(1)
	{
		i=0;
		while(1)
		{
			if(feof(fptr))
			{
				return FAILURE;
			}
			fread(&str[i],1,1,fptr);
			if(str[i]==',')
			{
				break;
			}
			i++;
		}
		str[i]='\0';
		if(strcmp(str,string)==0)
		{
			ch='\0';
			while(ch!='\n')
			{
				fread(&ch,1,1,fptr);
				if(feof(fptr))
				{
					return SUCCESS;
				}
			}
			while(1)
			{
				fread(&ch,1,1,fptr);
				if(feof(fptr))
				{
					break;
				}
				fwrite(&ch,1,1,cptr);
			}
			continue;
		}
		ch=',';
		fwrite(str,i,1,cptr);
		fwrite(&ch,1,1,cptr);
		while(ch != '\n')
		{
			fread(&ch,1,1,fptr);
			if(feof(fptr))return FAILURE;
			fwrite(&ch,1,1,cptr);

		}
	}
}

