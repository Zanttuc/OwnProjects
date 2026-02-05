#ifndef LEASE_H
#define LEASE_H

#include <string>
#include <chrono>

struct Date {
    int day;
    int month;
    int year;
    int date;
    
    // Convert to chrono time_point
    std::chrono::system_clock::time_point toTimePoint() const;
};

class Lease
{
    public:
        void setPurchaseDate(int date);
        void setLeasingYears(int years);
        void setLimit(int limit);
        void setKmUsed(int km);

        Date getCurrentDate();
        Date getEndingDate();

        int getLimit();
        int getKmUsed();
        int getDLeft(Date targetDate);
        int getKmLeft();
        int getKmLeftThisYear();
        int getKmLeftDaily();
        int getKmLeftDailyThisYear();

    private:
        Date m_startingDate;
        Date m_endingDate;
        int m_leasingYears;
        int m_limit;
        int m_kmUsed;
        int m_dayDiff;
};

#endif