#ifndef XMLITEM_H
#define XMLITEM_H
#include <json.hpp>
#include <string>


class XMLItem {
private:
    std::string title;
    std::string link;
    std::string category;

public:
    XMLItem(const std::string &title = "", const std::string &link = "", const std::string &category = "");

    const std::string &getTitle() const;

    const std::string &getLink() const;

    const std::string &getCategory() const;

    void setTitle(const std::string &title);

    void setLink(const std::string &link);

    void setCategory(const std::string &category);

    nlohmann::json toJson() const;
};


#endif //XMLITEM_H
