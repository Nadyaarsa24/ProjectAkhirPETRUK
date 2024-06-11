void manageMovies(vector<Movie>& movies) {
    int choice;
    cout << "1. Tambahkan Film Baru" << endl;
    cout << "2. Ubah Film Yang Tersedia" << endl;
    cout << "Masukkan Pilihan Anda: ";
    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string title, showtime;
    double price;
    cout << "Masukkan Judul Film: ";
    getline(cin, title);
    cout << "Masukkan Waktu: ";
    getline(cin, showtime);
    cout << "Masukkan Harga: ";
    cin >> price;

    if (choice == 1) {
        movies.emplace_back(title, showtime, price);
        cout << "Penambahan Film Berhasil!" << endl;
    } else if (choice == 2) {
        bool found = false;
        for (auto& movie : movies) {
            if (movie.title == title) {
                movie.showtime = showtime;
                movie.price = price;
                cout << "Perubahan Film Berhasil!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Film Tidak Ditemukan." << endl;
        }
    } else {
        cout << "Pilihan Invalid." << endl;
    }

    cout << "Tekan Enter Untuk Kembali ke Menu Utama...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void displayMovies(vector<Movie>& movies) {
    cout << "Film Yang Tersedia:" << endl;
    for (int i = 0; i < movies.size(); ++i) {
        cout << i + 1 << ". " << movies[i].title << " Pukul " << movies[i].showtime 
             << " - Harga: Rp" << movies[i].price << endl;
    }
}

int findAvailableSeat(int* seats, int low, int high) {
    if (low > high) return -1; 

    int mid = low + (high - low) / 2;
    if (seats[mid] == 1) return mid;
    int leftSearch = findAvailableSeat(seats, low, mid - 1);
    if (leftSearch != -1) return leftSearch;
    return findAvailableSeat(seats, mid + 1, high);
}

void bookTicket(vector<Movie>& movies) {
    int movieIndex;
    displayMovies(movies);
    cout << "Pilih Film (nomor): ";
    cin >> movieIndex;
    --movieIndex;

    cout << "Bangku Yang Tersedia Untuk " << movies[movieIndex].title << ":" << endl;
    for (int i = 0; i < 10; ++i) {
        if (movies[movieIndex].availableSeats[i] == 1) {
            cout << i + 1 << ". Bangku Tersedia" << endl;
        } else {
            cout << i + 1 << ". Bangku Sudah Dipesan" << endl;
        }
    }

    int seatIndex;
    cout << "Pilih Nomor Bangku: ";
    cin >> seatIndex;
    --seatIndex;

    if (seatIndex >= 0 && seatIndex < 10 && movies[movieIndex].availableSeats[seatIndex] == 1) {
        movies[movieIndex].availableSeats[seatIndex] = 0;
        cout << "Tiket Berhasil dipesan! Nomor Bangku Anda adalah " << seatIndex + 1 << endl;
        cout << "Harga Tiket: Rp" << movies[movieIndex].price << endl;
        cout << "Barcode: |||| ||| ||||| ||||" << endl;
    } else {
        cout << "Pemilihan Kursi Tidak Valid atau Kursi Sudah Dipesan. Silahkan Coba Lagi." << endl;
    }
}
