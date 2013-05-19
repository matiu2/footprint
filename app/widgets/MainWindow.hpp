#ifndef WIDGETS_MAINWINDOW_H
#define WIDGETS_MAINWINDOW_H

#include <Wt/WContainerWidget>

namespace footprint {
namespace widgets {

class MainWindow : public Wt::WContainerWidget {
public:
    MainWindow(Wt::WContainerWidget* parent=0);
};

} // namespace widgets
} // namespace footprint

#endif // WIDGETS_MAINWINDOW_H
