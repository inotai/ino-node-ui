#ifndef __UI_MSG_H__
#define __UI_MSG_H__

namespace ui {

	//------------------------------------------------------------------------
	class Msg
	//------------------------------------------------------------------------
	{
	public:
		Msg(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
		{
			m_msg.hwnd = hwnd;
			m_msg.message = msg;
			m_msg.wParam = w_param;
			m_msg.lParam = l_param;
			m_l_result = 0;
		}

		HWND getHWND() const
		{ return m_msg.hwnd; }
		void setHWND(HWND hwnd)
		{ m_msg.hwnd = hwnd; }

		UINT getMessage() const
		{ return m_msg.message; }
		void setMessage(UINT message)
		{ m_msg.message = message; }

		WPARAM getWPARAM() const
		{ return m_msg.wParam; }
		void setWPARAM(WPARAM w_param)
		{ m_msg.wParam = w_param; }

		WPARAM getLPARAM() const
		{ return m_msg.lParam; }
		void setLPARAM(LPARAM l_param)
		{ m_msg.lParam = l_param; }

		LRESULT getLRESULT() const
		{ return m_l_result; }
		void setLRESULT(LRESULT l_result)
		{ m_l_result = l_result; }

		const MSG & getMSG() const
		{ return m_msg; }
		void setMSG(const MSG & msg)
		{ m_msg = msg; }

	private:
		MSG m_msg;
		LRESULT	m_l_result;
	};


}

#endif // __UI_MSG_H__