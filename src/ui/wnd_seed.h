#ifndef __UI_WND_SEED_H__
#define __UI_WND_SEED_H__

namespace ino {

	struct wnd_seed
	{
		DWORD style_ex;
		std::wstring class_name;
		std::wstring title;
		DWORD style;
		Rect rect;
		HWND parent;
	}

}

#endif // __UI_WND_SEED_H__