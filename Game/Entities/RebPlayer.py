import Reb3D
import RebWAEM


class RebPlayer:
    def __init__(self, initd):
        self.params = dict(initd)
        RebWAEM.rwaem.AddMouseEventListener(self)
        

    def Update(self):
        pass

    def onEvent(self, me):
        relm = me.GetRel()
        self.params["ori"] = self.params["ori"] + relm

    def GetParam(self, key):
        if key in self.params:
            return self.params[key]
        return "__Wrong_Key__"


