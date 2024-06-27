#pragma once
#include<iostream>
using namespace std;

class Date {
    uint16_t year;
    uint8_t month;
    uint8_t day;

    uint8_t checkMonth(uint8_t monthP)
    {
        if (monthP < 1) return 1;
        if (monthP > 12) return 12;
        return monthP;
    }
    uint8_t checkDay(uint8_t dayP, uint8_t monthP, uint16_t yearP)
    {
        const uint8_t maxDays{ Date::daysInMonth(monthP, yearP) };
        if (dayP < 1) return 1;
        if (dayP > maxDays) return maxDays;
        return dayP;
    }
public:
    static uint8_t daysInMonth(uint8_t month, uint16_t year)
    {
        return 30 + (((month < 8) and (month % 2 != 0)) or ((month >= 8) and (month % 2 == 0))) + ((month == 2) * (-2) + isLeapYear(year));
    }

    static bool isLeapYear(uint16_t year)
    {
        return year % 400 == 0 or year % 4 == 0 and year % 100 != 0;
    }
    static const uint8_t maxMonth{ 12 };

    Date() : Date(1, 1, 1970) {}
    Date(uint8_t dayP, uint8_t monthP, uint16_t yearP)
        : year{ yearP }, month{ checkMonth(monthP) }, day{ checkDay(dayP,month,yearP) } {}

    Date& setDay(uint8_t dayP) { day = checkDay(dayP, month, year); return *this; }
    Date& setMonth(uint8_t monthP) { month = checkMonth(monthP); day = checkDay(day, month, year); return *this; }
    Date& setYear(uint16_t yearP) { year = yearP; return *this; }

    uint8_t getDay() const { return day; }
    uint8_t getMonth() const { return month; }
    uint16_t getYear() const { return year; }

    Date& init(uint8_t dayP, uint8_t monthP, uint16_t yearP);

    friend ostream& operator<<(ostream& out, const Date& object);
    friend istream& operator>>(istream& in, Date& object);

    friend bool operator==(const Date& left, const Date& right);
    friend bool operator!=(const Date& left, const Date& right);
};

Date& Date::init(uint8_t dayP, uint8_t monthP, uint16_t yearP)
{
    setDay(dayP); setMonth(monthP); setYear(yearP); return *this;
}

ostream& operator<<(ostream& out, const Date& object)
{
    out << (int)object.day << '.' << (int)object.month << '.' << object.year; return out;
}

istream& operator>>(istream& in, Date& object)
{
    in >> object.day >> object.month >> object.year;
    return in;
}

bool operator==(const Date& left, const Date& right)
{
    return (left.day == right.day and left.month == right.month and left.year == right.year);
}

bool operator!=(const Date& left, const Date& right)
{
    return !(left == right);
}

class Man
{
    uint16_t id;
    char* surname;
    char* name;
    char* secondName;
    Date dateOfBirth;
public:
    Man() : id{ 0 }, surname{ nullptr }, name{ nullptr }, secondName{ nullptr }, dateOfBirth() {}
    Man(uint16_t idP, const char* surnameP, const char* nameP, const char* secondNameP, uint8_t dayP, uint8_t monthP, uint16_t yearP);
    Man(const Man& object);
    Man(Man&& object);

    Man& setId(uint16_t idP) { id = idP; return *this; }

    Man& setSurname(const char* surnameP);
    Man& setName(const char* nameP);
    Man& setSecondName(const char* secondNameP);

    Man& setDateOfBirth(uint8_t dayP, uint8_t monthP, uint16_t yearP) { dateOfBirth.init(dayP, monthP, yearP); return *this; }

    Man& init(uint16_t idP, const char* surnameP, const char* nameP, const char* secondNameP, uint8_t dayP, uint8_t monthP, uint16_t yearP);

