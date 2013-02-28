#ifndef __UI_RECT_H__
#define __UI_RECT_H__

namespace ui {

	//------------------------------------------------------------------------
	template<class F>
	class TRect
	//------------------------------------------------------------------------
	{
	public:
		F left;
		F top;
		F right;
		F bottom;

		TRect()
		:	left((F)0.0f), 
			top((F)0.0f),
			right((F)0.0f),
			bottom((F)0.0f)
		{}

		TRect(F left, F top, F right, F bottom)
		:	left(left),
			top(top),
			right(right),
			bottom(bottom)
		{}

		TRect(const TRect & rect)
		:	left(rect.left),
			top(rect.top),
			right(rect.right),
			bottom(rect.bottom)
		{}

		void set(F l, F t, F r, F b)
		{
			left = l;
			top = t;
			right = r;
			bottom = b;
		}

		void set(const TRect<F> & other)
		{
			set(other.left, other.top, other.right, other.bottom);
		}

		TRect<F> & operator=(const TRect<F> & other)
		{
			set(other);
			return *this;
		}

		bool operator==(const TRect<F> & other) const
		{
			return memcmp(&other, this, sizeof(TRect<F>)) == 0;
		}

		bool operator!=(const TRect<F> & other) const
		{
			return memcmp(&other, this, sizeof(TRect<F>)) != 0;
		}

		F getWidth() const
		{ return right - left; }
		void setWidth(F w)
		{ right = left + w; }
		F getHeight() const
		{ return bottom - top; }
		void setHeight(F w)
		{ bottom = top + w; }

		F getHorizontalSum() const
		{ return right + left; }
		F getVerticalSum() const
		{ return bottom + top; }

		bool empty() const
		{
			return left >= right || top >= bottom;
		}

		bool equalSize(const TRect<F> & other) const
		{
			return (other.getWidth() == getWidth()) && (other.getHeight() == getHeight());
		}

		bool equalPosition( const TRect<F> & other ) const
		{
			return (other.left == left) && (other.top == top);
		}

		void offset(F offset_l, F offset_t)
		{
			left += offset_l;
			top += offset_t;
			right += offset_l;
			bottom += offset_t;
		}

		void inflate(F l, F t, F r, F b)
		{
			left += l;
			top += t;
			right -= r;
			bottom -= b;
		}
		
		void inflate(F h, F v)
		{
			inflate(h, v, h, v);
		}

		void inflate(const TRect<F> & r)
		{
			inflate(r.left, r.top, r.right, r.bottom);
		}

		bool intersect(F l, F t, F r, F b)
		{
			if (l < r && t < b && !empty() && // check for empties
				left < r && l < right && top < b && t < bottom)
			{
				if (left < l) left = l;
				if (top < t) top = t;
				if (right > r) right = r;
				if (bottom > b) bottom = b;
				return true;
			}
			return false;
		}

		bool intersect(const TRect<F> & r)
		{
			return intersect(r.left, r.top, r.right, r.bottom);
		}

		bool intersects(F l, F t, F r, F b) const
		{
			return  !empty() && (l>=r && t>=b) &&
				left < r && l < right &&
				top < b && t < bottom;
		}

		bool intersects(const TRect<F> & r) const
		{
			return intersects(r.left, r.top, r.right, r.bottom);
		}

		bool contains( F x, F y ) const
		{
			return ( ( x >= left ) && ( x <= right ) &&
				( y >= top )  && ( y <= bottom ) );
		}
		
		void alignTo(const TRect<F> & other, int gravity /* = Gravity::G_CenterVertical | Gravity::G_CenterHorizontal */)
		{
			TRect<F> r( *this );
			switch( gravity & Gravity::GM_VerticalGravityMask )
			{
			case Gravity::G_CenterVertical:
				r.top = other.top + ( ( other.getHeight() - r.getHeight() ) / ((F)2.0f) );
				r.bottom = r.top + getHeight(); // Use original height
				break;
			case Gravity::G_Top:
				r.top = other.top;
				r.bottom = r.top + getHeight(); // Use original height
				break;
			case Gravity::G_Bottom:
				r.bottom = other.bottom;
				r.top = r.bottom - getHeight(); // Use original height
				break;
			}

			switch( gravity & Gravity::GM_HorizontalGravityMask )
			{
			case Gravity::G_CenterHorizontal:
				r.left = other.left + (( other.getWidth() - r.getWidth() ) / ((F)2.0f) );
				r.right = r.left + getWidth();
				break;
			case Gravity::G_Left:
				r.left = other.left;
				r.right = r.left + getWidth();
				break;
			case Gravity::G_Right:
				r.right = other.right;
				r.left = r.left - getWidth();
				break;
			}

			set(r);
		}

// #if	INO_OS == INO_OS_WINDOWS_NT
		void setRECT(const RECT & rc)
		{
			set((F)rc.left, (F)rc.top, (F)rc.right, (F)rc.bottom);
		}

		RECT getRECT() const
		{
			RECT rc = { (LONG)rf.left, (LONG)rf.top, (LONG)rf.right, (LONG)rf.bottom };
			return rc;
		}

		void getRECT(RECT * o_rc) const
		{
			INO_CHECK_PTR(o_rc);
			o_rc->left = (LONG)left;
			o_rc->top = (LONG)top;
			o_rc->right = (LONG)right;
			o_rc->bottom = (LONG)bottom;
		}
// #endif

	};

	typedef TRect<CoordF> RectF;
	typedef TRect<CoordI> RectI;

	namespace traits {
		typedef TByRef<ui::RectF> RectF;
		typedef TByRef<ui::RectI> RectI;
	}
}

#endif // __UI_RECT_H__