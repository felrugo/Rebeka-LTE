#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>



extern "C"
{
	int __declspec(dllexport) CreateContext(HWND hWnd)
	{
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
			32,                        //Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                        //Number of bits for the depthbuffer
			8,                        //Number of bits for the stencilbuffer
			0,                        //Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};


		HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

		int  letWindowsChooseThisPixelFormat;
		letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
		SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

		HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
		wglMakeCurrent(ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

		


		
		//wglDeleteContext(ourOpenGLRenderingContext);

		return 0;
	}



	HDC __declspec(dllexport) GetHDC(HWND hwnd)
	{
		return GetDC(hwnd);
	}


	void __declspec(dllexport) TRender(HDC hdc)
	{
		

		glClearColor(1, 0, 0, 1);

		glClear(GL_COLOR_BUFFER_BIT);

		SwapBuffers(hdc);
	}

}


