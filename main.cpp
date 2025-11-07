#include <QApplication>
#include "file.h"
#include "mode.h"
#include "FileWatchlist.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "repotype.h"
#include "gui.h"
#include "ui/Ui.h"
#include "repository/Repository.h"
#include "repository/TextfileRepository.h"
#include "Exceptions/Exceptions.h"
#include "BarChartWidget.h"
#include <QMainWindow>
#include "MainWindow.h"
#include <QMessageBox>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    std::vector<Movies> movies;
    try {

        RepositoryTypeDialog repoTypeDialog;
        if (repoTypeDialog.exec() != QDialog::Accepted) {
            return 0;
        }
        int repoType = repoTypeDialog.getSelectedRepoType();

        std::unique_ptr<IRepository> repo;
        if (repoType == 1) {
            repo = std::make_unique<Repository>();
        } else if (repoType == 2) {
            repo = std::make_unique<TextfileRepository>("MovieList.txt");
        } else {
            QMessageBox::critical(nullptr, "Error", "Invalid repository type selected!");
            return 1;
        }

        FileTypeDialog fileTypeDialog;
        if (fileTypeDialog.exec() != QDialog::Accepted) {
            return 0;
        }
        int fileType = fileTypeDialog.getSelectedType();

        FileWatchlist* fileWatchlist = nullptr;
        if (fileType == 1) {
            fileWatchlist = new CVSRepository("C:\\Users\\patri\\OneDrive\\Documents\\GitHub\\a6-7-cianeedssomehelp\\cmake-build-debug\\Watchlist.csv");
        } else if (fileType == 2) {
            fileWatchlist = new HTMLRepository("Watchlist.html");
        } else {
            QMessageBox::critical(nullptr, "Error", "Invalid file type selected!");
            return 1;
        }

        ModeSelectionDialog modeDialog;
        if (modeDialog.exec() != QDialog::Accepted) {
            delete fileWatchlist;
            return 0;
        }
        int mode = modeDialog.getSelectedMode();

        WatchList watch_list;
        Service service(*repo, watch_list, fileWatchlist);

        service.setWatchlistFilename(fileWatchlist->getFilename());

        if (repoType == 1) {
            Ui ui(service);
            ui.inntializeMovieDatabase();
            ui.innitializeWatchlist();
        }

        MainWindow mainWin(service, mode);
        mainWin.show();
        return app.exec();

    } catch (const FileException& e) {
        QMessageBox::critical(nullptr, "File Error", QString::fromStdString(e.what()));
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Error", QString::fromStdString(e.what()));
    }

    return 0;
}