/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2013-2014 Planets Communications B.V.
   Copyright (C) 2013-2024 Bareos GmbH & Co. KG

   This program is Free Software; you can modify it under the terms of
   version three of the GNU Affero General Public License as published by the
   Free Software Foundation, which is listed in the file LICENSE.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/
/**
 * @file
 * This defines the Python types in C++ and the callbacks from Python we
 * support.
 */

#ifndef BAREOS_PLUGINS_FILED_PYTHON_MODULE_BAREOSFD_H_
#define BAREOS_PLUGINS_FILED_PYTHON_MODULE_BAREOSFD_H_

#define PYTHON_MODULE_NAME bareosfd
#define PYTHON_MODULE_NAME_QUOTED "bareosfd"

/* common code for all python plugins */
#include "plugins/include/python_plugins_common.h"
#include "plugins/include/common.h"

#include "structmember.h"

/* include automatically generated C API */
#include "c_api/capi_1.inc"


#ifdef BAREOSFD_MODULE

#  include "include/filetypes.h"
/* This section is used when compiling bareosfd.cc */

namespace filedaemon {

// Python structures mapping C++ ones.

/**
 * This packet is used for the restore objects.
 * It is passed to the plugin when restoring the object.
 */
typedef struct {
  PyObject_HEAD PyObject* object_name; /* Object name */
  PyObject* object;                    /* Restore object data to restore */
  char* plugin_name;                   /* Plugin name */
  int32_t object_type;                 /* FT_xx for this file */
  int32_t object_len;                  /* restore object length */
  int32_t object_full_len;             /* restore object uncompressed length */
  int32_t object_index;                /* restore object index */
  int32_t object_compression;          /* set to compression type */
  int32_t stream;                      /* attribute stream id */
  uint32_t JobId;                      /* JobId object came from */
} PyRestoreObject;

// Forward declarations of type specific functions.
static void PyRestoreObject_dealloc(PyRestoreObject* self);
static int PyRestoreObject_init(PyRestoreObject* self,
                                PyObject* args,
                                PyObject* kwds);
static PyObject* PyRestoreObject_repr(PyRestoreObject* self);

static PyMethodDef PyRestoreObject_methods[] = {
    {} /* Sentinel */
};

static PyMemberDef PyRestoreObject_members[]
    = {{(char*)"object_name", T_OBJECT, offsetof(PyRestoreObject, object_name),
        0, (char*)"Object Name"},
       {(char*)"object", T_OBJECT, offsetof(PyRestoreObject, object), 0,
        (char*)"Object Content"},
       {(char*)"plugin_name", T_STRING, offsetof(PyRestoreObject, plugin_name),
        0, (char*)"Plugin Name"},
       {(char*)"object_type", T_INT, offsetof(PyRestoreObject, object_type), 0,
        (char*)"Object Type"},
       {(char*)"object_len", T_INT, offsetof(PyRestoreObject, object_len), 0,
        (char*)"Object Length"},
       {(char*)"object_full_len", T_INT,
        offsetof(PyRestoreObject, object_full_len), 0,
        (char*)"Object Full Length"},
       {(char*)"object_index", T_INT, offsetof(PyRestoreObject, object_index),
        0, (char*)"Object Index"},
       {(char*)"object_compression", T_INT,
        offsetof(PyRestoreObject, object_compression), 0,
        (char*)"Object Compression"},
       {(char*)"stream", T_INT, offsetof(PyRestoreObject, stream), 0,
        (char*)"Attribute Stream"},
       {(char*)"jobid", T_UINT, offsetof(PyRestoreObject, JobId), 0,
        (char*)"Jobid"},
       {} /* Sentinel */};

// The PyStatPacket type
typedef struct {
  PyObject_HEAD uint32_t dev;
  uint64_t ino;
  uint16_t mode;
  int16_t nlink;
  uint32_t uid;
  uint32_t gid;
  uint32_t rdev;
  uint64_t size;
  time_t atime;
  time_t mtime;
  time_t ctime;
  uint32_t blksize;
  uint64_t blocks;
} PyStatPacket;

// Forward declarations of type specific functions.
static void PyStatPacket_dealloc(PyStatPacket* self);
static int PyStatPacket_init(PyStatPacket* self,
                             PyObject* args,
                             PyObject* kwds);
static PyObject* PyStatPacket_repr(PyStatPacket* self);

static PyMethodDef PyStatPacket_methods[] = {
    {} /* Sentinel */
};

static PyMemberDef PyStatPacket_members[] = {
    {(char*)"st_dev", T_UINT, offsetof(PyStatPacket, dev), 0, (char*)"Device"},
    {(char*)"st_ino", T_ULONGLONG, offsetof(PyStatPacket, ino), 0,
     (char*)"Inode number"},
    {(char*)"st_mode", T_USHORT, offsetof(PyStatPacket, mode), 0,
     (char*)"Mode"},
    {(char*)"st_nlink", T_USHORT, offsetof(PyStatPacket, nlink), 0,
     (char*)"Number of hardlinks"},
    {(char*)"st_uid", T_UINT, offsetof(PyStatPacket, uid), 0, (char*)"User Id"},
    {(char*)"st_gid", T_UINT, offsetof(PyStatPacket, gid), 0,
     (char*)"Group Id"},
    {(char*)"st_rdev", T_UINT, offsetof(PyStatPacket, rdev), 0, (char*)"Rdev"},
    {(char*)"st_size", T_ULONGLONG, offsetof(PyStatPacket, size), 0,
     (char*)"Size"},
    {(char*)"st_atime", T_UINT, offsetof(PyStatPacket, atime), 0,
     (char*)"Access Time"},
    {(char*)"st_mtime", T_UINT, offsetof(PyStatPacket, mtime), 0,
     (char*)"Modification Time"},
    {(char*)"st_ctime", T_UINT, offsetof(PyStatPacket, ctime), 0,
     (char*)"Change Time"},
    {(char*)"st_blksize", T_UINT, offsetof(PyStatPacket, blksize), 0,
     (char*)"Blocksize"},
    {(char*)"st_blocks", T_ULONGLONG, offsetof(PyStatPacket, blocks), 0,
     (char*)"Blocks"},
    {} /* Sentinel */};

// The PySavePacket type
typedef struct {
  PyObject_HEAD PyObject* fname; /* Full path and filename */
  PyObject* link;                /* Link name if any */
  PyObject* statp;               /* System stat() packet for file */
  int32_t type;                  /* FT_xx for this file */
  PyObject* flags;               /* Bareos internal flags */
  bool no_read;        /* During the save, the file should not be saved */
  bool portable;       /* set if data format is portable */
  bool accurate_found; /* Found in accurate list (valid after CheckChanges()) */
  char* cmd;           /* Command */
  time_t save_time;    /* Start of incremental time */
  uint32_t delta_seq;  /* Delta sequence number */
  PyObject* object_name; /* Object name to create */
  PyObject* object;      /* Restore object data to save */
  int32_t object_len;    /* Restore object length */
  int32_t object_index;  /* Restore object index */
} PySavePacket;

// Forward declarations of type specific functions.
static void PySavePacket_dealloc(PySavePacket* self);
static int PySavePacket_init(PySavePacket* self,
                             PyObject* args,
                             PyObject* kwds);
static PyObject* PySavePacket_repr(PySavePacket* self);

static PyMethodDef PySavePacket_methods[] = {
    {} /* Sentinel */
};

static PyMemberDef PySavePacket_members[] = {
    {(char*)"fname", T_OBJECT, offsetof(PySavePacket, fname), 0,
     (char*)"Filename"},
    {(char*)"link", T_OBJECT, offsetof(PySavePacket, link), 0,
     (char*)"Linkname"},
    {(char*)"statp", T_OBJECT, offsetof(PySavePacket, statp), 0,
     (char*)"Stat Packet"},
    {(char*)"type", T_INT, offsetof(PySavePacket, type), 0, (char*)"Type"},
    {(char*)"flags", T_OBJECT, offsetof(PySavePacket, flags), 0,
     (char*)"Flags"},
    {(char*)"no_read", T_BOOL, offsetof(PySavePacket, no_read), 0,
     (char*)"No Read"},
    {(char*)"portable", T_BOOL, offsetof(PySavePacket, portable), 0,
     (char*)"Portable"},
    {(char*)"accurate_found", T_BOOL, offsetof(PySavePacket, accurate_found), 0,
     (char*)"Accurate Found"},
    {(char*)"cmd", T_STRING, offsetof(PySavePacket, cmd), 0, (char*)"Command"},
    {(char*)"save_time", T_UINT, offsetof(PySavePacket, save_time), 0,
     (char*)"Save Time"},
    {(char*)"delta_seq", T_UINT, offsetof(PySavePacket, delta_seq), 0,
     (char*)"Delta Sequence"},
    {(char*)"object_name", T_OBJECT, offsetof(PySavePacket, object_name), 0,
     (char*)"Restore Object Name"},
    {(char*)"object", T_OBJECT, offsetof(PySavePacket, object), 0,
     (char*)"Restore ObjectName"},
    {(char*)"object_len", T_INT, offsetof(PySavePacket, object_len), 0,
     (char*)"Restore ObjectLen"},
    {(char*)"object_index", T_INT, offsetof(PySavePacket, object_index), 0,
     (char*)"Restore ObjectIndex"},
    {} /* Sentinel */};

// The PyRestorePacket type
typedef struct {
  PyObject_HEAD int32_t stream; /* Attribute stream id */
  int32_t data_stream;          /* Id of data stream to follow */
  int32_t type;                 /* File type FT */
  int32_t file_index;           /* File index */
  int32_t LinkFI;               /* File index to data if hard link */
  uint32_t uid;                 /* Userid */
  PyObject* statp;              /* Decoded stat packet */
  const char* attrEx;           /* Extended attributes if any */
  const char* ofname;           /* Output filename */
  const char* olname;           /* Output link name */
  const char* where;            /* Where */
  const char* RegexWhere;       /* Regex where */
  int replace;                  /* Replace flag */
  int create_status;            /* Status from createFile() */
  int filedes;                  /* filedescriptor for read/write in core */
} PyRestorePacket;

// Forward declarations of type specific functions.
static void PyRestorePacket_dealloc(PyRestorePacket* self);
static int PyRestorePacket_init(PyRestorePacket* self,
                                PyObject* args,
                                PyObject* kwds);
static PyObject* PyRestorePacket_repr(PyRestorePacket* self);

static PyMethodDef PyRestorePacket_methods[] = {
    {} /* Sentinel */
};

static PyMemberDef PyRestorePacket_members[] = {
    {(char*)"stream", T_INT, offsetof(PyRestorePacket, stream), 0,
     (char*)"Attribute stream id"},
    {(char*)"data_stream", T_INT, offsetof(PyRestorePacket, data_stream), 0,
     (char*)"Id of data stream to follow"},
    {(char*)"type", T_INT, offsetof(PyRestorePacket, type), 0,
     (char*)"File type FT"},
    {(char*)"file_index", T_INT, offsetof(PyRestorePacket, file_index), 0,
     (char*)"File index"},
    {(char*)"linkFI", T_INT, offsetof(PyRestorePacket, LinkFI), 0,
     (char*)"File index to data if hard link"},
    {(char*)"uid", T_UINT, offsetof(PyRestorePacket, uid), 0, (char*)"User Id"},
    {(char*)"statp", T_OBJECT, offsetof(PyRestorePacket, statp), 0,
     (char*)"Stat Packet"},
    {(char*)"attrEX", T_STRING, offsetof(PyRestorePacket, attrEx), 0,
     (char*)"Extended attributes"},
    {(char*)"ofname", T_STRING, offsetof(PyRestorePacket, ofname), 0,
     (char*)"Output filename"},
    {(char*)"olname", T_STRING, offsetof(PyRestorePacket, olname), 0,
     (char*)"Output link name"},
    {(char*)"where", T_STRING, offsetof(PyRestorePacket, where), 0,
     (char*)"Where"},
    {(char*)"regexwhere", T_STRING, offsetof(PyRestorePacket, RegexWhere), 0,
     (char*)"Regex where"},
    {(char*)"replace", T_INT, offsetof(PyRestorePacket, replace), 0,
     (char*)"Replace flag"},
    {(char*)"create_status", T_INT, offsetof(PyRestorePacket, create_status), 0,
     (char*)"Status from createFile()"},
    {(char*)"filedes", T_INT, offsetof(PyRestorePacket, filedes), 0,
     (char*)"file descriptor of current file"},
    {NULL, 0, 0, 0, NULL}};

// The PyIOPacket type
typedef struct {
  PyObject_HEAD uint16_t func; /* Function code */
  int32_t count;               /* Read/Write count */
  int32_t flags;               /* Open flags */
  int32_t mode;                /* Permissions for created files */
  PyObject* buf;               /* Read/Write buffer */
  const char* fname;           /* Open filename */
  int32_t status;              /* Return status */
  int32_t io_errno;            /* Errno code */
  int32_t lerror;              /* Win32 error code */
  int32_t whence;              /* Lseek argument */
  int64_t offset;              /* Lseek argument */
  bool win32;                  /* Win32 GetLastError returned */
  int filedes;                 /* filedescriptor for read/write in core */
} PyIoPacket;

// Forward declarations of type specific functions.
static void PyIoPacket_dealloc(PyIoPacket* self);
static int PyIoPacket_init(PyIoPacket* self, PyObject* args, PyObject* kwds);
static PyObject* PyIoPacket_repr(PyIoPacket* self);

static PyMethodDef PyIoPacket_methods[] = {
    {} /* Sentinel */
};

static PyMemberDef PyIoPacket_members[]
    = {{(char*)"func", T_USHORT, offsetof(PyIoPacket, func), 0,
        (char*)"Function code"},
       {(char*)"count", T_INT, offsetof(PyIoPacket, count), 0,
        (char*)"Read/write count"},
       {(char*)"flags", T_INT, offsetof(PyIoPacket, flags), 0,
        (char*)"Open flags"},
       {(char*)"mode", T_INT, offsetof(PyIoPacket, mode), 0,
        (char*)"Permissions for created files"},
       {(char*)"buf", T_OBJECT, offsetof(PyIoPacket, buf), 0,
        (char*)"Read/write buffer"},
       {(char*)"fname", T_STRING, offsetof(PyIoPacket, fname), 0,
        (char*)"Open filename"},
       {(char*)"status", T_INT, offsetof(PyIoPacket, status), 0,
        (char*)"Return status"},
       {(char*)"io_errno", T_INT, offsetof(PyIoPacket, io_errno), 0,
        (char*)"Errno code"},
       {(char*)"lerror", T_INT, offsetof(PyIoPacket, lerror), 0,
        (char*)"Win32 error code"},
       {(char*)"whence", T_INT, offsetof(PyIoPacket, whence), 0,
        (char*)"Lseek argument"},
       {(char*)"offset", T_LONGLONG, offsetof(PyIoPacket, offset), 0,
        (char*)"Lseek argument"},
       {(char*)"win32", T_BOOL, offsetof(PyIoPacket, win32), 0,
        (char*)"Win32 GetLastError returned"},
       {(char*)"filedes", T_INT, offsetof(PyIoPacket, filedes), 0,
        (char*)"file descriptor of current file"},
       {NULL, 0, 0, 0, NULL}};

// The PyAclPacket type
typedef struct {
  PyObject_HEAD const char* fname; /* Filename */
  PyObject* content;               /* ACL content */
} PyAclPacket;

// Forward declarations of type specific functions.
static void PyAclPacket_dealloc(PyAclPacket* self);
static int PyAclPacket_init(PyAclPacket* self, PyObject* args, PyObject* kwds);
static PyObject* PyAclPacket_repr(PyAclPacket* self);

static PyMethodDef PyAclPacket_methods[] = {
    {} /* Sentinel */
};

static PyMemberDef PyAclPacket_members[]
    = {{(char*)"fname", T_STRING, offsetof(PyAclPacket, fname), 0,
        (char*)"Filename"},
       {(char*)"content", T_OBJECT, offsetof(PyAclPacket, content), 0,
        (char*)"ACL content buffer"},
       {} /* Sentinel */};

// The PyXattrPacket type
typedef struct {
  PyObject_HEAD const char* fname; /* Filename */
  PyObject* name;                  /* XATTR name */
  PyObject* value;                 /* XATTR value */
} PyXattrPacket;

// Forward declarations of type specific functions.
static void PyXattrPacket_dealloc(PyXattrPacket* self);
static int PyXattrPacket_init(PyXattrPacket* self,
                              PyObject* args,
                              PyObject* kwds);
static PyObject* PyXattrPacket_repr(PyXattrPacket* self);

static PyMethodDef PyXattrPacket_methods[] = {
    {} /* Sentinel */
};

static PyMemberDef PyXattrPacket_members[]
    = {{(char*)"fname", T_STRING, offsetof(PyXattrPacket, fname), 0,
        (char*)"Filename"},
       {(char*)"name", T_OBJECT, offsetof(PyXattrPacket, name), 0,
        (char*)"XATTR name buffer"},
       {(char*)"value", T_OBJECT, offsetof(PyXattrPacket, value), 0,
        (char*)"XATTR value buffer"},
       {} /* Sentinel */};

// Callback methods from Python.
static PyObject* PyBareosGetValue(PyObject* self, PyObject* args);
static PyObject* PyBareosSetValue(PyObject* self, PyObject* args);
static PyObject* PyBareosDebugMessage(PyObject* self, PyObject* args);
static PyObject* PyBareosJobMessage(PyObject* self, PyObject* args);
static PyObject* PyBareosRegisterEvents(PyObject* self, PyObject* args);
static PyObject* PyBareosUnRegisterEvents(PyObject* self, PyObject* args);
static PyObject* PyBareosGetInstanceCount(PyObject* self, PyObject* args);
static PyObject* PyBareosAddExclude(PyObject* self, PyObject* args);
static PyObject* PyBareosAddInclude(PyObject* self, PyObject* args);
static PyObject* PyBareosAddOptions(PyObject* self, PyObject* args);
static PyObject* PyBareosAddRegex(PyObject* self, PyObject* args);
static PyObject* PyBareosAddWild(PyObject* self, PyObject* args);
static PyObject* PyBareosNewOptions(PyObject* self, PyObject* args);
static PyObject* PyBareosNewInclude(PyObject* self, PyObject* args);
static PyObject* PyBareosNewPreInclude(PyObject* self, PyObject* args);
static PyObject* PyBareosCheckChanges(PyObject* self, PyObject* args);
static PyObject* PyBareosAcceptFile(PyObject* self, PyObject* args);
static PyObject* PyBareosSetSeenBitmap(PyObject* self, PyObject* args);
static PyObject* PyBareosClearSeenBitmap(PyObject* self, PyObject* args);

static PyMethodDef Methods[] = {
    {"GetValue", PyBareosGetValue, METH_VARARGS, "Get a Plugin value"},
    {"SetValue", PyBareosSetValue, METH_VARARGS, "Set a Plugin value"},
    {"DebugMessage", PyBareosDebugMessage, METH_VARARGS,
     "Print a Debug message"},
    {"JobMessage", PyBareosJobMessage, METH_VARARGS, "Print a Job message"},
    {"RegisterEvents", PyBareosRegisterEvents, METH_VARARGS,
     "Register Plugin Events"},
    {"UnRegisterEvents", PyBareosUnRegisterEvents, METH_VARARGS,
     "Unregister Plugin Events"},
    {"GetInstanceCount", PyBareosGetInstanceCount, METH_VARARGS,
     "Get number of instances of current plugin"},
    {"AddExclude", PyBareosAddExclude, METH_VARARGS, "Add Exclude pattern"},
    {"AddInclude", PyBareosAddInclude, METH_VARARGS, "Add Include pattern"},
    {"AddOptions", PyBareosAddOptions, METH_VARARGS, "Add Include options"},
    {"AddRegex", PyBareosAddRegex, METH_VARARGS, "Add regex"},
    {"AddWild", PyBareosAddWild, METH_VARARGS, "Add wildcard"},
    {"NewOptions", PyBareosNewOptions, METH_VARARGS, "Add new option block"},
    {"NewInclude", PyBareosNewInclude, METH_VARARGS, "Add new include block"},
    {"NewPreInclude", PyBareosNewPreInclude, METH_VARARGS,
     "Add new pre include block"},
    {"CheckChanges", PyBareosCheckChanges, METH_VARARGS,
     "Check if a file have to be backed up using Accurate code"},
    {"AcceptFile", PyBareosAcceptFile, METH_VARARGS,
     "Check if a file would be saved using current Include/Exclude code"},
    {"SetSeenBitmap", PyBareosSetSeenBitmap, METH_VARARGS,
     "Set bit in the Accurate Seen bitmap"},
    {"ClearSeenBitmap", PyBareosClearSeenBitmap, METH_VARARGS,
     "Clear bit in the Accurate Seen bitmap"},
    {NULL, NULL, 0, NULL}};

static bRC set_bareos_core_functions(CoreFunctions* new_bareos_core_functions);
static bRC set_plugin_context(PluginContext* new_plugin_context);
static void PyErrorHandler(PluginContext* plugin_ctx, int msgtype);
static bRC PyParsePluginDefinition(PluginContext* plugin_ctx, void* value);
static bRC PyGetPluginValue(PluginContext* plugin_ctx,
                            pVariable var,
                            void* value);
static bRC PySetPluginValue(PluginContext* plugin_ctx,
                            pVariable var,
                            void* value);
static bRC PyHandlePluginEvent(PluginContext* plugin_ctx,
                               bEvent* event,
                               void* value);
static bRC PyStartBackupFile(PluginContext* plugin_ctx, save_pkt* sp);
static bRC PyEndBackupFile(PluginContext* plugin_ctx);
static bRC PyPluginIO(PluginContext* plugin_ctx, io_pkt* io);
static bRC PyStartRestoreFile(PluginContext* plugin_ctx, const char* cmd);
static bRC PyEndRestoreFile(PluginContext* plugin_ctx);
static bRC PyCreateFile(PluginContext* plugin_ctx, restore_pkt* rp);
static bRC PySetFileAttributes(PluginContext* plugin_ctx, restore_pkt* rp);
static bRC PyCheckFile(PluginContext* plugin_ctx, char* fname);
static bRC PyGetAcl(PluginContext* plugin_ctx, acl_pkt* ap);
static bRC PySetAcl(PluginContext* plugin_ctx, acl_pkt* ap);
static bRC PyGetXattr(PluginContext* plugin_ctx, xattr_pkt* xp);
static bRC PySetXattr(PluginContext* plugin_ctx, xattr_pkt* xp);
static bRC PyRestoreObjectData(PluginContext* plugin_ctx,
                               restore_object_pkt* rop);
static bRC PyHandleBackupFile(PluginContext* plugin_ctx, save_pkt* sp);

} /* namespace filedaemon */
using namespace filedaemon;

