#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <QByteArray>

class Service;
class AdminGUI;
class UserGUI;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(Service& service,
                        int initialMode = 2,
                        const QByteArray& adminPasswordHash = QByteArray(),
                        QWidget* parent = nullptr);
    void setActiveMode(int mode);

private:
    QTabWidget* tabs_;
    AdminGUI* adminWidget_;
    UserGUI* userWidget_;
    void setupUi();
    void applyStyle();

    bool adminAuthenticated_ = false;
    QByteArray adminPasswordHash_;
    int lastTabIndex_ = 0;
    bool ensureAdminAuth();
};