    const uint16_t getId()const { return id; }
    const char* getSurname()const { return surname; }
    const char* getName()const { return name; }
    const char* getSecondName()const { return secondName; }
    uint8_t getDateOfBirthDay()const { return dateOfBirth.getDay(); }
    uint8_t getDateOfBirthMonth()const { return dateOfBirth.getMonth(); }
    uint16_t getDateOfBirthYear()const { return dateOfBirth.getYear(); }

    Man& operator=(const Man& object);
    Man& operator=(Man&& object);

    friend ostream& operator<<(ostream& out, const Man& object);
    friend istream& operator>>(istream& out, Man& object);
    friend bool operator==(const Man& left, const Man& right);
    friend bool operator!=(const Man& left, const Man& right);

    ~Man() { delete[]surname; delete[]name; delete[]secondName; }
};

Man::Man(uint16_t idP, const char* surnameP, const char* nameP, const char* secondNameP, uint8_t dayP, uint8_t monthP, uint16_t yearP) :
    id{ idP }, surname{ new char[strlen(surnameP) + 1] }, name{ new char[strlen(nameP) + 1] }, secondName{ new char[strlen(secondNameP) + 1] }, dateOfBirth{ dayP,monthP,yearP }
{
    strcpy_s(surname, strlen(surnameP) + 1, surnameP);
    strcpy_s(name, strlen(nameP) + 1, nameP);
    strcpy_s(secondName, strlen(secondNameP) + 1, secondNameP);
}

Man::Man(const Man& object) :
    id{ object.id }, surname{ new char[strlen(object.surname) + 1] }, name{ new char[strlen(object.name) + 1] }, secondName{ new char[strlen(object.secondName) + 1] }, dateOfBirth{ object.dateOfBirth }
{
    strcpy_s(surname, strlen(object.surname) + 1, object.surname);
    strcpy_s(name, strlen(object.name) + 1, object.name);
    strcpy_s(secondName, strlen(object.secondName) + 1, object.secondName);
}

Man::Man(Man&& object) :
    id{ object.id }, surname{ object.surname }, name{ object.name }, secondName{ object.secondName }, dateOfBirth{ object.dateOfBirth }
{
    object.id = 0;
    object.surname = nullptr;
    object.name = nullptr;
    object.secondName = nullptr;
    object.dateOfBirth.init(0, 0, 0);
}

Man& Man::setSurname(const char* surnameP)
{
    delete[] surname;
    surname = new char[strlen(surnameP) + 1];
    strcpy_s(surname, strlen(surnameP) + 1, surnameP);
    return *this;
}

Man& Man::setName(const char* nameP)
{
    delete[] name;
    name = new char[strlen(nameP) + 1];
    strcpy_s(name, strlen(nameP) + 1, nameP);
    return *this;
}

Man& Man::setSecondName(const char* secondNameP)
{
    delete[] secondName;
    secondName = new char[strlen(secondNameP) + 1];
    strcpy_s(secondName, strlen(secondNameP) + 1, secondNameP);
    return *this;
}

Man& Man::init(uint16_t idP, const char* surnameP, const char* nameP, const char* secondNameP, uint8_t dayP, uint8_t monthP, uint16_t yearP)
{
    id = idP;
    setSurname(surnameP); setName(nameP); setSecondName(secondNameP);
    dateOfBirth.init(dayP, monthP, yearP);
    return *this;
}

Man& Man::operator=(const Man& object)
{
    if (this == &object) { return *this; }

    delete[]surname;
    delete[]name;
    delete[]secondName;

    id = object.id;
    surname = new char[strlen(object.surname) + 1];
    name = new char[strlen(object.name) + 1];
    secondName = new char[strlen(object.secondName) + 1];
    dateOfBirth = object.dateOfBirth;

    strcpy_s(surname, strlen(object.surname) + 1, object.surname);
    strcpy_s(name, strlen(object.name) + 1, object.name);
    strcpy_s(secondName, strlen(object.secondName) + 1, object.secondName);

    return *this;
}

