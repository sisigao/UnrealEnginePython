#include "UnrealEnginePythonPrivatePCH.h"

PyObject *py_unreal_engine_get_game_viewport_client(PyObject * self, PyObject * args) {

	UGameViewportClient *viewport_client = GEngine->GameViewport;
	if (!viewport_client) {
		return PyErr_Format(PyExc_Exception, "no engine GameViewport found");
	}
	ue_PyUObject *ret = ue_get_python_wrapper(GEngine->GameViewport);
	if (!ret)
		return PyErr_Format(PyExc_Exception, "uobject is in invalid state");
	Py_INCREF(ret);
	return (PyObject *)ret;
}

#if WITH_EDITOR
PyObject *py_unreal_engine_get_editor_game_viewport_client(PyObject * self, PyObject * args) {

	UGameViewportClient *viewport_client = GEditor->GameViewport;
	if (!viewport_client) {
		return PyErr_Format(PyExc_Exception, "no editor GameViewport found");
	}
	ue_PyUObject *ret = ue_get_python_wrapper(GEditor->GameViewport);
	if (!ret)
		return PyErr_Format(PyExc_Exception, "uobject is in invalid state");
	Py_INCREF(ret);
	return (PyObject *)ret;
}
#endif

PyObject *py_ue_add_viewport_widget_content(ue_PyUObject *self, PyObject * args) {

	ue_py_check(self);

	PyObject *py_widget;
	int z_order = 0;

	if (!PyArg_ParseTuple(args, "O|i:add_viewport_widget_content", &py_widget, &z_order)) {
		return NULL;
	}

	UGameViewportClient *viewport = ue_py_check_type<UGameViewportClient>(self);
	if (!viewport)
		return PyErr_Format(PyExc_Exception, "object is not a GameViewportClient");

	ue_PySWidget *py_swidget = py_ue_is_swidget(py_widget);
	if (!py_swidget) {
		return PyErr_Format(PyExc_Exception, "argument is not a SWidget");
	}
	// TODO: decrement reference when destroying parent
	Py_INCREF(py_swidget);

	viewport->AddViewportWidgetContent(py_swidget->s_widget_owned, z_order);

	Py_INCREF(Py_None);
	return Py_None;
}

PyObject *py_ue_remove_viewport_widget_content(ue_PyUObject *self, PyObject * args) {

	ue_py_check(self);

	PyObject *py_widget;

	if (!PyArg_ParseTuple(args, "O:remove_viewport_widget_content", &py_widget)) {
		return NULL;
	}

	UGameViewportClient *viewport = ue_py_check_type<UGameViewportClient>(self);
	if (!viewport)
		return PyErr_Format(PyExc_Exception, "object is not a GameViewportClient");

	ue_PySWidget *py_swidget = py_ue_is_swidget(py_widget);
	if (!py_swidget) {
		return PyErr_Format(PyExc_Exception, "argument is not a SWidget");
	}
	Py_DECREF(py_swidget);

	viewport->RemoveViewportWidgetContent(py_swidget->s_widget_owned);

	Py_INCREF(Py_None);
	return Py_None;
}

PyObject *py_ue_remove_all_viewport_widgets(ue_PyUObject *self, PyObject * args) {

	ue_py_check(self);

	UGameViewportClient *viewport = ue_py_check_type<UGameViewportClient>(self);
	if (!viewport)
		return PyErr_Format(PyExc_Exception, "object is not a GameViewportClient");

	
	viewport->RemoveAllViewportWidgets();

	Py_INCREF(Py_None);
	return Py_None;
}