#pragma once
#include "ContentsLevel.h"

#define OneQuater 90.0f

// ���� :
class MapEditorLevel : public ContentsLevel
{
public:
	std::shared_ptr<class MouseManager> m_MouseManager = nullptr;
	class RendererActor* SelectActor = nullptr;


public:
	// constrcuter destructer
	MapEditorLevel();
	~MapEditorLevel();

	// delete Function
	MapEditorLevel(const MapEditorLevel& _Other) = delete;
	MapEditorLevel(MapEditorLevel&& _Other) noexcept = delete;
	MapEditorLevel& operator=(const MapEditorLevel& _Other) = delete;
	MapEditorLevel& operator=(MapEditorLevel&& _Other) noexcept = delete;

	int _SelectDepth = 0;
	float _RendererHeight = 0.0f;

	std::string _SelcetSprite = "";

	float4 m_BaseScale = float4::ZERO;
	float4 m_SaveLocation = float4::ZERO;


	std::shared_ptr<GameEngineActor> m_MapBaseActor;
	std::shared_ptr<GameEngineSpriteRenderer> m_MapBaseRenderer;


	float CalculateDepth(const float _PositionY) const;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateMapEditor(float _Delta);
	bool ClickCreateActor();
	bool ClickForSelectActor();
	bool MoveSelectActor();
	bool RotateSelectActor();
	bool EraseSelectActor();
	bool PlaceThis();



};

