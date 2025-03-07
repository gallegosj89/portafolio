#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory_management.h"

// Variable estatica (almacenada en el segmento de datos)
static int static_var = 0;

// Variable del segmento BSS (variable global no inicializada)
int bss_var;

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

// Prototipos de funciones
const char* genreToString(genre_t genre);
void addBook(book_t **library, int* count);
book_t* findBookById(book_t *library, int bookID);
void displayBooksRecursive(book_t *library);
void displayBooks(book_t *library);
void addMember(member_t **members, int *memberCount);
void issueBook(book_t *library, member_t *members);
void returnBook(book_t *library, member_t *members);
void freeLibrary(book_t *library);
void freeMembers(member_t *members);
void saveLibraryToFile(book_t *library, const char *filename);
void loadLibraryFromFile(book_t **library, int *bookCount, const char *filename);
void saveMembersToFile(member_t *members, const char *filename);
void loadMembersFromFile(member_t **members, int *memberCount, const char *filename);
void displayMembers(member_t *members, book_t *library);
void searchMember(member_t *members, book_t *library);

// Función para convertir el género a texto
const char* genreToString(genre_t genre) {
    switch (genre) {
        case FICTION: return "Ficcion";
        case NON_FICTION: return "No Ficcion";
        case SCIENCE: return "Ciencia";
        case HISTORY: return "Historia";
        case FANTASY: return "Fantasia";
        case BIOGRAPHY: return "Biografia";
        case OTHER: return "Otro";
        default: return "Desconocido";
    }
}

void addBook(book_t **library, int* count ) {
    // Asignacion de memoria en el heap
    book_t *new_book = (book_t *)malloc(sizeof(book_t));
    if (!new_book) {
        printf("Error al asignar memoria para el nuevo libro.\n");
        return;
    }
    incrementHeapAllocations(new_book, sizeof(book_t));
    printf("Memoria asignada para un nuevo libro (ID: %d) en el heap\n", new_book->id);

    printf("\nIngresa ID del libro: ");
    scanf("%d", &new_book->id);

    printf("Ingresa titulo del libro: ");
    getchar();
    fgets(new_book->title, 100, stdin);
    new_book->title[strcspn(new_book->title, "\n")] = '\0';

    printf("Ingresa nombre del autor: ");
    fgets(new_book->author, 100, stdin);
    new_book->author[strcspn(new_book->author, "\n")] = '\0';

    printf("Ingresa el ano de publicacion: ");
    scanf("%d", &new_book->publication_year);

    printf("Ingresa el genero del libro (0: FICTION, 1: NON_FICTION, 2: SCIENCE, 3: HISTORY, 4: FANTASY, 5: BIOGRAPHY, 6: OTHER): ");
    int genre;
    scanf("%d", &genre);
    new_book->genre = (genre_t)genre;

    printf("Ingresa la cantidad de libros: ");
    scanf("%d", &new_book->quantity);

    new_book->next = *library;
    *library = new_book;
    (*count)++;

    printf("\nEl libro fue agregado exitosamente!\n");
    displayMemoryUsage();
}

