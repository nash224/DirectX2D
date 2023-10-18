#include "PreCompile.h"
#include "Dian.h"

Dian::Dian() 
{
}

Dian::~Dian() 
{
}


void Dian::Start()
{
	StaticEntity::Start();
}

void Dian::Update(float _Delta)
{
	StaticEntity::Update(_Delta);
}

void Dian::Release()
{
	StaticEntity::Release();
}

void Dian::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Dian::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Dian::Init()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 60.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
}

void Dian::RendererSetting()
{
	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Object);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle", "Dian_idle.png", 0.15f, 3, 7, true);
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({0.0f, m_RendererBias });
	m_Body->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Shadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Shadow->Transform.SetLocalPosition({ 0.0f, m_RendererBias });
	m_Shadow->SetSprite("Dian_idle.png", 0);
}