document.getElementById('isDigital').addEventListener('change', function() {
    document.getElementById('digitalBookFields').style.display = this.checked ? 'block' : 'none';
});

async function fetchGenres() {
    const response = await fetch('/genres');
    const genres = await response.json();
    const genreSelect = document.getElementById('genre');
    genres.forEach(genre => {
        const option = document.createElement('option');
        option.value = genre;
        option.textContent = genre;
        genreSelect.appendChild(option);
    });
}

async function fetchBooks() {
    const response = await fetch('/books');
    const books = await response.json();
    const booksTableBody = document.getElementById('books');
    booksTableBody.innerHTML = '';
    books.forEach(book => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${book.id}</td>
            <td>${book.title}</td>
            <td>${book.author}</td>
            <td>${book.publication_year}</td>
            <td>${book.genre}</td>
            <td>${book.quantity}</td>
            <td>${book.file_format || ''}</td>
        `;
        booksTableBody.appendChild(row);
    });
}

async function fetchMembers() {
    const response = await fetch('/members');
    const members = await response.json();
    const membersTableBody = document.getElementById('members');
    membersTableBody.innerHTML = '';
    members.forEach(member => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${member.id}</td>
            <td>${member.name}</td>
            <td>${member.issued_books.length}</td>
        `;
        membersTableBody.appendChild(row);
    });
}

document.getElementById('addBookForm').addEventListener('submit', async function(event) {
    event.preventDefault();
    const formData = new FormData(event.target);
    const data = Object.fromEntries(formData.entries());
    data.is_digital = formData.get('is_digital') === 'on';
    const response = await fetch('/books', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    });
    if (response.ok) {
        fetchBooks();
        event.target.reset();
        document.getElementById('digitalBookFields').style.display = 'none';
    }
});

document.getElementById('addMemberForm').addEventListener('submit', async function(event) {
    event.preventDefault();
    const formData = new FormData(event.target);
    const data = Object.fromEntries(formData.entries());
    const response = await fetch('/members', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    });
    if (response.ok) {
        fetchMembers();
        event.target.reset();
    }
});

document.getElementById('issueBookForm').addEventListener('submit', async function(event) {
    event.preventDefault();
    const formData = new FormData(event.target);
    const data = Object.fromEntries(formData.entries());
    const response = await fetch('/issue_book', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    });
    if (response.ok) {
        fetchBooks();
        fetchMembers();
        event.target.reset();
    }
});

document.getElementById('returnBookForm').addEventListener('submit', async function(event) {
    event.preventDefault();
    const formData = new FormData(event.target);
    const data = Object.fromEntries(formData.entries());
    const response = await fetch('/return_book', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    });
    if (response.ok) {
        fetchBooks();
        fetchMembers();
        event.target.reset();
    }
});

fetchGenres();
fetchBooks();
fetchMembers();