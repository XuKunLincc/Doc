##QT for Android源码编译

D:\Qt\Qt5.7.1\Src\qt-everywhere-opensource-src-5.7.1\configure.bat -prefix D:\MyQt\QT-Android5.7.1-armv7 -xplatform android-g++ -nomake tests -nomake examples -android-ndk E:\Andorid_SDK\Android\sdk\ndk-bundle -android-sdk E:\Andorid_SDK\Android\sdk -android-ndk-host windows-x86_64 -android-toolchain-version 25.0.2 -skip qttranslations -skip qtserialport -no-warnings-are-errors -opensource

D:\MyQt\qt-android-bulid>D:\Qt\Qt5.7.1\Src\qt-everywhere-opensource-src-5.7.1\configure.bat -prefix D:\MyQt\QT-Android5.7.1-armv7 -xplatform android-g++ -nomake tests -nomake examples -android-ndk E:\Andorid_SDK\Android\sdk\ndk-bundle -android-sdk E:\Andorid_SDK\Android\sdk -android-ndk-host windows-x86_64 -android-toolchain-version 4.9 -skip qttranslations -skip qtserialport -no-warnings-are-errors -opensource -platform win32-g++ -android-arch arm64-v8a
编译出来的arch是arm64-v8a
