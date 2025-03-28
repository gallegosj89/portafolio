'''Este archivo contiene la implementación de la aplicación web de la biblioteca.
Se utiliza Flask para crear una API REST que permite realizar operaciones CRUD
sobre los libros y miembros de la biblioteca.'''

from flask import Flask, request, jsonify, render_template
from memory_management import memory_management
from biblioteca import Book, DigitalBook, Member, Library, Genre

app = Flask(__name__)
library = Library()

# Cargar datos al iniciar la aplicación
library.load_library_from_file("library.json")
library.load_members_from_file("members.json")


@app.route('/')
def index():
    '''Ruta principal de la aplicación web.'''
    return render_template('index.html')


@app.route('/books', methods=['GET'])
def get_books():
    '''Obtener todos los libros de la biblioteca.'''
    books = [book.to_dict() for book in library.books]
    return jsonify(books)


@app.route('/books', methods=['POST'])
def add_book():
    '''Agregar un libro a la biblioteca'''
    data = request.json
    is_digital = data.get('is_digital', False)
    if is_digital:
        book = DigitalBook(
            int(data['id']), data['title'], data['author'], data['publication_year'],
            data['genre'], data['quantity'], data['file_format']
        )
    else:
        book = Book(
            int(data['id']), data['title'], data['author'], int(data['publication_year']),
            data['genre'], int(data['quantity'])
        )
    library.add_book(book)
    # Guardar datos después de agregar un libro
    library.save_library_to_file("library.json")
    memory_management.display_memory_usage()
    return jsonify(book.to_dict()), 201


@app.route('/members', methods=['GET'])
def get_members():
    '''Obtener todos los miembros de la biblioteca.'''
    members = [member.to_dict() for member in library.members]
    return jsonify(members)


@app.route('/members', methods=['POST'])
def add_member():
    '''Agregar un miembro a la biblioteca.'''
    data = request.json
    member_id = int(data['id'])
    member = Member(member_id, data['name'])
    library.add_member(member)
    # Guardar datos después de agregar un miembro
    library.save_members_to_file("members.json")
    memory_management.display_memory_usage()
    return jsonify(member.to_dict()), 201


@app.route('/issue_book', methods=['POST'])
def issue_book():
    '''Prestar un libro a un miembro de la biblioteca.'''
    data = request.json
    book_id = int(data['book_id'])
    member_id = int(data['member_id'])
    library.issue_book(book_id, member_id)
    # Guardar datos después de prestar un libro
    library.save_library_to_file("library.json")
    library.save_members_to_file("members.json")
    memory_management.display_memory_usage()
    return jsonify({"message": "Libro prestado satisfactoriamente!"})


@app.route('/return_book', methods=['POST'])
def return_book():
    '''Devolver un libro a la biblioteca.'''
    data = request.json
    book_id = int(data['book_id'])
    member_id = int(data['member_id'])
    library.return_book(book_id, member_id)
    # Guardar datos después de devolver un libro
    library.save_library_to_file("library.json")
    library.save_members_to_file("members.json")
    memory_management.display_memory_usage()
    return jsonify({"message": "Libro devuelto satisfactoriamente!"})


@app.route('/save', methods=['POST'])
def save():
    '''Guardar los datos de la biblioteca en un archivo.'''
    library.save_library_to_file("library.json")
    library.save_members_to_file("members.json")
    memory_management.display_memory_usage()
    return jsonify({"message": "Datos guardados exitosamente!"})


@app.route('/load', methods=['POST'])
def load():
    '''Cargar los datos de la biblioteca desde un archivo.'''
    library.load_library_from_file("library.json")
    library.load_members_from_file("members.json")
    memory_management.display_memory_usage()
    return jsonify({"message": "Datos cargados exitosamente!"})


@app.route('/genres', methods=['GET'])
def get_genres():
    '''Obtener todos los géneros de la biblioteca.'''
    genres = Genre.all_genres()
    return jsonify(genres)


if __name__ == '__main__':
    app.run(debug=True)
