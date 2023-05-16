There is an exclusive repo from 'esp' for the tflite. The git hub link for the repo is given below:
	https://github.com/espressif/tflite-micro-esp-examples/tree/master

To work with esp controller, we need following directories: 
	1. bus 
	2. esp32-camera
	3. esp-nn
    4. tflite-lib 

Copy the above folders into project, edit the CMake to point to these folders. 
In our project, added the following line in CMakeLists: 
     'set(EXTRA_COMPONENT_DIRS ./platform/esp/ml/)'
