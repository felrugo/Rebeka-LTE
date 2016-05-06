

class Geom:
	def __init__(self, il):
		self.pl = il
		self.cad = il["cad"]
		obj = self.pl.get("obj")
		if obj != None:
                       self.vc = RebGL_LoadVC(obj)
                else:
                        self.vc = None
		
	def update(self):
                pass
        
		
	
