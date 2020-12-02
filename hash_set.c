

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_INT 101

// STRUCTURE DEFINITIONS
typedef struct element_tag{
    char *data;
    struct element_tag *next;
}   element;

typedef struct key_tag{
    int count;
    element *e;
}   key;

typedef struct set_tag{
    int cardinality;
    key Bucket[MAX_INT];
}   set;

// FUNCTION DECLARATIONS
int get_set();
int hash_key(char *s);
element *create_element(char *s);
set *create_set(set *x);
int is_empty(set *x);
int size(set *x);
set *add(set *x, char *s);
void remov(set *x, char *s);
set *add_hash(set *x, char *s, int hash);
set *sets_union(set *x, set *y);
set *sets_intersection(set *x, set *y);
set *sets_difference(set *x, set *y);
int is_subset(set *x, set *y);
void enumerate(set *x);
set *build(set *x, char **s, int siz);
int is_element_of(set *x, char *s);
int is_subset(set *x, set *y);

void main()
{
    FILE *fp;
    set *a,*b,*union_ab,*intersection_ab,*difference_ab;
    
    // Create set 'a':
    fp = fopen("seta.txt","r");
    char *s[100];
    int i=0;
    for(i=0;i<100;i++)
    {
        s[i] = (char*)malloc(sizeof(char)*15);
    }
    for(i=0;i<6;i++)
    {
        fscanf(fp,"%s",s[i]);
    }
    printf("Building set A....\n");
    a = build(a, s, i);
    printf("Set A created successfully!\n");
    fclose(fp);

    // Create set 'b':
    fp = fopen("setb.txt","r");
    char *(k[15]);
    for(i=0;i<100;i++)
    {
        k[i] = (char*)malloc(sizeof(char)*15);
    }
    i=0;
    for(i=0;i<3;i++)
    {
        fscanf(fp,"%s",k[i]);
    }
   
    printf("Building set B....\n");
    b = build(b, k, i);
    printf("Set B created successfully!\n");
    fclose(fp);

    int input, exit=0, temp, ans;
    char *str;
    while(exit==0)
    {
        printf("Enter the required function number:\n1. Check if set is empty\n2. Know the size of set\n3. Print the elements of set\n4. Check if an element is present in set\n5. Add an element\n6. Remove an element\n7. Check if a set is subset of the other\n8. Create union of sets\n9. Create intersection of sets\n10. Create difference of sets\n11. Exit\n");
        scanf("%d",&input);
        switch(input)
        {
            case 1: temp = get_set();
                    
                    if(temp == 1){ans = is_empty(a);}
                    else{ans = is_empty(b);}
                    
                    if(ans==1){printf("Yes!\n");}
                    else{printf("No!\n");}
                    break;

            case 2: temp = get_set();
                    
                    if(temp == 1){ans = size(a);}
                    else{ans = size(b);}
                    printf("The set contains %d elements.\n",ans);
                    break;

            case 3: temp = get_set();
                    
                    if(temp == 1){enumerate(a);}
                    else{enumerate(b);}
                    break;

            case 4: temp = get_set();
                    
                    printf("Enter the element: ");
                    scanf("%s",str);
                    if(temp == 1){ans = is_element_of(a, str);}
                    else{ans = is_element_of(b, str);}

                    if(ans==1){printf("Yes!\n");}
                    else{printf("No!\n");}
                    break;

            case 5: temp = get_set();
                    
                    printf("Enter the element: ");
                    scanf("%s",str);
                    if(temp == 1){add(a, str);}
                    else{add(b, str);}
                    break;

            case 6: temp = get_set();
                    
                    printf("Enter the element: ");
                    scanf("%s",str);
                    if(temp == 1){remov(a, str);}
                    else{remov(b, str);}
                    break;

            case 7: temp = get_set();
                    
                    if(temp == 1){ans = is_subset(a, b);}
                    else{ans = is_subset(b, a);}

                    if(ans==1){printf("Yes!\n");}
                    else{printf("No!\n");}
                    break;

            case 8: union_ab = sets_union(a,b);
                    enumerate(union_ab);
                    break;

            case 9: intersection_ab = sets_intersection(a,b);
                    enumerate(intersection_ab);
                    break;

            case 10:printf("1. A-B\n2. B-A\n");
                    scanf("%d",&temp);
                    
                    if(temp == 1){ difference_ab = sets_difference(a,b);}
                    else{difference_ab = sets_difference(b,a);} 
                    enumerate(difference_ab);
                    break;

            case 11: exit = 1;
                     break;

            default: printf("Enter valid input!\n");
                     break;
        }
    }

}

