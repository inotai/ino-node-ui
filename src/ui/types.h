#ifndef __UI_TYPES_H__
#define __UI_TYPES_H__

namespace ui {

	typedef float CoordF;
	typedef int CoordI;

	namespace traits {
		typedef TByVal<ui::CoordF> CoordF;
		typedef TByVal<ui::CoordI> CoordI;
	}

}


#include "ui/Constructor.h"
#include "ui/Rect.h"

#endif // __UI_TYPES_H__