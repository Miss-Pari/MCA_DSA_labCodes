//this application stores details of people
//using structure 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct person{
    char name[20];
    char email[20];
    long int number;
    char note[100];
};

//define data type -> person
typedef struct person person;

void menu(); 
void list();
void addPerson(); 
void serachPerson();
void removePerson();
void updatePerson();
void deleteRecords();
void getInput(person *p);

void main()
{
    int menuOption;
    while(1){
        printf("menu options:\n\t1 to list records\n\t2 to delete all records\n\t3 to add a person\n\t4 to remove a person\n\t5 to update a record\n\t6 to search a person\n\t0 to exit\nyour choice:  ");
        scanf("%d",&menuOption);
        switch(menuOption){
            case 1:
                list();
                break;
            case 2:
                deleteRecords();
                break;
            case 3:
                addPerson();
                break;
            case 4:
                removePerson();
                break;
            case 5:
                updatePerson();
                break;
            case 6:
                serachPerson();
                break;
            case 0:
                printf("Good day!\n");
                exit(1);
                break;
            default:
                printf("Unknown option, exiting contact diary");
                exit(1);
        }
    }
}

void menu(){
    printf("menu options:\n\t1 to list records\n\t2 to delete all records\n\t3 to add a person\n\t4 to remove a person\n\t5 to update a record\n\t6 to search a person\n\t0 to exit\nyour choice:  ");
}

void addPerson(){
    FILE *fp;
    fp = fopen("db","ab+");
    if(fp==NULL){
        printf("error, press enter to continue!");
        return;
    }else{
        person p;
        getInput(&p);
        fwrite(&p,sizeof(p),1,fp);
        fclose(fp);
        printf("record added!\npress enter to continue!");
    }
}

void getInput(person *p){
    printf("enter name: ");
    scanf("%s", &p->name);
    printf("enter E-mail: ");
    scanf("%s", &p->email);
    printf("any notes: ");
    scanf("%s", &p->note);
    printf("enter contact number: ");
    scanf("%ld", &p->number);
}

void list(){
    FILE *fp;
    fp = fopen("db", "rb");
    if(fp==NULL){
        printf("error, press enter to continue!");
        return;
    }else{
        person p;
        printf("\nAll the records are:\n");
        printf("\nName\t\tEmail\t\t\tContact\t\tNotes\n");
        while(fread(&p, sizeof(p),1,fp)==1){
            int i;
            int namelen = 25 - strlen(p.name);
            int emaillen = 20 - strlen(p.email);
            int notelen = 150 - strlen(p.note);
            // int numlen = 22 - strlen(&p.number);
            int numlen = 22;

            printf("%s",p.name);
            for(i=0;i<namelen;i++){printf(" ");}

            printf("%s",p.email);
            for(i=0;i<emaillen;i++){printf(" ");}

            printf("%ld",p.number);
            for(i=0;i<numlen;i++){printf(" ");}

            printf("%s",p.note);
            for(i=0;i<notelen;i++){printf(" ");}

            printf("\n");
            fflush(stdin);
        }
        fflush(stdin);
        fclose(fp);
        printf("End of database, press any key to continue");
    }
}

void serachPerson(){
    long int pnum;
    printf("Enter number to search:");
    scanf("%ld",&pnum);

    FILE *fp;
    fp = fopen("db", "rb");
    if(fp==NULL){
        printf("error, press enter to continue!");
        return;
    }else{
        int flag=0;
        person p;
        while (fread(&p, sizeof(p),1,fp)==1){
            if(p.number==pnum){
                printf("\nName\t\tEmail\t\t\tContact\t\tNotes\n");
                int i;
                int namelen = 25 - strlen(p.name);
                int emaillen = 20 - strlen(p.email);
                int notelen = 150 - strlen(p.note);
                // int numlen = 22 - strlen(&p.number);
                int numlen = 22;

                printf("%s",p.name);
                for(i=0;i<namelen;i++){printf(" ");}

                printf("%s",p.email);
                for(i=0;i<emaillen;i++){printf(" ");}

                printf("%ld",p.number);
                for(i=0;i<numlen;i++){printf(" ");}

                printf("%s",p.note);
                for(i=0;i<notelen;i++){printf(" ");}

                flag=1;
                break;
            }
        }
        if(flag==0){printf("Record not found!");}
        fclose(fp);
    }
}

void deleteRecords(){
    remove("./db");
    printf("\nrecords cleared!\n");
}

void updatePerson(){
    FILE *fp, *fp1;
    fp = fopen("db","rb");
    fp1 = fopen("db","wb+");
    if(fp1==NULL){
        printf("error, press enter to continue!");
        return;
    }else{
        long int pnum;
        printf("Enter number to search:");
        scanf("%ld",&pnum);
        int flag=0;
        person p;
        while (fread(&p, sizeof(p),1,fp1)==1){
            if(p.number==pnum){
                getInput(&p);
                fwrite(&p,sizeof(p),1,fp1);
                printf("record updated!\npress enter to continue!");
                flag=1;
            }else{
                fwrite(&p,sizeof(p),1,fp1);
                printf("record added!\npress enter to continue!");
            }
        }
        if(flag==0){printf("Record not found!");}
        fclose(fp);
        fclose(fp1);
        remove("db");
        rename("fp1","db");
        fflush(stdin);
    }
}

void removePerson(){
    FILE *fp, *fp1;
    fp = fopen("db","rb");
    fp1 = fopen("db","wb+");
    if(fp1==NULL){
        printf("error, press enter to continue!");
        return;
    }else{
        long int pnum;
        printf("Enter number to delete:");
        scanf("%ld",&pnum);
        int flag=0;
        person p;
        while (fread(&p, sizeof(p),1,fp)==1){
            if(p.number==pnum){
                printf("record deleted!\npress enter to continue!");
                flag=1;
            }else{
                fwrite(&p,sizeof(p),1,fp1);
                fflush(stdin);
            }
        }
        if(flag==0){printf("Record not found!");}
        fclose(fp);
        fclose(fp1);
        remove("db");
        rename("fp1","db");
        fflush(stdin);
    }
}