/* variables storing bareos pointers */
thread_local PluginContext* plugin_context = NULL;

// per interpreter state of the bareosfd module
struct fd_module_state {
  PyTypeObject* stat_pkt;
  PyTypeObject* io_pkt;
  PyTypeObject* save_pkt;
  PyTypeObject* restore_pkt;
  PyTypeObject* acl_pkt;
  PyTypeObject* xattr_pkt;
  PyTypeObject* restore_obj;

  static fd_module_state* get(PyObject* module)
  {
    return static_cast<fd_module_state*>(PyModule_GetState(module));
  }

  template <typename T> PyTypeObject* typeobj() = delete;
  template <typename T> T* make() { return PyObject_New(T, typeobj<T>()); }
};

template <> PyTypeObject* fd_module_state::typeobj<PyStatPacket>()
{
  return stat_pkt;
}
template <> PyTypeObject* fd_module_state::typeobj<PyIoPacket>()
{
  return io_pkt;
}
template <> PyTypeObject* fd_module_state::typeobj<PySavePacket>()
{
  return save_pkt;
}
template <> PyTypeObject* fd_module_state::typeobj<PyRestorePacket>()
{
  return restore_pkt;
}
template <> PyTypeObject* fd_module_state::typeobj<PyAclPacket>()
{
  return acl_pkt;
}
template <> PyTypeObject* fd_module_state::typeobj<PyXattrPacket>()
{
  return xattr_pkt;
}
template <> PyTypeObject* fd_module_state::typeobj<PyRestoreObject>()
{
  return restore_obj;
}

