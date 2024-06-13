#include "book.h"

char str[50];
int pos,choice;
char *string;
Status read_and_validation(BookInfo *book,char *argv)
{
	if(strstr(argv,".") && strcmp(strstr(argv,"."),".csv")==0)
	{
		book->fname=argv;
		if((book->fptr=fopen(argv,"r+"))!=NULL)
		{
			return SUCCESS;
		}
		printf("NO FILE WITH NAME %s\n",argv);
	}
	return FAILURE;
}

Status add_contact(BookInfo *book)
{
	int i,flag;
	char ch;
	while(1)
	{
		printf("\nenter a unique name: ");
		scanf(" %[^\n]",book->name);
		pos=1;
		string=book->name;
		if(search_name(book)==FAILURE)
		{
			printf("name is already taken try another one\n");
		}
		else
		{

			while(1)
			{
				printf("\nEnter the mobile number: ");
				scanf(" %[^\n]",book->number);
				flag=0,i=0;
				while(book->number[i])
				{
					if(book->number[i]<'0' || book->number[i]>'9')
					{
						flag=1;
						break;
					}
					i++;
				}
				if(strlen(book->number)!=10 ||flag==1)
				{
					printf("Invalid Number try again\n");
				}
				else
				{
					pos=2;
					string=book->number;
					if(search_name(book)==FAILURE)
					{
						printf("Number is already taken try again\n");
						continue;
					}
					break;
				}	

			}	
			while(1)
			{
				printf("\nEnter a unique valid mail id : ");
				scanf(" %[^\n]",book->mail);
				
				if( strchr(book->mail,'@') && strstr(book->mail,".") && strcmp(strstr(book->mail,"."),".com")==0 )
				{
					pos=3;
					string=book->mail;
					if(search_name(book)!=SUCCESS)
					{
						printf("Mail is already taken enter a different one\n");
						continue;
					}
					break;
				}
				printf("Invalid mail id try again\n");				
			}
			printf("\nEnter the location: ");
			scanf(" %[^\n]",book->location);

			printf("\nDo you want to save the data or not (y/n): ");
			scanf(" %c",&ch);
			printf("\n");
			if(ch=='y' || ch=='Y')
			{
				fseek(book->fptr,-1,SEEK_END);
				if(ftell(book->fptr)!=0)
				{
					ch='\n';
					fwrite(&ch,1,1,book->fptr);
				}
				ch=',';
				i=0;
				while(book->name[i])
				{
					fwrite(&book->name[i],1,1,book->fptr);
					i++;
				}
				fwrite(&ch,1,1,book->fptr);
				fwrite(book->number,10,1,book->fptr);
				fwrite(&ch,1,1,book->fptr);
				i=0;
				while(book->mail[i])
				{
					fwrite(&book->mail[i],1,1,book->fptr);
					i++;
				}
				fwrite(&ch,1,1,book->fptr);
				i=0;
				while(book->location[i])
				{
					fwrite(&book->location[i],1,1,book->fptr);
					i++;
				}
				ch='\n';
				fwrite(&ch,1,1,book->fptr);
				return SUCCESS;
			}
		}
	}
}

Status search_name(BookInfo *book)
{
	rewind(book->fptr);
	int i;
	char ch='\0';
	while(1)
	{
		i=0;
		int count=0;
		while(1)
		{
			if(feof(book->fptr))
			{
				return SUCCESS;
			}
			fread(&str[i],1,1,book->fptr);
			if(str[i]==',')
			{
				count++;
				if(count==pos)
				{
					break;
				}
				i=0;
				continue;
			}
			i++;
		}
		str[i]='\0';
		if(strcmp(str,string)==0)
		{
			return FAILURE;
		}
		while(ch != '\n')
		{
			fread(&ch,1,1,book->fptr);
		}
	}

}
Status print_contact(FILE *fptr)
{
	rewind(fptr);
	int i=0,j=0;
	printf("\n");
	while(1)
	{
		if(feof(fptr))
		{
			return SUCCESS;
		}
		fread(&str[i],1,1,fptr);
		if(str[i]==',' || str[i]=='\n')
		{
			str[i]='\0';
			printf("%-10s : %s\n",info[j],str);
			i=0;
			j=(j+1)%4;
			if(j==0)
			{
				printf("\n");
			}
			continue;
		}
		i++;

	}
}
