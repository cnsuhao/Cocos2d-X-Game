#include "WordCard.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

char* WordCard::cardStyle[] = {
	"EnglishExam/CardRed.png",
	"EnglishExam/CardBlue.png",
	"EnglishExam/CardDarkBlue.png",
	"EnglishExam/CardYellow.png",
	"EnglishExam/CardPurple.png",
	"EnglishExam/CardGreen.png"
};

WordCard::WordCard(const std::string& name, const CardType& type)
	:cardType(type)
	, cardName(name)
	, potDrawNode(nullptr)
{

}

WordCard::~WordCard()
{
}

bool WordCard::init()
{
	if (!Sprite::initWithFile(cardStyle[random<int>(0, 5)]))
	{
		return false;
	}

	auto cardLabel = Label::createWithTTF(getTTFConfig(cardType), cardName, TextHAlignment::CENTER, 0);
	cardLabel->setPosition(Vec2(getContentSize() / 2));
	addChild(cardLabel);

	cardLayout = Layout::create();

	cardLayout->setTouchEnabled(true);
	cardLayout->setContentSize(getContentSize());
	setPosition(Vec2(cardLayout->getContentSize().width / 2.0f,
	cardLayout->getContentSize().height / 2.0f));
	cardLayout->addChild(this);
	cardLayout->setAnchorPoint(Vec2::ZERO);

	auto lp1 = LinearLayoutParameter::create();
	cardLayout->setLayoutParameter(lp1);
	lp1->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
	lp1->setMargin(Margin(4.0f, 0.0f, 4.0f, 0.0f));

	return true;
}

void WordCard::setPotDrawNode(Vec2 drawPoint)
{
	potDrawNode = cocos2d::DrawNode::create();
	log("****************ref:%d", potDrawNode->getReferenceCount());
	// Draw 4 circles
	for (int i = 0; i < 4; i++)
	{
		potDrawNode->drawDot(drawPoint, 4 * (4 - i), cocos2d::Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
		log("****************ref:%d", potDrawNode->getReferenceCount());
	}

	addChild(potDrawNode);
}

void setSegmentDrawNode(cocos2d::Vec2 startPoint, cocos2d::Vec2 stopPoint)
{

}

cocos2d::TTFConfig WordCard::getTTFConfig(CardType type)
{
	TTFConfig ttfConfig;
	switch (type)
	{
	case WordCard::CardType_EN:
	{
		ttfConfig = TTFConfig("fonts/Schwarzwald.ttf", 32, GlyphCollection::NEHE);
	}
	break;
	case WordCard::CardType_ZH:
	{
		ttfConfig = TTFConfig("fonts/FontKaTong.ttf", 32, GlyphCollection::NEHE);	
	}
	break;
	default:
		break;
	}

	return ttfConfig;
}
