class RebPlayer:
    def __init__(self, initd):
        self.params = dict(initd)
        

    def Update(self):
        pass

    def GetParam(self, key):
        if key in self.params:
            return self.params[key]
        return "__Wrong Key__"