static PyType_Slot PyStatPacket_slots[] = {
    {Py_tp_dealloc, (void*)PyStatPacket_dealloc},
    {Py_tp_doc, (void*)"test doc"},
    {Py_tp_members, PyStatPacket_members},
    {Py_tp_methods, PyStatPacket_methods},
    {Py_tp_repr, (void*)PyStatPacket_repr},
    {Py_tp_init, (void*)PyStatPacket_init},
    {Py_tp_new, (void*)PyType_GenericNew},
    {0, NULL},
};
static PyType_Slot PyIoPacket_slots[] = {
    {Py_tp_dealloc, (void*)PyIoPacket_dealloc},
    {Py_tp_doc, (void*)"test doc"},
    {Py_tp_members, PyIoPacket_members},
    {Py_tp_methods, PyIoPacket_methods},
    {Py_tp_repr, (void*)PyIoPacket_repr},
    {Py_tp_init, (void*)PyIoPacket_init},
    {Py_tp_new, (void*)PyType_GenericNew},
    {0, NULL},
};
static PyType_Slot PySavePacket_slots[] = {
    {Py_tp_dealloc, (void*)PySavePacket_dealloc},
    {Py_tp_doc, (void*)"test doc"},
    {Py_tp_members, PySavePacket_members},
    {Py_tp_methods, PySavePacket_methods},
    {Py_tp_repr, (void*)PySavePacket_repr},
    {Py_tp_init, (void*)PySavePacket_init},
    {Py_tp_new, (void*)PyType_GenericNew},
    {0, NULL},
};
static PyType_Slot PyRestorePacket_slots[] = {
    {Py_tp_dealloc, (void*)PyRestorePacket_dealloc},
    {Py_tp_doc, (void*)"test doc"},
    {Py_tp_members, PyRestorePacket_members},
    {Py_tp_methods, PyRestorePacket_methods},
    {Py_tp_repr, (void*)PyRestorePacket_repr},
    {Py_tp_init, (void*)PyRestorePacket_init},
    {Py_tp_new, (void*)PyType_GenericNew},
    {0, NULL},
};
static PyType_Slot PyAclPacket_slots[] = {
    {Py_tp_dealloc, (void*)PyAclPacket_dealloc},
    {Py_tp_doc, (void*)"test doc"},
    {Py_tp_members, PyAclPacket_members},
    {Py_tp_methods, PyAclPacket_methods},
    {Py_tp_repr, (void*)PyAclPacket_repr},
    {Py_tp_init, (void*)PyAclPacket_init},
    {Py_tp_new, (void*)PyType_GenericNew},
    {0, NULL},
};
static PyType_Slot PyXattrPacket_slots[] = {
    {Py_tp_dealloc, (void*)PyXattrPacket_dealloc},
    {Py_tp_doc, (void*)"test doc"},
    {Py_tp_members, PyXattrPacket_members},
    {Py_tp_methods, PyXattrPacket_methods},
    {Py_tp_repr, (void*)PyXattrPacket_repr},
    {Py_tp_init, (void*)PyXattrPacket_init},
    {Py_tp_new, (void*)PyType_GenericNew},
    {0, NULL},
};
static PyType_Slot PyRestoreObject_slots[] = {
    {Py_tp_dealloc, (void*)PyRestoreObject_dealloc},
    {Py_tp_doc, (void*)"test doc"},
    {Py_tp_members, PyRestoreObject_members},
    {Py_tp_methods, PyRestoreObject_methods},
    {Py_tp_repr, (void*)PyRestoreObject_repr},
    {Py_tp_init, (void*)PyRestoreObject_init},
    {Py_tp_new, (void*)PyType_GenericNew},
    {0, NULL},
};