// FUNCTION DEFINITIONS

// Returns the selected set
int get_set()
{
    int i;
    printf("Select:\n1. set A\n2. set B\n");
    scanf("%d",&i);
    return i;
}
// Returns the hash-key for the data
int hash_key(char *s)
{
    int i=0,num=0;
    while(s[i]!='\0')
    {
        num+=(s[i] - 'a');
        i++;
    }
    num %= MAX_INT;
    return num;
}

// Creates and returns an element node
element *create_element(char *s)
{
    element *el;
    el = (element*)malloc(sizeof(element));
    el->data = (char*)malloc(sizeof(char)*15);
    strcpy(el->data, s);
    el->next = NULL;
    return el;
}

// Creates an empty set
set *create_set(set *x)
{
    x = (set*)malloc(sizeof(set));
    int i=0;
    x->cardinality = 0;
    for(i=0;i<MAX_INT;i++)
    {
        x->Bucket[i].count = 0;
        x->Bucket[i].e = NULL;
    }
    printf("Empty set created!\n");
    return x;
}

// Checks if set is empty (1->empty)
int is_empty(set *x)
{
    if(x->cardinality == 0)
    {
        return 1;
    }
    return 0;
}

// Returns the size of set
int size(set *x)
{
    return (x->cardinality);
}

// Adds an element to set if not already present
set *add(set *x, char *s)
{
    int hashKey = hash_key(s);
    printf("Hash key : %d\n",hashKey);
    element *new,*head,*ptr = x->Bucket[hashKey].e;
    head = ptr;
    while((ptr!=NULL)&&(strcmp(ptr->data, s)!=0))
    {
        ptr = ptr->next;
    }
    
    if(ptr==NULL)   // If element is not already present
    {
        new = create_element(s);
        new->next = head;
        x->Bucket[hashKey].e = new;
        (x->Bucket[hashKey].count)++;
        (x->cardinality)++;
        printf("The element %s has been added!\n",s);
    }
    else
    {
        printf("The element %s is already present!\n",s);
    }
    return x;
}

// Removes an element if already present
void remov(set *x, char *s)
{
    element *prev=NULL,*ptr;
    int hashKey = hash_key(s);
    ptr = x->Bucket[hashKey].e;
    if(ptr!=NULL) // Key is not empty
    {
        if(strcmp(s, ptr->data)) // 1st element is not the data
        {
            prev = ptr;
            ptr = ptr->next;
            while((ptr!=NULL)&&(strcmp(s, ptr->data)))
            {
                prev = ptr;
                ptr = ptr->next;
            }
            if(ptr!=NULL) // Element is found
            {
                prev->next = ptr->next;
                free(ptr);
                (x->Bucket[hashKey].count)--;
                (x->cardinality)--;
                printf("The elment has been removed successfully!\n");
            }
            else
            {
                printf("The element %s is not found!\n",s);
            }
            
        }
        else    // 1st element is the required data
        {
            x->Bucket[hashKey].e = ptr->next;
            free(ptr);
            x->Bucket[hashKey].count--;
            x->cardinality--;
            printf("The elment has been removed successfully!\n");
        }
    }
    else // The key is empty
    {
        printf("The element %s is not found!\n",s);        
    }
}

// Adds element when key is already known
set *add_hash(set *x, char *s, int hash)
{
    element *new,*head,*ptr = x->Bucket[hash].e;
    head = ptr;
    while((ptr!=NULL)&&(strcmp(ptr->data, s)!=0))
    {
        ptr = ptr->next;
    }
    if(ptr==NULL)   // If element is not already present
    {
        new = create_element(s);
        new->next = head;
        x->Bucket[hash].e = new;
        (x->Bucket[hash].count)++;
        (x->cardinality)++;
        printf("The element %s has been added!\n",s);
    }
    return x;
}

