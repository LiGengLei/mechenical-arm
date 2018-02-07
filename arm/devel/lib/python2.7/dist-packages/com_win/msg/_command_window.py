# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from com_win/command_window.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class command_window(genpy.Message):
  _md5sum = "080fa35438d753e3eb4d759df3a9e3e2"
  _type = "com_win/command_window"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string     CommandMode
string     Coordinator
string     ZeroAxis
string     Aux_swing
string     Aux_Home
float64[]  CtrlValues
int8 CommandEmit
int8 ManualSwitch
"""
  __slots__ = ['CommandMode','Coordinator','ZeroAxis','Aux_swing','Aux_Home','CtrlValues','CommandEmit','ManualSwitch']
  _slot_types = ['string','string','string','string','string','float64[]','int8','int8']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       CommandMode,Coordinator,ZeroAxis,Aux_swing,Aux_Home,CtrlValues,CommandEmit,ManualSwitch

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(command_window, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.CommandMode is None:
        self.CommandMode = ''
      if self.Coordinator is None:
        self.Coordinator = ''
      if self.ZeroAxis is None:
        self.ZeroAxis = ''
      if self.Aux_swing is None:
        self.Aux_swing = ''
      if self.Aux_Home is None:
        self.Aux_Home = ''
      if self.CtrlValues is None:
        self.CtrlValues = []
      if self.CommandEmit is None:
        self.CommandEmit = 0
      if self.ManualSwitch is None:
        self.ManualSwitch = 0
    else:
      self.CommandMode = ''
      self.Coordinator = ''
      self.ZeroAxis = ''
      self.Aux_swing = ''
      self.Aux_Home = ''
      self.CtrlValues = []
      self.CommandEmit = 0
      self.ManualSwitch = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self.CommandMode
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.Coordinator
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.ZeroAxis
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.Aux_swing
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.Aux_Home
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      length = len(self.CtrlValues)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.CtrlValues))
      _x = self
      buff.write(_struct_2b.pack(_x.CommandEmit, _x.ManualSwitch))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.CommandMode = str[start:end].decode('utf-8')
      else:
        self.CommandMode = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Coordinator = str[start:end].decode('utf-8')
      else:
        self.Coordinator = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.ZeroAxis = str[start:end].decode('utf-8')
      else:
        self.ZeroAxis = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Aux_swing = str[start:end].decode('utf-8')
      else:
        self.Aux_swing = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Aux_Home = str[start:end].decode('utf-8')
      else:
        self.Aux_Home = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.CtrlValues = struct.unpack(pattern, str[start:end])
      _x = self
      start = end
      end += 2
      (_x.CommandEmit, _x.ManualSwitch,) = _struct_2b.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self.CommandMode
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.Coordinator
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.ZeroAxis
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.Aux_swing
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.Aux_Home
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      length = len(self.CtrlValues)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.CtrlValues.tostring())
      _x = self
      buff.write(_struct_2b.pack(_x.CommandEmit, _x.ManualSwitch))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.CommandMode = str[start:end].decode('utf-8')
      else:
        self.CommandMode = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Coordinator = str[start:end].decode('utf-8')
      else:
        self.Coordinator = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.ZeroAxis = str[start:end].decode('utf-8')
      else:
        self.ZeroAxis = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Aux_swing = str[start:end].decode('utf-8')
      else:
        self.Aux_swing = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Aux_Home = str[start:end].decode('utf-8')
      else:
        self.Aux_Home = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.CtrlValues = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      _x = self
      start = end
      end += 2
      (_x.CommandEmit, _x.ManualSwitch,) = _struct_2b.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2b = struct.Struct("<2b")
