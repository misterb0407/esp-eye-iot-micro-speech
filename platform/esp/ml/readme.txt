There is an exclusive repo from 'esp' for the tflite. The git hub link for the repo is given below:
	https://github.com/espressif/tflite-micro-esp-examples/tree/master

To work with esp controller, we need following directories: 
	1. bus 
	2. esp32-camera
	3. esp-nn
	4. tflite-lib 

Copy the above folders into project, edit the CMake file to point to these folders. 
In our project, added the following line in CMakeLists: 
     'set(EXTRA_COMPONENT_DIRS ./platform/esp/ml/)'


******************************************************
After adding hello-world example project, the flash size is not enough. Do the following things
1. Increase the flash size in "idfx menucofnig" to 'Single factory app (large), no OTA' 
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/partition-tables.html

2. Also increase the FLASH-SIZE to 4 MB
https://github.com/espressif/esp-idf/issues/4829
https://espressif-docs.readthedocs-hosted.com/projects/esp-idf/en/latest/api-reference/kconfig.html#config-esptoolpy-flashsize