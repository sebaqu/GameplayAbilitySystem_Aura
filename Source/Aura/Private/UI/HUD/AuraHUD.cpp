// Copyright Sebaqu Games

#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayAuraWidgetController.h"

UOverlayAuraWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayAuraWidgetController == nullptr)
	{
		OverlayAuraWidgetController = NewObject<UOverlayAuraWidgetController>(this, OverlayAuraWidgetControllerClass);
		OverlayAuraWidgetController->SetWidgetControllerParams(WCParams);
		OverlayAuraWidgetController->BindCallbacksToDependencies();
		return OverlayAuraWidgetController;
	}
	return OverlayAuraWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unitialized, please set BP_AuraHUD"));
	checkf(OverlayAuraWidgetControllerClass, TEXT("Overlay Widget Controller class unitialized, please set BP_AuraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayAuraWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}