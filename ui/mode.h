#pragma once
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#ifndef MODE_H
#define MODE_H

class ModeSelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit ModeSelectionDialog(QWidget* parent = nullptr) : QDialog(parent), selectedMode(-1) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QPushButton* adminButton = new QPushButton("Admin", this);
        QPushButton* userButton = new QPushButton("User", this);

        layout->addWidget(adminButton);
        layout->addWidget(userButton);

        connect(adminButton, &QPushButton::clicked, this, [this]() {
            selectedMode = 1;
            accept();
        });

        connect(userButton, &QPushButton::clicked, this, [this]() {
            selectedMode = 2; // User
            accept();
        });

        setLayout(layout);
        setWindowTitle("Select Mode");
    }

    int getSelectedMode() const { return selectedMode; }

private:
    int selectedMode;
};
#endif //MODE_H
