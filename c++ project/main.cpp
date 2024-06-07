#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <regex>
#include <chrono>
#include <cstdlib>
#include <conio.h>


struct Showtime {
    std::string day;
    std::string time;
};

struct CinemaRoom {
    CinemaRoom() {}

    std::vector<std::vector<bool>> seats;

    CinemaRoom(int rows, int cols) : seats(rows, std::vector<bool>(cols, false)) {}
};

std::map<std::string, std::vector<Showtime>> movieShowtimes;
std::map<std::string, std::map<std::string, std::map<std::string, CinemaRoom>>> cinemaRooms;

void saveData() {
    std::ofstream outFile("cinema_data.txt");
    for (const auto& movie : cinemaRooms) {
        for (const auto& day : movie.second) {
            for (const auto& time : day.second) {
                outFile << movie.first << ";" << day.first << ";" << time.first;
                for (const auto& row : time.second.seats) {
                    for (bool seat : row) {
                        outFile << ";" << seat;
                    }
                }
                outFile << std::endl;
            }
        }
    }
    outFile.close();
}

void loadData() {
    std::ifstream inFile("cinema_data.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            std::string movie, day, time;
            std::getline(ss, movie, ';');
            std::getline(ss, day, ';');
            std::getline(ss, time, ';');
            CinemaRoom room(10, 10);
            for (auto& row : room.seats) {
                for (std::_Bit_reference seat : row) {
                    std::string seatStr;
                    std::getline(ss, seatStr, ';');
                    seat = std::stoi(seatStr);
                }
            }
            cinemaRooms[movie][day][time] = room;
        }
        inFile.close();
    }
}

void initializeData() {
    movieShowtimes["Dune"] = {{"Monday", "12:00 PM"}, {"Wednesday", "02:00 PM"}};
    movieShowtimes["Dune2"] = {{"Tuesday", "11:00 AM"}, {"Friday", "01:00 PM"}};
    movieShowtimes["The Notebook"] = {{"Wednesday", "03:00 PM"}, {"Saturday", "05:00 PM"}};
    movieShowtimes["The Shawshank Redemption"] = {{"Monday", "01:00 PM"}, {"Thursday", "03:00 PM"}};
    movieShowtimes["The Godfather"] = {{"Tuesday", "02:00 PM"}, {"Friday", "04:00 PM"}};
    movieShowtimes["The Dark Knight"] = {{"Wednesday", "04:00 PM"}, {"Saturday", "06:00 PM"}};
    movieShowtimes["Pulp Fiction"] = {{"Thursday", "05:00 PM"}, {"Sunday", "07:00 PM"}};
    movieShowtimes["Schindler's List"] = {{"Monday", "03:00 PM"}, {"Wednesday", "05:00 PM"}};
    movieShowtimes["The Lord of the Rings: The Return of the King"] = {{"Tuesday", "01:00 PM"}, {"Thursday", "03:00 PM"}};
    movieShowtimes["Fight Club"] = {{"Wednesday", "06:00 PM"}, {"Friday", "08:00 PM"}};
    movieShowtimes["Forrest Gump"] = {{"Thursday", "07:00 PM"}, {"Saturday", "09:00 PM"}};
    movieShowtimes["Inception"] = {{"Monday", "01:00 PM"}, {"Wednesday", "03:00 PM"}};
    movieShowtimes["The Matrix"] = {{"Tuesday", "02:00 PM"}, {"Thursday", "04:00 PM"}};
    movieShowtimes["The Silence of the Lambs"] = {{"Wednesday", "03:00 PM"}, {"Friday", "05:00 PM"}};
    movieShowtimes["Se7en"] = {{"Thursday", "04:00 PM"}, {"Saturday", "06:00 PM"}};
    movieShowtimes["Gladiator"] = {{"Monday", "05:00 PM"}, {"Wednesday", "07:00 PM"}};
    movieShowtimes["Saving Private Ryan"] = {{"Tuesday", "06:00 PM"}, {"Thursday", "08:00 PM"}};
    movieShowtimes["Braveheart"] = {{"Wednesday", "07:00 PM"}, {"Friday", "09:00 PM"}};
    movieShowtimes["Titanic"] = {{"Thursday", "08:00 PM"}, {"Saturday", "10:00 PM"}};
    movieShowtimes["The Lion King"] = {{"Monday", "10:00 AM"}, {"Wednesday", "12:00 PM"}};
    movieShowtimes["Jurassic Park"] = {{"Tuesday", "11:00 AM"}, {"Thursday", "01:00 PM"}};
    movieShowtimes["The Avengers"] = {{"Wednesday", "01:00 PM"}, {"Friday", "03:00 PM"}};
    movieShowtimes["Star Wars: Episode V"] = {{"Thursday", "02:00 PM"}, {"Saturday", "04:00 PM"}};
    for (const auto& [movie, showtimes] : movieShowtimes) {
        for (const auto& showtime : showtimes) {
            cinemaRooms[movie][showtime.day][showtime.time] = CinemaRoom(10, 10);
        }
    }
    loadData();
}

