#ifndef _EXAMINATIONANSWER_H_
#define _EXAMINATIONANSWER_H_

#include <map>
#include <vector>
#include <string>
#include <stdint.h>
#include "ExamInfoDef.h"

/**
 * @class	ExaminationAnswer
 *
 * @brief	An examination answer.
 *
 * @author	Azraelly
 * @date	2015/6/10
 */

class ExaminationAnswer
{
	struct AnswerInfo
	{
		std::string EnAnser;
		std::string ZhAnser;
	};

	typedef std::vector<AnswerInfo> RecordAnswerInfo;

public:
	ExaminationAnswer();
	~ExaminationAnswer();

	static ExaminationAnswer* defaultInstance()
	{
		static ExaminationAnswer inst;
		return &inst;
	}

	/**
	 * @fn	bool ExaminationAnswer::recordAnswer(RecordAnswerInfo info);
	 *
	 * @brief	Record answer.
	 *
	 * @author	Azraelly
	 * @date	2015/6/10
	 *
	 * @param	info	The information.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	bool recordAnswer(RecordAnswerInfo info);

	/**
	 * @fn	void ExaminationAnswer::reset();
	 *
	 * @brief	重新考试.
	 *
	 * @author	Azraelly
	 * @date	2015/6/10
	 */

	void reset();

	/**
	 * @fn	uint32_t ExaminationAnswer::submit();
	 *
	 * @brief	提交试卷 返回分数.
	 *
	 * @author	Azraelly
	 * @date	2015/6/10
	 *
	 * @return	An uint32_t.
	 */
	uint32_t submit();

private:
	AnswerInfoMap answerInfo;
};

#endif

