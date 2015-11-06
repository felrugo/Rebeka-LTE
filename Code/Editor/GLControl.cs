using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class GLControl : System.Windows.Forms.Control
    {
        OpenGL gl;

        public GLControl()
        {
            gl = new OpenGL();
            gl.CC(Handle);
        }

        public void Draw()
        {
            gl.Render();
        }

    

       
    }
}
