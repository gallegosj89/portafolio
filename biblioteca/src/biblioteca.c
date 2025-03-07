#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    FICTION,
    NON_FICTION,
    SCIENCE,
    HISTORY,
    FANTASY,
    BIOGRAPHY,
    OTHER
} genre_t;

typedef struct _book {
    int id;
    char title[100];
    char author[100];
    int publication_year;
    genre_t genre;
    int quantity;
    struct _book *next;
} book_t;

typedef struct _member {
    int id;
    char name[100];
    int issued_count;
    int *issued_books;
    struct _member *next;
} member_t;

void addBook(book_t **library, int* count ) {
    book_t *new_book = (book_t *)malloc(sizeof(book_t));
    if (!new_book) {
        printf("Error al asignar memoria para el nuevo libro.\n");
        return;
    }

    printf("\nIngresa ID del libro: ");
    scanf("%d", &new_book->id);

    printf("Ingresa título del libro: ");
    getchar();
    fgets(new_book->title, 100, stdin);
    new_book->title[strcspn(new_book->title, "\n")] = '\0';

    printf("Ingresa nombre del autor: ");
    fgets(new_book->author, 100, stdin);
    new_book->author[strcspn(new_book->author, "\n")] = '\0';

    printf("Ingresa el año de publicación: ");
    scanf("%d", &new_book->publication_year);

    printf("Ingresa el género del libro (0: FICTION, 1: NON_FICTION, 2: SCIENCE, 3: HISTORY, 4: FANTASY, 5: BIOGRAPHY, 6: OTHER): ");
    int genre;
    scanf("%d", &genre);
    new_book->genre = (genre_t)genre;

    printf("Ingresa la cantidad de libros: ");
    scanf("%d", &new_book->quantity);

    new_book->next = *library;
    *library = new_book;
    (*count)++;

    printf("\nEl libro fue agregado exitosamente!\n");
}

void displayBooksRecursive(book_t *library) {
    if (!library) {
        return;
    }
    printf("\nID libro: %d\nTitulo: %s\nAutor: %s\nAño de publicación: %d\nGénero: %d\nCantidad: %d\n",
        library->id, library->title, library->author, library->publication_year, library->genre, library->quantity);
    displayBooksRecursive(library->next);
}

void displayBooks(book_t *library) {
    if (!library) {
        printf("\nNo hay libros disponibles.\n");
        return;
    }

    printf("\nLibros disponibles en biblioteca:\n");
    displayBooksRecursive(library);
}

void addMember(member_t **members, int *memberCount) {
    member_t *new_member = (member_t *)malloc(sizeof(member_t));
    if (!new_member) {
        printf("Error al asignar memoria para el nuevo miembro.\n");
        return;
    }

    printf("\nIngresa el ID del miembro: ");
    scanf("%d", &new_member->id);
    printf("Ingresa el nombre del miembro: ");
    getchar();
    fgets(new_member->name, 100, stdin);
    new_member->name[strcspn(new_member->name, "\n")] = '\0';
    new_member->issued_count = 0;
    new_member->issued_books = NULL;
    new_member->next = *members;
    *members = new_member;
    (*memberCount)++;
    printf("\nMiembro agregado exitosamente!\n");
}

void issueBook(book_t *library, member_t *members) {
    int bookID, memberID;
    printf("\nIngresa el ID del miembro: ");
    scanf("%d", &memberID);
    printf("Ingresa el ID del libro: ");
    scanf("%d", &bookID);

    book_t *bookFound = NULL;
    member_t *memberFound = NULL;

    book_t *current_book = library;
    while (current_book) {
        if (current_book->id == bookID && current_book->quantity > 0) {
            bookFound = current_book;
            break;
        }
        current_book = current_book->next;
    }

    member_t *current_member = members;
    while (current_member) {
        if (current_member->id == memberID) {
            memberFound = current_member;
            break;
        }
        current_member = current_member->next;
    }

    if (bookFound && memberFound) {
        bookFound->quantity--;
        memberFound->issued_count++;
        memberFound->issued_books = realloc(memberFound->issued_books, memberFound->issued_count * sizeof(int));
        memberFound->issued_books[memberFound->issued_count - 1] = bookID;
        printf("\nLibro prestado satisfactoriamente!\n");
    } else {
        printf("\nLibro o miembro no encontrados.\n");
    }
}

