#include "PreCompile.h"
#include "UI_Alert_Tutorial.h"

UI_Alert_Tutorial::UI_Alert_Tutorial() 
{
}

UI_Alert_Tutorial::~UI_Alert_Tutorial() 
{
}


void UI_Alert_Tutorial::Update(float _Delta)
{
	UI_Alert_Base::Update(_Delta);
}

void UI_Alert_Tutorial::Release()
{
	AlertInfo.ZoneFrame = nullptr;
	AlertInfo.Black = nullptr;
	AlertInfo.Font = nullptr;
}

void UI_Alert_Tutorial::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

float UI_Alert_Tutorial::AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName)
{
	const std::shared_ptr<UI_Alert_Tutorial>& Alert = _Level->CreateActor<UI_Alert_Tutorial>(EUPDATEORDER::Objects);
	Alert->Init(_LevelName);

	return 0.0f;
}

void UI_Alert_Tutorial::Init(std::string_view _LevelName)
{
	const float4& Position = float4(0.0f, 200.0f);
	Transform.SetLocalPosition(Position);

	RendererSetting(_LevelName);
	UI_Alert_Base::FSMSetting();
}

void UI_Alert_Tutorial::RendererSetting(std::string_view _LevelName)
{
	if (nullptr == GameEngineSprite::Find("ZoneName_Animation.png"))
	{
		GameEngineSprite::CreateCut("ZoneName_Animation.png", 7, 6);
	}

	const int RenderOrder = 0;

	const float ShadowDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Shadow);
	const float BaseDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Base);
	const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Font);

	const float4& fShadowDepth = float4(0.0f, 0.0f, ShadowDepth);
	const float4& fZoneFrameDepth = float4(0.0f, 0.0f, BaseDepth);
	const float4& fFontDepth = float4(0.0f, 0.0f, FontDepth);


	{
		AlertInfo.Black = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertInfo.Black->Transform.SetLocalPosition(fShadowDepth);
		AlertInfo.Black->GetColorData().MulColor = float4::ZERO;
		AlertInfo.Black->SetSprite("Default_Particle.png");
		AlertInfo.Black->GetImageTransform().SetLocalScale(float4(300.0f, 200.0f));
	}

	{
		static constexpr const float ZoneFrame_Animation_Inter = 0.045f;

		AlertInfo.ZoneFrame = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertInfo.ZoneFrame->Transform.SetLocalPosition(fZoneFrameDepth);
		AlertInfo.ZoneFrame->AutoSpriteSizeOn();
		AlertInfo.ZoneFrame->CreateAnimation("Alert", "ZoneName_Animation.png", ZoneFrame_Animation_Inter, 0, 36, false);
		AlertInfo.ZoneFrame->ChangeAnimation("Alert");
	}

	{
		static constexpr const float FontScale = 21.0f;

		AlertInfo.Font = CreateComponent<GameEngineUIRenderer>(RenderOrder);
		AlertInfo.Font->Transform.SetLocalPosition(fFontDepth);
		AlertInfo.Font->SetText(GlobalValue::Font_Sandoll, _LevelName.data(), FontScale, InitialFontColor, FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void UI_Alert_Tutorial::StartFadeIn(GameEngineState* _Parent)
{
	if (nullptr == AlertInfo.Font)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == AlertInfo.Black)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	ChangeFontAlpha(AlertInfo.Font, 0.0f);
	ChangeMulColor(AlertInfo.Black, 0.0f);
}


void UI_Alert_Tutorial::UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = _Parent->GetStateTime() / AlertInfo.Fade_Change_Time;

	ChangeFontAlpha(AlertInfo.Font, MulColorValue);
	ChangeMulColor(AlertInfo.Black, MulColorValue);

	if (_Parent->GetStateTime() > AlertInfo.Fade_Change_Time)
	{
		ChangeFontAlpha(AlertInfo.Font, 1.0f);
		ChangeMulColor(AlertInfo.Black, 1.0f);
		ChangeState(EENTERSTATE::Stay);
	}
}

void UI_Alert_Tutorial::UpdateStay(float _DeltaTime, GameEngineState* _Parent)
{
	static constexpr const float WaitTime = 1.6f;

	if (_Parent->GetStateTime() > WaitTime)
	{
		ChangeState(EENTERSTATE::FadeOut);
	}
}

void UI_Alert_Tutorial::UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent)
{
	float MulColorValue = 1.0f - _Parent->GetStateTime() / AlertInfo.Fade_Change_Time;

	ChangeFontAlpha(AlertInfo.Font, MulColorValue);
	ChangeMulColor(AlertInfo.ZoneFrame, MulColorValue);
	ChangeMulColor(AlertInfo.Black, MulColorValue);

	if (_Parent->GetStateTime() > AlertInfo.Fade_Change_Time)
	{
		ChangeFontAlpha(AlertInfo.Font, 0.0f);
		ChangeMulColor(AlertInfo.ZoneFrame, 0.0f);
		ChangeMulColor(AlertInfo.Black, 0.0f);
		Death();
	}
}