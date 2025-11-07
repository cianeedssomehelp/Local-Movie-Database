#pragma once
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QMessageBox>

#ifndef FILE_H
#define FILE_H


class FileTypeDialog : public QDialog {
    Q_OBJECT

public:
    explicit FileTypeDialog(QWidget* parent = nullptr) : QDialog(parent), selectedType(-1) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QPushButton* csvButton = new QPushButton("CSV", this);
        QPushButton* htmlButton = new QPushButton("HTML", this);

        layout->addWidget(csvButton);
        layout->addWidget(htmlButton);

        connect(csvButton, &QPushButton::clicked, this, [this]() {
            selectedType = 1; // CSV
            accept();
        });

        connect(htmlButton, &QPushButton::clicked, this, [this]() {
            selectedType = 2; // HTML
            accept();
        });

        setLayout(layout);
        setWindowTitle("Select File Type");
    }

    int getSelectedType() const { return selectedType; }

private:
    int selectedType;
};
#endif //FILE_H
