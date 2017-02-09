##QT exec调用链
>**目标：**理清exec函数的调用链


    QApplication::exec()
        -->QGuiApplication::exec()
            -->QCoreApplication::exec()
                -->QEventLoop::exec()
                    -->bool QEventDispatcherUNIX::processEvents(QEventLoop::ProcessEventsFlags flags)


####QCoreApplication::exec()描述
    Enters the main event loop and waits until exit() is called.  Returns
    the value that was passed to exit() (which is 0 if exit() is called via
    quit()).

    It is necessary to call this function to start event handling. The
    main event loop receives events from the window system and
    dispatches these to the application widgets.

    To make your application perform idle processing (by executing a
    special function whenever there are no pending events), use a
    QTimer with 0 timeout. More advanced idle processing schemes can
    be achieved using processEvents().

####QEventLoop::exec()描述
    Enters the main event loop and waits until exit() is called.
    Returns the value that was passed to exit().

    If \a flags are specified, only events of the types allowed by
    the \a flags will be processed.

    It is necessary to call this function to start event handling. The
    main event loop receives events from the window system and
    dispatches these to the application widgets.

    Generally speaking, no user interaction can take place before
    calling exec(). As a special case, modal widgets like QMessageBox
    can be used before calling exec(), because modal widgets
    use their own local event loop.

    To make your application perform idle processing (i.e. executing a
    special function whenever there are no pending events), use a
    QTimer with 0 timeout. More sophisticated idle processing schemes
    can be achieved using processEvents().