#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wmissing-field-initializers"
static PyType_Spec PyStatPacket_spec = {
    .name = "bareosfd.StatPacket",
    .basicsize = sizeof(PyStatPacket),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE),
    .slots = PyStatPacket_slots,
};
static PyType_Spec PyIoPacket_spec = {
    .name = "bareosfd.IoPacket",
    .basicsize = sizeof(PyIoPacket),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE),
    .slots = PyIoPacket_slots,
};
static PyType_Spec PySavePacket_spec = {
    .name = "bareosfd.SavePacket",
    .basicsize = sizeof(PySavePacket),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE),
    .slots = PySavePacket_slots,
};
static PyType_Spec PyRestorePacket_spec = {
    .name = "bareosfd.RestorePacket",
    .basicsize = sizeof(PyRestorePacket),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE),
    .slots = PyRestorePacket_slots,
};
static PyType_Spec PyAclPacket_spec = {
    .name = "bareosfd.AclPacket",
    .basicsize = sizeof(PyAclPacket),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE),
    .slots = PyAclPacket_slots,
};
static PyType_Spec PyXattrPacket_spec = {
    .name = "bareosfd.XattrPacket",
    .basicsize = sizeof(PyXattrPacket),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE),
    .slots = PyXattrPacket_slots,
};
static PyType_Spec PyRestoreObject_spec = {
    .name = "bareosfd.RestoreObject",
    .basicsize = sizeof(PyRestoreObject),
    .flags = (Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE),
    .slots = PyRestoreObject_slots,
};
#  pragma GCC diagnostic pop

