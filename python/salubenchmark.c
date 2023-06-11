#include <Python.h>
#include <math.h>

double generateRandomNumber(double min, double max) {
    double scale = rand() / (double)RAND_MAX;
    return min + scale * (max - min);
}

void generateRandomVectors(double vector3_1[3], double vector3_2[3]) {
    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        vector3_1[i] = generateRandomNumber(1.0, 10.0);
        vector3_2[i] = generateRandomNumber(1.0, 10.0);
    }
}

int fib(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

static PyObject *method_fib(PyObject *self, PyObject *args) {
    int n = 0;
    if(!PyArg_ParseTuple(args, "i", &n)) {
        return NULL;
    }
    int result = fib(n);
    return Py_BuildValue("i", result);
}


double testGeometry(double vector3_1[3], double vector3_2[3], double radius) {
    double distance = sqrt(pow(vector3_2[0] - vector3_1[0], 2) + pow(vector3_2[1] - vector3_1[1], 2) + pow(vector3_2[2] - vector3_1[2], 2));
    double distance_between_centers = sqrt(pow(vector3_2[0] - vector3_1[0], 2) + pow(vector3_2[1] - vector3_1[1], 2) + pow(vector3_2[2] - vector3_1[2], 2));
    double sphere_volume = (4.0 / 3.0) * 3.1415 * pow(radius, 3);
    return (distance + distance_between_centers + sphere_volume);
}

static PyObject *method_fastgengeometry(PyObject *self, PyObject *args){
    double geometrySum = 0;
    for(int i = 0; i < 10000000; i++){
        double radius = 0;
        double vector3_1bar[3] = {0,0,0};
        double vector3_2bar[3] = {0,0,0};
        generateRandomVectors(vector3_1bar, vector3_2bar);
        radius = generateRandomNumber(1.0, 10.0);
        geometrySum += testGeometry(vector3_1bar, vector3_2bar, radius);
    }
    return Py_BuildValue("d", geometrySum);
}

static PyObject *method_fastgeometry(PyObject *self, PyObject *args){
    double vector3_1bar[3] = {0,0,0};
    double vector3_2bar[3] = {0,0,0};
    double radius = 0;
    if(!PyArg_ParseTuple(args, "(ddd)(ddd)d", &vector3_1bar[0], &vector3_1bar[1], &vector3_1bar[2], &vector3_2bar[0], &vector3_2bar[1], &vector3_2bar[2], &radius)){
        return NULL;
    }
    double geometrySum = 0;
    for(int i = 0; i < 10000000; i++){
        geometrySum += testGeometry(vector3_1bar, vector3_2bar, radius);
    }
    return Py_BuildValue("d", geometrySum);
}

static PyObject *method_geometry(PyObject *self, PyObject *args){
    PyObject* vector3_1;
    PyObject* vector3_2;
    double *vector3_1bar;
    double *vector3_2bar;
    int vector3_1len = 0;
    int vector3_2len = 0;
    double radius = 0;
    if(!PyArg_ParseTuple(args, "OOd", &vector3_1, &vector3_2, &radius)){
        return NULL;
    }
    vector3_1 = PySequence_Fast(vector3_1, "argument must be iterable");
    if(!vector3_1){
        return 0;
    }
    vector3_1len = PySequence_Fast_GET_SIZE(vector3_1);
    vector3_1bar = malloc(vector3_1len*sizeof(double));
    if(!vector3_1bar) {
        Py_DECREF(vector3_1);
        return PyErr_NoMemory();
    }
    for(int i = 0; i < vector3_1len; i++){
        PyObject *fitem;
        PyObject *item = PySequence_Fast_GET_ITEM(vector3_1, i);
        if(!item){
            Py_DECREF(vector3_1);
            free(vector3_1bar);
            return 0;
        }
        fitem = PyNumber_Float(item);
        if(!fitem) {
            Py_DECREF(vector3_1);
            free(vector3_1bar);
            PyErr_SetString(PyExc_TypeError, "all items must be numbers");
            return 0;
        }
        vector3_1bar[i] = PyFloat_AS_DOUBLE(fitem);
        Py_DECREF(fitem);
    }
    vector3_2 = PySequence_Fast(vector3_2, "argument must be iterable");
    if(!vector3_2){
        return 0;
    }
    vector3_2len = PySequence_Fast_GET_SIZE(vector3_2);
    vector3_2bar = malloc(vector3_2len*sizeof(double));
    if(!vector3_2bar) {
        Py_DECREF(vector3_2);
        return PyErr_NoMemory();
    }
    for(int i = 0; i < vector3_2len; i++){
        PyObject *fitem;
        PyObject *item = PySequence_Fast_GET_ITEM(vector3_2, i);
        if(!item){
            Py_DECREF(vector3_2);
            free(vector3_2bar);
            return 0;
        }
        fitem = PyNumber_Float(item);
        if(!fitem) {
            Py_DECREF(vector3_2);
            free(vector3_2bar);
            PyErr_SetString(PyExc_TypeError, "all items must be numbers");
            return 0;
        }
        vector3_2bar[i] = PyFloat_AS_DOUBLE(fitem);
        Py_DECREF(fitem);
    }
    double geometrySum = 0;
    for(int i = 0; i < 10000000; i++){
        geometrySum += testGeometry(vector3_1bar, vector3_2bar, radius);
    }
    free(vector3_1bar);
    free(vector3_2bar);
    return Py_BuildValue("d", geometrySum);
}

static PyMethodDef salubenchmarkMethods[] = {
    {"fib", method_fib, METH_VARARGS, "Calculate fibonacci"},
    {"geometry", method_geometry, METH_VARARGS, "Geometry Benchmark"},
    {"fastgeometry", method_fastgeometry, METH_VARARGS, "Geometry Benchmark"},
    {"fastgengeometry", method_fastgengeometry, METH_NOARGS, "Geometry Benchmark with generated numbers"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef salubenchmarkmodule = {
    PyModuleDef_HEAD_INIT,
    "salubenchmark",
    "Python interface for the salubenchmark C library function",
    -1,
    salubenchmarkMethods
};

PyMODINIT_FUNC PyInit_salubenchmark(void) {
    return PyModule_Create(&salubenchmarkmodule);
}