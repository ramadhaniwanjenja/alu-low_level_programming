#include <Python.h>
#include <stdlib.h>
#include <time.h>

static PyObject* get_sensor_data(PyObject* self, PyObject* args) {
    srand(time(NULL) + rand());
    
    float temperature = 20.0 + (rand() % 15);
    float humidity = 40.0 + (rand() % 30);
    int battery = 50 + (rand() % 50);
    
    return Py_BuildValue("{s:f,s:f,s:i}", 
                         "temperature", temperature,
                         "humidity", humidity,
                         "battery", battery);
}

static PyMethodDef SensorMethods[] = {
    {"get_sensor_data", get_sensor_data, METH_NOARGS, "Get sensor readings"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef sensormodule = {
    PyModuleDef_HEAD_INIT,
    "sensor_module",
    "IoT Sensor Module",
    -1,
    SensorMethods
};

PyMODINIT_FUNC PyInit_sensor_module(void) {
    return PyModule_Create(&sensormodule);
}