void returnBook(book_t *library, member_t *members) {
    int bookID, memberID;
    printf("\nIngresa el ID del miembro: ");
    scanf("%d", &memberID);
    printf("Ingresa el ID del libro: ");
    scanf("%d", &bookID);

    book_t *bookFound = NULL;
    member_t *memberFound = NULL;

    book_t *current_book = library;
    while (current_book) {
        if (current_book->id == bookID) {
            bookFound = current_book;
            break;
        }
        current_book = current_book->next;
    }

    member_t *current_member = members;
    while (current_member) {
        if (current_member->id == memberID) {
            memberFound = current_member;
            break;
        }
        current_member = current_member->next;
    }

    if (bookFound && memberFound) {
        int found = 0;
        for (int i = 0; i < memberFound->issued_count; i++) {
            if (memberFound->issued_books[i] == bookID) {
                found = 1;
                for (int j = i; j < memberFound->issued_count - 1; j++) {
                    memberFound->issued_books[j] = memberFound->issued_books[j + 1];
                }
                memberFound->issued_count--;
                memberFound->issued_books = realloc(memberFound->issued_books, memberFound->issued_count * sizeof(int));
                break;
            }
        }
        if (found) {
            bookFound->quantity++;
            printf("\nLibro devuelto satisfactoriamente!\n");
        } else {
            printf("\nEl miembro no tiene este libro prestado.\n");
        }
    } else {
        printf("\nLibro o miembro no encontrados.\n");
    }
}

void freeLibrary(book_t *library) {
    book_t *current = library;
    while (current) {
        book_t *next = current->next;
        free(current);
        current = next;
    }
}

void freeMembers(member_t *members) {
    member_t *current = members;
    while (current) {
        member_t *next = current->next;
        free(current->issued_books);
        free(current);
        current = next;
    }
}

void saveLibraryToFile(book_t *library, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error al abrir el archivo para guardar la biblioteca.\n");
        return;
    }

    book_t *current = library;
    while (current) {
        fprintf(file, "%d\n%s\n%s\n%d\n%d\n%d\n", current->id, current->title, current->author, current->publication_year, current->genre, current->quantity);
        current = current->next;
    }

    fclose(file);
    printf("Biblioteca guardada exitosamente en %s\n", filename);
}

void loadLibraryFromFile(book_t **library, int *bookCount, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error al abrir el archivo para cargar la biblioteca.\n");
        return;
    }

    while (!feof(file)) {
        book_t *new_book = (book_t *)malloc(sizeof(book_t));
        if (!new_book) {
            printf("Error al asignar memoria para el nuevo libro.\n");
            fclose(file);
            return;
        }

        fscanf(file, "%d\n", &new_book->id);
        fgets(new_book->title, 100, file);
        new_book->title[strcspn(new_book->title, "\n")] = '\0';
        fgets(new_book->author, 100, file);
        new_book->author[strcspn(new_book->author, "\n")] = '\0';
        fscanf(file, "%d\n", &new_book->publication_year);
        fscanf(file, "%d\n", (int *)&new_book->genre);
        fscanf(file, "%d\n", &new_book->quantity);

        new_book->next = *library;
        *library = new_book;
        (*bookCount)++;
    }

    fclose(file);
    printf("Biblioteca cargada exitosamente desde %s\n", filename);
}

int main() {
    book_t *library = NULL;
    member_t *members = NULL;
    int bookCount = 0, memberCount = 0;
    int choice = 0;

    loadLibraryFromFile(&library, &bookCount, "library.txt");

    do {
        printf("\nMenu de sistema de manejo de biblioteca\n");
        printf("\t1. Agregar un libro\n");
        printf("\t\t- Ingresa los detalles del libro como ID, título, autor, año de publicación, género y cantidad.\n");
        printf("\t2. Mostrar libros disponibles\n");
        printf("\t\t- Muestra todos los libros disponibles en la biblioteca.\n");
        printf("\t3. Agregar un miembro\n");
        printf("\t\t- Ingresa los detalles del miembro como ID y nombre.\n");
        printf("\t4. Prestar libro\n");
        printf("\t\t- Ingresa el ID del miembro y el ID del libro para prestar el libro al miembro.\n");
        printf("\t5. Devolver libro\n");
        printf("\t\t- Ingresa el ID del miembro y el ID del libro para devolver el libro a la biblioteca.\n");
        printf("\t6. Guardar y salir\n");
        printf("\t\t- Guarda los datos de la biblioteca en un archivo y sale del programa.\n");
        printf("Indica tu opcion: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(&library, &bookCount);
                break;
            case 2:
                displayBooks(library);
                break;
            case 3:
                addMember(&members, &memberCount);
                break;
            case 4:
                issueBook(library, members);
                break;
            case 5:
                returnBook(library, members);
                break;
            case 6:
                saveLibraryToFile(library, "library.txt");
                printf("Saliendo del programa\n");
                break;
            default:
                printf("Esta no es una opción válida!!!\n");
                break;
        }
    } while(choice != 6);

    freeLibrary(library);
    freeMembers(members);

    return 0;
}
