using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor
{






    public partial class Form1 : Form
    {
        


        public Form1()
        {
            InitializeComponent();

            

        }

        

        private void glControl1_Paint_1(object sender, PaintEventArgs e)
        {
            glControl1.Draw();
        }
    }
}
