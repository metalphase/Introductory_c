#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXWORD 100

struct wordcount
{
    char *word;
    int count;

    struct wordcount *higher;
    struct wordcount *lower;
};

struct decreasing_count
{
    char *word;
    int count;

    struct decreasing_count *next;
};



char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void);
void ungetch1(int);
int getword(char *word, int lim);


// wordcount functions
void printlist(struct wordcount *head);
struct wordcount *search(struct wordcount *head, char *search_word);
struct wordcount *create_node(char *word);
void delete(struct wordcount *head);
void insert(struct wordcount **head, char *insert_word);

// decreasing_count functions
struct decreasing_count *create_decreasing_count_node(char *word, int count);
void print_decreasing_count_list(struct decreasing_count **head);
void insert_decreasing_count_node(struct decreasing_count **head, struct decreasing_count *new_node);
void delete_decreasing_count_list(struct decreasing_count **head);
void binary_to_decreasing_list(struct wordcount *binary_head, struct decreasing_count **decreasing_head);

// Tests

void test1()
{
    // testing decreasing_count structure
    printf("Test 1\n");
    char word[10] = "testing";
    int count = 2;

    struct decreasing_count count_1;
    count_1.count = count;
    count_1.word = &word[0];
    count_1.next = NULL;

    if(count_1.word != NULL)
    {
        printf("%s: %d\n", count_1.word, count_1.count);
        printf("Success\n");
    }
    printf("\n");
}

void test2()
{
    // testing create_decreasing_count_node structure
    printf("Test 2\n");
    char word[10] = "testing";
    int count = 2;

    struct decreasing_count *count_1;
    count_1 = create_decreasing_count_node(&word[0], count);

    if(count_1->word != NULL)
    {
        printf("%s: %d\n", count_1->word, count_1->count);
        printf("Success\n");
    }
    printf("\n");
}

void test3()
{
    // testing create_decreasing_count_node structure
    printf("Test 3\n");
    char word1[10] = "apple";
    char word2[10] = "baby";

    int count1 = 2;
    int count2 = 4;

    struct decreasing_count *dc_1;
    struct decreasing_count *dc_2;
    
    dc_1 = create_decreasing_count_node(&word1[0], count1);
    dc_2 = create_decreasing_count_node(&word2[0], count2);
    dc_1->next = dc_2;

    if(dc_1->word != NULL && dc_2->word != NULL)
    {
        printf("%s: %d\n", dc_1->word, dc_1->count);
        printf("%s: %d\n", dc_1->next->word, dc_1->next->count);
        printf("Success\n");
    }
    printf("\n");
}

void test4()
{
    // testing print_decreasing_count_list
    printf("Test 4\n");
    char word1[10] = "apple";
    char word2[10] = "baby";
    char word3[10] = "candy";
    char word4[10] = "potato";
    char word5[10] = "ore";

    int count1 = 2;
    int count2 = 4;
    int count3 = 5;
    int count4 = 8;
    int count5 = 7;

    struct decreasing_count *dc_1;
    struct decreasing_count *dc_2;
    struct decreasing_count *dc_3;
    struct decreasing_count *dc_4;
    struct decreasing_count *dc_5;
    
    dc_1 = create_decreasing_count_node(&word1[0], count1);
    dc_2 = create_decreasing_count_node(&word2[0], count2);
    dc_3 = create_decreasing_count_node(&word3[0], count3);
    dc_4 = create_decreasing_count_node(&word4[0], count4);
    dc_5 = create_decreasing_count_node(&word5[0], count5);

    dc_1->next = dc_2;
    dc_2->next = dc_3;
    dc_3->next = dc_4;
    dc_4->next = dc_5;

    print_decreasing_count_list(&dc_1);
    printf("\n");
}

void test5()
{
    // testing insert_decreasing_count_node
    printf("Test 5\n");
    char word1[10] = "apple";

    int count1 = 2;

    struct decreasing_count *dc_1;
    struct decreasing_count *head = NULL;

    dc_1 = create_decreasing_count_node(&word1[0], count1);
    insert_decreasing_count_node(&head, dc_1);
    
    print_decreasing_count_list(&head);
    printf("\n");
} 