book_t* findBookById(book_t *library, int bookID) {
    book_t *current = library;
    while (current) {
        if (current->id == bookID) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayBooksRecursive(book_t *library) {
    if (!library) {
        return;
    }
    printf("\nID libro: %d\nTitulo: %s\nAutor: %s\nAno de publicacion: %d\nGenero: %s\nCantidad: %d\n",
        library->id, library->title, library->author, library->publication_year, genreToString(library->genre), library->quantity);
    displayBooksRecursive(library->next);
}

void displayBooks(book_t *library) {
    if (!library) {
        printf("\nNo hay libros disponibles.\n");
        return;
    }

    printf("\nLibros disponibles en biblioteca:\n");
    displayBooksRecursive(library);
    displayMemoryUsage();
}

void addMember(member_t **members, int *memberCount) {
    // Asignacion de memoria en el heap
    member_t *new_member = (member_t *)malloc(sizeof(member_t));
    if (!new_member) {
        printf("Error al asignar memoria para el nuevo miembro.\n");
        return;
    }
    incrementHeapAllocations(new_member, sizeof(member_t));
    printf("Memoria asignada para un nuevo miembro (ID: %d) en el heap\n", new_member->id);

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
    displayMemoryUsage();
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
        incrementHeapAllocations(memberFound->issued_books, memberFound->issued_count * sizeof(int));
        printf("Memoria reasignada para los libros prestados del miembro (ID: %d) en el heap\n", memberFound->id);
        memberFound->issued_books[memberFound->issued_count - 1] = bookID;
        printf("\nLibro prestado satisfactoriamente!\n");
    } else {
        printf("\nLibro o miembro no encontrados.\n");
    }
    displayMemoryUsage();
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
                incrementHeapAllocations(memberFound->issued_books, memberFound->issued_count * sizeof(int));
                printf("Memoria reasignada para los libros prestados del miembro (ID: %d) en el heap\n", memberFound->id);
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
    displayMemoryUsage();
}

void freeLibrary(book_t *library) {
    book_t *current = library;
    while (current) {
        book_t *next = current->next;
        incrementHeapDeallocations(current);
        free(current);
        current = next;
    }
    displayMemoryUsage();
}

void freeMembers(member_t *members) {
    member_t *current = members;
    while (current) {
        member_t *next = current->next;
        incrementHeapDeallocations(current->issued_books);
        free(current->issued_books);
        incrementHeapDeallocations(current);
        free(current);
        current = next;
    }
    displayMemoryUsage();
}

void saveLibraryToFile(book_t *library, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error al abrir el archivo para guardar la biblioteca.\n");
        return;
    }

    book_t *current = library;
    while (current) {
        fprintf(file, "%d\n%s\n%s\n%d\n%s\n%d\n", current->id, current->title, current->author, current->publication_year, genreToString(current->genre), current->quantity);
        current = current->next;
    }

    fclose(file);
    printf("Biblioteca guardada exitosamente en %s\n", filename);
    displayMemoryUsage();
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
        char genre_str[50];
        fgets(genre_str, 50, file);
        genre_str[strcspn(genre_str, "\n")] = '\0';
        if (strcmp(genre_str, "Ficcion") == 0) new_book->genre = FICTION;
        else if (strcmp(genre_str, "No Ficcion") == 0) new_book->genre = NON_FICTION;
        else if (strcmp(genre_str, "Ciencia") == 0) new_book->genre = SCIENCE;
        else if (strcmp(genre_str, "Historia") == 0) new_book->genre = HISTORY;
        else if (strcmp(genre_str, "Fantasia") == 0) new_book->genre = FANTASY;
        else if (strcmp(genre_str, "Biografia") == 0) new_book->genre = BIOGRAPHY;
        else new_book->genre = OTHER;
        fscanf(file, "%d\n", &new_book->quantity);

        new_book->next = *library;
        *library = new_book;
        (*bookCount)++;
        incrementHeapAllocations(new_book, sizeof(book_t));
    }

    fclose(file);
    printf("Biblioteca cargada exitosamente desde %s\n", filename);
    displayMemoryUsage();
}

void saveMembersToFile(member_t *members, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error al abrir el archivo para guardar los miembros.\n");
        return;
    }

    member_t *current = members;
    while (current) {
        fprintf(file, "%d\n%s\n%d\n", current->id, current->name, current->issued_count);
        for (int i = 0; i < current->issued_count; i++) {
            fprintf(file, "%d\n", current->issued_books[i]);
        }
        current = current->next;
    }

    fclose(file);
    printf("Miembros guardados exitosamente en %s\n", filename);
}

