#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

// Structure for User
struct User {
    char username[50];
    char password[50];
};

// Class for Movie
class Movie {
public:
    string title;
    string showtime;
    double price;
    int availableSeats[10]; // assuming 10 seats for simplicity

    Movie(string t, string s, double p) : title(t), showtime(s), price(p) {
        for (int i = 0; i < 10; ++i) {
            availableSeats[i] = 1; // all seats available initially
        }
    }
};

// Function to register user
void registerUser(list<User>& users) {
    User* newUser = new User;
    cout << "Masukkan username: ";
    cin >> newUser->username;
    cout << "Masukkan password: ";
    cin >> newUser->password;
    users.push_back(*newUser);

    ofstream outFile("users.txt", ios::app);
    outFile << newUser->username << " " << newUser->password << endl;
    outFile.close();
    delete newUser;
}

// Function to login user
bool loginUser(list<User>& users) {
    char username[50];
    char password[50];
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    for (User user : users) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            return true;
        }
    }
    return false;
}

// Function to load users from file
void loadUsers(list<User>& users) {
    ifstream inFile("users.txt");
    if (!inFile) return;
    User user;
    while (inFile >> user.username >> user.password) {
        users.push_back(user);
    }
    inFile.close();
}

// Function to add or update movie schedule
void manageMovies(vector<Movie>& movies) {
    int choice;
    cout << "1. Tambahkan Film Baru" << endl;
    cout << "2. Ubah Film Yang Tersedia" << endl;
    cout << "Masukkan Pilihan Anda: ";
    cin >> choice;

    // Clear input buffer before taking string input
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

    // Pause to show message before returning to main menu
    cout << "Tekan Enter Untuk Kembali ke Menu Utama...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Function to display movie schedule
void displayMovies(vector<Movie>& movies) {
    cout << "Film Yang Tersedia:" << endl;
    for (int i = 0; i < movies.size(); ++i) {
        cout << i + 1 << ". " << movies[i].title << " Pukul " << movies[i].showtime 
             << " - Harga: Rp" << movies[i].price << endl;
    }
}

// Divide and Conquer technique for searching available seats
int findAvailableSeat(int* seats, int low, int high) {
    if (low > high) return -1; // No seat found

    int mid = low + (high - low) / 2;
    if (seats[mid] == 1) return mid;
    int leftSearch = findAvailableSeat(seats, low, mid - 1);
    if (leftSearch != -1) return leftSearch;
    return findAvailableSeat(seats, mid + 1, high);
}

// Function to book ticket
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
        // Generate a simple barcode representation
        cout << "Barcode: |||| ||| ||||| ||||" << endl;
    } else {
        cout << "Pemilihan Kursi Tidak Valid atau Kursi Sudah Dipesan. Silahkan Coba Lagi." << endl;
    }
}

// Function to view booking history using stack
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

    return 0;
}
