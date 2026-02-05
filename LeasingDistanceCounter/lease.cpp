#include "lease.h"
#include <chrono>
#include <ctime>

std::chrono::system_clock::time_point Date::toTimePoint() const
{
    std::tm timeStruct = {};
    timeStruct.tm_year = year - 1900;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_mday = day;
    timeStruct.tm_hour = 0;
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0;
    
    std::time_t time = std::mktime(&timeStruct);
    return std::chrono::system_clock::from_time_t(time);
}

void Lease::setPurchaseDate(int date)
{
    m_startingDate.year = date % 10000;
    m_startingDate.month = (date / 10000) % 100;
    m_startingDate.day = date / 1000000;
    m_startingDate.date = ((m_startingDate.year * 100) 
                          + m_startingDate.month) * 100 
                          + m_startingDate.day;
}

void Lease::setLeasingYears(int years)
{
    m_leasingYears = years;
}

void Lease::setLimit(int limit)
{
    m_limit = limit;
}

void Lease::setKmUsed(int km)
{
    m_kmUsed = km;
}

Date Lease::getCurrentDate()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* ltm = std::localtime(&now_time);

    Date date;
    date.year = 1900 + ltm->tm_year;
    date.month = 1 + ltm->tm_mon;
    date.day = ltm->tm_mday;
    date.date = ((date.year * 100) + date.month) * 100 + date.day;

    return date;
}

Date Lease::getEndingDate()
{
    m_endingDate.year = m_startingDate.year + m_leasingYears;
    m_endingDate.month = m_startingDate.month;
    m_endingDate.day = m_startingDate.day;
    m_endingDate.date = ((m_endingDate.year * 100)
                        + m_endingDate.month) * 100
                        + m_endingDate.day;
    return m_endingDate;
}

int Lease::getLimit()
{
    return m_limit;
}

int Lease::getKmUsed()
{
    return m_kmUsed;
}

int Lease::getDLeft(Date targetDate)
{
    Date currentDate = getCurrentDate();
    
    auto targetTimePoint = targetDate.toTimePoint();
    auto currentTimePoint = currentDate.toTimePoint();
    
    auto duration = targetTimePoint - currentTimePoint;
    int daysLeft = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
    
    return daysLeft > 0 ? daysLeft : 0;
}

int Lease::getKmLeft()
{
    int kmLeft = m_limit - m_kmUsed;
    return kmLeft;
}

int Lease::getKmLeftThisYear()
{
    int nextLeaseYear = m_startingDate.date;
    int leaseYear = 0;
    int kmLeftThisYear = 0;

    while (getCurrentDate().date > nextLeaseYear)
    {
        leaseYear++;
        nextLeaseYear = nextLeaseYear + 10000;
        if (leaseYear == 10) //This is a failsafe
        {
            return 1;
        }
    }

    kmLeftThisYear = ((m_limit / m_leasingYears) * leaseYear) - m_kmUsed;

    return kmLeftThisYear;
}

int Lease::getKmLeftDaily()
{
    int kmLeftDaily = getKmLeft() / getDLeft(getEndingDate());
    return kmLeftDaily;
}

int Lease::getKmLeftDailyThisYear()
{
    Date nextLeaseYear;
    nextLeaseYear.year = m_startingDate.year;
    nextLeaseYear.month = m_startingDate.month;
    nextLeaseYear.day = m_startingDate.day;

    while (getCurrentDate().date > nextLeaseYear.date)
    {
        nextLeaseYear.year++;
        nextLeaseYear.date = 0;
        nextLeaseYear.date = ((nextLeaseYear.year * 100)
                             + nextLeaseYear.month) * 100
                             + nextLeaseYear.day;
    }

    int kmLeftDailyThisYear = getKmLeftThisYear() / getDLeft(nextLeaseYear);   

    return kmLeftDailyThisYear;
}