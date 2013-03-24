#include "MainWindow.hpp"

#include <Wt/WBorderLayout>
#include <Wt/WImage>
#include <Wt/WText>

namespace widgets {

// So we know which parts of the layout aren't filled in yet
typedef Wt::WText PlaceHolder;

/// Holds all the fields so we don't have too many imports in the header file
struct MainWindow::Fields : public Wt::WObject {

    Fields(Wt::WContainerWidget* parent) : Wt::WObject(parent) {
        logo = new Wt::WImage("/images/logo.jpg", parent);
        auto body = new PlaceHolder(Wt::WText::tr("lorem-impsum"), parent);
        auto left = new PlaceHolder("This is the left pane", parent);
        auto right = new PlaceHolder("This is the right pane", parent);
        auto bottom = new PlaceHolder("This is the footer", parent);
    }
};

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent), _fields(new Fields(this)) {
}

} // namespace widgets
