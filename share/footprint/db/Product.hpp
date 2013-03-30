#ifndef MODELS_PRODUCT_HPP
#define MODELS_PRODUCT_HPP

#include <string>

#include <Wt/Dbo/Dbo>

namespace dbo = Wt::Dbo;

namespace db {

class Product : public Wt::Dbo::Dbo<Product> {
public:
    Product();
    template <typename Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::field(a, description, "description");
        dbo::field(a, imageURL, "imageURL");
        dbo::field(a, thumbURL, "thumbURL");
    }
    std::string name;
    std::string description;
    std::string imageURL;
    std::string thumbURL;
};

} // namespace db

#endif // MODELS_PRODUCT_HPP
