# QTCHESS

This is a chess project developed by QT


#QT中国象棋
这是一个由QT开发的中国象棋游戏

包含了简单的人机对弈，双人对战，以及简略的网络对战的雏形
如果希望丰富以实现真正的网络对战，请在```NetGame.cpp```文件中将
```
_socket->connectToHost(QHostAddress("127.0.0.1"), 9899);
```
中的ip地址更改为你想要的地址