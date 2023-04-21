AIoT  app
====================

This is AIoT application using development board [ESP-EYE](https://www.espressif.com/en/products/devkits/esp-eye/overview).

Please check [ESP-IDF docs](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for getting started instructions.

 To run idf in docker in interactive mode:
 $docker run --rm -v $PWD:/project -w /project -it espressif/idf:release-v5.1

 Then edit the code on separate email.

 To run in one time command
$ docker run --rm -v $PWD:/project -w /project espressif/idf:release-v5.1 idf.py build
