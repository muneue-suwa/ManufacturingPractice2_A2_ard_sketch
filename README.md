## Arduino IDE PERMISSION DENIED
```shell-session:arduino_ide_permission_denied
sudo usermod -a -G dialout $USER && \
sudo chmod a+rw /dev/ttyUSB0 
```
