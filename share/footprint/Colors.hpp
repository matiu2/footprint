#ifndef FOOTPRINT_COLORS_H
#define FOOTPRINT_COLORS_H

#include <vector>
#include <string>

#include <Wt/WColor>

namespace footprint {

struct Colors {
    //  Color Palette by Color Scheme Designer
    //  Palette URL: http://colorschemedesigner.com/#2P61ThWs0g0g0
    //  Color Space: RGB;
    typedef std::vector<Wt::WColor> ColorVec;
    typedef std::vector<ColorVec> ColorCollection;

    Colors();
    static Colors* instance();

    const ColorCollection colors;

    std::string bg(size_t a, size_t b);
    std::string fg(size_t a, size_t b);
    std::string get(size_t a, size_t b);
};

} // namespace footprint

#endif // FOOTPRINT_COLORS_H
