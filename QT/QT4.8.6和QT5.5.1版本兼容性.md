##QT4.8.6和QT5.5.1版本兼容性

####自定义日志宏不兼容：
    HsDebug：在文件 F:\work\hsecoapp\src\infrastructure\logger.h:70 

####QString toAscii()函数被移除
    在QT5.0.1版本的时候已经将该API移除，应当使用toLatin1函数进行替代

####错误

- F:\work\hsecoapp\src\framework\hsapplication.cpp:112: error: incomplete type 'QTime' used in nested name specifier qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

- variable ‘QApplication app’ has initializer but incomplete type
加上头文件进行处理


g++ -Wl,-subsystem,windows -mthreads -o ..\..\..\debug\HsEcoApp.exe object_script.HsEcoApp.Debug  -lmingw32 -LD:\Qt\Qt5.7.1\5.7\mingw53_32\lib D:\Qt\Qt5.7.1\5.7\mingw53_32\lib\libqtmaind.a -lshell32 -LC:\utils\my_sql\my_sql\lib -LC:\utils\postgresql\pgsql\lib -L..\3rdparty\hsecolib\lib -L..\3rdparty\userresolver -lHsEcoClient -lmxml1 -lUserResolverLib D:\Qt\Qt5.7.1\5.7\mingw53_32\lib\libQt5Widgetsd.a D:\Qt\Qt5.7.1\5.7\mingw53_32\lib\libQt5Guid.a D:\Qt\Qt5.7.1\5.7\mingw53_32\lib\libQt5Cored.a 

cl -c -nologo -Zc:wchar_t -Zi -MDd -GR -W3 -w34100 -w34189 -w44996 -EHsc /Fd..\..\..\debug\HsEcoApp.pdb -DUNICODE -DWIN32 -DQT_DLL -DQT_WIDGETS_LIB -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I..\HsEcoApp -I. -I..\HsEcoApp\GeneratedFiles -I..\HsEcoApp -I..\HsEcoApp\GeneratedFiles\Debug -I../../../3rdparty/hsecolib/include -I../../../3rdparty/userresolver -I../../../src -I../../../src/infrastructure -I../../../src/service -I../../../src/service/notifyevent -I../../../src/service/uimodel -I../../../src/service/comm -I../../../src/service/user -I../../../src/service/urgent -I../../../src/service/monitor -I../../../src/service/code -I../../../src/ui -I../../../src/ui/activities -I../../../src/ui/activities/monitor -I../../../src/ui/activities/auto -I../../../src/framework -ID:\Qt\Qt5.5.1\5.5\msvc2010\include -ID:\Qt\Qt5.5.1\5.5\msvc2010\include\QtWidgets -ID:\Qt\Qt5.5.1\5.5\msvc2010\include\QtGui -ID:\Qt\Qt5.5.1\5.5\msvc2010\include\QtANGLE -ID:\Qt\Qt5.5.1\5.5\msvc2010\include\QtCore -IGeneratedFiles\debug -IGeneratedFiles -ID:\Qt\Qt5.5.1\5.5\msvc2010\mkspecs\win32-msvc2010 -Fodebug\ @C:\Users\ADMINI~1\AppData\Local\Temp\moc_uiparaactiv.obj.7928.35147.jom
moc_uiparaactiv.cpp

link /NOLOGO /DYNAMICBASE /NXCOMPAT /DEBUG /SUBSYSTEM:WINDOWS "/MANIFESTDEPENDENCY:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' publicKeyToken='6595b64144ccf1df' language='*' processorArchitecture='*'" /MANIFEST /MANIFESTFILE:..\..\..\debug\HsEcoApp.exe.embed.manifest /OUT:..\..\..\debug\HsEcoApp.exe @C:\Users\ADMINI~1\AppData\Local\Temp\HsEcoApp.exe.6328.36067.jom