const std::string daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int getCurrentDayOfWeek() {
    time_t t = time(0);
    struct tm *now = localtime(&t);
    return now->tm_wday;
}

void viewProgramForDay(const std::string &day) {
    std::ifstream file(day + ".txt");
    std::string line;

    if (file.is_open()) {
        std::cout << "Program for " << day << ":" << std::endl;

        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    } else {
        std::cout << "Unable to open the file '" << day << ".txt'" << std::endl;
    }
}

void viewThisWeeksProgram() {
    int currentDay = getCurrentDayOfWeek();
    std::string userChoice;

    while (true) {
        std::cout << "This Week's Program from today:" << std::endl;
        for (int i = 0; i < 7; ++i) {
            std::cout << daysOfWeek[(currentDay + i) % 7] << std::endl;
        }

        std::cout << "Enter the day you want to see (or type 'back' to return to menu): ";
        std::cin >> userChoice;

        if (userChoice == "back") {
            return;
        }

        bool validDay = false;
        for (const std::string &day : daysOfWeek) {
            if (userChoice == day) {
                validDay = true;
                viewProgramForDay(userChoice);
                break;
            }
        }

        if (!validDay) {
            std::cout << "Invalid day. Please enter a valid day of the week." << std::endl;
        }
    }
}

void viewAllMovies() {
    std::ifstream file("movies.txt");
    std::string line;

    if (file.is_open()) {
        int movieCount = 1;

        while (std::getline(file, line)) {
            std::cout << movieCount << ". " << line << std::endl;
            ++movieCount;
        }
        file.close();

        std::string movieName;
        std::cout << "Enter the name of the movie you want to view details (0 to go back): ";
        std::cin.ignore();
        std::getline(std::cin, movieName);
        if (movieName != "0") {
            std::ifstream movieFile(movieName + ".txt");
            if (movieFile.is_open()) {
                while (std::getline(movieFile, line)) {
                    std::cout << line << std::endl;
                }
                movieFile.close();
            } else {
                std::cout << "Unable to open the details for this movie." << std::endl;
            }
        }
    } else {
        std::cout << "Unable to open the file 'movies.txt'" << std::endl;
    }
}

void viewMoviesByGenre() {
    std::string genre;
    std::ifstream file;
    std::string line;

    while (true) {
        std::cout << "Enter the genre you want to see (or type 'back' to return to menu): ";
        std::cin >> genre;

        if (genre == "back") {
            return;
        }

        std::string filename = genre + ".txt";
        file.open(filename);

        if (file.is_open()) {

            std::cout << "Movies in " << genre << " genre:" << std::endl;
            while (std::getline(file, line)) {
                std::cout << line << std::endl;
            }
            file.close();
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        } else {
            std::cout << "Unable to open the file '" << genre << ".txt'" << std::endl;
        }
    }
}

void displaySeatingMap(const CinemaRoom &room) {
    std::cout << "  A B C D E F G H" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 8; ++j) {
            std::cout << (room.seats[i][j] ? "X " : "O ");
        }
        std::cout << std::endl;
    }
}

bool validatePaymentDetails(const std::string &paymentDetails) {
    std::regex regex("\\d{13}");
    return std::regex_match(paymentDetails, regex);
}