static bool module_add_types(PyObject* m, fd_module_state* s)
{
  s->stat_pkt
      = (PyTypeObject*)PyType_FromModuleAndSpec(m, &PyStatPacket_spec, NULL);
  s->io_pkt
      = (PyTypeObject*)PyType_FromModuleAndSpec(m, &PyIoPacket_spec, NULL);
  s->save_pkt
      = (PyTypeObject*)PyType_FromModuleAndSpec(m, &PySavePacket_spec, NULL);
  s->restore_pkt
      = (PyTypeObject*)PyType_FromModuleAndSpec(m, &PyRestorePacket_spec, NULL);
  s->acl_pkt
      = (PyTypeObject*)PyType_FromModuleAndSpec(m, &PyAclPacket_spec, NULL);
  s->xattr_pkt
      = (PyTypeObject*)PyType_FromModuleAndSpec(m, &PyXattrPacket_spec, NULL);
  s->restore_obj
      = (PyTypeObject*)PyType_FromModuleAndSpec(m, &PyRestoreObject_spec, NULL);
#  define ADDTYPE(Type)                                       \
    do {                                                      \
      if (PyModule_AddType(m, s->Type) < 0) { return false; } \
    } while (0)
  ADDTYPE(stat_pkt);
  ADDTYPE(io_pkt);
  ADDTYPE(save_pkt);
  ADDTYPE(restore_pkt);
  ADDTYPE(acl_pkt);
  ADDTYPE(xattr_pkt);
  ADDTYPE(restore_obj);
#  undef ADDTYPE

  return true;
}

