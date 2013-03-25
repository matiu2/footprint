#include "MainWindow.hpp"

#include <Wt/WBorderLayout>
#include <Wt/WTemplate>
#include <Wt/WApplication>

#include "../share/footprint/Colors.hpp"

namespace widgets {

void applyColors() {
    const auto& colors = footprint::Colors::instance();
    auto app = Wt::WApplication::instance();
    auto& ss = app->styleSheet();
    // Only needs to be done once per app instance
    if (ss.isDefined("header-background"))
        return;
    ss.addRule("#header", colors->bg(1, 0), "header-background");
    ss.addRule("#controls", colors->bg(1, 1));
    ss.addRule("#content", colors->bg(1, 2));
    ss.addRule("#footer", colors->bg(2, 0));
}

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent) {
    auto tmpl = new Wt::WTemplate(tr("main-template"), this);
    applyColors();
}

} // namespace widgets
