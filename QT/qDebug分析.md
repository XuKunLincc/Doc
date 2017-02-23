##qDebug分析

qDebug("before event->key()");
    -->#define qDebug QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug
    宏展开后就是新建了一个类，然后调用它的debug函数