void test6()
{
    // testing insert_decreasing_count_node
    printf("Test 6\n");
    char word1[10] = "apple";
    char word2[10] = "baby";

    int count1 = 2;
    int count2 = 4;

    struct decreasing_count *dc_1;
    struct decreasing_count *dc_2;
    struct decreasing_count *head = NULL;

    dc_1 = create_decreasing_count_node(&word1[0], count1);
    dc_2 = create_decreasing_count_node(&word2[0], count2);

    insert_decreasing_count_node(&head, dc_1);
    print_decreasing_count_list(&head);
    printf("\n");

    insert_decreasing_count_node(&head, dc_2);
    print_decreasing_count_list(&head);
    printf("\n");
}

void test7()
{
    // testing insert_decreasing_count_node
    printf("Test 7\n");
    char word1[10] = "apple";
    char word2[10] = "baby";
    char word3[10] = "candy";
    int count1 = 2;
    int count2 = 4;
    int count3 = 5;
    
    struct decreasing_count *dc_1;
    struct decreasing_count *dc_2;
    struct decreasing_count *dc_3;
    struct decreasing_count *head = NULL;

    dc_1 = create_decreasing_count_node(&word1[0], count1);
    dc_2 = create_decreasing_count_node(&word2[0], count2);
    dc_3 = create_decreasing_count_node(&word3[0], count3);

    insert_decreasing_count_node(&head, dc_1);
    print_decreasing_count_list(&head);
    printf("\n");

    insert_decreasing_count_node(&head, dc_2);
    print_decreasing_count_list(&head);
    printf("\n");

    insert_decreasing_count_node(&head, dc_3);
    print_decreasing_count_list(&head);
    printf("\n");
}

void test8()
{
    // testing insert_decreasing_count_node
    printf("Test 8\n");
    char word1[10] = "apple";
    char word2[10] = "baby";
    char word3[10] = "candy";
    char word4[10] = "potato";
    char word5[10] = "ore";

    int count1 = 2;
    int count2 = 4;
    int count3 = 5;
    int count4 = 3;
    int count5 = 7;

    struct decreasing_count *dc_1;
    struct decreasing_count *dc_2;
    struct decreasing_count *dc_3;
    struct decreasing_count *dc_4;
    struct decreasing_count *dc_5;
    struct decreasing_count *head = NULL;

    dc_1 = create_decreasing_count_node(&word1[0], count1);
    dc_2 = create_decreasing_count_node(&word2[0], count2);
    dc_3 = create_decreasing_count_node(&word3[0], count3);
    dc_4 = create_decreasing_count_node(&word4[0], count4);
    dc_5 = create_decreasing_count_node(&word5[0], count5);

    insert_decreasing_count_node(&head, dc_1);
    print_decreasing_count_list(&head);
    printf("\n");
    
    insert_decreasing_count_node(&head, dc_2);
    print_decreasing_count_list(&head);
    printf("\n");

    insert_decreasing_count_node(&head, dc_3);
    print_decreasing_count_list(&head);
    printf("\n");

    insert_decreasing_count_node(&head, dc_4);
    print_decreasing_count_list(&head);
    printf("\n");

    insert_decreasing_count_node(&head, dc_5);
    print_decreasing_count_list(&head);
    printf("\n");
}

void test9()
{
    // testing delete_decreasing_count_list
    printf("Test 9\n");
    char word1[10] = "apple";
    char word2[10] = "baby";
    char word3[10] = "candy";
    char word4[10] = "potato";
    char word5[10] = "ore";

    int count1 = 2;
    int count2 = 4;
    int count3 = 5;
    int count4 = 3;
    int count5 = 7;

    struct decreasing_count *dc_1;
    struct decreasing_count *dc_2;
    struct decreasing_count *dc_3;
    struct decreasing_count *dc_4;
    struct decreasing_count *dc_5;
    struct decreasing_count *head = NULL;

    dc_1 = create_decreasing_count_node(&word1[0], count1);
    dc_2 = create_decreasing_count_node(&word2[0], count2);
    dc_3 = create_decreasing_count_node(&word3[0], count3);
    dc_4 = create_decreasing_count_node(&word4[0], count4);
    dc_5 = create_decreasing_count_node(&word5[0], count5);

    insert_decreasing_count_node(&head, dc_1);
    insert_decreasing_count_node(&head, dc_2);
    insert_decreasing_count_node(&head, dc_3);
    insert_decreasing_count_node(&head, dc_4);
    insert_decreasing_count_node(&head, dc_5);
    
    delete_decreasing_count_list(&head);
    printf("\n");
}


