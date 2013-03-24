#include "MainWindow.hpp"

#include <Wt/WBorderLayout>
#include <Wt/WImage>
#include <Wt/WText>

namespace widgets {

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent) {
    auto logo = new Wt::WImage("/images/logo.jpg", this);
}

} // namespace widgets
