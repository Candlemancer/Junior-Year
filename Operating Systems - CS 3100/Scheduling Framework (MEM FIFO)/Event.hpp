// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Event Class Header

#ifndef EVENT_HPP
#define EVENT_HPP

class Event {
public:

	Event(
		int taskType = NO_OP,
		double startTime = 0.0,
		double duration = 0.0,
		int taskNumber = -1,
		int idRequested = -1
	) :
	m_taskType(taskType),
	m_startTime(startTime),
	m_duration(duration),
	m_taskNumber(taskNumber),
	m_idRequested(idRequested) {}

	enum TaskTypes
	{
		NO_OP,
		TASK_START,
		TASK_STOP,
		CPU_START,
		CPU_STOP,
		IO_START,
		IO_STOP,
		MEM_FETCH,
		END_PROCESS
	};

	int m_taskType;
	double m_startTime;
	double m_duration;
	int m_taskNumber;
	int m_idRequested;

};

inline bool operator< (const Event& lhs, const Event& rhs){ 
	if (lhs.m_startTime < rhs.m_startTime) { return true; } 
	return false; 
}
inline bool operator> (const Event& lhs, const Event& rhs){return rhs < lhs;}
inline bool operator<=(const Event& lhs, const Event& rhs){return !(lhs > rhs);}
inline bool operator>=(const Event& lhs, const Event& rhs){return !(lhs < rhs);}


#endif
