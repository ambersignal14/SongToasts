#include "Toast.hpp"

bool Toast::init(std::string name, std::string artist) {
    if (!CCNode::init()) return false;

    float width = 220.f;
    float height = 48.f;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto bg = CCScale9Sprite::create("GJ_square01.png");
    bg->setContentSize({ width, height });
    this->addChild(bg);

    float paddingLeft = 12.f;
    float paddingRight = 12.f;
    float paddingDown = 12.f;
    float maxTextWidth = width - paddingLeft - paddingRight;

    auto fitLabel = [maxTextWidth](CCLabelBMFont* label, float targetScale) {
        label->setScale(targetScale);
        float currentWidth = label->getContentWidth() * targetScale;
        if (currentWidth > maxTextWidth) {
            float newScale = targetScale * (maxTextWidth / currentWidth);
            label->setScale(newScale);
        }
    };

    auto nameLabel = CCLabelBMFont::create(name.c_str(), "bigFont.fnt");
    nameLabel->setAnchorPoint({ 0.f, 0.5f });
    fitLabel(nameLabel, 0.45f);
    nameLabel->setPosition({ paddingLeft, (height * 0.68f) });
    bg->addChild(nameLabel);

    std::string artistText = artist.empty() ? "Unknown Artist" : fmt::format("By {}", artist);
    auto artistLabel = CCLabelBMFont::create(artistText.c_str(), "goldFont.fnt");
    artistLabel->setAnchorPoint({ 0.f, 0.5f });
    fitLabel(artistLabel, 0.35f);
    artistLabel->setPosition({ paddingLeft, (height * 0.32f) });
    bg->addChild(artistLabel);

    float initialX = -(width / 2.f);
    float initialY = winSize.height - (height / 2.f) - paddingDown;
    this->setPosition({ initialX, initialY });

    return true;
}

Toast* Toast::create(std::string name, std::string artist) {
    Toast* ret = new Toast();
    if (ret && ret->init(name, artist)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

void Toast::animate() {
    float width = 220.f;
    float padding = 5.f;

    float slideDistance = width + padding;

    auto firstDelay = CCDelayTime::create(0.5f);
    auto moveIn = CCMoveBy::create(0.5f, { slideDistance, 0.f });
    auto secondDelay = CCDelayTime::create(2.0f);
    auto moveOut = CCMoveBy::create(0.5f, { -slideDistance, 0.f });
    auto remove = CCRemoveSelf::create();

    auto sequence = CCSequence::create(firstDelay, moveIn, secondDelay, moveOut, remove, nullptr);
    this->runAction(sequence);
}