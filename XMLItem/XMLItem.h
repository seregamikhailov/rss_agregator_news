//
// Created by Serg on 25.11.2024.
//

#ifndef XMLITEM_H
#define XMLITEM_H
#include <string>
using namespace std;


class XMLItem {
private:
    string title;
    string link;
    string category;

public:
    XMLItem(const string &title = "", const string &link = "", const string &category = "");

    const string &getTitle() const;

    const string &getLink() const;

    const string &getCategory() const;

    void setTitle(const std::string &title);

    void setLink(const std::string &link);

    void setCategory(const std::string &category);

    void print_item() const;
};


#endif //XMLITEM_H