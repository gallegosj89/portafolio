#include <stdio.h>

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    int publication_year;
    // TODO: agregar genero del libro
    int quantity;
} book_t;

typedef struct Member {
    int id;
    char name[100];
    int bookIssued; // TODO: hacer una lista de libros prestados
} member_t;

void addBook() {
    printf("Añadiendo un libro\n");
}

void displayBooks() {
    printf("Mostrando los libros disponibles en la biblioteca\n");
}

void addMember() {
    printf("Añadiendo un miembro\n");
}

void issueBook() {
    printf("Prestando un libro\n");
}

int main() {
    int choice = 0;

    do {
        printf("\nMenú de sistema de manejo de biblioteca\n");
        printf("\t1. Agregar un libro\n");
        printf("\t2. Mostrar libros disponibles\n");
        printf("\t3. Agregar un miembro\n");
        printf("\t4. Prestar libro\n");
        printf("\t5. Salir.\n");
        printf("Indica tu opción: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                addMember();
                break;
            case 4:
                issueBook();
                break;
            default:
                printf("Esta no es una opción válida!!!\n");
                break;
        }
    } while(choice != 5);

    return 0;
}