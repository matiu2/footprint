#include "MainWindow.hpp"

#include <Wt/WBorderLayout>
#include <Wt/WTemplate>

namespace widgets {

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent) {
    auto tmpl = new Wt::WTemplate(tr("main-template"), this);

}

} // namespace widgets
