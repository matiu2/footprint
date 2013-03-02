#ifndef WIDGETS_MAINWINDOW_H
#define WIDGETS_MAINWINDOW_H

#include <Wt/WContainerWidget>

namespace widgets {

class MainWindow : public Wt::WContainerWidget {
public:
    class Fields;
private:
    Fields* _fields;
public:
    MainWindow(Wt::WContainerWidget* parent=0);
};

} // namespace widgets

#endif // WIDGETS_MAINWINDOW_H
