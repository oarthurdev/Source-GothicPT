





#pragma once








template <class T, int MAX > class CRingBuff
{
protected:
	int						m_Head;
	int						m_Tail;
	int						m_Count;
	T					    m_Buff[MAX];

public:
	CRingBuff(void)
	{
		m_Head = 0;
		m_Tail = 0;
		m_Count = 0;
		::ZeroMemory(m_Buff, sizeof(m_Buff));
	}

	inline BOOL IsFull(void)
	{
		return (m_Count >= MAX) ? TRUE : FALSE;
	}
	inline BOOL IsEmpty(void)
	{
		return (m_Count <= 0) ? TRUE : FALSE;
	}
	inline int  GetCount(void)
	{
		return m_Count;
	}

	BOOL Push(T &Data)
	{
		if(m_Count >= MAX)
			return FALSE;
		m_Buff[m_Tail] = Data;
		if(m_Tail + 1 >= MAX)		m_Tail = 0;
		else							m_Tail++;
		m_Count++;
		return TRUE;
	}


	BOOL Pop(T &Data)
	{
		if(m_Count <= 0)
			return FALSE;
		Data = m_Buff[m_Head];
		if(m_Head + 1 >= MAX)		m_Head = 0;
		else							m_Head++;
		m_Count--;
		return TRUE;
	}

	BOOL TotalPop(T *lpData, DWORD &Count)
	{
		if(m_Count <= 0)
			return FALSE;

		if(m_Head < m_Tail)
		{
			Count = m_Tail - m_Head;
			::CopyMemory(lpData, &m_Buff[m_Head], sizeof(T) * Count);
		}
		else
		{
			Count = MAX - m_Head;
			::CopyMemory(lpData, &m_Buff[m_Head], sizeof(T) * Count);
			::CopyMemory(&lpData[Count], m_Buff, sizeof(T) * m_Tail);
			Count += m_Tail;
		}

		m_Head = m_Tail;
		m_Count = 0;
		return TRUE;
	}

	BOOL Peek(T &Data)
	{
		if(m_Count <= 0)
			return FALSE;
		Data = m_Buff[m_Head];
		return TRUE;
	}
};
