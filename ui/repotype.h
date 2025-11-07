#pragma once
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#ifndef REPOTYPE_H
#define REPOTYPE_H



class RepositoryTypeDialog : public QDialog {
    Q_OBJECT

public:
    explicit RepositoryTypeDialog(QWidget* parent = nullptr) : QDialog(parent), selectedRepoType(-1) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QPushButton* memoryRepoButton = new QPushButton("Memory Repository", this);
        QPushButton* fileRepoButton = new QPushButton("File Repository", this);

        layout->addWidget(memoryRepoButton);
        layout->addWidget(fileRepoButton);

        connect(memoryRepoButton, &QPushButton::clicked, this, [this]() {
            selectedRepoType = 1; // Memory Repository
            accept();
        });

        connect(fileRepoButton, &QPushButton::clicked, this, [this]() {
            selectedRepoType = 2; // File Repository
            accept();
        });

        setLayout(layout);
        setWindowTitle("Select Repository Type");
    }

    int getSelectedRepoType() const { return selectedRepoType; }

private:
    int selectedRepoType;
};

#endif //REPOTYPE_H
