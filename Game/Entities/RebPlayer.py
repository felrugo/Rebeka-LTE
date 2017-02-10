import Reb3D
import RebGL
import RebWAEM


class RebPlayer:
    def __init__(self, initd):
        self.params = dict(initd)
        RebWAEM.rwaem.AddMouseEventListener(self)
        

    def Update(self):
        vrm = Reb3D.RebMatrix()
        vrm.RotOri(self.params["ori"])
        vtm = Reb3D.RebMatrix()
        vtm.Translate(self.params["pos"])
        RebGL.rrd.SetViewportMat(vrm * vtm)
		

    def onMouseEvent(self, me):
        mmv = me.GetRel()
        ve = Reb3D.RebVector(mmv.GetY(), mmv.GetX(), 0.0)
        self.params["ori"] = self.params["ori"] + ve


