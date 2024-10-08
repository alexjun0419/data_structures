// Alex Jun (885103481)
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <exception>

template <typename T>
class Item {
public:
    T name;
    T expiration;
    T category;
    int quantity;

    Item(T n, T e, T c, int q) : name(n), expiration(e), category(c), quantity(q) {}
};

template<typename T>
class Inventory {
private:
    std::vector<Item <T> > items;

public:
    void displayItems() {
        std::cout << "-------Inventory-------" << std::endl;
        std::cout << std::left << std::setw(20) << "Name" << std::setw(15) << "Expiration" << std::setw(15) << "Quantity" << std::setw(10) << "Category" << std::endl;
        for (int i = 0; i < items.size(); i++) {
           std::cout<<std::left << std::setw(20)<<items[i].name<<std::setw(15)<<items[i].expiration<<std::setw(15)<<items[i].quantity<<std::setw(15)<<items[i].category<<std::endl;
        }
    }

    void addNewItem(const Item<T>& newItem) {
        for (const auto& item : items) {
            if (item.name == newItem.name) {
                std::cout << "Item is already present in inventory" << std::endl;
                return;
            }
        }
        items.push_back(newItem);
    }

    void increaseQuantity(const T& itemName, int quantity) {
        for (auto& item : items) {
            if (item.name == itemName) {
                item.quantity += quantity;
                return;
            }
        }
    }

    void updateItem(const T& itemName, const T& expiration, const T& category, int quantity) {
        for (auto& item : items) {
            if (item.name == itemName) {
                item.expiration = expiration;
                item.category = category;
                item.quantity = quantity;
                return;
            }
        }
            throw "Item Not Found";
    }

    void removeItem(const T& itemName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->name == itemName) {
                items.erase(it);
                return;
            }
        }
            throw "Item Not Found";
    }

    int Total() {
        return items.size();
    }

    Item<T> searchItem(const T& itemName) {
        for (const auto& item : items) {
            if (item.name == itemName) {
                return item;
            }
        }
            throw "Item Not Found";
    }
};

template<typename T>
class Appointment {
public:
    T c_name;
    T ap_date;
    T ap_time;
    T CWID;

    Appointment(T n, T d, T t, T cw) : c_name(n), ap_date(d), ap_time(t), CWID(cw) {}
};

template<typename T>
class AppointmentSystem {
private:
    std::vector<Appointment <T> > ap;

public:
    void display() {
        std::cout << "-------Appointments-------" << std::endl;
        std::cout << std::left << std::setw(20) << "Name" << std::setw(15) << "Date" << std::setw(15) << "Time" << std::setw(15) << "CWID" << std::endl;
        for (int i = 0; i < ap.size(); i++) {
            std::cout << std::left << std::setw(20) << ap[i].c_name << std::setw(15) << ap[i].ap_date << std::setw(15) << ap[i].ap_time << std::setw(15) << ap[i].CWID << std::endl;
        }
    }

    void schedule(const Appointment<T>& newAppointment) {
        for (const auto& appointment : ap) {
            if (appointment.CWID == newAppointment.CWID) {
                std::cout << "You have already scheduled an appointment!!!" << std::endl;
                return;
            }
        }
        ap.push_back(newAppointment);
    }

    int Total_appointments(const T& date, const T& time) {
        int count = 0;
        for (const auto& appointment : ap) {
            if (appointment.ap_date == date && appointment.ap_time == time) {
                count++;
            }
        }
        return count;
    }

    void removeRecent() {
        if (!ap.empty()) {
            ap.pop_back();
        }
    }
};

int main() {
    Inventory<std::string> i1;
    Item<std::string> I1("Protein Bar", "05/09/2023", "Snacks", 4);
    i1.addNewItem(I1);
    Item<std::string> I2("Milk", "05/12/2023", "Regular", 2);
    i1.addNewItem(I2);
    Item<std::string> I3("Cereals", "09/12/2023", "Snacks", 5);
    i1.addNewItem(I3);
    i1.displayItems();
    i1.updateItem("Milk", "09/24/2023", "Regular", 3);
    i1.displayItems();
    i1.increaseQuantity("Cereals", 10);
    i1.displayItems();
    try {
        i1.updateItem("Bar", "09/12/2023", "Snacks", 3);
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    i1.displayItems();
    i1.updateItem("Cereals", "09/27/2023", "Regular", 4);
    i1.displayItems();
    int totalItems = i1.Total();
    std::cout << "Total items in inventory: " << totalItems << std::endl;
    try {
        i1.removeItem("Bread");
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    try {
        i1.removeItem("Milk");
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    i1.displayItems();
    try {
        Item<std::string> searchResult = i1.searchItem("Cereals");
        std::cout << "Searched Item: " << searchResult.name << ", Expiration: " << searchResult.expiration
            << ", Quantity: " << searchResult.quantity << ", Category: " << searchResult.category << std::endl;
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    Appointment<std::string> a1("John Bob","09/12/2023","9:30AM","889456723");
    Appointment<std::string> a2("Jim Lee","09/12/2023","10:30AM","883476923");
    Appointment<std::string> a3("Chris Lynn","09/12/2023","12:00PM","879455714");
    Appointment<std::string> a4("Arnav Shah","09/12/2023","12:00PM","879459583");
    AppointmentSystem<std::string> s1;
    s1.schedule(a1);
    s1.schedule(a2);
    s1.schedule(a3);
    s1.schedule(a4);
    s1.display();
    s1.Total_appointments("09/12/2023","12:00PM");
    Appointment<std::string> a5("Chris Lynn","09/12/2023","12:00PM","879455714");
    s1.schedule(a5);
    s1.removeRecent();
    s1.display();
}