void testing_suite()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
}

/* Write a program that prints the distinct words in its input sorted into
decreasing order of frequency of occurrence. Preced each word by its count. */
int main(int argc, char *argv[])
{   
    // Make sure all tests are successful
    //testing_suite();

    // Number of identical beginning characters to consider
    int min_identical = 3;
    if (argc > 1)
        min_identical = atoi(argv[1]);

    
    int lim = 1000;
    char current_word[lim];

    // Have to make sure that the pointer for the word has pre-allocated 
    // space to store the words, in this case, with size lim.
    char first_letter = getword(&current_word[0], lim);
    
    // create a Node * structure and tie it to head_ref
    struct wordcount *head_ref = (struct wordcount *)malloc(sizeof(struct wordcount));
    struct wordcount **current = (struct wordcount **)malloc(sizeof(struct wordcount *));
    head_ref = NULL;
    *current = head_ref;

    while(first_letter != EOF)
    {   
        if(strlen(&current_word[0]) >= min_identical)
        {
            *current = search(head_ref, current_word);

            if(*current == NULL)
                insert(&head_ref, &current_word[0]);
            else
                (*current)->count++;
        }

        // get new word
        first_letter = getword(&current_word[0], lim);
    }

    //printlist(head_ref);    

    // create decreasing_count_list tree from information from wordcount tree
    struct decreasing_count *decreasing_head = NULL;

    binary_to_decreasing_list(head_ref, &decreasing_head);
    print_decreasing_count_list(&decreasing_head);

    return 0;
}

void binary_to_decreasing_list(struct wordcount *binary_head, struct decreasing_count **decreasing_head)
{
    if(binary_head == NULL)
        return;

    binary_to_decreasing_list(binary_head->lower, decreasing_head);

    insert_decreasing_count_node(decreasing_head, create_decreasing_count_node(binary_head->word, binary_head->count));

    binary_to_decreasing_list(binary_head->higher, decreasing_head);
    
}

// Delete node function
void delete_decreasing_count_list(struct decreasing_count **head)
{
    if(*head == NULL)
        printf("head is NULL\n");
    else
    {
        struct decreasing_count *current_node = *head;
        struct decreasing_count *next_node = NULL;
        
        while(current_node != NULL)
        {
            next_node = current_node->next;
            
            printf("current_node address: %p ", current_node);
            printf("current_node word: %s ", current_node->word);
            printf("Freeing current_node memory\n");
            free(current_node->word);
            free(current_node);
            current_node = next_node;
        }
    }
}


void print_decreasing_count_list(struct decreasing_count **head)
{   
    /*
        prints the whole decreasing_count list from head to end
    */

    struct decreasing_count *current_node;
    current_node = *head;
    while(current_node != NULL)
    {
        if(current_node->word == NULL)
            return;
        
        printf("%d, %s\n", current_node->count, current_node->word);
        current_node = current_node->next;
    }

}

struct decreasing_count *create_decreasing_count_node(char *word, int count)
{   
    /*
        creates an individual decreasing_count node
    */

    if(word == NULL)
        return NULL;

    int word_len = strlen(word);
    struct decreasing_count *temp = (struct decreasing_count*) malloc(sizeof(struct decreasing_count));


    temp->word = (char*) malloc(word_len * sizeof(char)) ;
    strcpy(temp->word, word);

    temp->count = count;
    temp->next = NULL;

    return temp;
}

