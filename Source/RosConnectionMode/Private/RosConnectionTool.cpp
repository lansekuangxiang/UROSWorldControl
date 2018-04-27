#include "RosConnectionTool.h"
#include "UObject/ConstructorHelpers.h"

URosConnectionTool::URosConnectionTool(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void URosConnectionTool::ConnectToRosBridge()
{
	World = GEditor->GetEditorWorldContext().World();

	if (Controller) {
		Controller->DisconnectFromROSBridge();
	}
	Controller = new ROSWorldControlManager(World, ServerAdress, ServerPort, Namespace);

	// Setup Callbacks
	FWebsocketInfoCallBack ErrorCallback;
	ErrorCallback.AddUObject(this, &URosConnectionTool::ConnectionErrorCallback);

	FWebsocketInfoCallBack ConnectedCallback;
	ConnectedCallback.AddUObject(this, &URosConnectionTool::ConnectedCallback);

	Controller->ConnectToROSBridge(ErrorCallback, ConnectedCallback);
}


void URosConnectionTool::ClearMap()
{
	for (auto Element : Controller->IdToActorMap)
	{
		Element.Value->Destroy();
	}
	Controller->IdToActorMap.Empty();
}

void URosConnectionTool::SetRelations()
{
	if (Controller->IdToActorMap.Num() > 2) {

		AActor* Parent = nullptr;
		AActor* Child = nullptr;
		int i = 0;
		for (auto Entry : Controller->IdToActorMap) {
			switch (i)
			{
			case 0:
				Parent = Entry.Value;
				break;
			case 1:
				Child = Entry.Value;
				break;
			}
			i++;
		}

		if (Child) {
			Child->AttachRootComponentToActor(Parent);
		}

	}
}

void URosConnectionTool::ConnectionErrorCallback() {
	ConnectionStatus = TEXT("Not connected.");
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Connection to RosBridge lost.")));

}

void URosConnectionTool::ConnectedCallback() {
	ConnectionStatus = TEXT("Connected to Rosbridge.");
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("You are now connected to RosBridge.")));

}