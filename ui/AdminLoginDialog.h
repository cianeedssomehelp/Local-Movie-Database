// cpp
#pragma once
#include <QDialog>
#include <QLineEdit>

class AdminLoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit AdminLoginDialog(QWidget* parent = nullptr);
    QString password() const;
    static bool authenticate(QWidget* parent, const QByteArray& expectedHash);

private:
    QLineEdit* passEdit_;
};