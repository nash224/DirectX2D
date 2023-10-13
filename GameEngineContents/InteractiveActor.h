#pragma once



enum class EINTERACTION_TYPE
{
	Near,
	Far,
	None,
};

enum class EINTERACTION_BUTTONTYPE
{
	Gathering,
	Gear,
	None,
};

// 설명 :
class InteractiveActor : public GameEngineActor
{
	friend class UI_InteractiveMark;
	friend class BackDrop;
	friend class Ellie;

public:
	// constrcuter destructer
	InteractiveActor();
	~InteractiveActor();

	// delete Function
	InteractiveActor(const InteractiveActor& _Other) = delete;
	InteractiveActor(InteractiveActor&& _Other) noexcept = delete;
	InteractiveActor& operator=(const InteractiveActor& _Other) = delete;
	InteractiveActor& operator=(InteractiveActor&& _Other) noexcept = delete;

	void CreateAndSetCollision(ECOLLISION _Order, const float4& _Scale, const float4& _Position, ColType _Type);
	void SetInteractionButtonType(const EINTERACTION_BUTTONTYPE _Type);
	void SetInteractionType(const EINTERACTION_TYPE _Type);
	EINTERACTION_TYPE GetInteractionType() const;
	EINTERACTION_BUTTONTYPE GetInteractionButtonType() const;
	ECOLLECTION_METHOD GetCollectionMethod() const;
	
	void InitialDepth(const float4& _Position);

	void ReachThis()
	{
		IsReach = true;
	}

	void SetInteractivePositionAndRange(const float4& _InteractivePosition, float _Range);

	float4 GetInteractiveLocalPositon() const
	{
		float4 ReturnValue = m_InteractiveLocalPosition + Transform.GetLocalPosition();
		return ReturnValue;
	}

	float GetInteractiveRange() const
	{
		return m_InteractiveRange;
	}

	virtual void GetCaught() {}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	std::shared_ptr<GameEngineCollision> m_InteractiveCol = nullptr;
	EINTERACTION_BUTTONTYPE m_InteractionButtonType = EINTERACTION_BUTTONTYPE::None;				// UI 상호작용시 버튼 타입
	EINTERACTION_TYPE m_InteractionType = EINTERACTION_TYPE::None;									// 상호작용시 접근 유무
	ECOLLECTION_METHOD m_CollectionMethod = ECOLLECTION_METHOD::None;								// 수집 모션타입
	ETOOLTYPE m_CollectionTool = ETOOLTYPE::None;													// 채집 도구 타입
	float4 m_InteractiveLocalPosition = float4::ZERO;												//
	float m_InteractiveRange = 1.0f;


	
	bool IsEnalbeActive = false;

private:
	bool IsReach = false;
};

