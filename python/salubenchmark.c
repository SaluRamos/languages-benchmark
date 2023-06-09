#include <Python.h>

static PyObject *method_fputs(PyObject *self, PyObject *args) {
    char *str, *filename = NULL;
    int bytes_copied = -1;
    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "ss", &str, &filename)) {
        return NULL;
    }
    FILE *fp = fopen(filename, "w+");
    bytes_copied = fputs(str, fp);
    fclose(fp);

    return PyLong_FromLong(bytes_copied);
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










static PyMethodDef salubenchmarkMethods[] = {
    {"fputs", method_fputs, METH_VARARGS, "Python interface for fputs C library function"},
    {"fib", method_fib, METH_VARARGS, "Calculate fibonacci"},
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