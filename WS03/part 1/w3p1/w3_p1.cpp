// Workshop 3 - Templates
// Created by: Jeevan Pant
// Date created: 2023/07/22


#include <iostream>
#include <iomanip>
#include <string>
#include "Book.h"
#include "Book.h"
#include "Collection.h"
#include "Collection.h"

// Cheching if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif
#ifndef SDDS_COLLECTION_H
    #error "The header guard for 'Collection.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces
int endl = 0;

int main(int argc, char** argv)
{
    std::cout << "Command Line Arguments:\n";
    std::cout << "---------------------------------\n";
    for (int i = 0; i < argc; ++i)
        std::cout << std::setw(3) << i + 1 << ": " << *(argv + i) << '\n';
    std::cout << "---------------------------------\n\n";

    // int, double, and Book data testing templated classes
    unsigned numBooks = 6;
    int ints[]{ 25, 30, 20, 15, 25, 5, 35 };
    double doubles[]{ 7.8, 9.10, 3.4, 1.2, 2.3, 6.7 };
    sdds::Book books[]{
        sdds::Book("Software Architecture for Busy Developers", 7, 174),
        sdds::Book("Low-Code Application Development with Appian",16,462),
        sdds::Book("Natural Language Processing with TensorFlow", 11, 514),
        sdds::Book("Learning DevOps",17,560),
        sdds::Book("SQL for Data Analytics",9,540),
        sdds::Book("Deciphering Object-Oriented Programming with C++",21,594),
    };

    std::cout << "1. Book tester >>> ===========================================================" << std::endl;
    std::cout << "total books: " << numBooks << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    for (auto i = 0u; i < numBooks-1; i++) {
        std::cout << "| " << i + 1 << ".";
        books[i].print(std::cout) << "|" << std::endl;;
    }
    std::cout << "| " << numBooks << ".";
    std::cout << books[numBooks-1] << "|" << std::endl;
    std::cout << "============================================================== <<< Book tester" << std::endl << std::endl;

    std::cout << "2. Collection tester for int and 10 >>> ======================================" << std::endl;
    {        // Collection tester for int-type
        sdds::Collection<int, 10> icol;
        for(auto i : ints)
            icol += i; 
        std::cout << "(smallest,largest) items: (" << icol.getSmallestItem() << "," << icol.getLargestItem() << ")" << std::endl;
        std::cout << "size/capacity: " << icol.size() << "/" << icol.capacity() << std::endl;
        std::cout << "Contents: ";
        icol.print(std::cout);
    }
    std::cout << "========================================= <<< Collection tester for int and 10" << std::endl;
    std::cout << std::endl;

    std::cout << "3. Collection tester for double and 10 >>>====================================" << std::endl;
    {// Collection tester for double-type
        sdds::Collection<double, 10> dcol;
        for (auto d : doubles)
            dcol += d;
        std::cout << "(smallest,largest) items: (" << dcol.getSmallestItem() << "," << dcol.getLargestItem() << ")" << std::endl;
        std::cout << "size/capacity: " << dcol.size() << "/" << dcol.capacity() << std::endl;
        std::cout << "Contents: ";
        dcol.print(std::cout);
    }
    std::cout << "====================================== <<< Collection tester for double and 10" << std::endl;
    std::cout << std::endl;

    std::cout << "4. Collection tester for Book and 10 >>> =====================================" << std::endl;
    {// Collection tester for Book-type, capacity 10
        std::cout << "[After creating collection in empty state]" << std::endl;
        sdds::Collection<sdds::Book, 10> bcol;
        std::cout << "Book with smallest pages-to-chapters ratio (initial-default state): " << std::endl;
        bcol.getSmallestItem().print(std::cout) << " |" << std::endl;
        std::cout << "Book with largest pages-to-chapters ratio (initial-deault-state): " << std::endl;
        bcol.getLargestItem().print(std::cout) << " |" << std::endl;
        std::cout << "size/capacity: " << bcol.size() << "/" << bcol.capacity() << std::endl;
    }
    std::cout << "======================================== <<< Collection tester for Book and 10" << std::endl;
    std::cout << std::endl;

    return cout + endl;
}