Man& Man::operator=(Man&& object)
{
    if (this == &object) { return *this; }

    delete[]surname;
    delete[]name;
    delete[]secondName;

    id = object.id;
    surname = object.surname;
    name = object.name;
    secondName = object.secondName;
    dateOfBirth = object.dateOfBirth;

    object.id = 0;
    object.surname = nullptr;
    object.name = nullptr;
    object.secondName = nullptr;
    object.dateOfBirth.init(0, 0, 0);

    return *this;
}

ostream& operator<<(ostream& out, const Man& object)
{
    if (object.id and object.surname and object.name and object.secondName)
    {
        out << '[' << "\033[1;93m" << "id: " << "\033[0m" << object.id << ' ' << object.surname
            << ' ' << object.name << ' ' << object.secondName << ' ' << object.dateOfBirth << ']' << ' ';
    }
    else { out << "[empty person]"; }
    return out;
}

istream& operator>>(istream& in, Man& object)
{
    in >> object.id >> object.surname >> object.name >> object.secondName >> object.dateOfBirth;
    return in;
}

bool operator==(const Man& left, const Man& right)
{
    return (left.id == right.id and strcmp(left.surname, right.surname) == 0 and strcmp(left.name, right.name) == 0 and strcmp(left.secondName, right.secondName) == 0 and left.dateOfBirth == right.dateOfBirth);
}

bool operator!=(const Man& left, const Man& right) { return !(left == right); }\

class Flat
{
    uint32_t number;
    uint16_t roomsCount;
    Man* occupants;
    uint16_t occupantsCount;
    void _addOccupantPlace();
    void _removeOccupantAt(const uint16_t idx);
public:
    Flat(const uint32_t numberP, const uint16_t roomsCountP) : number{ numberP }, roomsCount{ roomsCountP }, occupants{ nullptr }, occupantsCount{ 0 } {};
    Flat() : Flat(0, 0) {};

    Flat(const Flat& object);
    Flat(Flat&& object);

    Flat& operator=(const Flat& object);
    Flat& operator=(Flat&& object);

    const uint32_t getNumber() const { return number; };
    const uint16_t getRoomsCount() const { return roomsCount; };

    Flat& setNumber(const uint32_t numberP) { number = numberP; return *this; };
    Flat& setRoomsCount(const uint16_t roomsCountP) { roomsCount = roomsCountP; return *this; };

    Flat& addOccupant(const Man& object);
    Flat& addOccupant(Man&& object);
    bool removeOccupant(const Man& object);
    bool removeOccupantById(const uint16_t id);

    friend ostream& operator<<(ostream& out, const Flat& object);

    ~Flat() { delete[] occupants; }
};

void Flat::_addOccupantPlace()
{
    Man* newOccupants{ new Man[occupantsCount + 1] };
    for (uint16_t i{ 0 }; i < occupantsCount; ++i)
    {
        newOccupants[i] = move(occupants[i]);
    }
    delete[] occupants;
    occupants = newOccupants;
    ++occupantsCount;
}

void Flat::_removeOccupantAt(const uint16_t idx)
{
    Man* newOccupants{ new Man[occupantsCount - 1] };
    for (uint16_t i{ 0 }; i < occupantsCount - 1; ++i)
    {
        i < idx ? newOccupants[i] = move(occupants[i]) : newOccupants[i] = move(occupants[i + 1]);
    }
    delete[] occupants;
    occupants = newOccupants;
    --occupantsCount;
}

Flat& Flat::addOccupant(const Man& object)
{
    _addOccupantPlace();
    occupants[occupantsCount - 1] = object;
    return *this;
}

Flat& Flat::addOccupant(Man&& object)
{
    _addOccupantPlace();
    occupants[occupantsCount - 1] = move(object);
    return *this;
}

bool Flat::removeOccupant(const Man& object)
{
    for (uint16_t i{ 0 }; i < occupantsCount; ++i)
    {
        if (occupants[i] == object)
        {
            _removeOccupantAt(i);
            return true;
        }
    }
    return false;
}

