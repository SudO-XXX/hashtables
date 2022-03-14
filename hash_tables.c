
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
struct student{
    char name[30];
    int ID;
    int date[3];//day-mounth-year
    int score;
};
struct node{
    struct student * s ;
    struct node* next ;
};
struct hashtableop{
  int size;
  struct node*arr;
};
struct hashtable{
  int size;
  int consumed;
  struct student** arr;
};
//closed hashing 
//creat hashtable with size nodes
struct hashtable* creat(int size);

//search for an element with date of birth a[3] using linear probing.
int search(struct hashtable * h,int a[]);

//search for a student using qudratic probing.
int searchQ(struct hashtable*h,int a[]);

//hashing function for the name of the student.
int hashing(struct hashtable*h,int a[3]);

//compares to arrays of the same size.
int cmparr(int *a1,int *a2,int n);

//insert a student in a hashtable using linear probing.
int insert(struct hashtable * h,struct student*s);

//insert a student in hashtable using quadratic probing.
int insertQ(struct hashtable*h,struct student*s);

//delete a student from a hashtable using linear probing.
int deletnode(struct hashtable*h,int a[3]);

//delete a student from a hashtable using quadratic probing.
int deletnodeQ(struct hashtable*h,int a[3]);

//Calculates the time and performance of n random insertions using linear probing.
void timer(int n,int size);

//calculates the time and performance of n random insertions using quadratic probing.
void timerQ(int n,int size);

//intialize linear probing program.
void linear();

//initialize quadratic probing program.
void quadratic();

//print the closed hashing hashtable
void printht(struct hashtable * h);


//open hashing
//create a open hashing hashtable.
struct hashtableop * createop(int size);

//fill an array d with the date for search and delete.
void filldate(int d[]);

//hashing function for the name.
int hashingop(char* str,struct hashtableop * h);

//insert a student to the hashtable.
void insertop(struct student * s , struct hashtableop * h);

//search for a student structure in the hashtable by name.
struct node * searchbyName(char rat[],struct hashtableop *h);

//delte a student structure by name.
void delete(char * rat, struct hashtableop * h);

//interact with user to find the time of insertion, size and performance.
void timer_menuop();

//calculates the time of insertion, size and performance.
void timerop(int n,int size);

//create random string with k: the number of characters in the array.
void randomize(struct student * s,int k);

//diplay a node in the hashtable.
void dispnode(struct student *ptr);

//start a program for the closed hashing.
void closed_hashing();

//start open hashing program with actual values.
void open_hashing();

//main menu.
void choose();

//print open hashing hashtable.
void printhtop(struct hashtableop * h);

//fill student from screen.
struct student * fillstudent();

//print student name and ID on the screen.
void printstd(struct student * std);

//start the open hashing program
void menuop(struct hashtableop * h);

int main(){
    choose();

  //minue(h);

  return 0;
}
struct hashtableop * createop(int size){
    struct hashtableop * h = (struct hashtableop*)malloc(sizeof(struct hashtableop));
    h->size = size;
    h->arr = (struct node*)malloc(size * sizeof(struct node));
    return h;
}

void insertop(struct student * s , struct hashtableop * h){
  struct node * n = (struct node *)malloc(sizeof(struct student));
  n->s = s;
  int index = hashingop(n->s->name,h);
  if(h->arr[index].s==NULL)
    h->arr[index] = *n;
  else{
    struct node * t = &(h->arr[index]);
    while(t->next != NULL)
      t = t->next;
    t->next = n;
  }
  return;
}

void printhtop(struct hashtableop * h){
    struct node * n ;
    for(int i = 0;i<h->size;i++){
      n = &(h->arr[i]);
      printf("%d: ",i);
      if(n->s == NULL){
        printf("\n");
        continue;
      }
      else
        printstd(n->s);
      n = n->next;
      while(n != NULL){
        printf("->");
        printstd(n->s);
        n = n->next;
      }
      printf("\n");
    }
}

struct node * searchbyName(char rat[],struct hashtableop * h){
  int index = hashingop(rat,h);
  struct node * n = &(h->arr[index]);
  if(n->s == NULL)
    return NULL;
  while(n != NULL){
    if(!strcmp(n->s->name, rat))
      return n;
    n = n->next;
  }
  return n;
}

//djb2 hashing algorithm
int hashingop(char * str,struct hashtableop * h){
     unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash % h->size;
}

