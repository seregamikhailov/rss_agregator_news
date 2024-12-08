#include "XMLItem.h"

#include <iostream>
#include <string>


XMLItem::XMLItem(const std::string &title, const std::string &link, const std::string &category): title(title), link(link),
    category(category) {
};

const std::string &XMLItem::getTitle() const {
    return title;
}

const std::string &XMLItem::getLink() const {
    return link;
}

const std::string &XMLItem::getCategory() const {
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

nlohmann::json XMLItem::toJson() const {
    return {{"title", title}, {"link", link}, {"category", category}};
}
