#include "Colors.hpp"

#include <sstream>

#include "App.hpp"

namespace footprint {

Colors::Colors() :
    colors {
        {
            // Primary Color:
            Wt::WColor(79,179,79),
            Wt::WColor(80,156,80),
            Wt::WColor(49,147,49),
            Wt::WColor(101,198,101),
            Wt::WColor(112,198,112)
        },
        {
            // Secondary Color A:
            Wt::WColor(59,134,134),
            Wt::WColor(60,117,117),
            Wt::WColor(36,110,110),
            Wt::WColor(84,164,164),
            Wt::WColor(93,164,164),
        },
        {
            // Secondary Color B:
            Wt::WColor(169,208,92),
            Wt::WColor(152,182,93),
            Wt::WColor(133,172,57),
            Wt::WColor(184,220,112),
            Wt::WColor(188,220,124),
        },
        {
            // Complementary Color:
            Wt::WColor(223,98,98),
            Wt::WColor(195,100,100),
            Wt::WColor(184,61,61),
            Wt::WColor(231,118,118),
            Wt::WColor(231,131,131),
        }
    }
{ }

Colors* Colors::instance() {
    App* app = dynamic_cast<App*>(Wt::WApplication::instance());
    return &app->colors;
}

std::string Colors::bg(size_t a, size_t b) {
    return std::string("background-color:") + get(a, b) + ";";
}

std::string Colors::fg(size_t a, size_t b) {
    return std::string("color:") + get(a, b) + ";";
}

/// Returns the CSS format for a color, eg. #aabbcc
std::string Colors::get(size_t a, size_t b) {
    const Wt::WColor& col = colors[a][b];
    if (!col.name().empty())
        return col.name().toUTF8();
    std::stringstream result;
    result << '#' << std::hex << col.red() << col.green() << col.blue() << ';';
    return result.str();
}

} // namespace footprint