void delete(char * rat, struct hashtableop* h){
  int index = hashingop(rat,h);
  struct node * n = &(h->arr[index]);
  struct node * t = n->next;
  if(n->s ==NULL)
    return;
  else if(!strcmp(n->s->name,rat)){
    if(t==NULL)
    n->s = NULL;
    else
    *n = *t;
    free(t);
  }
  else
    while(t!=NULL){
      if(!strcmp(t->s->name, rat)){
        *n = *t;
        free(t);
        return;
      }
      t=t->next;
      n=n->next;
    }
  return;
}

void printstd(struct student * std){
    printf("%s  ",std->name);
    printf("%d  ",std->ID);
}


void menuop(struct hashtableop * h){
  int a;
  char rat[30];
  printf("define the size of the hashtable: ");
  scanf("%d",&(h->size));
  h->arr = (struct node *)malloc(h->size * sizeof(struct node));
  int v=0,f;
  while(1){
  system("clear");
  printf("Welcome to the hunger games...\n\nplease enter your choice form below:\n\n1:insert an element in the hashtable\n2:delete an element in the hashtable\n3:search for an element\n4:size of current table\n\n>>");
  scanf("%d",&a);
  system("clear");
  getchar();
  switch(a){
    case 1:
      insertop(fillstudent(),h);
      v++;
      printf("number of nodes: %d\n\n",v);
      printhtop(h);
      break;
    case 3:
      printf("name>> ");
      gets(rat);
      struct node *n = searchbyName(rat,h);
      if(n != NULL){
        printstd(n->s);
        printf("\n");
      }
      else
        printf("notfound\n");
      break;
    case 2:
      printf("name>> ");
      gets(rat);
      delete(rat,h);
      v--;
      printhtop(h);
      break;
    case 4:
        f = sizeof(struct student)+sizeof(struct node*);
        printf("the size of a single node: %d bytes\n\n",f);
        printf("size of the current table: %d bytes\n\n",v*f);
        break;
    default:
      printf("invalid input.\n");
  }
  printf("press any key to continue...");
  getchar();
  }
}

void timerop(int n,int size){
  srand(time(0));
  struct hashtableop * h = createop(size);
  clock_t sec,def = 0;
  for(int i = 0;i<n;i++){
    struct student * s = (struct student*)malloc(sizeof(struct student));
    randomize(s,15);
    sec = clock();
    insertop(s,h);
    def = clock() -sec;

  }
    printhtop(h);
    printf("-----------------------------------\n");
    double t = (double)def/CLOCKS_PER_SEC / n;
    int byte = n*sizeof(struct student);
    printf("excution time is:%.12lf\n\n",t);
    printf("size of table: %d bytes\n\n",n*sizeof(struct student));
    printf("performance: %lf x10^-6\n\n",1000000*t*n/byte);
}

void randomize(struct student * s,int k){
  for(int i = 0;i<k;i++)
    s->name[i] = rand()%59+65;
  s->ID = rand()/1000000;
    }

void choose(){
  char m;
   printf("1:open hashing\n2:closed hashing\n");
    scanf("%c",&m);
    getchar();
    switch(m){
        case '1':
            open_hashing();
            break;
        case '2':
            closed_hashing();
            break;

    }
}

void timer_menuop(){
    int n,size;
    char choice;
    printf("enter the number insertions: ");
    scanf("%d",&n);
    printf("enter number of slots in the hashtable: ");
    scanf("%d",&size);
    getchar();
    timerop(n,size);
    getchar();
}

void open_hashing(){
char m;
struct hashtableop *h = (struct hashtableop*)malloc(sizeof(struct hashtableop));
   printf("1:create table\n2:Calculate time, size and performance\n");
    scanf("%c",&m);
    getchar();
    switch(m){
        case '1':
            menuop(h);
            break;
        case '2':
            timer_menuop();
            break;
    }
   }

struct hashtable* creat(int size){
    struct hashtable * h = (struct hashtable *)malloc(sizeof(struct hashtable));
    h->size = size;
    h->consumed = 0;
    h->arr = (struct student**)malloc(size * sizeof(struct student*));
    return h;
}

void dispnode(struct student *ptr)
{
    printf("the name is : %s\t", ptr->name);
    printf("the ID is : %d  ", ptr->ID);
    printf("the last score is : %d  ", ptr->score);
    printf("the date of birth is : %d  %d  %d", ptr->date[0], ptr->date[1], ptr->date[2]);
}

//hashing function.
//takes the pointer to the hashtable and the date of birth as input.
int hashing(struct hashtable*h,int a[3]){
    return (a[0]+a[1]+a[2])%h->size;
}