// Creates union of two sets x and y
set *sets_union(set *x, set*y)
{
    set *u, *inter;
    element *p_x,*p_inter;
    int i=0;
    u = create_set(u);

    // Copy whole set X to set U
    for(i=0;i<MAX_INT;i++)
    {
        p_x = x->Bucket[i].e;
        
        while(p_x!=NULL)
        {
            u = add_hash(u, p_x->data, i);
            p_x = p_x->next;
        }
    }
    
    // Create (Y-X)
    inter = sets_difference(y, x);
    // Append elements of (Y-X) to U
    for(i=0;i<MAX_INT;i++)
    {
        p_inter = inter->Bucket[i].e;
        
        while(p_inter!=NULL)
        {
            u = add_hash(u, p_inter->data, i);
            p_inter = p_inter->next;
        }
    }
    printf("Union created successfully!\n");
    return u;
}

// Creates intersection of two sets x and y
set *sets_intersection(set *x, set *y)
{
    set *u;
    element *px,*py;
    u = create_set(u);
    int i=0,j=0,k=0;
    for(i=0;i<MAX_INT;i++)
    {
        px = x->Bucket[i].e;
        py = y->Bucket[i].e;
        for(j=0;j<(x->Bucket[i].count);j++)
        {
            py = y->Bucket[i].e;
            for(k=0;k<(y->Bucket[i].count);k++)
            {
                if(strcmp(px->data, py->data)==0)
                {
                    u = add_hash(u, px->data, i);
                    break;
                }
                py = py->next;
            }
            px = px->next;
        }
    }
    printf("Intersection created successfully!\n");
    return u;
}

// Creates difference of two sets x and y
set *sets_difference(set *x, set *y)
{
    set *u;
    element *px,*py;
    u = create_set(u);
    int i=0,j=0,k=0,flag=0;
    for(i=0;i<MAX_INT;i++)
    {
        px = x->Bucket[i].e;
        py = y->Bucket[i].e;
        for(j=0;j<(x->Bucket[i].count);j++)
        {
            flag = 0;
            py = y->Bucket[i].e;
            for(k=0;k<(y->Bucket[i].count);k++)
            {
                if(strcmp(px->data, py->data)==0)
                {
                    flag = 1;
                    break;
                }
                py = py->next;
            }

            if(flag==0)
            {
                u = add_hash(u, px->data, i);
            }

            px = px->next;
        }
    }
    printf("Difference created successfully!\n");
    return u;
}

// Prints the elements of the set
void enumerate(set *x)
{
    int i=0;
    element *ptr;
    printf("The %d elements of set are:\n",x->cardinality);
    for(i=0;i<MAX_INT;i++)
    {
        ptr = x->Bucket[i].e;
        while(ptr!=NULL)
        {
            printf("%s\n",ptr->data);
            ptr = ptr->next;
        }
    }
}

// Builds set by taking all values at a time
set *build(set *x, char **s, int siz)
{
    int i=0;
    x = create_set(x);
    for(i=0;i<siz;i++)
    {
        x = add(x, s[i]);
    }
    return x;
}

// Checks whether s is an element of set x
int is_element_of(set *x, char *s)
{
    element *px;
    int retval=1,flag=0;
    int hashKey = hash_key(s);
    px = x->Bucket[hashKey].e;
    while((flag==0)&&(px!=NULL))
    {
        if(strcmp(px->data, s)==0)
        {
            flag = 1;
        }
        px = px->next;
    }
    if(flag==0)
    {
        retval = 0;
    }
    return retval;
}

// Checks whether x is a subset of y
int is_subset(set *x, set *y)
{
    int retval=1,flag=0;
    element *px;
    int i=0,j=0;
    if(x->cardinality <= y->cardinality)
    {
        for(i=0;(i<MAX_INT)&&(flag==0);i++)
        {
            if((x->Bucket[i].count) <= (y->Bucket[i].count))
            {
                px = x->Bucket[i].e;
                for(j=0;j<(x->Bucket[i].count);j++)
                {
                    if(is_element_of(y, px->data)==1)
                    {
                        px = px->next;
                    }
                    else
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            else
            {
                flag = 1;
            }
        }
    }
    else
    {
        flag=1;
    }
    
    if(flag == 1)
    {
        retval = 0;
    }
    return retval;
}