void insert_decreasing_count_node(struct decreasing_count **head, struct decreasing_count *new_node)
{
    /*
        Inserts a new node into an existing list in proper order.
    */

    if(*head == NULL)
    {
        *head = new_node;
        return;
    }

    struct decreasing_count *current_node = *head;
    struct decreasing_count *previous_node = NULL;
    
    while(current_node != NULL)
    {
        if(new_node->count  >= current_node->count)
        {
            // If we are looking at the beginning of the list
            if(strcmp(current_node->word, (*head)->word) == 0)
            {
                new_node->next  = current_node;
                *head = new_node;
                return;
            }
            
            // If we are replacing elsewhere in the list
            else
            {
                previous_node->next = new_node;
                new_node->next  = current_node;
                return;
            }
            
        }
        else if(current_node->next  == NULL)
        {
            current_node->next = new_node;
            return;
        }
        
        previous_node = current_node;
        current_node = current_node->next;
    }
}






// Functions relateing to wordcount structure

void printlist(struct wordcount *head)
{
    if(head == NULL)
        return;

    // print the lower alphabetical value words
    printlist(head->lower);

    // print the head word
    printf("%s %d\n", head->word, head->count);

    // print the higher alphabetical value words
    printlist(head->higher);
}

struct wordcount *create_node(char *word)
{   
    if(word == NULL)
        return NULL;

    int word_len = strlen(word);
    struct wordcount *temp = (struct wordcount*) malloc(sizeof(struct wordcount));

    temp->word = (char*) malloc(word_len * sizeof(char)) ;
    strcpy(temp->word, word);

    temp->count = 1;
    temp->higher = NULL;
    temp->lower = NULL;

    return temp;
}

void delete(struct wordcount *head)
{
    free(head->word);
    free(&(head->count));
    free(head->higher);
    free(head->lower);
    printf("Deleted node contents\n");

    free(head);
    printf("Deleted node pointer\n");
}

struct wordcount *search(struct wordcount *head, char *search_word)
{   
    if(head == NULL)
        return NULL;

    struct wordcount *head_ptr;

    head_ptr = head;

    while(strcmp(head_ptr->word, search_word) != 0)
    {
        if(head_ptr->word != NULL)
        {
            //go to right tree
            if(strcmp(head_ptr->word, search_word) < 0)
                head_ptr = head_ptr->higher;
            //go to left tree
            else if(strcmp(head_ptr->word, search_word) > 0)
                head_ptr = head_ptr->lower;

            if(head_ptr == NULL)
                return NULL;
        }


    }
    return head_ptr;
}

void insert(struct wordcount **head, char *insert_word)
{
    if(insert_word == NULL)
        return;

    struct wordcount *temp = create_node(insert_word);
    struct wordcount *current;
    struct wordcount *parent;

    //if tree is empty
    if(*head == NULL)
    {
        *head = temp;
    }
    else
    {
        current = *head;
        parent = NULL;

        while(1)
        {
            parent = current;

            //go to left of the tree
            if(strcmp(parent->word, insert_word) > 0)
            {
                current = current->lower;
                //insert to the left

                if(current == NULL)
                {
                    parent->lower = temp;
                    return;
                }
            }
            //go to right of the tree
            else if(strcmp(parent->word, insert_word) < 0)
            {
                current = current->higher;

                //insert to the right
                if(current == NULL)
                {
                    parent->higher = temp;
                    return;
                }
            }
            else
            {
                parent->count+=1;
                return;
            }
        }
    }
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;
    // Skip comments of the type '//' and '/* */'
    if(c == '/')
    {
        c = getch();
        if(c == '/')
            while((c = getch()) != '\n')
                ;
        else if(c == '*')
            while((c = getch()) != '/')
                ;
    }
    // Check for preprocessor control lines, for which we skip entire to the 
    // next line
    if(c == '#')
        while((c = getch()) != '\n')
            ;
    // We include underscores in our string when encountered
    if (c != EOF && (isalpha(c) || c == '_'))
        *w++ = c;
    if (c != '_' && !isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && (*w != '_')) {
            ungetch1(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp == 1) ? buf[--bufp] : getchar();
}

void ungetch1(int c) /* push character back on input */
{
    if (bufp >= 1)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