//Compares two array of the same length.
int cmparr(int *a1,int *a2,int n){
    for(int i = 0;i<n;i++)
        if(a1[i]!=a2[i])
            return 0;
    return 1;
}

//fills the data of a new student structure.
struct student * fillstudent(){
    struct student * node=(struct student*)malloc(sizeof(struct student));
    printf("filling the  slot in the table\n");
    printf("Enter the name :");
    gets(node->name);//store a string till a new line charcter entered.
    printf("Enter the ID :");
    scanf("%d", &(node->ID));
    printf("Enter the last score :");
    scanf("%d", &(node->score));
    printf("Enter the date of birth :\n1st no.is year >>");
    scanf("%d", &(node->date[0]));
    printf("2nd is month>>");
    scanf("%d", &(node->date[1]));
    printf("third is day>>");
    scanf("%d", &(node->date[2]));
    getchar();//ignore last charcter in the stream stdin.
    return node;
}

//fills the date of a student to use it in search or delete.

void filldate(int d[]){
    printf("Enter the date of birth :\n1st no.is year >>");
    scanf("%d", d);
    printf("2nd is month>>");
    scanf("%d", d+1);
    printf("third is day>>");
    scanf("%d", d+2);
    getchar();
}
void printht(struct hashtable * h){
    for(int i = 0;i<h->size;i++){
        printf("%d: ",i);
        if(h->arr[i]!=NULL){
            if(h->arr[i]->ID != -1)
                dispnode(h->arr[i]);
        }
        printf("\n");
    }
}

int search(struct hashtable * h,int a[]){
    int index = hashing(h,a);
    //printf("index:%d\n\n",index);
    if(h->arr[index]==NULL)
        return -1;//invalid index.
    //int i = index;
    for(int k = 0;k<h->size&&h->arr[index]!=NULL;k++){
        if(h->arr[index]->ID==-1)
            index=(index+1)%h->size;
        if(cmparr(h->arr[index]->date,a,3))
            return index;
        index=(index+1)%h->size;
    }
    return -1;//not found;
}

int searchQ(struct hashtable*h,int a[]){
    int index = hashing(h,a);
    if(h->arr[index]==NULL)
        return -1;//invalid index.
    int i = index;
    for(int k = 1;k<=h->size&&h->arr[index]!=NULL;k++){
        if(h->arr[index]->ID==-1)
            index=(i+k*k)%h->size;
        if(cmparr(h->arr[index]->date,a,3))
            return index;
        index=(i+k*k)%h->size;
    }
    return -1;//not found;
}

//insert a student structure in the hashtable.
//the hashtable should have free or deleted places.
//before insertion.
int insert(struct hashtable * h,struct student*s){
    int index = hashing(h,s->date);
    for(int i = 0;i<h->size&&h->arr[index]!=NULL;i++){
        if(h->arr[index]->ID==-1){
            struct student *temp = h->arr[index];
            h->arr[index]=s;
            free(temp);
            return 1;
        }
        index=(index+1)%h->size;
    }
    if(h->arr[index]==NULL){
        h->arr[index] = (struct student*)malloc(sizeof (struct student));
        h->arr[index] = s;
        return 1;
    }
    return 0;//full hashtable.
}

int insertQ(struct hashtable*h,struct student*s){
    if(h->consumed==h->size)
        return 0;
    int index = hashing(h,s->date);
    int k = index;
    for(int i = 1;i<=h->size&&h->arr[index]!=NULL;i++){
        if(h->arr[index]->ID==-1){
            struct student *temp = h->arr[index];
            h->arr[index]=s;
            free(temp);
            h->consumed++;
            return 1;
        }
        index=(k+i*i)%h->size;
    }
    if(h->arr[index]==NULL){
        h->arr[index] = (struct student*)malloc(sizeof (struct student));
        h->arr[index] = s;
        h->consumed++;
        return 1;
    }
    return 0;//full hashtable
}

int deletnode(struct hashtable*h,int a[3]){
    int index = search(h,a);
    if(index != -1){
        h->arr[index]->ID = -1;
        return 1;
    }
    return 0;
}

int deletnodeQ(struct hashtable*h,int a[3]){
    int index = searchQ(h,a);
    if(index != -1){
        h->arr[index]->ID = -1;
        h->consumed--;
        return 1;
    }
    return 0;
}

