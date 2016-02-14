#python class wrapper for embedded code

class RebFile:
	def __init__(self, swp):
		self.wp = swp
	def GetName(self):
		return RF_GetName(self.wp)
	def GetAPath(self):
		return RF_GetAPath(self.wp)
	def GetExtension(self):
		return RF_GetExtension(self.wp)


class RebDir:

