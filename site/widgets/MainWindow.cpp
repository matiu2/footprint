#include "MainWindow.hpp"

#include <Wt/WBorderLayout>
#include <Wt/WImage>
#include <Wt/WText>

namespace widgets {

// So we know which parts of the layout aren't filled in yet
typedef Wt::WText PlaceHolder;

/// Holds all the fields so we don't have too many imports in the header file
struct MainWindow::Fields : public Wt::WObject {
    Wt::WBorderLayout* layout;
    Wt::WImage* logo;
    Fields(Wt::WContainerWidget* parent) : Wt::WObject(parent) {
        layout = new Wt::WBorderLayout(parent);
        logo = new Wt::WImage("logo.jpg", parent);
        typedef Wt::WBorderLayout::Position Pos;
        layout->addWidget(logo, Pos::North);
        auto body = new PlaceHolder(Wt::WText::tr("lorem-impsum"), parent);
        layout->addWidget(body, Pos::Center);
        auto left = new PlaceHolder("This is the left pane", parent);
        layout->addWidget(left, Pos::West);
        auto right = new PlaceHolder("This is the right pane", parent);
        layout->addWidget(right, Pos::East);
        auto bottom = new PlaceHolder("This is the footer", parent);
        layout->addWidget(bottom, Pos::East);
    }
};

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent), _fields(new Fields(this)) {
}

} // namespace widgets
