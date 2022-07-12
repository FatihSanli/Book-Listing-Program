#include <stdio.h>
int menu (void);
int clear (void);
int show (void);
int add (void);
int delete (void);
int edit (void);

typedef struct {
    char bookName[20];
    char writerName[20];
    unsigned int page;
    unsigned int count;
    unsigned int no;
} book;

book emptyBook = {"", "", 0, 0, 0};
book aBook;
FILE *file;

int main() {
    int choice;
    do {
    choice = menu();
    switch (choice) {
        case 1:
            add();
            break;
        case 2:
            delete();
            break;
        case 3:
            edit();
            break;
        case 4:
            show();
            break;
        case 5:
            clear();
            break;
        case 0:
            printf("Program ended.\n");
            break;
        default:
            printf("Invalid entry.\n");
            break;
        }
    } while (choice != 0);
    return 0;
}

int menu (void) {
    int choice;
    printf("----------------------------\n");
    printf("--- Book listing program ---\n");
    printf("1- Add a book. \n");
    printf("2- Delete a book. \n");
    printf("3- Edit a book. \n");
    printf("4- Show books. \n");
    printf("5- Clear all books. \n");
    printf("0- Exit. \n");
    printf("----------------------------\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    return choice;
}

int add (void) {
    unsigned int bookID;
    
    file = fopen("book.txt", "w");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }
    printf("ID of the book to add: ");
    scanf("%u", &bookID);
    fseek(file, (bookID - 1) * sizeof(book), 0);
    fread(&aBook, sizeof(book), 1, file);
    if (aBook.no != 0) {
        printf("%u ID numbered book is unavaible.\n", bookID);
    } else {
        printf("Please enter the book's name, writer's name, page count and book count.\n");
        scanf("%s %s %u %u", aBook.bookName, aBook.writerName, &aBook.page, &aBook.count);
        aBook.no = bookID;
        fseek(file, (bookID - 1) * sizeof(book), 0);
        fwrite(&aBook, sizeof(book), 1, file);
        printf("%u ID numbered book is added successfully.\n", bookID);
    }
    fclose(file);
    return 0;
}

int delete (void) {
    unsigned int bookID;
    
    file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }
    printf("Book ID of the book to delete: ");
    scanf("%u", &bookID);
    fseek(file, (bookID - 1) * sizeof(book), 0);
    fread(&aBook, sizeof(book), 1, file);
    if (aBook.no == 0) {
        printf("%u ID numbered book is unavaible.\n", bookID);
    } else {
        fseek(file, (bookID - 1) * sizeof(book), 0);
        fwrite(&emptyBook, sizeof(book), 1, file);
        printf("%u ID numbered book is deleted successfully.\n", bookID);
    }
    fclose(file);
    return 0;
}

int edit (void) {
    unsigned int bookID;
    
    file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }
    printf("ID of the book to edit: ");
    scanf("%u", &bookID);
    fseek(file, (bookID - 1) * sizeof(book), 0);
    fread(&aBook, sizeof(book), 1, file);
    if (aBook.no == 0) {
        printf("%u ID numbered book is unavaible.\n", bookID);
    } else {
        printf("--- information of the %u ID numbered book --- \n", bookID);
        printf("Book's name: %s \n", aBook.bookName);
        printf("Writer's name: %s \n", aBook.writerName);
        printf("Page count: %d \n", aBook.page);
        printf("Book count: %u \n", aBook.count);
        printf("New book's information: ");
        scanf("%s %s %u %u", aBook.bookName, aBook.writerName, &aBook.page, &aBook.count);
        fseek(file, (bookID - 1) * sizeof(book), 0);
        fwrite(&emptyBook, sizeof(book), 1, file);
        printf("%u ID numbered book's information has been changed successfully.\n", bookID);
    }
    fclose(file);
    return 0;
}

int show (void) {
    file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }
    printf("--- Informations of the current books ---\n");
    printf("----------------------------------------------\n");
    while (!feof(file)) {
        fread(&aBook, sizeof(book), 1, file);
        if (aBook.no != 0) {
            printf("Book's name: %s \n", aBook.bookName);
            printf("Writer's name: %s \n", aBook.writerName);
            printf("Page count: %d \n", aBook.page);
            printf("Book count: %u \n", aBook.count);
            printf("Book ID: %u \n", aBook.no);
            printf("----------------------------------------------\n");
        }
    }
    fclose(file);
    return 0;
}

int clear (void) {
    file = fopen("book.txt", "r+");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }
    for (int i = 0; i < 100; i++) {
        fwrite(&emptyBook, sizeof(book), 1, file);
    }
    printf("All books have cleared successfully.\n");
    fclose(file);
    return 0;
}
