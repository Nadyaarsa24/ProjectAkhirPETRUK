void viewBookingHistory(stack<string>& history) {
    if (!history.empty()) {
        cout << "Riwayat Pesanan:" << endl;
        queue<string> tempQueue;
        while (!history.empty()) {
            cout << history.top() << endl;
            tempQueue.push(history.top());
            history.pop();
        }
        while (!tempQueue.empty()) {
            history.push(tempQueue.front());
            tempQueue.pop();
        }
    } else {
        cout << "Tidak Ada Riwayat Pesanan." << endl;
    }
}

int main() {
    list<User> users;
    loadUsers(users);
    vector<Movie> movies = {
        Movie("Movie 1", "10:00 WIB", 40000),
        Movie("Movie 2", "12:00 WIB", 50000),
        Movie("Movie 3", "22:00 WIB", 45000)
    };

    int choice;
    bool loggedIn = false;
    stack<string> history;

    while (true) {
        cout << "1. Registrasi" << endl;
        cout << "2. Login" << endl;
        cout << "3. Tampilkan Film" << endl;
        cout << "4. Pesan Tiket" << endl;
        cout << "5. Lihat History Pesanan" << endl;
        cout << "6. Kelola Film (Admin)" << endl;
        cout << "7. Exit" << endl;
        cout << "Masukkan Pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2:
                loggedIn = loginUser(users);
                if (loggedIn) {
                    cout << "Login Berhasil!" << endl;
                } else {
                    cout << "Username atau Password Invalid!" << endl;
                }
                break;
            case 3:
                displayMovies(movies);
                break;
            case 4:
                if (loggedIn) {
                    bookTicket(movies);
                    history.push("Pemesanan Tiket.");
                } else {
                    cout << "Mohon Login Terlebih Dahulu!" << endl;
                }
                break;
            case 5:
                viewBookingHistory(history);
                break;
            case 6:
                manageMovies(movies);
                break;
            case 7:
                return 0;
            default:
                cout << "Pilihan Invalid. Coba Lagi." << endl;
        }
    }

    return 0;
}
