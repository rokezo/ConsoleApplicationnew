#include <iostream>

class DateTime {
private:
    int day_;
    int month_;
    int year_;
    int hours_;
    int minutes_;
    int seconds_;

    // Helper function to check if a year is a leap year
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }

    // Helper function to get the number of days in a month
    int daysInMonth(int month, int year) const {
        if (month == 2) {
            return isLeapYear(year) ? 29 : 28;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        }
        else {
            return 31;
        }
    }

public:
    // Constructor with default values
    DateTime(int day = 1, int month = 1, int year = 1970, int hours = 0, int minutes = 0, int seconds = 0) {
        setDay(day);
        setMonth(month);
        setYear(year);
        setHours(hours);
        setMinutes(minutes);
        setSeconds(seconds);
    }

    // Getters
    int getDay() const {
        return day_;
    }

    int getMonth() const {
        return month_;
    }

    int getYear() const {
        return year_;
    }

    int getHours() const {
        return hours_;
    }

    int getMinutes() const {
        return minutes_;
    }

    int getSeconds() const {
        return seconds_;
    }

    // Setters
    void setDay(int day) {
        if (day < 1 || day > daysInMonth(month_, year_)) {
            throw std::runtime_error("Invalid day");
        }
        day_ = day;
    }

    void setMonth(int month) {
        if (month < 1 || month > 12) {
            throw std::runtime_error("Invalid month");
        }
        month_ = month;
    }

    void setYear(int year) {
        if (year < 1) {
            throw std::runtime_error("Invalid year");
        }
        year_ = year;
    }

    void setHours(int hours) {
        if (hours < 0 || hours > 23) {
            throw std::runtime_error("Invalid hours");
        }
        hours_ = hours;
    }

    void setMinutes(int minutes) {
        if (minutes < 0 || minutes > 59) {
            throw std::runtime_error("Invalid minutes");
        }
        minutes_ = minutes;
    }

    void setSeconds(int seconds) {
        if (seconds < 0 || seconds > 59) {
            throw std::runtime_error("Invalid seconds");
        }
        seconds_ = seconds;
    }

    // Operator overloads
    DateTime operator+(const DateTime& other) const {
        int totalDays = day_ + other.day_ - 1;
        int totalMonths = month_ + other.month_ - 1;
        int totalYears = year_ + other.year_;
        int totalHours = hours_ + other.hours_;
        int totalMinutes = minutes_ + other.minutes_;
        int totalSeconds = seconds_ + other.seconds_;

        int carryDays = totalDays / daysInMonth(month_, year_);
        int carryMonths = totalMonths / 12;

        totalDays %= daysInMonth(month_, year_);
        totalMonths %= 12;

        totalYears += carryMonths;
        totalMonths += carryDays;

        return DateTime(totalDays + 1, totalMonths + 1, totalYears, totalHours, totalMinutes, totalSeconds);
    }

    DateTime operator-(const DateTime& other) const {
        int totalDays = day_ - other.day_;
        int totalMonths = month_ - other.month_;
        int totalYears = year_ - other.year_;
        int totalHours = hours_ - other.hours_;
        int totalMinutes = minutes_ - other.minutes_;
        int totalSeconds = seconds_ - other.seconds_;

        if (totalDays < 0) {
            totalDays += daysInMonth(month_ - 1, year_);
            totalMonths--;
        }

        if (totalMonths < 0) {
            totalMonths += 12;
            totalYears--;
        }

        return DateTime(totalDays, totalMonths, totalYears, totalHours, totalMinutes, totalSeconds);
    }

    DateTime& operator+=(int days) {
        day_ += days;
        while (day_ > daysInMonth(month_, year_)) {
            day_ -= daysInMonth(month_, year_);
            month_++;
            if (month_ > 12) {
                month_ = 1;
                year_++;
            }
        }
        return