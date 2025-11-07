// cpp
#include "AdminLoginDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QCryptographicHash>

AdminLoginDialog::AdminLoginDialog(QWidget* parent)
    : QDialog(parent),
      passEdit_(new QLineEdit(this))
{
    setWindowTitle(tr("Admin Login"));
    passEdit_->setEchoMode(QLineEdit::Password);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(tr("Enter admin password:"), this));
    layout->addWidget(passEdit_);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &AdminLoginDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &AdminLoginDialog::reject);
    layout->addWidget(buttons);

    setLayout(layout);
    setFixedSize(320, 120);
}

QString AdminLoginDialog::password() const {
    return passEdit_->text();
}

bool AdminLoginDialog::authenticate(QWidget* parent, const QByteArray& expectedHash) {
    AdminLoginDialog dlg(parent);
    if (dlg.exec() != QDialog::Accepted) return false;

    const QByteArray enteredHash = QCryptographicHash::hash(dlg.password().toUtf8(),
                                                            QCryptographicHash::Sha256).toHex();
    return enteredHash == expectedHash;
}