bool Flat::removeOccupantById(const uint16_t id)
{
    for (uint16_t i{ 0 }; i < occupantsCount; ++i)
    {
        if (occupants[i].getId() == id)
        {
            _removeOccupantAt(i);
            return true;
        }
    }
    return false;
}

Flat::Flat(const Flat& object) :
    number{ object.number }, roomsCount{ object.roomsCount }, occupants{ new Man[object.occupantsCount]{} }, occupantsCount{ object.occupantsCount }
{
    for (int i{ 0 }; i < occupantsCount; ++i)
    {
        occupants[i] = object.occupants[i];
    }
}
Flat::Flat(Flat&& object) :
    number{ object.number }, roomsCount{ object.roomsCount }, occupants{ object.occupants }, occupantsCount{ object.occupantsCount }
{
    object.number = 0;
    object.roomsCount = 0;
    object.occupants = nullptr;
    object.occupantsCount = 0;
}

Flat& Flat::operator=(const Flat& object)
{
    if (!(this == &object))
    {
        if (occupantsCount != object.occupantsCount)
        {
            delete[]occupants;
            occupants = new Man[object.occupantsCount];
        }
        number = object.number;
        roomsCount = object.roomsCount;
        occupantsCount = object.occupantsCount;
        for (int i{ 0 }; i < occupantsCount; ++i) { occupants[i] = object.occupants[i]; }
    }
    return *this;
}

Flat& Flat::operator=(Flat&& object)
{
    if (!(this == &object))
    {
        delete[]occupants;
        number = object.number;
        roomsCount = object.roomsCount;
        occupants = object.occupants;
        occupantsCount = object.occupantsCount;

        object.number = 0;
        object.roomsCount = 0;
        object.occupants = nullptr;
        object.occupantsCount = 0;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Flat& object)
{
    if (object.number and object.roomsCount)
    {
        out << "\033[1;32m" << "Flat #" << object.number << "\033[0m" << ' ' << object.roomsCount << " rooms ";
        if (object.occupantsCount)
        {
            for (uint16_t i{ 0 }; i < object.occupantsCount; ++i) { out << object.occupants[i]; }
            cout << ' ';
        }
        else { out << "[no occupants]"; }
    }
    else { out << "[empty flat]"; }
    return out;
}

class Home
{
    uint16_t number;
    uint16_t flatsCount;
    Flat* flats;

public:
    Home(const uint16_t numberP, const uint16_t flatsCountP) : number{ numberP }, flatsCount{ flatsCountP }, flats{ new Flat[flatsCountP] {} } {}
    Home() : Home(1, 4) {}

    Home& setNumber(const uint16_t numberP) { number = numberP; return *this; }
    Home& setFlatCount(const uint16_t flatCountP) { flatsCount = flatCountP; return *this; }

    const uint16_t getNumber()const { return number; }
    const uint16_t getFlatCount()const { return flatsCount; }

    Home& addFlat(const Flat& object, uint16_t idx);
    Home& addFlat(Flat&& object, uint16_t idx);
    Home& removeFlat(uint16_t idx);

    friend ostream& operator<<(ostream& out, const Home& object);

    ~Home() { delete[]flats; }
};

Home& Home::addFlat(const Flat& object, uint16_t idx)
{
    flats[idx] = object;
    return *this;
}

Home& Home::addFlat(Flat&& object, uint16_t idx)
{
    flats[idx] = move(object);
    return *this;
}

Home& Home::removeFlat(uint16_t idx)
{
    Flat emptyFlat;
    flats[idx] = emptyFlat;
    return *this;
}

ostream& operator<<(ostream& out, const Home& object)
{
    if (object.number and object.flatsCount and object.flats)
    {
        out << "\033[1;34m" << "Home #" << object.number << "\033[0m" << ' ' << object.flatsCount << " flats:\n";
        if (object.flats)
        {
            for (uint16_t i{ 0 }; i < object.flatsCount; ++i) { out << object.flats[i] << '\n'; }
        }
        else { out << "[empty flats]"; }
    }
    else { out << "[empty home]"; }
    return out;
}