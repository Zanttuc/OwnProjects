#include "lease.h"

#include <iostream>

int main()
{
    Lease lease;

    std::cout << "Welcome to your leasing car distance counter!" << std::endl;

    std::cout << "Please set the date you started your lease (DDMMYYYY): ";
    int date;
    std::cin >> date;
    lease.setPurchaseDate(date);

    std::cout << "Please set the length of your leasing contract in years: ";
    int leasLenght;
    std::cin >> leasLenght;
    lease.setLeasingYears(leasLenght);

    std::cout << "Please set the limit assigned in your leasing contract in kilometers: ";
    int limit = 0;
    std::cin >> limit;
    lease.setLimit(limit);

    std::cout << "Please set your driven kilometers: ";
    int km = 0;
    std::cin >> km;
    lease.setKmUsed(km);

    std::cout << "\nYou have used " << lease.getKmUsed() << " kilometers." << std::endl;
    std::cout << "You have " << lease.getKmLeft() << " kilometers left in your leasing contract." << std::endl;
    std::cout << "You have " << lease.getKmLeftThisYear() << " kilometers left for this year." << std::endl;
    std::cout << "You have " << lease.getKmLeftDaily() << " kilometers / day left in your leasing contract." << std::endl;
    std::cout << "You have " << lease.getKmLeftDailyThisYear() << " kilometers / day left for this year." << std::endl;
    std::cout << "\nThank you for using leasing car distance counter - designed by Zanttuc!" << std::endl;

    return 0;
}