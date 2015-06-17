#ifndef _EXAMINATIONPAPER_H_
#define _EXAMINATIONPAPER_H_

#include <map>
#include <vector>
#include <stdint.h>
#include "ExamInfoDef.h"

class ExaminationPaper
{
	typedef std::map<std::string, std::string> QuestionBankInfo;

	struct QuestoinInfo
	{
		std::string EnQuestion;
		std::string ZhQuestion;
	};

public:
	typedef std::vector <QuestoinInfo> Questoins;
	
public:
	ExaminationPaper();
	~ExaminationPaper();

	static ExaminationPaper* defaultInstance()
	{
		static ExaminationPaper inst;
		return &inst;
	}

	/// 加载题库
	bool loadQuestionBank();

	/// 获取试题
	bool getQuestion(Questoins &questoins, const uint32_t count = 7);

	/// 评分
	uint32_t grade(const AnswerInfoMap& ansewerInfo);

private:
	bool readDB();

private:
	QuestionBankInfo englishQuestionBank;

};



#endif //_EXAMINATIONPAPER_H_