// cpp
#include "MainWindow.h"
#include "AdminGUI.h"
#include "UserGUI.h"
#include "AdminLoginDialog.h"
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QFont>
#include <QApplication>
#include <QCryptographicHash>
#include <QMessageBox>

MainWindow::MainWindow(Service& service, int initialMode, const QByteArray& adminPasswordHash, QWidget* parent)
    : QMainWindow(parent),
      tabs_(new QTabWidget(this)),
      adminWidget_(new AdminGUI(service, tabs_)),
      userWidget_(new UserGUI(service, tabs_)),
      adminPasswordHash_(adminPasswordHash)
{

    if (adminPasswordHash_.isEmpty()) {
        adminPasswordHash_ = QCryptographicHash::hash("admin", QCryptographicHash::Sha256).toHex();
    }

    setupUi();
    applyStyle();
    tabs_->addTab(adminWidget_, tr("Admin"));
    tabs_->addTab(userWidget_, tr("User"));

    setCentralWidget(tabs_);
    setWindowTitle(tr("Movie Manager"));
    resize(1000, 700);

    lastTabIndex_ = tabs_->currentIndex();

    connect(tabs_, &QTabWidget::tabBarClicked, this, [this](int index) {
        if (index == 0 && !adminAuthenticated_) {
            const bool ok = ensureAdminAuth();
            if (!ok) {

                tabs_->setCurrentIndex(lastTabIndex_);
                return;
            }
        }
        lastTabIndex_ = index;
    });

    setActiveMode(initialMode);
}

bool MainWindow::ensureAdminAuth() {
    if (adminAuthenticated_) return true;

    const bool ok = AdminLoginDialog::authenticate(this, adminPasswordHash_);
    if (ok) {
        adminAuthenticated_ = true;
        statusBar()->showMessage(tr("Admin authenticated"), 2000);
        return true;
    } else {
        QMessageBox::warning(this, tr("Authentication failed"), tr("Incorrect admin password."));
        return false;
    }
}

void MainWindow::setupUi() {
    auto* tb = addToolBar(tr("Main"));
    tb->setMovable(false);

    QAction* refreshAct = new QAction(tr("Refresh"), this);
    connect(refreshAct, &QAction::triggered, [this]() {
        adminWidget_->update();
        userWidget_->update();
    });
    tb->addAction(refreshAct);

    QAction* aboutAct = new QAction(tr("About"), this);
    connect(aboutAct, &QAction::triggered, [this]() {
        statusBar()->showMessage(tr("Movie Manager — built with Qt"), 3000);
    });
    tb->addAction(aboutAct);

    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::applyStyle() {
    const QString style = R"(
        /* Window / central */
        QMainWindow { background: #f1f3f6; }

        /* Toolbar - darker strip for visibility */
        QToolBar {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                        stop:0 #2f3b52, stop:1 #263244);
            padding: 6px;
            spacing: 8px;
            border-bottom: 1px solid rgba(0,0,0,0.12);
        }
        QToolButton {
            color: #ffffff; /* keep toolbar buttons light on dark strip */
            background: transparent;
            border: none;
            padding: 6px 10px;
            border-radius: 4px;
        }
        QToolButton:hover {
            background: rgba(255,255,255,0.06);
        }

        /* Tab widget: give tabs a card-like appearance */
        QTabWidget::pane {
            background: transparent;
            border: none;
            margin: 12px;
        }
        QTabBar::tab {
            background: #e4e9f2;
            color: #2b2b2b;
            padding: 10px 16px;
            border-top-left-radius: 8px;
            border-top-right-radius: 8px;
            margin-right: 6px;
            min-width: 120px;
        }
        QTabBar::tab:selected {
            background: #ffffff;
            color: #0f1720;
            font-weight: 600;
            border: 1px solid rgba(0,0,0,0.06);
            margin-bottom: 0px;
        }
        QTabBar::tab:!selected {
            border: 1px solid rgba(0,0,0,0.03);
        }

        /* Status bar */
        QStatusBar {
            background: #ffffff;
            border-top: 1px solid rgba(0,0,0,0.06);
            color: #333333;
        }

        /* Buttons and interactive controls - make text dark and highly readable */
        QPushButton {
            background-color: #e8eef8; /* light button background */
            color: #0b0b0b;           /* dark text so 'Next' is visible */
            border: 1px solid #c6d0e6;
            border-radius: 6px;
            padding: 6px 10px;
        }
        QPushButton.primary {
            /* if you mark primary buttons with objectName or dynamicProperty,
               keep a colored background but ensure dark or white text as needed */
            background-color: #3b82f6;
            color: #ffffff; /* primary still readable */
        }
        QPushButton:hover {
            background-color: #dceafe;
        }
        QPushButton:disabled {
            background-color: #f0f2f6;
            color: #7b8796;
            border-color: #e0e6ef;
        }

        /* Ensure other controls also have readable text */
        QLineEdit, QPlainTextEdit, QTextEdit, QComboBox, QSpinBox, QDoubleSpinBox {
            color: #0b0b0b;
            background: #ffffff;
            border: 1px solid #e0e6ef;
            selection-background-color: #cfe3ff;
            selection-color: #0b2a4a;
        }

        /* Table / lists */
        QTableView, QListView {
            background: #ffffff;
            alternate-background-color: #f7f8fb;
            gridline-color: #e6e9ef;
            selection-background-color: #cfe3ff;
            selection-color: #0b2a4a;
            color: #0b0b0b;
        }

        /* Tooltips / dialogs */
        QToolTip {
            background-color: #333333;
            color: #ffffff;
            border: none;
            padding: 6px;
            border-radius: 4px;
        }
    )";
    qApp->setFont(QFont("Segoe UI", 10));
    qApp->setStyleSheet(style);
}
void MainWindow::setActiveMode(int mode){
    if (mode == 1) {
        if (ensureAdminAuth()) tabs_->setCurrentIndex(0);
    } else {
        tabs_->setCurrentIndex(1);
    }
}