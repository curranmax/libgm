from ctypes import cdll
gm_lib = cdll.LoadLibrary('/usr/local/lib/libgm.so')

class GM:
	def __init__(self,ch = 0,lib = gm_lib):
		self.lib = lib
		self.gm_obj = self.lib.GM_new(ch)

	def connectDevice(self):
		self.lib.GM_connectDevice(self.gm_obj)

	def disconnectDevice(self):
		self.lib.GM_disconnectDevice(self.gm_obj)

	def setValue(self,v):
		return self.lib.GM_setValue(self.gm_obj,v)

	def getValue(self):
		return self.lib.GM_getValue(self.gm_obj)
