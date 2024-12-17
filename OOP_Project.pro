QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_add_car.cpp \
    admin_login.cpp \
    admin_menu.cpp \
    admin_remove_car.cpp \
    admin_view_car.cpp \
    main.cpp \
    main_menu.cpp \
    select_role.cpp \
    user_choice.cpp \
    user_menu.cpp \
    user_rent_car.cpp \
    user_return_car.cpp \
    user_view_car.cpp

HEADERS += \
    admin_add_car.h \
    admin_login.h \
    admin_menu.h \
    admin_remove_car.h \
    admin_view_car.h \
    main_menu.h \
    select_role.h \
    user_choice.h \
    user_menu.h \
    user_rent_car.h \
    user_return_car.h \
    user_view_car.h

FORMS += \
    admin_add_car.ui \
    admin_login.ui \
    admin_menu.ui \
    admin_remove_car.ui \
    admin_view_car.ui \
    main_menu.ui \
    select_role.ui \
    user_choice.ui \
    user_menu.ui \
    user_rent_car.ui \
    user_return_car.ui \
    user_view_car.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
