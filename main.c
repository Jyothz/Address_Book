#include "book.h"


int main(int argc, char *argv[])
{
	BookInfo book;

	if(argc==2)
	{

		if(read_and_validation(&book,argv[1])==SUCCESS)
		{
			int opt;
			while(1)
			{
				printf("1.Add Contact\n2.Edit Contact\n3.Search Contact\n4.Delete Contact\n5.Print Contacts\n6.Exit\nEnter the choice: ");
				scanf("%d",&opt);

				switch(opt)
				{
					case 1:
						add_contact(&book);
						break;
					case 2:
						edit_contact(&book);
						break;
					case 3:
						search_contact(&book);
						break;
					case 4:
						delete_contact(&book);
						break;
					case 5:
						print_contact(book.fptr);
						break;
					case 6:
						return 0;
					default:
						printf("Invalid Choice try again\n\n");
				}
			}
		}

	}
	printf("INVALID INPUT\nGive input as : ./a.out < .csv file>\n");
	return 0;

}
