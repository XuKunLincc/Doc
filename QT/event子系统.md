##QT Event子系统
######进行事件分发的核心

    bool processEvents(ProcessEventsFlags flags = AllEvents);
    void processEvents(ProcessEventsFlags flags, int maximumTime);
    掉用Windows的API函数DispatchMessage()后跳转到callback函数
    LRESULT QT_WIN_CALLBACK qt_internal_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
    QCoreApplication::sendEvent(sn->obj, &event);
    bool QCoreApplication::notifyInternal2(QObject *receiver, QEvent *event)
    static bool doNotify(QObject *receiver, QEvent *event)
    bool QCoreApplication::notify(QObject *receiver, QEvent *event){
          return receiver->isWidgetType() ? false : QCoreApplicationPrivate::notify_helper(receiver, event);
          好像是判断是不是widget 如果不是就返回flase 那么这个就不是我们想要的
}
    }