void linear(){
    int choice,a[3];
    struct student*k;
    clock_t sec,def;
    printf("Enter the numbere of places of the hashtable: ");
    scanf("%d",&choice);
    printf("the size of the structure is: %d bytes\n\n",sizeof(struct student));
    printf("the size of the hastable: %d bytes\n\n",choice*sizeof(struct student));
    struct hashtable*h= creat(choice);
    while(1){
        printf("\n1:insert\n2:search\n3:delete\n\n>>");
        scanf("%d",&choice);
        getchar();

        switch(choice){
            //insert
            case 1:
                if(!insert(h,fillstudent()))
                    printf("full hashtable!\n\n");
                break;
            //search
            case 2:
                filldate(a);
                choice = search(h,a);
                if(choice == -1)
                    printf("notfound!\n");
                else
                    dispnode(h->arr[choice]);
                printf("\n");
                break;
            //delete
            case 3:
                filldate(a);
                if(deletnode(h,a))
                    printf("deleted!!\n\n");
                else
                    printf("not found!\n\n");
                break;
        }
        printht(h);
    }
}

void quadratic(){
    int choice,a[3];
    struct student*k;
    printf("Enter the numbere of places of the hashtable: ");
    scanf("%d",&choice);
    printf("the size of the structure is: %d bytes\n\n",sizeof(struct student));
    printf("the size of the hastable: %d bytes\n\n",choice*sizeof(struct student));
    struct hashtable*h= creat(choice);
    while(1){
        printf("\n1:insert\n2:search\n3:delete\n\n>>");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            //insert
            case 1:
                if(!insertQ(h,fillstudent()))
                    printf("insetion failed!\n\n");
                break;
            //search
            case 2:
                filldate(a);
                choice = searchQ(h,a);
                if(choice == -1)
                    printf("notfound!\n");
                else
                    dispnode(h->arr[choice]);
                printf("\n");
                break;
            //delete
            case 3:
                filldate(a);
                if(deletnodeQ(h,a))
                    printf("deleted!!\n\n");
                else
                    printf("not found!\n\n");
                break;
        }
        printht(h);
    }
}

void timer(int n,int size){
    srand(time(0));
    struct hashtable * h = creat(size);
    clock_t sec,def = 0;
    for(int i=0;i<n;i++){
        struct student * s = (struct student*)malloc(sizeof(struct student));
        s->date[0] = rand()%2003;
        s->date[1] = rand()%13;
        s->date[2] = rand()%31;
        sec = clock();
        if(insert(h,s))
            def += clock() - sec;
    }
    printht(h);
    printf("-----------------------------------\n");
    double t = (double)def/CLOCKS_PER_SEC / n;
    int byte = n*sizeof(struct student);
    printf("excution time is:%.12lf\n\n",t);
    printf("size of table: %d bytes\n\n",n*sizeof(struct student));
    printf("performance: %lf x10^-6\n\n",1000000*t*n/byte);
}

void timerQ(int n,int size){
    srand(time(0));
    struct hashtable * h = creat(size);
    clock_t sec,def = 0;
    int k=0;
    for(int i=0;i<n;i++){
        struct student * s = (struct student*)malloc(sizeof(struct student));
        s->date[0] = rand()%2003;
        s->date[1] = rand()%13;
        s->date[2] = rand()%31;
        sec = clock();
        if(insertQ(h,s)){
            def += clock() - sec;
            k++;
        }

    }
    printht(h);
    printf("-----------------------------------\n\n");
    double t = (double)def/CLOCKS_PER_SEC / n;
    int byte = k*sizeof(struct student);
    printf("excution time is:%.12lf\n\n",t);
    printf("size of table: %d bytes\n\n",k*sizeof(struct student));
    printf("performance: %lf x10^-6\n\n",1000000*t*k/byte);
}

void closed_hashing(){
    char choice;
    int n,size;
    printf("1:linear probing\n2:quadratic probing\n3:calculating avarage time,size and performance\n\n>>");
    scanf("%c",&choice);
    switch(choice){
        case '1':
            linear();
            break;
        case '2':
            quadratic();
            break;
        case '3':
            printf("enter the number insertion: ");
            scanf("%d",&n);
            printf("enter number of slots in the hashtable: ");
            scanf("%d",&size);
            getchar();
            printf("1:quadratic\n2:linear\n\n>>");
            scanf("%c",&choice);
            getchar();
            switch(choice){
                case '1':
                    timerQ(n,size);
                    break;
                case '2':
                    timer(n,size);
                    break;
            }
    }
}