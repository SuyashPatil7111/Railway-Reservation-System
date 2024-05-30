#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

class Passenger {
private:
    std::string name;
    std::string contactNumber;
    std::string seatNumber;

public:
    Passenger(const std::string& name, const std::string& contactNumber, const std::string& seatNumber) {
        this->name = name;
        this->contactNumber = contactNumber;
        this->seatNumber = seatNumber;
    }

    std::string getName() const {
        return name;
    }

    std::string getContactNumber() const {
        return contactNumber;
    }

    std::string getSeatNumber() const {
        return seatNumber;
    }
};

class Train {
private:
    std::string trainNumber;
    std::string trainName;
    std::string departureStation;
    std::string arrivalStation;
    int totalSeats;
    std::vector<bool> seatsAvailable;
    std::vector<Passenger> passengers;

public:
    Train(std::string trainNumber, std::string trainName, std::string departureStation, std::string arrivalStation, int totalSeats) {
        this->trainNumber = trainNumber;
        this->trainName = trainName;
        this->departureStation = departureStation;
        this->arrivalStation = arrivalStation;
        this->totalSeats = totalSeats;
        seatsAvailable.resize(totalSeats, true); // Initialize all seats as available
    }

    std::string getTrainNumber() const {
        return trainNumber;
    }

    std::string getTrainName() const {
        return trainName;
    }

    std::string getDepartureStation() const {
        return departureStation;
    }

    std::string getArrivalStation() const {
        return arrivalStation;
    }

    int getTotalSeats() const {
        return totalSeats;
    }

    int getAvailableSeats() const {
        int count = 0;
        for (bool seatAvailable : seatsAvailable) {
            if (seatAvailable) {
                count++;
            }
        }
        return count;
    }

    void displayAvailableSeats() const {
        std::cout << "Available Seats for Train " << trainNumber << " (" << trainName << "):\n";
        std::cout << "----------------------------------------------\n";
        std::cout << "Seat Number    Status\n";
        std::cout << "----------------------------------------------\n";
        for (int i = 0; i < totalSeats; ++i) {
            std::cout << std::setw(10) << std::left << ("Seat " + std::to_string(i + 1));
            if (seatsAvailable[i]) {
                std::cout << "Available\n";
            } else {
                std::cout << "Booked\n";
            }
        }
        std::cout << "----------------------------------------------\n";
    }

    void bookTicket(const Passenger& passenger, int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats) {
            std::cout << "Invalid seat number!\n";
            return;
        }

        if (!seatsAvailable[seatNumber - 1]) {
            std::cout << "Seat " << seatNumber << " is already booked.\n";
            return;
        }

        seatsAvailable[seatNumber - 1] = false;
        passengers.push_back(passenger);

        std::cout << "Ticket booked successfully!\n";
        std::cout << "Passenger Name: " << passenger.getName() << std::endl;
        std::cout << "Contact Number: " << passenger.getContactNumber() << std::endl;
        std::cout << "Seat Number: " << passenger.getSeatNumber() << std::endl;
    }

    void cancelTicket(const std::string& passengerName) {
        auto it = std::find_if(passengers.begin(), passengers.end(), [passengerName](const Passenger& p) {
            return p.getName() == passengerName;
        });

        if (it != passengers.end()) {
            seatsAvailable[std::stoi(it->getSeatNumber().substr(5)) - 1] = true;
            passengers.erase(it);
            std::cout << "Ticket canceled successfully.\n";
        } else {
            std::cout << "Passenger not found or no ticket booked.\n";
        }
    }

    void displayPassengerTickets() const {
        if (passengers.empty()) {
            std::cout << "No tickets booked for this train.\n";
        } else {
            std::cout << "Passenger Tickets for Train " << trainNumber << " (" << trainName << "):\n";
            std::cout << "----------------------------------------------\n";
            std::cout << "Passenger Name    Contact Number    Seat Number\n";
            std::cout << "----------------------------------------------\n";
            for (const Passenger& passenger : passengers) {
                std::cout << std::setw(17) << std::left << passenger.getName();
                std::cout << std::setw(17) << passenger.getContactNumber();
                std::cout << passenger.getSeatNumber() << std::endl;
            }
            std::cout << "----------------------------------------------\n";
        }
    }
};  

int main() {
    Train train("12345", "Express", "Station A", "Station B", 50);

    char choice;
    do {
        std::cout << "\n1. Display Train Schedule\n2. Display Available Seats\n3. Book Ticket\n4. Cancel Ticket\n5. Display Passenger's Tickets\n6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1': {
                std::cout << "\nTrain Schedule:\n";
                train.displayAvailableSeats();
                break;
            }
            case '2': {
                train.displayAvailableSeats();
                break;
            }
            case '3': {
                std::string name, contactNumber;
                int seatNumber;
                std::cout << "Enter Passenger Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter Contact Number: ";
                std::getline(std::cin, contactNumber);
                std::cout << "Enter Seat Number: ";
                std::cin >> seatNumber;

                Passenger passenger(name, contactNumber, "Seat " + std::to_string(seatNumber));
                train.bookTicket(passenger, seatNumber);
                break;
            }
            case '4': {
                std::string name;
                std::cout << "Enter Passenger Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                train.cancelTicket(name);
                break;
            }
            case '5': {
                train.displayPassengerTickets();
                break;
            }
            case '6': {
                std::cout << "Exiting program.\n";
                break;
            }
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != '6');

    

    return 0;
}
