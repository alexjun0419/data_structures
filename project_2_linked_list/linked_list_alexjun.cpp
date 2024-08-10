#include<iostream>
#include<memory>
#include<vector>
#include<string>

template <typename T>
class Tab {
public:
    std::string url;
    std::string name;
    T memory;
    Tab* prev;
    Tab* next;

    Tab(const std::string& url, const std::string& name, const T& memory) {
        this->url = url;
        this->name = name;
        this->memory = memory;
        prev = nullptr;
        next = nullptr;
    }
};

template <typename T>
class Browser {
private:
    Tab<T>* head;
    Tab<T>* tail;
    Tab<T>* currentTab;
    std::vector <std::pair <std::string, std::string> > bookmarks;

public:
    Browser() {
        head = nullptr;
        tail = nullptr;
        currentTab = nullptr;
    }

    void addNewTab(const std::string& url, const std::string& name, const T& memory) {
        Tab<T>* newTab = new Tab<T>(url, name, memory);

        if (!head) {
            head = newTab;
            tail = newTab;
            currentTab = newTab;
        } else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
            currentTab = newTab;
        }
    }

    void switchToPrevTab() {
        if (currentTab && currentTab->prev) {
            currentTab = currentTab->prev;
            printTabDetails(currentTab);
        } else {
            std::cout << "No previous tab" << std::endl;
        }
    }

    void switchToNextTab() {
        if (currentTab && currentTab->next) {
            currentTab = currentTab->next;
            printTabDetails(currentTab);
        } else {
            std::cout << "No next tab" << std::endl;
        }
    }

    void closeCurrentTab() {
        if (currentTab) {
            Tab<T>* tabToClose = currentTab;

            if (tabToClose->prev) {
                tabToClose->prev->next = tabToClose->next;
            } else {
                head = tabToClose->next;
            }

            if (tabToClose->next) {
                tabToClose->next->prev = tabToClose->prev;
            } else {
                tail = tabToClose->prev;
            }

            currentTab = tabToClose->next;
            std::cout << "Now current tab is = " << currentTab->name << std::endl;

            delete tabToClose;
        } else {
            std::cout << "No current tab to close." << std::endl;
        }
    }

void bookmarkCurrent() {
    if (currentTab == nullptr) {
        std::cout << "No current tab to bookmark." << std::endl;
        return;
    }

    bool isBookmarked = false;
    for (const auto& bookmark : bookmarks) {
        if (bookmark.second == currentTab->url) {
            isBookmarked = true;
            break;
        }
    }

    if (isBookmarked) {
        std::cout << "The bookmark is already added!!" << std::endl;
    } else {
        // If not already bookmarked, add the current tab to bookmarks
        bookmarks.push_back(std::make_pair(currentTab->name, currentTab->url));
        std::cout << "Bookmark added: " << currentTab->name << " (" << currentTab->url << ")" << std::endl;
    }
}

   void showBookmarkTab() {
    if (!bookmarks.empty()) {
        std::cout << "Bookmarks:" << std::endl;
        for (const auto& bookmark : bookmarks) {
            std::cout << bookmark.first << " (" << bookmark.second << ")" << std::endl;
        }
    } else {
        std::cout << "No bookmarks available." << std::endl;
    }
}

  void moveCurrentToFirst() {
    if (currentTab && currentTab != head) {
        if (currentTab->next) {
            currentTab->next->prev = currentTab->prev;
        } else {
            tail = currentTab->prev;
        }

        currentTab->prev->next = currentTab->next;
        currentTab->next = head;
        currentTab->prev = nullptr;
        head->prev = currentTab;
        head = currentTab;
    }
    else if (!currentTab) {
        std::cout << "No current tab to move." << std::endl;
    }
}

    T total_memory() {
        T total = 0;
        Tab<T>* curr = head;
        while (curr != nullptr) {
            total += curr->memory;
            curr = curr->next;
        }
        return total;
    }

    void deleteTab() {
        if (head) {
            Tab<T>* tabToDelete = nullptr;
            T maxMemory = head->memory;

            Tab<T>* curr = head;
            while (curr != nullptr) {
                if (curr->memory > maxMemory) {
                    maxMemory = curr->memory;
                    tabToDelete = curr;
                }
                curr = curr->next;
            }

            if (tabToDelete) {
                if (tabToDelete->prev) {
                    tabToDelete->prev->next = tabToDelete->next;
                } else {
                    head = tabToDelete->next;
                }

                if (tabToDelete->next) {
                    tabToDelete->next->prev = tabToDelete->prev;
                } else {
                    tail = tabToDelete->prev;
                }

                std::cout << "Deleted element = " << tabToDelete->name << " with memory size = " << tabToDelete->memory << std::endl;
                delete tabToDelete;
            } else {
                std::cout << "No tabs to delete." << std::endl;
            }
        } else {
            std::cout << "No tabs to delete." << std::endl;
        }
    }

    void display() {
        auto curr = head;
        std::cout << "Browser tab list = " << std::endl;
        while (curr) {
            std::cout << "| " << curr->name << "  x|--> ";
            curr = curr->next;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    
  void printTabDetails(Tab<T>* tab) {
    std::cout << tab->url << std::endl;
    std::cout << tab->name << std::endl;
    std::cout << tab->memory << std::endl;
}
};

int main(){
    
    Browser<double> b1;
b1.addNewTab("https://www.google.com","Google",23.45);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to Next tab = "<<std::endl;
b1.switchToNextTab();
b1.addNewTab("https://www.youtube.com","YouTube",56);
b1.bookmarkCurrent();
b1.display();
b1.addNewTab("https://www.geeksforgeeks.com","GeeksForGeeks",45.78);
b1.bookmarkCurrent();
b1.addNewTab("https://chat.openai.com","ChatGPT",129);
b1.addNewTab("https://linkedin.com","LinkedIn",410);
b1.bookmarkCurrent();
b1.addNewTab("https://github.com","Github",110);
b1.addNewTab("https://kaggle.com","Kaggle",310);
b1.bookmarkCurrent();
b1.display();
std::cout<<"Total memory consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.showBookmarkTab();
b1.moveCurrentToFirst();
b1.display();
b1.deleteTab();
b1.display();
std::cout<<"Switch to next tab = "<<std::endl;
b1.switchToNextTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
b1.showBookmarkTab();
std::cout<<"Total Memory Consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.deleteTab();
b1.display();
b1.addNewTab("https://docs.google.com/","Google Docs",102.34);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.bookmarkCurrent();
b1.showBookmarkTab();
b1.total_memory();
b1.deleteTab();
b1.display();
return 0;
}