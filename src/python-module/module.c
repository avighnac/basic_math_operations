#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#include <string.h>

#include "../library/basic_math_operations.h"

static PyObject *basic_math_operations_add(PyObject *self, PyObject *args) {
  // Parse the input tuple
  const char *a, *b;
  if (!PyArg_ParseTuple(args, "ss", &a, &b)) {
    return NULL;
  }

  // Call the C function: void add(const char *a, const char *b, char *res)
  char *res = (char *)calloc(strlen(a) + strlen(b) + 3, 1);
  add(a, b, res);

  // Build the output tuple
  PyObject *ret = Py_BuildValue("s", res);

  // Free the memory
  free(res);

  return ret;
}

static PyObject *basic_math_operations_subtract(PyObject *self,
                                                PyObject *args) {
  // Parse the input tuple
  const char *a, *b;
  if (!PyArg_ParseTuple(args, "ss", &a, &b)) {
    return NULL;
  }

  // Call the C function: void subtract(const char *a, const char *b, char *res)
  char *res = (char *)calloc(strlen(a) + strlen(b) + 3, 1);
  subtract(a, b, res);

  // Build the output tuple
  PyObject *ret = Py_BuildValue("s", res);

  // Free the memory
  free(res);

  return ret;
}

static PyObject *basic_math_operations_multiply(PyObject *self,
                                                PyObject *args) {
  // Parse the input tuple
  const char *a, *b;
  if (!PyArg_ParseTuple(args, "ss", &a, &b)) {
    return NULL;
  }

  // Call the C function: void multiply(const char *a, const char *b, char *res)
  char *res = (char *)calloc(strlen(a) + strlen(b) + 3, 1);
  multiply(a, b, res);

  // Build the output tuple
  PyObject *ret = Py_BuildValue("s", res);

  // Free the memory
  free(res);

  return ret;
}

static PyObject *basic_math_operations_divide(PyObject *self, PyObject *args) {
  // Parse the input tuple, along with the size_t, not integer, accuracy
  const char *a, *b;
  size_t accuracy;
  if (!PyArg_ParseTuple(args, "ssn", &a, &b, &accuracy)) {
    return NULL;
  }

  // Call the C function: void divide(const char *a, const char *b, char *res,
  // size_t accuracy)
  char *res = (char *)calloc(strlen(a) + strlen(b) + accuracy + 3, 1);
  divide(a, b, res, accuracy);

  // Build the output tuple
  PyObject *ret = Py_BuildValue("s", res);

  // Free the memory
  free(res);

  return ret;
}

static PyObject *basic_math_operations_mod(PyObject *self, PyObject *args) {
  // Parse the input tuple, along with the size_t, not integer, accuracy
  const char *a, *b;
  if (!PyArg_ParseTuple(args, "ss", &a, &b)) {
    return NULL;
  }

  size_t a_len = strlen(a);
  size_t b_len = strlen(b);

  size_t max_len = a_len;
  if (b_len > max_len)
    max_len = b_len;

  char *quotient = (char *)calloc(a_len + b_len + 3, 1);
  char *remainder = (char *)calloc(max_len + 1, 1);
  divide_whole_with_remainder(a, b, quotient, remainder);

  // Build the output tuple
  PyObject *ret = Py_BuildValue("s", remainder);

  // Free the memory
  free(quotient);
  free(remainder);

  return ret;
}

static PyMethodDef basic_math_operations_methods[] = {
    {"add", basic_math_operations_add, METH_VARARGS,
     "Add two numbers represented as strings."},
    {"subtract", basic_math_operations_subtract, METH_VARARGS,
     "Subtract two numbers represented as strings."},
    {"multiply", basic_math_operations_multiply, METH_VARARGS,
     "Multiply two numbers represented as strings."},
    {"divide", basic_math_operations_divide, METH_VARARGS,
     "Divide two numbers represented as strings with a specified accuracy."},
    {"mod", basic_math_operations_mod, METH_VARARGS,
     "Find the remainder when the first number is divided by the second "
     "number. Both numbers are represented as strings."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef basic_math_operationsmodule = {
    PyModuleDef_HEAD_INIT, "basic_math_operations", /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module,
             or -1 if the module keeps state in global variables. */
    basic_math_operations_methods};

PyMODINIT_FUNC PyInit_basic_math_operations(void) {
  return PyModule_Create(&basic_math_operationsmodule);
}