static void* load_module_impl(PyObject* m, fd_module_state* s)
{
  static void* Bareosfd_API[Bareosfd_API_pointers];
  PyObject* c_api_object;

  /* Initialize the C API pointer array */
#  include "c_api/capi_3.inc"

  /* Create a Capsule containing the API pointer array's address */
  c_api_object = PyCapsule_New((void*)Bareosfd_API,
                               PYTHON_MODULE_NAME_QUOTED "._C_API", NULL);

  if (c_api_object != NULL) {
    PyModule_AddObject(m, "_C_API", c_api_object);
  } else {
    return MOD_ERROR_VAL;
  }

  if (!module_add_types(m, s)) { return MOD_ERROR_VAL; }

  /* module dictionaries */
  DEFINE_bRCs_DICT();
  DEFINE_bJobMessageTypes_DICT();

#  define EXPORT_ENUM_VALUE(dict, symbol) ConstSet_StrLong(dict, symbol, symbol)

  const char* bVariable = "bVariable";
  PyObject* pDictbVariable = NULL;
  pDictbVariable = PyDict_New();
  if (!pDictbVariable) { return MOD_ERROR_VAL; }
  EXPORT_ENUM_VALUE(pDictbVariable, bVarJobId);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarFDName);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarLevel);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarType);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarClient);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarJobName);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarJobStatus);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarSinceTime);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarAccurate);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarFileSeen);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarVssClient);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarWorkingDir);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarWhere);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarRegexWhere);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarExePath);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarVersion);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarDistName);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarPrevJobName);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarPrefixLinks);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarCheckChanges);
  EXPORT_ENUM_VALUE(pDictbVariable, bVarUsedConfig);
  if (PyModule_AddObject(m, bVariable, pDictbVariable)) {
    return MOD_ERROR_VAL;
  }


  const char* bFileType = "bFileType";
  PyObject* pDictbFileType = NULL;
  pDictbFileType = PyDict_New();
  if (!pDictbFileType) { return MOD_ERROR_VAL; }
  EXPORT_ENUM_VALUE(pDictbFileType, FT_LNKSAVED);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_REGE);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_REG);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_LNK);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_DIREND);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_SPEC);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_NOACCESS);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_NOFOLLOW);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_NOSTAT);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_NOCHG);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_DIRNOCHG);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_ISARCH);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_NORECURSE);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_NOFSCHG);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_NOOPEN);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_RAW);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_FIFO);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_DIRBEGIN);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_INVALIDFS);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_INVALIDDT);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_REPARSE);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_PLUGIN);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_DELETED);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_BASE);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_RESTORE_FIRST);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_JUNCTION);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_PLUGIN_CONFIG);
  EXPORT_ENUM_VALUE(pDictbFileType, FT_PLUGIN_CONFIG_FILLED);
  if (PyModule_AddObject(m, bFileType, pDictbFileType)) {
    return MOD_ERROR_VAL;
  }


  const char* bCFs = "bCFs";
  PyObject* pDictbCFs = NULL;
  pDictbCFs = PyDict_New();
  if (!pDictbCFs) { return MOD_ERROR_VAL; }
  EXPORT_ENUM_VALUE(pDictbCFs, CF_SKIP);
  EXPORT_ENUM_VALUE(pDictbCFs, CF_ERROR);
  EXPORT_ENUM_VALUE(pDictbCFs, CF_EXTRACT);
  EXPORT_ENUM_VALUE(pDictbCFs, CF_CREATED);
  EXPORT_ENUM_VALUE(pDictbCFs, CF_CORE);
  if (PyModule_AddObject(m, bCFs, pDictbCFs)) { return MOD_ERROR_VAL; }

  const char* bEventType = "bEventType";
  PyObject* pDictbEventType = NULL;
  pDictbEventType = PyDict_New();
  if (!pDictbEventType) { return MOD_ERROR_VAL; }
  EXPORT_ENUM_VALUE(pDictbEventType, bEventJobStart);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventJobEnd);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventStartBackupJob);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventEndBackupJob);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventStartRestoreJob);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventEndRestoreJob);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventStartVerifyJob);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventEndVerifyJob);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventBackupCommand);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventRestoreCommand);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventEstimateCommand);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventLevel);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventSince);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventCancelCommand);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventRestoreObject);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventEndFileSet);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventPluginCommand);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventOptionPlugin);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventHandleBackupFile);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventNewPluginOptions);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssInitializeForBackup);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssInitializeForRestore);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssSetBackupState);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssPrepareForBackup);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssBackupAddComponents);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssPrepareSnapshot);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssCreateSnapshots);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssRestoreLoadComponentMetadata);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssRestoreSetComponentsSelected);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssCloseRestore);
  EXPORT_ENUM_VALUE(pDictbEventType, bEventVssBackupComplete);
  if (PyModule_AddObject(m, bEventType, pDictbEventType)) {
    return MOD_ERROR_VAL;
  }


  const char* bIOPS = "bIOPS";
  PyObject* pDictbIOPS = NULL;
  pDictbIOPS = PyDict_New();
  if (!pDictbIOPS) { return MOD_ERROR_VAL; }
  EXPORT_ENUM_VALUE(pDictbIOPS, IO_OPEN);
  EXPORT_ENUM_VALUE(pDictbIOPS, IO_READ);
  EXPORT_ENUM_VALUE(pDictbIOPS, IO_WRITE);
  EXPORT_ENUM_VALUE(pDictbIOPS, IO_CLOSE);
  EXPORT_ENUM_VALUE(pDictbIOPS, IO_SEEK);
  if (PyModule_AddObject(m, bIOPS, pDictbIOPS)) { return MOD_ERROR_VAL; }

  const char* bIOPstatus = "bIOPstatus";
  PyObject* pDictbIOPstatus = NULL;
  pDictbIOPstatus = PyDict_New();
  if (!pDictbIOPstatus) { return MOD_ERROR_VAL; }
  ConstSet_StrLong(pDictbIOPstatus, iostat_error, IoStatus::error);
  ConstSet_StrLong(pDictbIOPstatus, iostat_do_in_plugin, IoStatus::success);
  ConstSet_StrLong(pDictbIOPstatus, iostat_do_in_core, IoStatus::do_io_in_core);
  if (PyModule_AddObject(m, bIOPstatus, pDictbIOPstatus)) {
    return MOD_ERROR_VAL;
  }


  const char* bLevels = "bLevels";
  PyObject* pDictbLevels = NULL;
  pDictbLevels = PyDict_New();
  if (!pDictbLevels) { return MOD_ERROR_VAL; }
  ConstSet_StrStr(pDictbLevels, L_FULL, "F");
  ConstSet_StrStr(pDictbLevels, L_INCREMENTAL, "I");
  ConstSet_StrStr(pDictbLevels, L_DIFFERENTIAL, "D");
  ConstSet_StrStr(pDictbLevels, L_SINCE, "S");
  ConstSet_StrStr(pDictbLevels, L_VERIFY_CATALOG, "C");
  ConstSet_StrStr(pDictbLevels, L_VERIFY_INIT, "V");
  ConstSet_StrStr(pDictbLevels, L_VERIFY_VOLUME_TO_CATALOG, "O");
  ConstSet_StrStr(pDictbLevels, L_VERIFY_DISK_TO_CATALOG, "d");
  ConstSet_StrStr(pDictbLevels, L_VERIFY_DATA, "A");
  ConstSet_StrStr(pDictbLevels, L_BASE, "B");
  ConstSet_StrStr(pDictbLevels, L_NONE, " ");
  ConstSet_StrStr(pDictbLevels, L_VIRTUAL_FULL, "f");
  if (PyModule_AddObject(m, bLevels, pDictbLevels)) { return MOD_ERROR_VAL; }

  return m;
}

