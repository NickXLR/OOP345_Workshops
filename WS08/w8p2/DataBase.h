#ifndef SDDS_DATABASE_H
#define SDDS_DATABASE_H
// Workshop 8 - Smart Pointers


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
    template <typename T>
    class DataBase {
		std::vector<T> database;
	public:
		DataBase() { }
		DataBase(const char* fn) {
			std::ifstream file(fn);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(fn) + std::string(" ***");
            while (file) {
                T e;
				try {
					if (e.load(file))
						database.push_back(T(e));
				}
				catch (...) {
					break;
				}
            }
		}
		size_t size() const { return database.size(); }
		const T& operator[](size_t i) const { return database[i]; }

		// TODO: Overload the += operator with a raw pointer
		//       as a second operand.
		void operator+=(T* address)
		{
			database.push_back(*address);
			//database.push_back(std::move(*address));
		}
		
		// TODO: Overload the += operator with a smart pointer
		//       as a second operand.
		void operator +=(std::shared_ptr<T> ptr)
		{
			database.push_back(*ptr);
			//database.push_back(std::move(*ptr));
		}


		void display(std::ostream& os) const {
            os << std::fixed << std::setprecision(2);
			for (auto& e : database)
				os << e;
        }
	};

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const DataBase<T>& db) {
		db.display(os);
		return os;
	}
}
#endif