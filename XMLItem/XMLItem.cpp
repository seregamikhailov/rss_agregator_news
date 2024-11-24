//
// Created by Serg on 25.11.2024.
//

#include "XMLItem.h"

#include <iostream>
#include <string>
using namespace std;


XMLItem::XMLItem(const string &title, const string &link, const string &category): title(title), link(link),
    category(category) {
};

const string &XMLItem::getTitle() const {
    return title;
}

const string &XMLItem::getLink() const {
    return link;
}

const string &XMLItem::getCategory() const {
    return category;
}

void XMLItem::setTitle(const std::string &title) {
    this->title = title;
}

void XMLItem::setLink(const std::string &link) {
    this->link = link;
}

void XMLItem::setCategory(const std::string &category) {
    this->category = category;
}

void XMLItem::print_item() const {
    cout << "Title " << title << endl;
    cout << "Link " << link << endl;
    cout << "Category " << category << endl;
}