void buyTicket() {
    std::string movieName;
    std::cout << "Enter the name of the movie you want to watch: ";
    std::cin.ignore();
    std::getline(std::cin, movieName);

    if (movieShowtimes.find(movieName) == movieShowtimes.end()) {
        std::cout << "Movie not found." << std::endl;
        return;
    }

    std::cout << "Available days for " << movieName << ":" << std::endl;
    std::map<std::string, std::vector<Showtime>> dayMap;
    for (const auto &showtime : movieShowtimes[movieName]) {
        std::cout << showtime.day << std::endl;
        dayMap[showtime.day].push_back(showtime);
    }

    std::string chosenDay;
    std::cout << "Enter the day: ";
    std::cin >> chosenDay;

    if (dayMap.find(chosenDay) == dayMap.end()) {
        std::cout << "Day not found." << std::endl;
        return;
    }

    std::string chosenTime = dayMap[chosenDay][0].time;
    CinemaRoom &room = cinemaRooms[movieName][chosenDay][chosenTime];

    std::cout << "Seating map for " << movieName << " on " << chosenDay << ":" << std::endl;
    displaySeatingMap(room);

    int numTickets;
    std::cout << "Enter the number of tickets you want to buy: ";
    std::cin >> numTickets;

    std::vector<std::pair<int, int>> selectedSeats;
    for (int i = 0; i < numTickets; ++i) {
        int row;
        char col;
        bool isValidSeat;
        do {
            std::cout << "Enter the row and column for ticket " << i + 1 << " (e.g., 1 A): ";
            std::cin >> row >> col;

            col = toupper(col);

            --row;

            isValidSeat = (row >= 0 && row < room.seats.size() && col >= 'A' && col < 'A' + room.seats[0].size() && !room.seats[row][col - 'A']);
            if (!isValidSeat) {
                std::cout << "Invalid or already reserved seat." << std::endl;
            }
        } while (!isValidSeat);

        room.seats[row][col - 'A'] = true;
        selectedSeats.push_back({row + 1, col});
    }

    std::string paymentDetails;
    do {
        std::cout << "Total: "<< numTickets*20.00<< "lei."<< std::endl;
        std::cout << "Enter payment details (14-digit number): ";
        std::cin.ignore();
        std::getline(std::cin, paymentDetails);
    } while (!validatePaymentDetails(paymentDetails));

    std::string name, surname;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your surname: ";
    std::getline(std::cin, surname);

    std::string folderName = name + "_" + surname;
    std::filesystem::create_directory(folderName);

    auto currentTime = std::chrono::system_clock::now();
    std::time_t timestamp = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y%m%d_%H%M%S");
    std::string timestampStr = ss.str();

    std::string last_dig = paymentDetails.substr(paymentDetails.length() - 4);

    for (int i = 0; i < numTickets; ++i) {
        std::ofstream ticketFile(folderName + "/ticket_" + timestampStr + "_" + std::to_string(i + 1) + ".txt");
        ticketFile << "---- TICKET ----\n";
        ticketFile << "Movie: " << movieName << "\n";
        ticketFile << "Day: " << chosenDay << "\n";
        ticketFile << "Time: " << chosenTime << "\n";
        ticketFile << "Seat: (" << selectedSeats[i].first << "," << static_cast<char>(selectedSeats[i].second) << ")\n";
        std::cout << "Payment Details: **********" << last_dig << std::endl;
        ticketFile << "----------------\n";
        ticketFile.close();


        std::cout << "Ticket " << i + 1 << " details:" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "Movie: " << movieName << std::endl;
        std::cout << "Day: " << chosenDay << std::endl;
        std::cout << "Time: " << chosenTime << std::endl;
        std::cout << "Seat: (" << selectedSeats[i].first << "," << static_cast<char>(selectedSeats[i].second) << ")" << std::endl;
        std::cout << "Payment Details: **********" << last_dig << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout <<std::endl;
        std::cout <<std::endl;



    }

    saveData();
    std::cout << "Tickets booked successfully! Confirmation saved in the folder '" << folderName << "'." << std::endl;
}


void viewSpecificMovieProgram() {

    std::string movieName;
    std::cout << "Enter the name of the movie you want to view the program for: ";
    std::cin.ignore();
    std::getline(std::cin, movieName);

    if (movieShowtimes.find(movieName) == movieShowtimes.end()) {
        std::cout << "Movie not found." << std::endl;
        return;
    }

    std::cout << "Showtimes for " << movieName << ":" << std::endl;
    for (const auto &showtime : movieShowtimes[movieName]) {
        std::cout << showtime.day << " at " << showtime.time << std::endl;
    }

    std::cout << "Press Enter to continue...";
    std::cin.get();
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int main() {
    initializeData();
    int choice;

    while (true) {
        std::cout << "Cinema Ticket Booking System" << std::endl;
        std::cout << "1. View Today's Program" << std::endl;
        std::cout << "2. View This Week's Program" << std::endl;
        std::cout << "3. View All Movies" << std::endl;
        std::cout << "4. View Movies by Genre" << std::endl;
        std::cout << "5. Buy Ticket" << std::endl;
        std::cout << "6. View Specific Movie Program" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:

                viewProgramForDay(daysOfWeek[getCurrentDayOfWeek()]);
                break;
            case 2:
                viewThisWeeksProgram();
                break;
            case 3:
                viewAllMovies();
                break;
            case 4:
                viewMoviesByGenre();
                break;
            case 5:
                buyTicket();
                break;
            case 6:
                viewSpecificMovieProgram();
                break;
            case 7:
                std::cout << "Exiting the program..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