static int load_module(PyObject* module)
{
  return load_module_impl(
             module, static_cast<fd_module_state*>(PyModule_GetState(module)))
             ? 0
             : -1;
}

static int bareosfd_traverse(PyObject* module, visitproc visit, void* arg)
{
  auto* state = fd_module_state::get(module);
  Py_VISIT(state->stat_pkt);
  Py_VISIT(state->stat_pkt);
  Py_VISIT(state->io_pkt);
  Py_VISIT(state->save_pkt);
  Py_VISIT(state->restore_pkt);
  Py_VISIT(state->acl_pkt);
  Py_VISIT(state->xattr_pkt);
  Py_VISIT(state->restore_obj);
  return 0;
}

static int bareosfd_clear(PyObject* module)
{
  auto* state = fd_module_state::get(module);
  Py_CLEAR(state->stat_pkt);
  Py_CLEAR(state->io_pkt);
  Py_CLEAR(state->save_pkt);
  Py_CLEAR(state->restore_pkt);
  Py_CLEAR(state->acl_pkt);
  Py_CLEAR(state->xattr_pkt);
  Py_CLEAR(state->restore_obj);
  return 0;
}

static void bareosfd_free(void* module) { bareosfd_clear((PyObject*)module); }

MOD_INIT(bareosfd)
{
  static PyModuleDef_Slot slots[]
      = { {Py_mod_exec, (void*)&load_module},
          {},  // null terminator
        };

  static PyModuleDef moduledef
      = {PyModuleDef_HEAD_INIT,
         PYTHON_MODULE_NAME_QUOTED,
         "python plugin api of the bareos file daemon."
         " See https://docs.bareos.org/DeveloperGuide/PythonPluginAPI.html",
         sizeof(fd_module_state),
         Methods,
         slots,
         bareosfd_traverse,
         bareosfd_clear,
         bareosfd_free};

  return PyModuleDef_Init(&moduledef);
}


#else  // NOT BAREOSFD_MODULE


/* This section is used in modules that use bareosfd's API */

static void** Bareosfd_API;

/* include automatically generated C API */
#  include "c_api/capi_2.inc"

static int import_bareosfd()
{
  Bareosfd_API = (void**)PyCapsule_Import("bareosfd._C_API", 0);
  return (Bareosfd_API != NULL) ? 0 : -1;
}
#endif  // BAREOSFD_MODULE

#endif  // BAREOS_PLUGINS_FILED_PYTHON_MODULE_BAREOSFD_H_
