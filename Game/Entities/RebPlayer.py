import Reb3D
import RebGL
import RebWAEM


class RebPlayer:
    def __init__(self, initd):
        self.params = initd
        self.akd = dict()
        RebWAEM.rwaem.AddMouseEventListener(self)
        RebWAEM.rwaem.AddKeyEventListener(self)


    def Mot(self):
        if "W" in self.akd:
            if self.akd["W"]:
                return Reb3D.RebVector(0.0, 0.0, -1.0)
        if "S" in self.akd:
            if self.akd["S"]:
                return Reb3D.RebVector(0.0, 0.0, 1.0)
        if "A" in self.akd:
            if self.akd["A"]:
                return Reb3D.RebVector(-1.0, 0.0, 0.0)
        if "D" in self.akd:
            if self.akd["D"]:
                return Reb3D.RebVector(1.0, 0.0, 0.0)
        return Reb3D.RebVector(0.0, 0.0, 0.0)

    def Update(self):
        vrm = Reb3D.RebMatrix()
        vrm.RotOri(self.params["ori"])
        vtm = Reb3D.RebMatrix()
        mv = self.params["pos"] + (vrm * self.Mot())
        self.params["pos"] = mv
        vtm.Translate(mv)
        V = Reb3D.RebMatrix()
        V.InverseOf(vtm * vrm)
        RebGL.rrd.SetViewportMat(V)
		

    def onMouseEvent(self, me):
        v = me.GetRel()
        mv = self.params["ori"] + Reb3D.RebVector(-v.GetY(), -v.GetX(), 0.0)
        self.params["ori"] = mv

    def onKeyEvent(self, ke):
        self.akd[ke.GetChar()] = ke.GetPOR()
