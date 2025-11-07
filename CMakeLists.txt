cmake_minimum_required(VERSION 3.16)
project(a8_9_cianeedssomehelp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(domain)
include_directories(Exceptions)
include_directories(repository)
include_directories(service)
include_directories(tests)
include_directories(ui)
include_directories(WatchList)

set(CMAKE_PREFIX_PATH "D:\\Qt\\6.9.0\\mingw_64")

add_definitions(-DNOMINMAX -DWIN32_LEAN_AND_MEAN)
add_executable(a8_9_cianeedssomehelp
        domain/domain.cpp
        domain/domain.h
        Exceptions/Exceptions.cpp
        Exceptions/Exceptions.h
        repository/CSVRepository.cpp
        repository/CSVRepository.h
        repository/FileWatchlist.cpp
        repository/FileWatchlist.h
        repository/HTMLRepository.cpp
        repository/HTMLRepository.h
        repository/IRepository.h
        repository/Repository.cpp
        repository/Repository.h
        repository/TextfileRepository.cpp
        repository/TextfileRepository.h
        service/Service.cpp
        service/Service.h
        tests/Tests.cpp
        tests/Tests.h
        ui/Ui.cpp
        ui/Ui.h
        ui/gui.cpp
        ui/gui.h
        WatchList/WatchList.cpp
        WatchList/WatchList.h
        main.cpp
        Utils.cpp
        Utils.h
        validator.cpp
        validator.h
        ui/mode.cpp
        ui/mode.h
        ui/file.cpp
        ui/file.h
        ui/repotype.cpp
        ui/repotype.h
        ui/AdminGUI.cpp
        ui/AdminGUI.h
        ui/UserGUI.cpp
        ui/UserGUI.h
        ui/BarChartWidget.cpp
        ui/BarChartWidget.h
        ui/MainWindow.cpp
        ui/MainWindow.h
        ui/AdminLoginDialog.cpp
        ui/AdminLoginDialog.h
)

target_link_libraries(a8_9_cianeedssomehelp Qt6::Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6Widgets REQUIRED)