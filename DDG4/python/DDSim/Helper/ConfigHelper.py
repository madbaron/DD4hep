"""Helper object to identify configuration parameters so we can easily overwrite
them via command line magic or via the steering file

To add additional arguments create either a member variable or a property to a
subclass of the ConfigHelper. To add additional arguments to the add_argument
call for the parser object create an additional member::

  self.member = [1,2]
  self._member_EXTRA = {'help': 'description for parameter',
                        'nargs': '+',
                       }

"""

from __future__ import absolute_import, unicode_literals

import ddsix as six


class ConfigHelper(object):
  """Base class for configuration helper"""

  def __init__(self):
    pass

  def getOptions(self):
    finalVars = {}

    # get all direct members not starting with underscore
    allVars = vars(self)
    for var, val in six.iteritems(allVars):
      if not var.startswith('_'):
        extraArgumentsName = "_%s_EXTRA" % var
        options = getattr(self, extraArgumentsName) if hasattr(self, extraArgumentsName) else None
        finalVars[var] = {'default': val}
        if options:
          finalVars[var].update(options)

    # now get things defined with @property
    props = [(p, getattr(type(self), p)) for p in dir(type(self)) if isinstance(getattr(type(self), p), property)]
    for propName, prop in props:
      optName = "_%s_EXTRA" % propName
      doc = prop.__doc__
      options = getattr(self, optName) if hasattr(self, optName) else None
      finalVars[propName] = {'default': getattr(self, propName)}
      if doc:
        finalVars[propName]['help'] = doc
      if options:
        finalVars[propName].update(options)

    return finalVars

  def __repr__(self):
    return self.printOptions()

  def printOptions(self):
    """print all parameters"""
    options = []
    for opt, val in six.iteritems(self.getOptions()):
      options.append("\n\t'%s': '%s'" % (opt, val['default']))
    return "".join(options)

  def setOption(self, name, val):
    """ set the attribute name to val """
    setattr(self, name, val)

  @staticmethod
  def makeList(stringVal, sep=" "):
    """returns a list from a string separated by sep"""
    if not stringVal:
      return []
    if isinstance(stringVal, list):
      return stringVal
    else:
      return stringVal.split(sep)

  @staticmethod
  def makeSet(stringVal, sep=" "):
    """returns a set from a string separated by sep"""
    if not stringVal:
      return set()
    if isinstance(stringVal, (list, set, tuple)):
      return set(stringVal)
    else:
      return set(stringVal.split(sep))

  @staticmethod
  def makeString(container):
    """Return a string that can be parsed by dd4hep into a vector."""
    if not container:
      return ""
    if isinstance(container, set):
      return '{%s}' % ','.join([str(s) for s in container])

  @staticmethod
  def makeTuple(val):
    """ returns a tuple of the string, separators are space or comma """
    myTuple = None
    if isinstance(val, tuple):
      myTuple = val
    if isinstance(val, list):
      myTuple = tuple(val)
    if isinstance(val, six.string_types):
      sep = ',' if ',' in val else ' '
      myTuple = tuple([_.strip("(), ") for _ in val.split(sep)])
    if myTuple is None:
      raise RuntimeError("Cannot parse input value %s" % val)
    return myTuple

  @staticmethod
  def makeBool(val):
    """check if val is a bool or a string of true/false, otherwise raise exception"""
    if isinstance(val, bool):
      return val
    elif isinstance(val, six.string_types):
      if val.lower() == 'true':
        return True
      elif val.lower() == 'false':
        return False
    raise RuntimeError(val)

  @staticmethod
  def addAllHelper(ddsim, parser):
    """all configHelper objects to commandline args"""
    for name, obj in six.iteritems(vars(ddsim)):
      if isinstance(obj, ConfigHelper):
        for var, optionsDict in six.iteritems(obj.getOptions()):
          optionsDict['action'] = 'store_true' if var.startswith("enable") else 'store'
          parser.add_argument("--%s.%s" % (name, var),
                              dest="%s.%s" % (name, var),
                              **optionsDict
                              )
