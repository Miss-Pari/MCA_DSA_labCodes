// singly linked list
// participants, voters, administrators
/*first create profile and then login and then list and then vote and then count
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct participant{
    char name[20];
    int vote;
    int id;
    struct node *next;
};
struct node *startParticipant;

struct voter{
    char name[20];
    int vote;
    int id;
    struct node *next;
};
struct node *startVoter;

void addParticipant(){
    struct participant *ptr, *tmp;
    char name_[20];
    int id_;
    ptr = (struct participant *)malloc(sizeof(struct participant));
    if (ptr == NULL){
        printf("\nerror: malloc\n");
    }else{
        printf("\nEnter participant's ID:");
        scanf("%d", &id_);
        printf("\nEnter participant's name: ");
        scanf("%s", &name_);

        ptr->id=id_;
        strcpy(ptr->name, name_);

        if(startParticipant == NULL) {
            startParticipant = ptr;
            ptr->next = NULL;
            printf("\nparticipant added!\n");
        }else{
            tmp = startParticipant;
            while (tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next = ptr;
            ptr->next = NULL;
            printf("\nparticipant added!\n");
        }
    }
}

void listParticipants(){
    struct participant *ptr;
    ptr = startParticipant;
    if (ptr == NULL){
        printf("\nNo participants registered!\n");
    }else{
        printf("\nParticipants registered\nID:\t\tName");
        while(ptr != NULL){
            printf("\n%d\t\t%s", ptr->id,ptr->name);
            ptr = ptr->next;
        }
    }
}

void listCandidates(){
    printf("\nBelow are all the candidates, vote for any one using their repective ID\n");
    listParticipants();
}

void addVoter(){
    struct voter *ptr, *temp;
    int id_;
    char name_[20];
    ptr = (struct voter *)malloc(sizeof(struct voter));
    if (ptr == NULL){
        printf("error allocating memory");
    }else{
        printf("\nEnter name of voter:\n");
        scanf("%s", name_);
        printf("\nEnter voting ID of voter: ");
        scanf("%d", &id_);

        ptr->vote = id_;
        strcpy(ptr->name, name_);
        if (startVoter == NULL){
            ptr->next = NULL;
            startVoter = ptr;
            printf("\nVoter added!!\n");
        }else{
            temp = startVoter;
            while (temp->next != NULL){
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->next = NULL;
            printf("\nVoter added!!\n");
        }
    }
}

void listVoter(){
    struct voter *ptr;
    ptr = startVoter;
    if (ptr == NULL){
        printf("No votes were entered");
    }else{
        printf("\nVoterss registered\nID:\t\tName\n");
        while (ptr != NULL){
            printf("\n%d\t\t%s", ptr->id,ptr->name);
            ptr = ptr->next;
        }
    }
}

void admin_Voter(){
    int choice, flag = 1;
    while (flag){
        printf("\nEnter your choice\n");
        printf("\n1.Add Voter\n2.List Voters\n3.Exit: ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            listVoter();
            addVoter();
            break;
        case 2:
            listVoter();
            break;
        case 3:
            flag = 0;
            break;
        default:
            printf("Invalid choice");
        }
    }
}

void top3(struct voter *startParticipant){
    struct voter *ptr = startParticipant;
    printf("Details of singer top 3");
    while (ptr != NULL){
        printf("\n%d", ptr->id);
        printf("\n%s", ptr->name);
        ptr = ptr->next;
    }
}

void admin_Participant(){
    int choice, flag = 1;
    while (flag){
        printf("\nEnter your choice\n");
        printf("\n1.Add participant\n2.List participant\n3.Exit: ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            addParticipant();
            break;
        case 2:
            listParticipants();
            break;
        case 3:
            flag = 0;
            break;
        default:
            printf("Invalid choice");
        }
    }
}

void cntVote(struct voter *startVoter, struct participant *startParticipant){
    struct voter *currentVoter = startVoter;
    struct participant *currentParticipant = startParticipant;
    while (currentVoter != NULL){
        currentVoter->vote = 0;
        while (currentParticipant != NULL){
            if (currentParticipant->vote == currentVoter->id){
                currentVoter->vote++;
            }
            currentParticipant = currentParticipant->next;
        }
        currentVoter = currentVoter->next;
    }
}

void sortNodes(){
    struct participant *current = startParticipant, *index = NULL;
    int tempID, tempVOTE;
    char tempNAME[20];

    if (startParticipant == NULL){
        return;
    }else{
        while (current != NULL){
            index = current->next;
            while (index != NULL){
                //swap
                if (current->vote > index->vote){
                    tempID = current->id;
                    current->id = index->id;
                    index->id = tempID;

                    tempVOTE = current->vote;
                    current->vote = index->vote;
                    index->vote = tempVOTE;

                    strcpy(tempNAME, current->name);
                    strcpy(current->name, index->name);
                    strcpy(index->name, tempNAME);
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

// void sort(struct node **h){
//     int a, b, c;
//     char t[20];
//     struct node *temp1;
//     struct node *temp2;
//     for (temp1 = *h; temp1 != NULL; temp1 = temp1->next){
//         for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next){
//             a = temp1->data;
//             temp1->data = temp2->data;
//             temp2->data = a;
//             c = temp1->vote;
//             temp1->vote = temp2->vote;
//             temp2->vote = c;
//             strcpy(t, temp1->name);
//             strcpy(temp1->name, temp2->name);
//             strcpy(temp2->name, t);
//         }
//     }
// }

struct voter *copyList(struct node *voter){ // to take top 3 singer acc to data
    int count = 0;
    struct voter *current = startVoter; // used to iterate over the original list
    struct voter *newList = NULL; // head of the new list
    struct voter *tail = NULL;    // point to the last node in a new list

    while (current != NULL && count != 3){
        if (newList == NULL){
            newList = (struct voter *)malloc(sizeof(struct voter));
            strcpy(newList->name, current->name);
            newList->id = current->id;
            newList->next = NULL;
            tail = newList;
        }else{
            tail->next = (struct voter *)malloc(sizeof(struct voter));
            tail = tail->next;
            tail->id = current->id;
            strcpy(tail->name, current->name);
            tail->next = NULL;
        }
        current = current->next;
        count++;
    }
    return newList;
}

int main(){
    printf("\n\t\tWelcome Applicants");
    admin_Participant();
    sortNodes();
    printf("\nWelcome to the Audience Applicants");
    admin_Voter();
    cntVote(startVoter, startParticipant);
    sortNodes();
    struct participant *cpy = copyList(startVoter);
    top3(cpy);
    printf("\nWinner of the day goes to");
    printf("\n\t\t%d", cpy->id);
    printf("\n\t\t%s", cpy->name);
    printf("\nthank you");
    return 0;
}