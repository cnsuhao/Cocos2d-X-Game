#include "ExaminationPaper.h"
#include <algorithm>
#include <fstream>


ExaminationPaper::ExaminationPaper()
{
}

ExaminationPaper::~ExaminationPaper()
{
}

bool ExaminationPaper::loadQuestionBank()
{
	englishQuestionBank.clear();
	englishQuestionBank["dog"] = "狗儿";
	englishQuestionBank["apples"] = "苹果";
	englishQuestionBank["pear"] = "梨子";
	englishQuestionBank["egg"] = "鸡蛋";
	englishQuestionBank["fruit"] = "水果";
	englishQuestionBank["study"] = "学习";
	englishQuestionBank["bird"] = "鸟儿";
	englishQuestionBank["plane"] = "飞机";
	englishQuestionBank["war"] = "战争";
	englishQuestionBank["two"] = "中文2";
	readDB();

	return true;
}

bool ExaminationPaper::readDB()
{
	char buffer[256];

	std::ifstream readExamInfo("C:\\ProgramData\\EnglishStudy\\ExamBank.db");

	if (readExamInfo.is_open())
	{
		while (!readExamInfo.eof())
		{
			readExamInfo.getline(buffer, 100);
			std::string strInfo = buffer;
			int pos = strInfo.find(":");
			if (pos < 0) continue;
			std::string key = strInfo.substr(0, pos);
			std::string value = strInfo.substr(pos+1, strInfo.length() - pos);
			englishQuestionBank.insert(std::make_pair(key, value));
		}
	}

	return true;
}

bool ExaminationPaper::getQuestion(Questoins &questoins, const uint32_t count)
{
	if (englishQuestionBank.size() == 0)
	{
		return false;
	}

	std::vector<std::string> EnQuestionVec;
	QuestionBankInfo::iterator it = englishQuestionBank.begin();

	uint32_t number = 0;
	for (; it != englishQuestionBank.end();it++)
	{
		EnQuestionVec.push_back(it->first);
		++number;
	}
	
	std::random_shuffle(EnQuestionVec.begin(), EnQuestionVec.end());

	std::vector<std::string> ZhQuestionVec;
	uint32_t icount = count;
	for (uint32_t i = 0; i < number; ++i)
	{
		--icount;
		QuestoinInfo info = { EnQuestionVec[i], ""};
		ZhQuestionVec.push_back(englishQuestionBank[EnQuestionVec[i]]);
		questoins.push_back(info);
		if (icount <= 0) break;
	}

	std::random_shuffle(ZhQuestionVec.begin(), ZhQuestionVec.end());
	for (uint32_t i = 0; i < count - icount;++i)
	{
		questoins[i].ZhQuestion = ZhQuestionVec[i];
	}

	return true;
}

uint32_t ExaminationPaper::grade(const AnswerInfoMap& ansewerInfo)
{
	return 0;
}
