#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// create a struct for contacts

struct contact {
    long phoneNumber;
    char name[30], address[50],email[30];
}list;

char query[20], name[20];

// declare the file pointers
FILE *fptr, *tptr;

int choice, i, found, len, ch;

int main()
{

    char body[7];





    main:




        // clear the screen and print welcome message

        printf("\n\t **** Welcome to My Contact Management System ****");

        printf("\n\n\n\t\t\tMAIN MENU\n");
        printf("\t\t=====================\n");
        printf("\t\t[1] Add a new Contact\n");
        printf("\t\t[2] List all Contacts\n");
        printf("\t\t[3] Search for contact\n");
        printf("\t\t[4] Edit a Contact\n");
        printf("\t\t[5] Delete a Contact\n");
        printf("\t\t[0] Exit\n");
        printf("\t\t=================\n\n");

        printf("\t\tEnter Your choice: ");
        scanf("%d", &choice);

        //check the option selected
        switch(choice){
        case 0:
            printf("\n\n\t\t Are you sure you want to exit?");
            //printf("\n\t\t[1] Yes");
            //printf("\n\t\t[1] No");
            break;

        case 1:
            system("cls");

            // create/open contacts file

            fptr = fopen("contact.dll", "a");

            for(;;){
                // flush the buffer
                fflush(stdin);
                printf("To exit enter blank space in the name input\nName: ");

                // keep accepting characters until new line is entered
                scanf("%[^\n]", list.name);
                //printf("%s",list.name);

                // check if the input is blank
                if (stricmp(list.name,"")== 0 || stricmp(list.name," ")== 0){
                    break;
                }

                fflush(stdin);
                printf("Phone: ");
                scanf("%ld", &list.phoneNumber);

                fflush(stdin);
                printf("Address: ");
                scanf("%[^\n]", &list.address);

                fflush(stdin);
                printf("Email Address: ");
                //scanf("%[^\n]", &list.email);
                gets(list.email);

                printf("\n");

                // write to file
                fwrite(&list, sizeof(list),1,fptr);

            }

            // close the file
            fclose(fptr);
            break;


        case 2:
            system("cls");
            printf("\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n\nName\t\tPhone No\t    Address\t\tE-mail ad.\n=================================================================\n\n");

            // loop through ascii values of a-z and A-Z

            for(i=97; i<=122; i=i+1)

            {

                fptr=fopen("contact.dll","r");

                fflush(stdin);

                found=0;

                while(fread(&list,sizeof(list),1,fptr)==1)

                {

                    if(list.name[0]==i || list.name[0]==i-32)


                    {
                        printf("%d",list.name[0]);

                        printf("\nName\t: %s\nPhone\t: %ld\nAddress\t: %s\nEmail\t: %s\n",list.name,

                               list.phoneNumber,list.address,list.email);

                        found++;

                    }

                }

                if(found!=0)

                {
                    printf("=========================================================== [%c]-(%d)\n\n",i-32,found);

                    // exit on character press

                    getch();
                }

                fclose(fptr);

            }

            break;

            ///// search contacts
        case 3:
            system("cls");

            do {
                found = 0;

                printf("\n\n\t..::CONTACT SEARCH\n\t===========================\n\t..::Name of contact to search: ");
                fflush(stdin);

                scanf("%[^\n]", &query);

                len = strlen(query);

                fptr = fopen("contact.dll", "r");

                system("cls");

                printf("\n\n..::Search result for '%s' \n===================================================\n",query);


                while (fread(&list,sizeof(list),1,fptr)==1) {

                    for (i = 0; i <len; i++){;
                        name[i] = list.name[i];

                    }
                    name[len] = '\0';
                     if (stricmp(name, query)==0){
                        printf("\n..::Name\t: %s\n..::Phone\t: %ld\n..::Address\t: %s\n..::Email\t: %s\n",list.name,list.phoneNumber,list.address,list.email);

                        found++;

                        if (found % 4==0){
                            printf("..::Press any key to continue...");

                            getch();
                        }
                     }
                }

                if(found==0)

                    printf("\n..::No match found!");

                else

                    printf("\n..::%d match(s) found!",found);

                fclose(fptr);

                printf("\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t");

                scanf("%d",&ch);

            }
            // check the choice made and exit the loop
            while(ch==1);



            break;




            /* *****************************edit contact ********** */

        case 4:
            system("cls");

            fptr = fopen("contact.dll", "r");
            // create temporary file to hold the contact
            tptr = fopen("temp.dat", "w");

            fflush(stdin);

             printf("..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit:");

             scanf("%[^\n]", &name);

             // read a new line from the contact file
             while (fread(&list,sizeof(list),1,fptr)==1){
                // while contact is not to be edited, write it to temporary file
                if (stricmp(name, list.name) !=0){
                    fwrite(&list, sizeof(list), 1,tptr);
                }

             }

             fflush(stdin);

             printf("\n\n..::Editing '%s'\n\n",name);

             // accept new contact parameters

             printf("..::Name(Use identical):");

            scanf("%[^\n]",&list.name);

            fflush(stdin);

            printf("..::Phone:");

            scanf("%ld",&list.phoneNumber);

            fflush(stdin);

            printf("..::address:");

            scanf("%[^\n]",&list.address);

            fflush(stdin);

            printf("..::email address:");

            gets(list.email);

            printf("\n");

            // save to temporary file

            fwrite(&list,sizeof(list),1,tptr);

            fclose(fptr);
            fclose(tptr);

            // delete old contact file
            remove("contact.dll");

            // rename temporary file to new contact

            rename("temp.dat", "contact.dll" );

            break;

        case 5:

            system("cls");
            fflush(stdin);

            printf("\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the name of contact to delete:");

            scanf("%[^\n]",&name);

            fptr = fopen("contact.dll", "r");

            tptr = fopen("temp.dat", "w");

            while(fread(&list,sizeof(list),1,fptr)!=0){
                // check for contact to be deleted
                if (stricmp(name, list.name)!=0){
                    fwrite(&list, sizeof(list),1,tptr);
                }

            }
            fclose(fptr);
            fclose(tptr);

            remove("contact.dll");

            rename("temp.dat", "contact.dll");

            break;

        default:
            printf("Invalid choice");
            break;

        }

    printf("\n\n\n..::Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n");

    scanf("%d",&ch);

    switch (ch)

    {

    case 1:

        goto main;

    case 0:

        break;

    default:

        printf("Invalid choice");

        break;

    }

    return 0;
}