void loadMembersFromFile(member_t **members, int *memberCount, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error al abrir el archivo para cargar los miembros.\n");
        return;
    }

    while (!feof(file)) {
        member_t *new_member = (member_t *)malloc(sizeof(member_t));
        if (!new_member) {
            printf("Error al asignar memoria para el nuevo miembro.\n");
            fclose(file);
            return;
        }

        fscanf(file, "%d\n", &new_member->id);
        fgets(new_member->name, 100, file);
        new_member->name[strcspn(new_member->name, "\n")] = '\0';
        fscanf(file, "%d\n", &new_member->issued_count);
        new_member->issued_books = (int *)malloc(new_member->issued_count * sizeof(int));
        for (int i = 0; i < new_member->issued_count; i++) {
            fscanf(file, "%d\n", &new_member->issued_books[i]);
        }

        new_member->next = *members;
        *members = new_member;
        (*memberCount)++;
        incrementHeapAllocations(new_member, sizeof(member_t));
        incrementHeapAllocations(new_member->issued_books, new_member->issued_count * sizeof(int));
    }

    fclose(file);
    printf("Miembros cargados exitosamente desde %s\n", filename);
    displayMemoryUsage();
}

void displayMembers(member_t *members, book_t *library) {
    if (!members) {
        printf("\nNo hay miembros disponibles.\n");
        return;
    }

    member_t *current = members;
    printf("\nMiembros disponibles en biblioteca:\n");
    while (current) {
        printf("\nID miembro: %d\nNombre: %s\nCantidad de libros prestados: %d\n",
            current->id, current->name, current->issued_count);
        for (int i = 0; i < current->issued_count; i++) {
            book_t *book = findBookById(library, current->issued_books[i]);
            if (book) {
                printf("  Libro ID: %d\n  Titulo: %s\n  Autor: %s\n", book->id, book->title, book->author);
            }
        }
        current = current->next;
    }
    displayMemoryUsage();
}

void searchMember(member_t *members, book_t *library) {
    int memberID;
    printf("\nIngresa el ID del miembro: ");
    scanf("%d", &memberID);

    member_t *current = members;
    while (current) {
        if (current->id == memberID) {
            printf("\nID miembro: %d\nNombre: %s\nCantidad de libros prestados: %d\n",
                current->id, current->name, current->issued_count);
            for (int i = 0; i < current->issued_count; i++) {
                book_t *book = findBookById(library, current->issued_books[i]);
                if (book) {
                    printf("  Libro ID: %d\n  Titulo: %s\n  Autor: %s\n", book->id, book->title, book->author);
                }
            }
            displayMemoryUsage();
            return;
        }
        current = current->next;
    }
    printf("\nMiembro no encontrado.\n");
    displayMemoryUsage();
}

int main() {
    // Variables automaticas (almacenadas en el stack)
    book_t *library = NULL;
    member_t *members = NULL;
    int bookCount = 0, memberCount = 0;
    int choice = 0;

    loadLibraryFromFile(&library, &bookCount, "library.txt");
    loadMembersFromFile(&members, &memberCount, "members.txt");

    do {
        printf("\nMenu de sistema de manejo de biblioteca\n");
        printf("\t1. Agregar un libro\n");
        printf("\t\t- Ingresa los detalles del libro como ID, titulo, autor, ano de publicacion, genero y cantidad.\n");
        printf("\t2. Mostrar libros disponibles\n");
        printf("\t\t- Muestra todos los libros disponibles en la biblioteca.\n");
        printf("\t3. Agregar un miembro\n");
        printf("\t\t- Ingresa los detalles del miembro como ID y nombre.\n");
        printf("\t4. Prestar libro\n");
        printf("\t\t- Ingresa el ID del miembro y el ID del libro para prestar el libro al miembro.\n");
        printf("\t5. Devolver libro\n");
        printf("\t\t- Ingresa el ID del miembro y el ID del libro para devolver el libro a la biblioteca.\n");
        printf("\t6. Mostrar miembros disponibles\n");
        printf("\t\t- Muestra todos los miembros disponibles en la biblioteca.\n");
        printf("\t7. Buscar miembro\n");
        printf("\t\t- Busca un miembro por ID y muestra sus detalles.\n");
        printf("\t8. Guardar y salir\n");
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
                displayMembers(members, library);
                break;
            case 7:
                searchMember(members, library);
                break;
            case 8:
                saveLibraryToFile(library, "library.txt");
                saveMembersToFile(members, "members.txt");
                printf("Saliendo del programa\n");
                break;
            default:
                printf("Esta no es una opcion valida!!!\n");
                break;
        }
    } while(choice != 8);

    freeLibrary(library);
    freeMembers(members);

    return 0;
}
