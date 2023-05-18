# AIoT  app
This is AIoT application using development board [ESP-EYE](https://www.espressif.com/en/products/devkits/esp-eye/overview).

Please check [ESP-IDF docs](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for getting started instructions.

## Development Setup (Using WSL2 Ubuntu 22.04.2 LTS)
* Install prerequisities:  
`sudo apt-get install git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0`

* Get ESP-IDF.  
`git clone -b v5.0.1 --recursive https://github.com/espressif/esp-idf.git` 

* Setup the tools  
`cd esp-idf`  
`./install.sh esp32`

* Setup environment variable  
`source . $HOME/esp/esp-idf/export.sh`

We can add this to `~/. bash_profile`:   
`alias get_idf='. $HOME/repo/esp-idf/export.sh'`   
`get_idf` to avoid doing it every startup  

* Install idfx to flash and monitor on USB port (ref: https://github.com/abobija/idfx)  
`curl https://git.io/JyBgj --create-dirs -L -o $HOME/bin/idfx && chmod u+x $HOME/bin/idfx`. Ensure `~/bin` is in your system path. See `idfx help` on how to use.

## Using Docker (Not suggested for poor support on serial port connection)
 To run idf in docker in interactive mode:  
 `$docker run --rm -v $PWD:/project -w /project -it espressif/idf:release-v5.1`

 Then edit the code on separate terminal.  

 To run in one time command  
`$ docker run --rm -v $PWD:/project -w /project espressif/idf:release-v5.1 idf.py build`
