using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class OpenGL
    {

        IntPtr hdc;


        [DllImport("kernel32.dll", EntryPoint = "LoadLibrary")]
        static extern int LoadLibrary(
            [MarshalAs(UnmanagedType.LPStr)] string lpLibFileName);

        [DllImport("kernel32.dll", EntryPoint = "GetProcAddress")]
        static extern IntPtr GetProcAddress(int hModule,
            [MarshalAs(UnmanagedType.LPStr)] string lpProcName);

        [DllImport("kernel32.dll", EntryPoint = "FreeLibrary")]
        static extern bool FreeLibrary(int hModule);

        //[DllImport("EditorDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        //static extern int CreateContext(IntPtr hwnd);


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate int CreateContext_Del(IntPtr hwnd);

        CreateContext_Del CreateContext;

        //[DllImport("EditorDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        //static extern IntPtr GetHDC(IntPtr hwnd);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate IntPtr GetHDC_Del(IntPtr hwnd);

        GetHDC_Del GetHDC;


        //[DllImport("EditorDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        //static extern void TRender(IntPtr hdc);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void TRender_Del(IntPtr hdc);

        TRender_Del TRender;

        public OpenGL()
        {

            int module;

            module = LoadLibrary("EditorDLL.dll");

            if (module != 0)
            {

                IntPtr fp = GetProcAddress(module, "CreateContext");
                if (fp != IntPtr.Zero)
                    CreateContext = (CreateContext_Del)Marshal.GetDelegateForFunctionPointer(fp, typeof(CreateContext_Del));

                fp = GetProcAddress(module, "GetHDC");
                if (fp != IntPtr.Zero)
                    GetHDC = (GetHDC_Del)Marshal.GetDelegateForFunctionPointer(fp, typeof(GetHDC_Del));


                fp = GetProcAddress(module, "TRender");
                if (fp != IntPtr.Zero)
                    TRender = (TRender_Del)Marshal.GetDelegateForFunctionPointer(fp, typeof(TRender_Del));

            }

        }

        public void CC(IntPtr hwnd)
        {
            if(CreateContext != null)
            CreateContext(hwnd);
            if(GetHDC != null)
            hdc = GetHDC(hwnd);
        }


        public void Render()
        {
            if(TRender != null)
            TRender(hdc);
        }

    }
}
