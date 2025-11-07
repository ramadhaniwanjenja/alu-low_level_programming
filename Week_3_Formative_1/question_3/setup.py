from distutils.core import setup, Extension

module = Extension('sensor_module', sources=['Question_3_ IoT_System.c'])

setup(name='SensorModule',
      version='1.0',
      description='IoT Sensor Module',
      ext_modules=[module])